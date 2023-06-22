const int MAX_RECORDS = 100; // Maximum number of records in a file
const char* FILE_PREFIX = "gpslogfile_"; // File name prefix
const char* FILE_EXTENSION = ".json"; // File extension



String getFileName(int fileNumber) {
  return "/" + String(FILE_PREFIX) + String(fileNumber) + String(FILE_EXTENSION);
}

int countRecordsInFile(int fileNumber) {
  int recordCount = 0;
  File file = SD.open(getFileName(fileNumber), FILE_READ);
  
  if (file) {
    while (file.available()) {
      String line = file.readStringUntil('\n');
      
      // Exclude empty lines or lines starting with a comment symbol
      if (line.length() > 0 && line[0] != '#') {
        recordCount++;
      }
    }
    
    file.close();
  }
  else {
    Serial.println("Error opening file " + String(fileNumber));
  }
  
  return recordCount;
}

void appendJsonToFile(String jsonData) {
  // Get the current file number
  int fileNumber = 1;
  while (SD.exists(getFileName(fileNumber))) {
    fileNumber++;
  }
  
  // Open the current file in append mode
  File file = SD.open(getFileName(fileNumber), FILE_WRITE);
  
  if (file) {
    // Append the JSON data to the file
    file.println(jsonData);
    file.close();
    
    Serial.println("JSON data appended to file " + String(fileNumber));
    
    // Check if the file exceeds the maximum number of records
    Serial.println("coutfile " + String(countRecordsInFile(fileNumber)));
    if (countRecordsInFile(fileNumber) >= MAX_RECORDS) {
      Serial.println("File " + String(fileNumber) + " has reached maximum records. Creating a new file.");
    }
  }
  else {
    Serial.println("Error opening file " + String(fileNumber));
  }
}


void listFiles(const char* directory) {
  File root = SD.open(directory);
  
   if (!root.isDirectory()) {
    Serial.println("Invalid directory!");
    return;
  }
  
  Serial.println("Files in directory: " + String(directory));
  
  while (true) {
    File file = root.openNextFile();
    
    if (!file) {
      break; // No more files
    }
    
    if (file.isDirectory()) {
      Serial.print("Directory: ");
    }
    else {
      Serial.print("File: ");
    }
    
    Serial.println(file.name());
    
    file.close();
  }
  
  Serial.println("End of directory");
  root.close(); 
}

void sdcardSetup(){


  SPI.begin(23,33,19,SD_CS_PIN);
    if(!SD.begin(SD_CS_PIN, SPI, 40000000)){
      Serial.println("initialization failed!");
    } 



}