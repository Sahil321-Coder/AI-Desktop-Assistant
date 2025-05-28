import serial
import threading
import speech_recognition as sr
import pyttsx3
import requests
import pygame
import time

# ----------------- CONFIGURATION -----------------

OPENROUTER_API_KEY = "<Your OPENROUTER API Key>"  # Your OpenRouter API key here
SERIAL_PORT = "COM7"  # Change to your Arduino COM port
SERIAL_BAUDRATE = 9600
CITY = "Nashik"
COUNTRY = "IN"
MUSIC_FILE = "song1.mp3"  # Your music file path

# ----------------- INITIALIZATION -----------------

pygame.mixer.init()
ser = serial.Serial(SERIAL_PORT, SERIAL_BAUDRATE, timeout=1)
engine = pyttsx3.init()
engine.setProperty('rate', 180)
recognizer = sr.Recognizer()
mic = sr.Microphone()
current_mode = -1


# ----------------- FUNCTIONS -----------------

def send_to_arduino(text):
    short_text = text[:30].replace('\n', ' ')  # Limit to 30 chars
    ser.write((short_text + '\n').encode())

def send_emoji(status):
    # Sends a command to Arduino to display emoji
    # Status can be "happy", "sad", "neutral"
    ser.write((f"EMOJI:{status}\n").encode())

def call_openrouter_api(prompt):
    url = "https://openrouter.ai/api/v1/chat/completions"
    headers = {
        "Authorization": f"Bearer {OPENROUTER_API_KEY}",
        "Content-Type": "application/json"
    }
    data = {
        "model": "gpt-4o-mini",
        "messages": [{"role": "user", "content": prompt}],
        "temperature": 0.7,
        "max_tokens": 150,
    }
    try:
        response = requests.post(url, headers=headers, json=data)
        response.raise_for_status()
        result = response.json()
        return result['choices'][0]['message']['content'].strip()
    except Exception as e:
        print("OpenRouter API error:", e)
        return "Sorry, API error."

def play_music():
    pygame.mixer.music.load(MUSIC_FILE)
    pygame.mixer.music.play()

def stop_music():
    pygame.mixer.music.stop()

def get_weather():
    prompt = f"Provide a brief current weather update for {CITY}, {COUNTRY}."
    return call_openrouter_api(prompt)

def get_time():
    prompt = f"Tell me the current local time in {CITY}, {COUNTRY}."
    return call_openrouter_api(prompt)

def handle_mode_change(mode):
    global current_mode
    if mode == current_mode:
        return  # no change
    current_mode = mode
    if mode == 0:
        send_to_arduino("Eye animation mode")
        send_emoji("neutral")
        stop_music()
    elif mode == 1:
        weather = get_weather()
        send_to_arduino(weather)
        send_emoji("happy")
        engine.say(weather)
        engine.runAndWait()
        stop_music()
    elif mode == 2:
        local_time = get_time()
        send_to_arduino(local_time)
        send_emoji("happy")
        engine.say(local_time)
        engine.runAndWait()
        stop_music()
    elif mode == 3:
        send_to_arduino("Playing music")
        send_emoji("happy")
        engine.say("Playing music now")
        engine.runAndWait()
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
            print("Serial listener error:", e)

def listen_and_respond():
    while True:
        try:
            with mic as source:
                recognizer.adjust_for_ambient_noise(source, duration=0.3)
                print("Listening for 10 seconds...")
                audio = recognizer.listen(source, timeout=10, phrase_time_limit=10)

            query = recognizer.recognize_google(audio)
            print("You said:", query)

            # Voice command to play music
            if "play music" in query.lower():
                handle_mode_change(3)
                continue

            # Stop music if playing and new query
            if current_mode == 3 and pygame.mixer.music.get_busy():
                stop_music()

            answer = call_openrouter_api(query)
            print("AI response:", answer)

            if answer and "sorry" not in answer.lower():
                engine.say(answer)
                engine.runAndWait()
                send_to_arduino(answer)
                send_emoji("happy")
            else:
                engine.say("Sorry, I did not get that.")
                engine.runAndWait()
                send_emoji("sad")

        except sr.WaitTimeoutError:
            continue
        except sr.UnknownValueError:
            print("Could not understand audio.")
            continue
        except Exception as e:
            print("Error in listen_and_respond:", e)

# ----------------- MAIN -----------------

if __name__ == "__main__":
    print("Starting Voice Assistant...")
    greeting = "Hello, I am your personal desktop assistant made by Sahil."
    print(greeting)
    engine.say(greeting)
    engine.runAndWait()

    threading.Thread(target=serial_listener, daemon=True).start()
    listen_and_respond()
