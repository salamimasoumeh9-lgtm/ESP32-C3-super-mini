
#include <WiFi.h>

// مشخصات وای فای
const char* ssid = "iPhone";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  // اتصال به وای فای با IP خودکار
  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // نمایش MAC Address
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
}
