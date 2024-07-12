#include "mqtt.h"

String regionCode = "ap-in-1";
const char *deviceID = "4329aac2-2506-11ef-84ba-139754672fc5";
const char *connectionkey = "4dde07bbbf28aa68887393aa896a17df";

const char *mqtt_broker = "mqtt.ap-in-1.anedya.io";
const char *mqtt_username = deviceID;
const char *mqtt_password = connectionkey;
const int mqtt_port = 8883;

String responseTopic = "$anedya/device/" + String(deviceID) + "/response";
String errorTopic = "$anedya/device/" + String(deviceID) + "/errors";

const char *ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIICDDCCAbOgAwIBAgITQxd3Dqj4u/74GrImxc0M4EbUvDAKBggqhkjOPQQDAjBL
MQswCQYDVQQGEwJJTjEQMA4GA1UECBMHR3VqYXJhdDEPMA0GA1UEChMGQW5lZHlh
MRkwFwYDVQQDExBBbmVkeWEgUm9vdCBDQSAzMB4XDTI0MDEwMTAwMDAwMFoXDTQz
MTIzMTIzNTk1OVowSzELMAkGA1UEBhMCSU4xEDAOBgNVBAgTB0d1amFyYXQxDzAN
BgNVBAoTBkFuZWR5YTEZMBcGA1UEAxMQQW5lZHlhIFJvb3QgQ0EgMzBZMBMGByqG
SM49AgEGCCqGSM49AwEHA0IABKsxf0vpbjShIOIGweak0/meIYS0AmXaujinCjFk
BFShcaf2MdMeYBPPFwz4p5I8KOCopgshSTUFRCXiiKwgYPKjdjB0MA8GA1UdEwEB
/wQFMAMBAf8wHQYDVR0OBBYEFNz1PBRXdRsYQNVsd3eYVNdRDcH4MB8GA1UdIwQY
MBaAFNz1PBRXdRsYQNVsd3eYVNdRDcH4MA4GA1UdDwEB/wQEAwIBhjARBgNVHSAE
CjAIMAYGBFUdIAAwCgYIKoZIzj0EAwIDRwAwRAIgR/rWSG8+L4XtFLces0JYS7bY
5NH1diiFk54/E5xmSaICIEYYbhvjrdR0GVLjoay6gFspiRZ7GtDDr9xF91WbsK0P
-----END CERTIFICATE-----
)EOF";

WiFiClientSecure esp_client;
PubSubClient mqtt_client(esp_client);

void connectToMQTT() {
  while (!mqtt_client.connected()) {
    const char *client_id = deviceID;

    Serial.print(F("Connecting to Anedya Broker....... "));
    if (mqtt_client.connect(client_id, mqtt_username, mqtt_password)) {
      Serial.println(F("Connected to Anedya broker"));
    } else {
      Serial.print(F("Failed to connect to Anedya broker, rc="));
      Serial.print(mqtt_client.state());
      Serial.println(F("Retrying in 5 seconds."));
      delay(5000);
    }
  }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  char res[150] = "";

  for (unsigned int i = 0; i < length; i++) {
    res[i] = payload[i];
  }

  String str_res(res);
  if (str_res.indexOf("deviceSendTime") != -1) {
    timeRes = str_res;
  } else {
    submitRes = str_res;
  }
}