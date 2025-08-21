#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String inputString = "";
bool stringComplete = false;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("❌ OLED gagal dijalankan."));
    while (true);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  if (stringComplete) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    int y = 0;
    String line = "";
    for (unsigned int i = 0; i < inputString.length(); i++) {
      char c = inputString[i];
      if (c == '\n') {
        display.setCursor(0, y);
        display.print(line);
        line = "";
        y += 10;
      } else {
        line += c;
      }
    }
    if (line.length() > 0) {
      display.setCursor(0, y);
      display.print(line);
    }

    display.display();
    stringComplete = false;
    inputString = "";
  }
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    delay(2);
  }

  if (inputString.length() > 0) {
    stringComplete = true;
  }
}

