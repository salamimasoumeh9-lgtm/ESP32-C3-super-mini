
#include <WiFi.h>

void setup() {
  Serial.begin(115200);

  delay(2000);

  WiFi.mode(WIFI_STA);

  Serial.println("My ESP32-C3 MAC Address:");

  Serial.println(WiFi.macAddress());
}

void loop() {
}
