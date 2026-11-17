
#include <EEPROM.h>

int led = 4;
int button = 10;

int ledState = 0;
int buttonState = 1;
int lastButton = 1;

void setup() {

  Serial.begin(115200);

  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  EEPROM.begin(1);

  // خواندن وضعیت قبلی LED
  ledState = EEPROM.read(0);

  if (ledState != 0 && ledState != 1) {
    ledState = 0;
  }

  digitalWrite(led, ledState);
}

void loop() {

  buttonState = digitalRead(button);

  // بررسی فشردن شستی
  if (buttonState == LOW && lastButton == HIGH) {

    ledState = !ledState;

    digitalWrite(led, ledState);

    // ذخیره وضعیت LED
    EEPROM.write(0, ledState);
    EEPROM.commit();

    delay(200);
  }

  lastButton = buttonState;
}
