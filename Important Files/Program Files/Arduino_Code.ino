// First, install the Adafruit SSD1306 library.
// For wiring go to Main>Important Files> ( you will see two option, 1st is in PNG and the other is in.txt , so choose which is better for you!
// Good Luck!!!!


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define BUTTON_PIN 2

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int mode = 0;
unsigned long lastBlink = 0;
bool eyesOpen = true;
String currentEmoji = "neutral";

void drawEyes(bool open) {
  display.clearDisplay();
  if (open) {
    display.fillCircle(40, 32, 10, WHITE);
    display.fillCircle(88, 32, 10, WHITE);
  } else {
    display.drawLine(30, 32, 50, 32, WHITE);
    display.drawLine(78, 32, 98, 32, WHITE);
  }
  display.display();
}

void drawEmoji(String emoji) {
  display.clearDisplay();
  if (emoji == "happy") {
    display.setCursor(10, 20);
    display.setTextSize(2);
    display.print(":)");
  } else if (emoji == "sad") {
    display.setCursor(10, 20);
    display.setTextSize(2);
    display.print(":(");
  } else {
    drawEyes(eyesOpen);
    return;
  }
  display.display();
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Booting...");
  display.display();
  delay(1000);
  drawEyes(true);
}

void loop() {
  static bool lastButtonState = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (lastButtonState == HIGH && buttonState == LOW) {
    mode = (mode + 1) % 4;
    Serial.print("MODE:");
    Serial.println(mode);
    delay(300);
  }
  lastButtonState = buttonState;

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.startsWith("EMOJI:")) {
      currentEmoji = input.substring(6);
      drawEmoji(currentEmoji);
    } else {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.println(input);
      display.display();
    }
  }

  // Eye blinking every 3s in neutral mode
  if (currentEmoji == "neutral" && mode == 0) {
    if (millis() - lastBlink > 3000) {
      eyesOpen = !eyesOpen;
      drawEyes(eyesOpen);
      lastBlink = millis();
    }
  }
}


