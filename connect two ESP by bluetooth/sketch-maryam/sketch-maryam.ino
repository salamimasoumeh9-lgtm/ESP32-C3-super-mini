
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define RX_UUID      "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *c) {
    String value = c->getValue().c_str();

    Serial.print("Received: ");
    Serial.println(value);
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32C3_SERVER");

  BLEServer *server = BLEDevice::createServer();

  BLEService *service =
    server->createService(SERVICE_UUID);

  BLECharacteristic *rx =
    service->createCharacteristic(
      RX_UUID,
      BLECharacteristic::PROPERTY_WRITE
    );

  rx->setCallbacks(new MyCallbacks());

  service->start();

  BLEDevice::getAdvertising()->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();

  Serial.println("Server Ready");
}

void loop() {
  delay(1000);
}
