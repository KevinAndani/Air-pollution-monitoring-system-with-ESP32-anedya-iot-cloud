#include <Arduino.h>
#include "x_wifi.h"
#include "mqtt.h"
#include "dht_sensor.h"
#include "time_sync.h"
#include "data_submission.h"
#include "Email.h"
//#include "sms_alert.h"

bool virtual_sensor = false;
float temperature;
float humidity;
float CarbonMonoxide;
float CarbonDioxide;
long long submitTimer;
String timeRes, submitRes;

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
  String htmlContent = readHTMLTemplate();
  if (htmlContent.isEmpty()) {
    Serial.println(F("HTML content is empty"));
    return;
  }

  sendMail(htmlContent);
  //sendSMS(F("Test message from Arduino."));

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

  //File file=open_file();

  CarbonMonoxide=analogRead(34);
  CarbonMonoxide=(CarbonMonoxide*100)/4095.0;
  CarbonDioxide=analogRead(35);
  CarbonDioxide=(CarbonDioxide*100)/4095.0;

  anedya_submitData(F("temperature"), temperature);
  Serial.print(F("Temperature : "));
  Serial.println(temperature);
  // String temp=temp_alert(temperature);
  // write_file(file,temp);

  anedya_submitData(F("humidity"), humidity);
  Serial.print(F("Humidity : "));
  Serial.println(humidity);
  // String humi=humi_alert(humidity);
  // write_file(file,humi);

  anedya_submitData(F("CarbonMonoxide"), CarbonMonoxide);
  Serial.print(F("Carbon Monoxide : "));
  Serial.println(CarbonMonoxide);

  anedya_submitData(F("CarbonDioxide"), CarbonDioxide);
  Serial.print(F("Carbon Dioxide : "));
  Serial.println(CarbonDioxide);

  if(CarbonMonoxide<500){
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
  }
  if(CarbonDioxide<500){
    digitalWrite(4,HIGH);
    delay(500);
    digitalWrite(4,LOW);
  }
  delay(5000);
}

String temp_alert(float temp){
  if(temp<-10){
    return "Extream Cold Temperature\n";
  }
  else if(temp>-11&&temp<0){
    return "Very Cold Temperature\n";
  }
  else if(temp>-1&&temp<11){
    return "Cold Temperature\n";
  }
  else if(temp>10&&temp<21){
    return "Cool Temperature\n";
  }
  else if(temp>20&&temp<31){
    return "Brisk Temperature\n";
  }
  else if(temp>30&&temp<35){
    return "Warm Temperature\n";
  }
  else if(temp>34&&temp<40){
    return "Hot Temperature\n";
  }
  else if(temp>39&&temp<50){
    return "Very Hot Temperature\n";
  }
  else{
    return "Extremly Hot Temperature\n";
  }
}

String humi_alert(float humi){
  if(humi<25){
    return "Poor Low HUmidity Levels\n";
  }
  else if(humi>=25&&humi<30){
    return "Fair Humidity Levels\n";
  }
  else if(humi>=30&&humi<60){
    return "Maintain Your Healty Levels\n";
  }
  else if(humi>=60&&humi<70){
    return "Fair Humidity Levels\n";
  }
  else{
    return "Poor High HUmidity Levels\n";
  }
}

// String CO_alert(float CO){
  
// }