
#include "M5Atom.h"
#include "GPSAnalyse.h"
#include <SPI.h>
#include "FS.h"
#include <SD.h>
#include <TimeLib.h> // Time library for Arduino
#include <Timezone.h> // Timezone library for Arduino 
#include "mysgps.h"
#include "adxl345.h"
#include "assets/encodejson.h"
#include "mysdcard.h"

#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

uint64_t chipid;
char chipname[256];

void readGPSLogFile() {
  if (!SD.begin(SS)) {
    Serial.println("Error initializing SD card.");
    return;
  }

  File file = SD.open("/GPSdata.txt");
  if (!file) {
    Serial.println("Error opening file.");
    return;
  }

  while (file.available()) {
    Serial.write(file.read());
  }

  file.close();
  SD.end();
}


void setup() {

      M5.begin(true,false,true); 
      gpsbegin();
      adxl345setup();
     /*  sdcardSetup(); */
      /* deleteAllFiles();  */

      delay(4000);

       chipid = ESP.getEfuseMac();
    SerialBT.begin("ESP32");
    sprintf( chipname, "SerialBT_%04X", (uint16_t)(chipid >> 32));
    Serial.printf("Bluetooth: %s\n", chipname);

SerialBT.begin("ESP32 Bluetooth");

  // Get the MAC address
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_BT);

  // Print the MAC address
  Serial.print("MAC Address: ");
  for (int i = 0; i < 6; i++) {
    Serial.print(mac[i], HEX);
    if (i < 5) Serial.print(":");
  }
  Serial.println();

  delay(10000);

    
}

void loop() {

  GPS.upDate();
    Lat = GPS.s_GNRMC.Latitude;
    Lon = GPS.s_GNRMC.Longitude;
    Utc = GPS.s_GNRMC.Utc;
    Serial.println("testing GPS");

    Serial.println(Lat);
    Serial.println(Lon);
    

    String gps=String(Lat)+"_"+String(Lon);

    Serial.println("end testing GPS");

    Serial.println(gps);
    
 
/* Serial.println(SerialBT.address()); */
/* String dataAll=jsonencodes(); */
  /* const char* data = dataAll.c_str(); */

  // Transmit the data via Bluetooth
   /* SerialBT.print(data); */
    
   /* Serial.println(dataAll);   */
   /*  appendJsonToFile(data);   */    
    /* listFiles("/");  */  
    Serial.printf("end");
    /* readGPSLogFile(); */
     /* readGPSLogFile(); */
     
     String alldata=gps+"_"+adxlgetValue();

      Serial.println(alldata); 
        /* writeLog(filename,dataAll);   */
        SerialBT.print(alldata);
        delay(300); 


  

    /* SerialBT.printf(dataAll); */
  /*   SerialBT.printf("Longitude= %.5f \r\n",Lon);
    SerialBT.printf("DATA= %s \r\n",Utc);
    Serial.printf("Latitude= %.5f \r\n",Lat);
    Serial.printf("Longitude= %.5f \r\n",Lon);
    Serial.printf("DATA= %s \r\n",Utc); */

   
    /*  deleteAllFiles();  */




}