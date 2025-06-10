import serial
import time
import threading
import pygame
import pyttsx3
import queue
from vosk import Model, KaldiRecognizer
import pyaudio
import json

# ----------------- CONFIGURATION -----------------

SERIAL_PORT = "/dev/ttyUSB0"  # Adjust this if different
SERIAL_BAUDRATE = 9600
MUSIC_FILE = "song1.mp3"
WAKE_WORD = "hi buddy"

# ----------------- INITIALIZATION -----------------

print("[INFO] Initializing...")
ser = serial.Serial(SERIAL_PORT, SERIAL_BAUDRATE, timeout=1)
engine = pyttsx3.init()
engine.setProperty('rate', 180)

pygame.mixer.init()

model = Model("vosk-model-small-en-us-0.15")
recognizer = KaldiRecognizer(model, 16000)
recognizer.SetWords(True)

p = pyaudio.PyAudio()
stream = p.open(format=pyaudio.paInt16, channels=1, rate=16000,
                input=True, frames_per_buffer=8000)
stream.start_stream()

command_queue = queue.Queue()
current_mode = -1

# ----------------- FUNCTIONS -----------------

def speak(text):
    print("Assistant:", text)
    engine.say(text)
    engine.runAndWait()

def send_to_arduino(text):
    short_text = text[:30].replace('\n', ' ')
    ser.write((short_text + '\n').encode())

def send_emoji(status):
    ser.write((f"EMOJI:{status}\n").encode())

def play_music():
    pygame.mixer.music.load(MUSIC_FILE)
    pygame.mixer.music.play()

def stop_music():
    pygame.mixer.music.stop()

def handle_mode_change(mode):
    global current_mode
    if mode == current_mode:
        return
    current_mode = mode
    if mode == 0:
        send_to_arduino("Eye animation mode")
        send_emoji("neutral")
        stop_music()
    elif mode == 1:
        send_to_arduino("Weather: clear & 25°C")  # Mocked
        send_emoji("happy")
        speak("The weather is clear and 25 degrees.")
        stop_music()
    elif mode == 2:
        current_time = time.strftime("Time is %I:%M %p")
        send_to_arduino(current_time)
        send_emoji("happy")
        speak(current_time)
        stop_music()
    elif mode == 3:
        send_to_arduino("Playing music")
        send_emoji("happy")
        speak("Playing music now.")
        play_music()

def serial_listener():
    while True:
        try:
            if ser.in_waiting > 0:
                line = ser.readline().decode().strip()
                if line.startswith("MODE:"):
                    try:
                        mode = int(line.split(":")[1])
                        handle_mode_change(mode)
                    except:
                        pass
        except Exception as e:
            print("Serial error:", e)

def command_handler():
    while True:
        command = command_queue.get()
        command = command.lower()
        if "play music" in command:
            handle_mode_change(3)
        elif "stop music" in command:
            stop_music()
            send_emoji("neutral")
            speak("Music stopped.")
        elif "what time" in command:
            handle_mode_change(2)
        elif "weather" in command:
            handle_mode_change(1)
        else:
            speak("Sorry, I didn’t understand.")
            send_emoji("sad")

def wake_word_listener():
    print("[INFO] Listening for wake word: 'Hi Buddy'")
    while True:
        data = stream.read(4000, exception_on_overflow=False)
        if recognizer.AcceptWaveform(data):
            result = json.loads(recognizer.Result())
            text = result.get("text", "")
            if WAKE_WORD in text:
                print("[WAKE WORD DETECTED]")
                speak("Hello, how can I help you?")
                listen_for_command()

def listen_for_command():
    timeout = time.time() + 7
    while time.time() < timeout:
        data = stream.read(4000, exception_on_overflow=False)
        if recognizer.AcceptWaveform(data):
            result = json.loads(recognizer.Result())
            text = result.get("text", "")
            if text:
                print("[COMMAND]", text)
                command_queue.put(text)
                return
    speak("I didn't catch that.")

# ----------------- MAIN -----------------

if __name__ == "__main__":
    print("[INFO] Starting Voice Assistant...")
    speak("Hello, I am your personal offline assistant.")

    threading.Thread(target=serial_listener, daemon=True).start()
    threading.Thread(target=command_handler, daemon=True).start()
    wake_word_listener()
