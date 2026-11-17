#define LED_PIN 4

hw_timer_t *Timer0_Cfg = NULL;

void ARDUINO_ISR_ATTR Timer0_ISR()
{
digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup()
{
pinMode(LED_PIN, OUTPUT);

Timer0_Cfg = timerBegin(1000000);

timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR);

timerAlarm(Timer0_Cfg, 500000, true, 0);
}

void loop()
{
}
