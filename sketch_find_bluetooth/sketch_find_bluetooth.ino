
#include <NimBLEDevice.h>

void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println("STEP 1: Starting BLE");

  NimBLEDevice::init("ESP32-C3");

  Serial.println("STEP 2: BLE Initialized");

  NimBLEServer *server =
      NimBLEDevice::createServer();

  Serial.println("STEP 3: Server Created");

  NimBLEAdvertising *advertising =
      NimBLEDevice::getAdvertising();

  Serial.println("STEP 4: Advertising Ready");

  advertising->setName("ESP32-C3");

  advertising->enableScanResponse(true);

  bool result = advertising->start();

  Serial.println("STEP 5: Advertising Start");

  if (result) {
    Serial.println("BLE ADVERTISING SUCCESS!");
  } else {
    Serial.println("BLE ADVERTISING FAILED!");
  }
}

void loop() {

  Serial.println("BLE RUNNING...");
  delay(2000);

}
