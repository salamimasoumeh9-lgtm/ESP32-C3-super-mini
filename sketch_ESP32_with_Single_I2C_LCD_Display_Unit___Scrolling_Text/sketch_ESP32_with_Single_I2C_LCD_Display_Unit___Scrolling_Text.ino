#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);

void setup() {
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("wellcome!");

  lcd.setCursor(0, 1);
  lcd.print("HI");
}

void loop() {
  // حرکت به چپ
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }

  // حرکت به راست
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayRight();
    delay(300);
  }
}
