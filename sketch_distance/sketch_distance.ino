#include <Wire.h>
#include "Adafruit_VL53L1X.h"

#define SDA_PIN 6
#define SCL_PIN 7

#define IRQ_PIN -1
#define XSHUT_PIN -1

Adafruit_VL53L1X sensor = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

void setup()
{
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("Starting Sensor...");

  if (!sensor.begin(0x29, &Wire))
  {
    Serial.println("Sensor not detected!");
    while (1);
  }

  sensor.startRanging();

  Serial.println("VL53L1X Ready!");
}

void loop()
{
  if (sensor.dataReady())
  {
    int16_t distance = sensor.distance();

    if (distance >= 0)
    {
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" mm");
    }

    sensor.clearInterrupt();
  }

  delay(1000);
}
