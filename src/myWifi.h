#include <WiFi.h>
void setupWifi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.println("Wifi connection lost. Attempting to reconnect...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(5000);
  }
}


/* void wifiReconnectWhenLost(const char* ssid, const char* password) {
  while (WiFi.status() == WL_DISCONNECTED) {
    Serial.println("Wifi connection lost. Attempting to reconnect...");
    WiFi.begin(ssid, password);
    //Serial.println(WiFi.begin(ssid, password));
    delay(5000);

  }
  //Serial.println("wifi still active");
} */

void wifiReconnectWhenLost(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 10) {
    Serial.println("Wifi connection lost. Attempting to reconnect...");
    WiFi.begin(ssid, password);
    retries++;
    delay(5000);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wifi reconnected!");
  } else {
    Serial.println("Unable to reconnect to Wifi!");
  }
}