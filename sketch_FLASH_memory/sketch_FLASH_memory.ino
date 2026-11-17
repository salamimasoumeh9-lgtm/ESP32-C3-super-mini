
#include <Arduino.h>
#include "esp_partition.h"

#define LED 4
#define BUTTON 10

int state = 0;
int magic = 12345;

const esp_partition_t *flash;

void setup() {

  Serial.begin(115200);

  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  flash = esp_partition_find_first(
    ESP_PARTITION_TYPE_DATA,
    ESP_PARTITION_SUBTYPE_ANY,
    "storage"
  );

  if (flash == NULL) {
    Serial.println("Flash not found!");
    return;
  }

  int savedMagic = 0;

  esp_partition_read(flash, 0, &savedMagic, 4);

  if (savedMagic == magic) {
    esp_partition_read(flash, 4, &state, 4);
  }

  digitalWrite(LED, state);
}

void loop() {

  if (digitalRead(BUTTON) == LOW) {

    delay(200);

    state = !state;

    esp_partition_erase_range(flash, 0, 4096);

    esp_partition_write(flash, 0, &magic, 4);
    esp_partition_write(flash, 4, &state, 4);

    digitalWrite(LED, state);

    Serial.println("Saved!");

    while (digitalRead(BUTTON) == LOW);
  }
}
