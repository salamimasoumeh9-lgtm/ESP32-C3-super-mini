
#include <WiFi.h>

const char* ssid = "iPhone";
const char* password = "12345678";

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected!");

}

void loop() {

  // خواندن قدرت سیگنال
  int rssi = WiFi.RSSI();

  Serial.print("WiFi Signal: ");
  Serial.print(rssi);
  Serial.println(" dBm");

  delay(1000);
}
