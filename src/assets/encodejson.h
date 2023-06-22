#include <ArduinoJson.h>


String jsonencodes() {

    GPS.upDate();
    Lat = GPS.s_GNRMC.Latitude;
    Lon = GPS.s_GNRMC.Longitude;
    Utc = GPS.s_GNRMC.Utc;
    Serial.println("testing GPS");

    Serial.println(Lat);
    Serial.println("end testing GPS");

  StaticJsonDocument<200> docs;
  docs["Lat"] = Lat;
  docs["Lon"] = Lon;
  docs["acceleration"] = adxlgetValue();
  docs["time"] = Utc;
  
  

  String output;
  serializeJson(docs, output);
  return output;

}