// Function to submit data to Anedya server
// For more info, visit [https://docs.anedya.io/devicehttpapi/submitdata/]
#include "data_submission.h"
void anedya_submitData(String datapoint, float sensor_data){
  boolean check = true;

  String strSubmitTopic = "$anedya/device/" + String(deviceID) + "/submitdata/json";
  const char *submitTopic = strSubmitTopic.c_str();
  while (check)
  {
    if (mqtt_client.connected())
    {
      if (millis() - submitTimer >= 2000)
      {
        submitTimer = millis();
        // Get current time and convert it to milliseconds
        long long current_time = now();                     // Get the current time
        long long current_time_milli = current_time * 1000; // Convert current time to milliseconds

        // Construct the JSON payload with sensor data and timestamp
        String jsonStr = "{\"data\":[{\"variable\": \"" + datapoint + "\",\"value\":" + String(sensor_data) + ",\"timestamp\":" + String(current_time_milli) + "}]}";
        const char *submitJsonPayload = jsonStr.c_str();

        mqtt_client.publish(submitTopic, submitJsonPayload);
      }
      mqtt_client.loop();

      if (submitRes != "")
      {
        // Parse the JSON response
        DynamicJsonDocument jsonResponse(100);    // Declare a JSON document with a capacity of 200 bytes
        deserializeJson(jsonResponse, submitRes); // Deserialize the JSON response from the server into the JSON document

        int errorCode = jsonResponse["errCode"]; // Get the server receive time from the JSON document

        if (errorCode == 0)
        {
          Serial.println("Data pushed to Anedya!!");
        }
        else if (errorCode == 4040)
        {
          Serial.print("Failed to push data!!\t");
          Serial.println("unknown variable Identifier");
          Serial.println(submitRes);
        }
        else
        {
          Serial.println("Failed to push data!!");
          Serial.println(submitRes);
        }
        check = false;
        submitTimer=5000;
      }
    }
    else
    {
      connectToMQTT();
    } // mqtt connect check end
  }
}