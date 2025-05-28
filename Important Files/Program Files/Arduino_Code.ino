// First, install the Adafruit SSD1306 library.
// For wiring go to Main>Important Files> ( you will see two option, 1st is in PNG and the other is in.txt , so choose which is better for you!
// Good Luck!!!!


#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 2;  // Mode switch button pin
int currentMode = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Halt if OLED not found
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Assistant Ready");
  display.display();
  delay(2000);

  sendModeToPython();
}

void loop() {
  static int lastButtonState = HIGH;
  int buttonState = digitalRead(buttonPin);

  // Detect button press (falling edge)
  if (buttonState == LOW && lastButtonState == HIGH) {
    currentMode = (currentMode + 1) % 4;  // Cycle through 0 to 3
    sendModeToPython();
    delay(300);  // Debounce delay
  }
  lastButtonState = buttonState;

  // Read incoming serial from Python (short text to display)
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Mode: " + String(currentMode));
    display.println();
    display.println(line);
    display.display();
  }
}

void sendModeToPython() {
  Serial.print("MODE:");
  Serial.println(currentMode);
}
