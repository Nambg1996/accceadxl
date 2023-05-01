#include <ArduinoJson.h>



String jsonencodes() {

    /* lib_deps =
  bblanchon/ArduinoJson
  Serial.println(jsonencodes());
   */

  StaticJsonDocument<200> docs;
  docs["value1"] = 1;
  docs["valu2"] = 2;
  docs["value3"] = 3;
  docs["value4"] = 4;

  String output;
  serializeJson(docs, output);
  return output;

}