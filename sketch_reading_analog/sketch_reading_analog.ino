#define LED_PIN 8
#define INT_PIN 4

volatile unsigned long interruptCount = 0;

unsigned long lastCount = 0;
bool ledState = false;

void IRAM_ATTR myISR() {
  interruptCount++;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(INT_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  attachInterrupt(
    digitalPinToInterrupt(INT_PIN),
    myISR,
    FALLING
  );

  Serial.println("External Interrupt Test Started!");
}

void loop() {

  if (interruptCount != lastCount) {

    lastCount = interruptCount;

    ledState = !ledState;

    digitalWrite(LED_PIN, ledState);

    Serial.print("Interrupt Detected! Count = ");
    Serial.println(lastCount);
  }
}
