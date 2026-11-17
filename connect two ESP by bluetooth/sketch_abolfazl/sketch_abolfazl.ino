
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEClient.h>

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define RX_UUID      "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEAdvertisedDevice *targetDevice;
BLERemoteCharacteristic *remoteChar;

bool found = false;
bool connected = false;

class ScanCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice d) {
    if (d.haveServiceUUID() &&
        d.isAdvertisingService(BLEUUID(SERVICE_UUID))) {

      Serial.println("Server Found!");

      targetDevice = new BLEAdvertisedDevice(d);
      found = true;

      BLEDevice::getScan()->stop();
    }
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32C3_CLIENT");

  BLEScan *scan = BLEDevice::getScan();
  scan->setAdvertisedDeviceCallbacks(new ScanCallbacks());
  scan->setActiveScan(true);

  Serial.println("Scanning...");
  scan->start(5, false);
}

void loop() {
  if (found && !connected) {
    BLEClient *client = BLEDevice::createClient();

    Serial.println("Connecting...");
    if (client->connect(targetDevice)) {
      Serial.println("Connected!");

      BLERemoteService *service =
        client->getService(BLEUUID(SERVICE_UUID));

      if (service) {
        remoteChar =
          service->getCharacteristic(BLEUUID(RX_UUID));

        if (remoteChar) {
          connected = true;
          Serial.println("Ready to Send");
        }
      }
    }

    found = false;
  }

  if (connected && remoteChar) {
    String msg = "Hello from C3 Client";

    remoteChar->writeValue(
      (uint8_t*)msg.c_str(),
      msg.length(),
      true
    );

    Serial.println("Sent: " + msg);

    delay(2000);
  }
}
