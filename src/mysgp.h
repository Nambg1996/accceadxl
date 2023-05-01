#include <Wire.h>
#include <Adafruit_SGP30.h>
#include <ArduinoJson.h>

/* 
lib_deps =
  bblanchon/ArduinoJson
  adafruit/Adafruit SGP30 Sensor
*/

Adafruit_SGP30 sgp;

void mysgbBegin(){

  Wire.begin(26, 32);  // Initialize pin 26,32.  
  while (!Serial) { delay(10); } // Wait for serial console to open!

  if (!sgp.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  

}


String tvocData() {
  StaticJsonDocument<200> doc;

   if (!sgp.IAQmeasure()||!sgp.IAQmeasureRaw()) {
    Serial.println("Measurement failed");
     doc["TVOC"] = "";
     doc["eCO2"] = "";

     doc["rawH2"] = "";
     doc["rawEthanol"] = "";
   
  }else{

  doc["TVOC"] = sgp.TVOC;

  doc["rawH2"] = sgp.rawH2;
  doc["rawEthanol"] = sgp.rawEthanol;
  doc["eCO2"] = sgp.eCO2;

  } 


  /* if (!sgp.IAQmeasureRaw()) {
    Serial.println("Raw Measurement failed");
    return "";
  } */

  String output;
  serializeJson(doc, output);
  return output;
}







