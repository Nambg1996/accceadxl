#include <M5Atom.h>
#include "GPSAnalyse.h"
#include <SPI.h>
#include "FS.h"
#include <SD.h>
#define SD_CS_PIN 4

GPSAnalyse GPS;


float Lat;
float Lon;
String Utc;
String Date;


const char filename[] = "/GPSdata.txt";
File txtFile;

bool writeLog(String filename, String dataAll) {
            //Write GPSdata to SDcard
  txtFile = SD.open(filename, FILE_APPEND);
  if(txtFile){
   /*  
    txtFile.print(Lat);
    txtFile.print(", ");
    txtFile.print(Lon);
    txtFile.print(", ");
    txtFile.println(Utc); */
    txtFile.println(dataAll); 
    txtFile.close();
  }else{
    return false;
  }
  return true;
}

void readFromFile(const char* filename) {
  File file = SD.open(filename);
  if (file) {
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    Serial.print("Unable to open file: ");
    Serial.println(filename);
  }
}

void deleteAllFiles() {
  File root = SD.open("/");
  while (true) {
    File file = root.openNextFile();
    if (!file) {
      // No more files
      Serial.print("there is nothing file: ");
      break;
    }
    if (file.isDirectory()) {
      // Skip directories
      continue;
    }
    Serial.print("Deleting file: ");
    Serial.println(file.name());
    SD.remove(file.name());
    file.close();
  }
  root.close();
}



void gpsbegin(){

    Serial1.begin(9600,SERIAL_8N1,22,-1); 
     GPS.setTaskName("GPS");
     GPS.setTaskPriority(2); 
      GPS.setSerialPtr(Serial1); 

   
  
      GPS.start();

 
   


}


