#include <LiquidCrystal.h>
// تعریف پایه‌های LCD
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
const int signalPin = 10;
unsigned long duration;
float frequency;
void setup() {
  lcd.begin(16, 2);
  pinMode(signalPin, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Frequency:");
  lcd.setCursor(0, 1);
  lcd.print("Hz");
}
void loop() {
  duration = pulseIn(signalPin, HIGH);
  if (duration > 0) {
    frequency = 1000000.0 / (2 * duration);
    lcd.setCursor(0, 1);
    lcd.print(frequency);
    lcd.print(" Hz   ");
  }
}
