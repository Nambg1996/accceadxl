#include <ArduinoJson.h>
#include <Wire.h>
#include "M5_ENV.h"
#include <cmath>



 


// Define the size of the JSON document
const int capacity = JSON_OBJECT_SIZE(3);

QMP6988 qmp6988;
SHT3X sht30;

String envdata() {

    // Create a dynamic JSON document
    DynamicJsonDocument doc(capacity);

    // Obtain the data of sht30 and qmp6988
    float pressure = qmp6988.calcPressure();
    float temperature = 0.0f;
    float humidity = 0.0f;
    if (sht30.get() == 0) {
        temperature = sht30.cTemp;
        humidity = sht30.humidity;
       
    }

    // Add the values to the JSON document

    if(round(temperature)==0&&round(humidity)==0){
        Serial.println("bang o that");
         doc["temperature"] = "";
        doc["humidity"] = "";
       /*  doc["pressure"] = ""; */
    }else{
        doc["temperature"] = round(temperature);
        doc["humidity"] = round(humidity);
        /* doc["pressure"] = round(pressure); */

    }
   

    // Serialize the JSON document to a string
    String jsonString;
    serializeJson(doc, jsonString);

    return jsonString;
    
} 


String combineJsonStrings(String json1, String json2) {
  // Create DynamicJsonDocument objects and parse the JSON strings
  DynamicJsonDocument doc1(1024);
  deserializeJson(doc1, json1);

  DynamicJsonDocument doc2(1024);
  deserializeJson(doc2, json2);

  // Combine the two JSON objects
  for (const auto& kvp : doc2.as<JsonObject>()) {
    doc1[kvp.key()] = kvp.value();
  }

  // Convert the combined JSON object to a string
  String combinedString;
  serializeJson(doc1, combinedString);

  // Return the combined JSON string
  return combinedString;
}
