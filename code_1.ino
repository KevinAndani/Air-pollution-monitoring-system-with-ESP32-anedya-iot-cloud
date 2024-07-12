#include <Arduino.h>
#include "x_wifi.h"
#include "mqtt.h"
#include "dht_sensor.h"
#include "time_sync.h"
#include "data_submission.h"
#include "Email.h"

bool virtual_sensor = false;
float temperature;
float humidity;
float CarbonMonoxide;
float CarbonDioxide;
long long submitTimer;
String timeRes, submitRes;
String htmlContent;

void setup() {
  Serial.begin(115200);
  delay(1500);

  pinMode(34,INPUT);
  pinMode(35,INPUT);
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  initWiFi();
  configMailClient();

  // Read HTML template
  htmlContent = readHTMLTemplate();
  if (htmlContent.isEmpty()) {
    Serial.println(F("HTML content is empty"));
    return;
  }

  submitTimer = millis();

  esp_client.setCACert(ca_cert);
  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setKeepAlive(60);
  mqtt_client.setCallback(mqttCallback);
  connectToMQTT();

  mqtt_client.subscribe(responseTopic.c_str());
  mqtt_client.subscribe(errorTopic.c_str());

  setDeviceTime();
  dhtInit();
}

void loop() {
  if (!virtual_sensor) {
    readDHTSensor(temperature, humidity);
  } else {
    generateVirtualSensorData(temperature, humidity);
  }

  CarbonMonoxide=analogRead(34);
  CarbonMonoxide=(CarbonMonoxide*100)/4095.0;
  CarbonDioxide=analogRead(35);
  CarbonDioxide=(CarbonDioxide*100)/4095.0;

  anedya_submitData(F("temperature"), temperature);
  if((temperature>-11&&temperature<0)||(temperature>39&&temperature<50)){
    sendMail(htmlContent);
  }

  anedya_submitData(F("humidity"), humidity);
  if(humidity<25||humidity>70){
    sendMail(htmlContent);
  }

  anedya_submitData(F("CarbonMonoxide"), CarbonMonoxide);
  if(CarbonMonoxide>35){
    sendMail(htmlContent);
  }

  anedya_submitData(F("CarbonDioxide"), CarbonDioxide);
  if(CarbonDioxide>1000){
    sendMail(htmlContent);
  }

  delay(5000);
}
