
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define LED_PIN 8
#define ADC_PIN 4

BLECharacteristic *pCharacteristic;

bool deviceConnected = false;

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "12345678-1234-1234-1234-123456789abd"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    BLEDevice::startAdvertising();
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String command = pCharacteristic->getValue().c_str();

    if (command == "ON") {
      digitalWrite(LED_PIN, HIGH);
    }

    if (command == "OFF") {
      digitalWrite(LED_PIN, LOW);
    }
  }
};

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(ADC_PIN, INPUT);

  BLEDevice::init("ESP32-C3");

  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService =
    pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();

  BLEDevice::startAdvertising();
}

void loop() {
  if (deviceConnected) {
    int adcValue = analogRead(ADC_PIN);

    char buffer[10];
    sprintf(buffer, "%d", adcValue);

    pCharacteristic->setValue(buffer);
    pCharacteristic->notify();

    Serial.println(adcValue);

    delay(100);
  }
}
