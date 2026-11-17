
#define POT_PIN 0

#define RX_PIN 20
#define TX_PIN 21

HardwareSerial MySerial(1);

void setup() {
  Serial.begin(115200);

  MySerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
}

void loop() {

  // خواندن مقدار پتانسیومتر
  int adcValue = analogRead(POT_PIN);

  // تبدیل مقدار ADC به ولتاژ
  float voltage = (adcValue * 3.3) / 4095.0;

  // شبیه سازی سنسور LM35
  // هر 10 میلی ولت برابر یک درجه سانتی گراد است
  float temperature = voltage * 100.0;

  // ارسال اطلاعات از طریق USB to TTL
  MySerial.print("ADC: ");
  MySerial.print(adcValue);

  MySerial.print(" | Voltage: ");
  MySerial.print(voltage, 3);

  MySerial.print(" V | Temperature: ");
  MySerial.print(temperature, 2);

  MySerial.println(" C");

  delay(1000);
}
