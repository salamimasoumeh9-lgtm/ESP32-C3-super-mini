
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// LED pin
#define LED_PIN 4

// BLE UUID
#define SERVICE_UUID        "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"

class MyCallbacks : public BLECharacteristicCallbacks {

  void onWrite(BLECharacteristic *pCharacteristic) override {

    String receivedText = pCharacteristic->getValue().c_str();

    receivedText.trim();
    receivedText.toUpperCase();

    Serial.print("Received: ");
    Serial.println(receivedText);

    if (receivedText == "ON") {

      digitalWrite(LED_PIN, HIGH);

      Serial.println("LED IS ON");

    }

    else if (receivedText == "OFF") {

      digitalWrite(LED_PIN, LOW);

      Serial.println("LED IS OFF");

    }

    else {

      Serial.println("Invalid Command! Send ON or OFF");

    }
  }
};

void setup() {

  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  // Start BLE
  BLEDevice::init("ESP32-C3");

  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService =
    pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic =
    pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_WRITE
    );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  BLEAdvertising *pAdvertising =
    BLEDevice::getAdvertising();

  pAdvertising->addServiceUUID(SERVICE_UUID);

  pAdvertising->start();

  Serial.println("BLE Started!");
  Serial.println("Waiting for Bluetooth Commands...");
}

void loop() {

  delay(100);

}
