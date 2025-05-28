// First, install the Adafruit SSD1306 library.
// For wiring go to Main>Important Files> ( you will see two option, 1st is in PNG and the other is in.txt , so choose which is better for you!
// Good Luck!!!!


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1
#define BUTTON_PIN 2

Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

int mode = 0;
unsigned long lastBlink = 0;
bool eyesOpen = true;
String lastLine = "";

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  showEyes();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(300);
    mode = (mode + 1) % 4;
    Serial.print("MODE:");
    Serial.println(mode);
    handleMode();
  }

  if (mode == 0 && millis() - lastBlink > 3000) {
    eyesOpen = !eyesOpen;
    showEyes();
    lastBlink = millis();
  }

  if (Serial.available()) {
    String incoming = Serial.readStringUntil('\n');
    lastLine = incoming;
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.setTextColor(SSD1306_WHITE);
    display.println(incoming);
    display.display();
    showEmoji(incoming);
  }
}

void handleMode() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);

  if (mode == 1) display.println("Fetching weather...");
  else if (mode == 2) display.println("Getting time...");
  else if (mode == 3) display.println("Playing music...");
  else showEyes();

  display.display();
}

void showEyes() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setCursor(30, 20);
  display.setTextColor(SSD1306_WHITE);
  if (eyesOpen)
    display.print("o o");
  else
    display.print("- -");
  display.display();
}

void showEmoji(String text) {
  if (text.indexOf("happy") >= 0) {
    display.setCursor(90, 50);
    display.print(":)");
  } else if (text.indexOf("sad") >= 0 || text.indexOf("error") >= 0) {
    display.setCursor(90, 50);
    display.print(":(");
  } else {
    display.setCursor(90, 50);
    display.print(":|");
  }
  display.display();
}

