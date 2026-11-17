
#include <WiFi.h>

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  delay(1000);

  Serial.println("ESP32-C3 WiFi Scanner");
}

void loop() {
  Serial.println("Scanning...");

  int n = WiFi.scanNetworks();

  Serial.println("Scan finished");

  if (n == 0) {
    Serial.println("No networks found");
  }
  else {
    Serial.print(n);
    Serial.println(" networks found");

    for (int i = 0; i < n; i++) {

      Serial.print("SSID: ");
      Serial.println(WiFi.SSID(i));

      Serial.print("Signal: ");
      Serial.print(WiFi.RSSI(i));
      Serial.println(" dBm");

      Serial.print("Channel: ");
      Serial.println(WiFi.channel(i));

      Serial.println("----------------");
    }
  }

  WiFi.scanDelete();

  delay(5000);
}
