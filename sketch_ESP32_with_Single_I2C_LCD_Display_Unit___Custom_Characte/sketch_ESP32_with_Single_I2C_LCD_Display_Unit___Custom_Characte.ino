#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heart[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.createChar(0, heart);

  lcd.setCursor(0, 0);
  lcd.print("Custom Character:");

  lcd.setCursor(0, 1);
  lcd.write(byte(0));
}

void loop() {
}
