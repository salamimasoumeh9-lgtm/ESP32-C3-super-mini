#include <WiFi.h>

const char* ssid = "iPhone";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  WiFi.setHostname("ESP32-C3-Masoumeh");

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());
}

void loop() {
}
