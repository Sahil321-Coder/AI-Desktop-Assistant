#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define BUTTON_PIN 2

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastBlinkTime = 0;
int blinkInterval = 3000;
bool eyesOpen = true;

int mode = 0;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  drawEyes();
}

void loop() {
  // Handle button mode switching
  bool currentButtonState = digitalRead(BUTTON_PIN);
  if (lastButtonState == HIGH && currentButtonState == LOW && millis() - lastDebounceTime > 200) {
    mode = (mode + 1) % 4;
    lastDebounceTime = millis();
    handleModeChange();
  }
  lastButtonState = currentButtonState;

  // Eye blinking
  if (mode == 0 && millis() - lastBlinkTime > blinkInterval) {
    eyesOpen = !eyesOpen;
    eyesOpen ? drawEyes() : drawClosedEyes();
    lastBlinkTime = millis();
  }

  // Listen to Serial
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd.startsWith("weather:")) showWeather(cmd);
    else if (cmd.startsWith("time:")) showTime(cmd.substring(5));
    else if (cmd.startsWith("short:")) showShort(cmd.substring(6));
    else if (cmd == "music") drawMusic();
  }
}

void handleModeChange() {
  if (mode == 1) Serial.println("get_weather");
  else if (mode == 2) Serial.println("get_time");
  else if (mode == 3) Serial.println("play_music");
  else drawEyes();
}

void drawEyes() {
  display.clearDisplay();
  display.drawRect(20, 20, 24, 24, WHITE);
  display.drawRect(84, 20, 24, 24, WHITE);
  display.display();
}

void drawClosedEyes() {
  display.clearDisplay();
  display.drawLine(20, 32, 44, 32, WHITE);
  display.drawLine(84, 32, 108, 32, WHITE);
  display.display();
}

void drawMusic() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.println("Playing Music");
  display.display();
}

void showTime(String t) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.println("Time (Nashik):");
  display.setTextSize(2);
  display.setCursor(10, 40);
  display.println(t);
  display.display();
}

void showWeather(String data) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Weather:");
  display.setCursor(0, 20);
  display.println(data); // Ex: "Temp: 30C Wind: 12km/h"
  display.display();
}

void showShort(String ans) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println(ans);
  display.display();
}
