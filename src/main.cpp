#include "envdata.h"
#include <M5Atom.h>
#include "setting.h"
#include "myWifi.h"
#include "postDataToServer.h"
#include "mysgp.h"

#include "assets/runfunctionEvery.h"


String generate_random_env_data() {
  StaticJsonDocument<128> docr;
  docr["TVOC"] = random(1000);
  docr["eCO2"] = random(500);
  docr["rawH2"] = random(15000);
  docr["humidity"] = random(20, 80);
  docr["rawEthanol"] = random(20000);
  docr["temperature"] = random(-5, 48);
  String json_data;
  serializeJson(docr, json_data);
  Serial.println(json_data);

  return json_data;
}





void setup()
{

  Serial.begin(115200);
  delay(1000);
 
  Wire.end();
  Wire.begin(26, 32);
  mysgbBegin();// eco2/tv0c
 
  setupWifi(ssid,password);
  qmp6988.init();



}

void postEnvDatatoSever() {

  String env_tvoc_data = combineJsonStrings(envdata(),tvocData());
Serial.println(env_tvoc_data); 



postDataTowebServer(env_tvoc_data, "TC");


postDataTowebServer(generate_random_env_data(), "品証");
postDataTowebServer(generate_random_env_data(), "管理C");
postDataTowebServer(generate_random_env_data(), "通気");
postDataTowebServer(generate_random_env_data(), "TPM");

postDataTowebServer(generate_random_env_data(), "RRO包装");
postDataTowebServer(generate_random_env_data(), "取鍋");
postDataTowebServer(generate_random_env_data(), "原材料課");
postDataTowebServer(generate_random_env_data(), "PC原料ライン");
postDataTowebServer(generate_random_env_data(), "PC原料マス");




postDataTowebServer(generate_random_env_data(), "FCS原料");
postDataTowebServer(generate_random_env_data(), "FCS7号");

postDataTowebServer(generate_random_env_data(), "FCS加工場");
postDataTowebServer(generate_random_env_data(), "FCS含浸");
postDataTowebServer(generate_random_env_data(), "中央MR");
postDataTowebServer(generate_random_env_data(), "RH");

postDataTowebServer(generate_random_env_data(), "1000T");
postDataTowebServer(generate_random_env_data(), "1600T");
postDataTowebServer(generate_random_env_data(), "RRA原料");



}






void loop()
{
  
wifiReconnectWhenLost(ssid,password);





runFunctionEvery(&postEnvDatatoSever, 5000);




}




