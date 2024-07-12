#ifndef MQTT_H
#define MQTT_H

#include <WiFiClientSecure.h>
#include <PubSubClient.h>

extern String regionCode;

extern const char *mqtt_broker;
extern const char *mqtt_username;
extern const char *mqtt_password;
extern const int mqtt_port;

extern String responseTopic;
extern String errorTopic;

extern const char *ca_cert;

extern WiFiClientSecure esp_client;
extern PubSubClient mqtt_client;

void connectToMQTT();
void mqttCallback(char *topic, byte *payload, unsigned int length);

#endif // MQTT_H