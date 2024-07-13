#include "time_sync.h"
#include "mqtt.h"

void setDeviceTime() {
  String timeTopic = "$anedya/device/" + String(deviceID) + "/time/json";
  const char *mqtt_topic = timeTopic.c_str();

  if (mqtt_client.connected()) {
    Serial.print("Time synchronizing......");

    boolean timeCheck = true;
    long long deviceSendTime;
    long long timeTimer = millis();
    while (timeCheck) {
      mqtt_client.loop();

      if (millis() - timeTimer >= 2000) {
        Serial.print(" .");
        timeTimer = millis();
        deviceSendTime = millis();

        StaticJsonDocument<200> requestPayload;
        requestPayload["deviceSendTime"] = deviceSendTime;
        String jsonPayload;
        serializeJson(requestPayload, jsonPayload);
        mqtt_client.publish(mqtt_topic, jsonPayload.c_str());
      }

      if (timeRes != "") {
        String strResTime(timeRes);
        DynamicJsonDocument jsonResponse(100);
        deserializeJson(jsonResponse, strResTime);

        long long serverReceiveTime = jsonResponse["serverReceiveTime"]; // Get the server receive time from the JSON document
        long long serverSendTime = jsonResponse["serverSendTime"];       // Get the server send time from the JSON document

        // Compute the current time
        long long deviceRecTime = millis();                                                                // Get the device receive time
        long long currentTime = (serverReceiveTime + serverSendTime + deviceRecTime - deviceSendTime) / 2; // Compute the current time
        long long currentTimeSeconds = currentTime / 1000;                                                 // Convert current time to seconds

        // Set device time
        setTime(currentTimeSeconds); // Set the device time based on the computed current time
        Serial.println("\n synchronized!");
        timeCheck = false;
      } // response check
    }   // while loop end
  }
  else
  {
    connectToMQTT();
  } // mqtt connect check end
} // set device time function end