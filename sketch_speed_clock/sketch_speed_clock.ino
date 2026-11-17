void setup() {
  Serial.begin(115200);
}

void loop() {

  setCpuFrequencyMhz(240);
  Serial.println(getCpuFrequencyMhz());
  delay(1000);

  setCpuFrequencyMhz(80);
  Serial.println(getCpuFrequencyMhz());
  delay(1000);

  setCpuFrequencyMhz(160);
  Serial.println(getCpuFrequencyMhz());
  delay(1000);
}
