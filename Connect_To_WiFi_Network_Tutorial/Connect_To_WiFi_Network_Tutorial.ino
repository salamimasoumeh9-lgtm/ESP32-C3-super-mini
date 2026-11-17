
#include <WiFi.h>

// Enter your WiFi credentials
const char* ssid = "iPhone";
const char* password = "12345678";

void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("ESP32-C3 WiFi Connection");

  // Set WiFi mode to Station
  WiFi.mode(WIFI_STA);

  // Start connecting
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  unsigned long startTime = millis();

  // Wait up to 20 seconds
  while (WiFi.status() != WL_CONNECTED &&
         millis() - startTime < 20000) {

    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println();
    Serial.println("WiFi Connected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal Strength: ");
    Serial.println(WiFi.RSSI());

  } else {

    Serial.println();
    Serial.println("WiFi Connection Failed!");

  }
}

void loop() {

}
