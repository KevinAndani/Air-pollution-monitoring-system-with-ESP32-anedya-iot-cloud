#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <DHT.h>

#define DHT_TYPE DHT11
#define DHT_PIN 5

void dhtInit();
void readDHTSensor(float &temperature, float &humidity);
void generateVirtualSensorData(float &temperature, float &humidity);

#endif // DHT_SENSOR_H