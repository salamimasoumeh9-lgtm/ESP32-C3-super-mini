
#include <Wire.h>
#include <MS5611.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

MS5611 sensor(0x77);

BLECharacteristic *temperatureCharacteristic;
bool connected = false;

#define SERVICE_UUID "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "abcd1234-1234-1234-1234-123456789abc"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *server) {
    connected = true;
  }

  void onDisconnect(BLEServer *server) {
    connected = false;
    BLEDevice::startAdvertising();
  }
};

void setup() {
  Serial.begin(115200);

  // راه اندازی I2C
  Wire.begin(8, 9);

  // راه اندازی سنسور
  if (!sensor.begin()) {
    Serial.println("Sensor not found!");
    while (1);
  }

  // راه اندازی BLE
  BLEDevice::init("ESP32C3-GY63");

  BLEServer *server = BLEDevice::createServer();
  server->setCallbacks(new MyServerCallbacks());

  BLEService *service = server->createService(SERVICE_UUID);

  temperatureCharacteristic = service->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_NOTIFY
  );

  temperatureCharacteristic->addDescriptor(new BLE2902());

  service->start();

  BLEAdvertising *advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->start();

  Serial.println("BLE Started!");
}

void loop() {

  sensor.read();

  float temperature = sensor.getTemperature();
  float pressure = sensor.getPressure();
  float altitude = sensor.getAltitude();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  // ارسال دما به گوشی
  char value[30];
  sprintf(value, "%.2f C", temperature);

  temperatureCharacteristic->setValue(value);

  if (connected) {
    temperatureCharacteristic->notify();
  }

  delay(1000);
}
