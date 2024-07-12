#include "x_wifi.h"

const char *ssid = "Unknownn";
const char *pass = "012345678";

void initWiFi() {
  WiFi.begin(ssid, pass);

  Serial.println();
  Serial.print(F("Connecting to WiFi..."));

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println();
  Serial.print(F("Connected, IP address: "));
  Serial.println(WiFi.localIP());
}