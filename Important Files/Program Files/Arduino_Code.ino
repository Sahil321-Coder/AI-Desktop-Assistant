// First, install the Adafruit SSD1306 library.
// For wiring go to Main>Important Files> ( you will see two option, 1st is in PNG and the other is in.txt , so choose which is better for you!
// Good Luck!!!!


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 2;
int mode = 0;
bool eyesOpen = true;
unsigned long lastBlink = 0;
bool inMusicMode = false;
int progress = 0;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  drawEyesOpen();
  display.display();
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    delay(200);
    mode = (mode + 1) % 4;
    Serial.print("MODE:");
    Serial.println(mode);
    handleMode(mode);
  }

  if (mode == 0 && millis() - lastBlink > 3000) {
    eyesOpen = !eyesOpen;
    eyesOpen ? drawEyesOpen() : drawEyesClosed();
    display.display();
    lastBlink = millis();
  }

  if (inMusicMode) {
    drawProgressBar();
    delay(500);
  }

  if (Serial.available()) {
    String msg = Serial.readStringUntil('\n');
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);

    if (msg.startsWith("😊") || msg.startsWith("😢")) {
      display.setCursor(0, 20);
      display.setTextSize(2);
      display.print(msg);
    } else if (msg.startsWith("☀️") || msg.startsWith("💨") || msg.startsWith("🌧️")) {
      display.setCursor(0, 20);
      display.setTextSize(2);
      display.print(msg);
    } else {
      display.print(msg);
    }
    display.display();
  }
}

void handleMode(int m) {
  inMusicMode = (m == 3);
  display.clearDisplay();
  if (m == 0) drawEyesOpen();
  else if (m == 1) display.print("Getting weather...");
  else if (m == 2) display.print("Getting time...");
  else if (m == 3) {
    display.print("Music Playing...");
    progress = 0;
  }
  display.display();
}

void drawEyesOpen() {
  display.clearDisplay();
  display.fillCircle(32, 32, 10, WHITE);
  display.fillCircle(96, 32, 10, WHITE);
}

void drawEyesClosed() {
  display.clearDisplay();
  display.drawLine(22, 32, 42, 32, WHITE);
  display.drawLine(86, 32, 106, 32, WHITE);
}

void drawProgressBar() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Music Playing...");
  int width = map(progress, 0, 100, 0, 128);
  display.drawRect(0, 20, 128, 10, WHITE);
  display.fillRect(0, 20, width, 10, WHITE);
  display.display();
  progress += 5;
  if (progress > 100) progress = 0;
}

