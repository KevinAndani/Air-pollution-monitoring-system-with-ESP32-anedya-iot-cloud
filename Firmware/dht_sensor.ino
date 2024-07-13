#include "dht_sensor.h"

DHT dht(DHT_PIN, DHT_TYPE);

void dhtInit() {
  dht.begin();
}

void readDHTSensor(float &temperature, float &humidity) {
  Serial.println("Fetching data from the Physical sensor");
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT !");
    delay(10000);
    return;
  }
}

void generateVirtualSensorData(float &temperature, float &humidity) {
  Serial.println("Fetching data from the Virtual sensor");
  temperature = random(20, 30);
  humidity = random(60, 80);
}