
#include <WiFi.h>
#include <esp_wifi.h>

void setup() {

  Serial.begin(115200);
  delay(2000);

  // فعال کردن وای فای
  WiFi.mode(WIFI_STA);

  // نمایش MAC قبلی
  Serial.println("Old MAC Address:");
  Serial.println(WiFi.macAddress());

  // تعریف MAC جدید
  uint8_t newMAC[] = {
    0x02, 0x11, 0x22,
    0x33, 0x44, 0x55
  };

  // تغییر MAC
  esp_err_t result = esp_wifi_set_mac(
    WIFI_IF_STA,
    newMAC
  );

  // بررسی نتیجه
  if (result == ESP_OK) {
    Serial.println("MAC Changed Successfully!");
  } else {
    Serial.println("MAC Change Failed!");
  }

  // نمایش MAC جدید
  Serial.println("New MAC Address:");
  Serial.println(WiFi.macAddress());
}

void loop() {
}
