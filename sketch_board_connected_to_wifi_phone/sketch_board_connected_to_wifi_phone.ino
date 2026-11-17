
#include <WiFi.h>

const char* ssid = "iPhone";
const char* password = "masou5";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");

  int counter = 0;

  while (WiFi.status() != WL_CONNECTED && counter < 40) {
    delay(500);
    Serial.print(".");
    counter++;
  }

  if (WiFi.status() == WL_CONNECTED) {

    Serial.println("\nConnected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("Signal: ");
    Serial.println(WiFi.RSSI());

  } else {
    Serial.println("\nConnection Failed!");
  }
}

void loop() {
}
