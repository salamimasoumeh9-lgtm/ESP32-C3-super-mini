
#include <WiFi.h>

// مشخصات وای فای
const char* ssid = "iPhone";
const char* password = "12345678";

// تنظیمات IP ثابت
IPAddress local_IP(192, 168, 1, 108);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  // تنظیم IP ثابت
  if (!WiFi.config(local_IP, gateway, subnet,
                   primaryDNS, secondaryDNS)) {
    Serial.println("IP Config Failed!");
    return;
  }

  // اتصال به مودم
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

  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
}
