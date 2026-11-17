
#include <LiquidCrystal.h>

// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

void setup() {

  lcd.begin(16, 2);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Hello World!");

  lcd.setCursor(0, 1);
  lcd.print("ESP32-C3");

}

void loop() {

}
