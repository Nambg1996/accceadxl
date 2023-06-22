int ADXL345 = 0x53; // The ADXL345 sensor I2C address
float X_out, Y_out, Z_out;  // Outputs


void adxl345setup(){

 Wire.begin(26,32); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device 
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  delay(10);

}


String adxlgetValue(){

  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read()| Wire.read() << 8); // X-axis value
  X_out = X_out/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = ( Wire.read()| Wire.read() << 8); // Y-axis value
  Y_out = Y_out/256;
  Z_out = ( Wire.read()| Wire.read() << 8); // Z-axis value
  Z_out = Z_out/256;

  return (String(X_out)+"_"+String(Y_out)+"_"+String(Z_out));
}


void  showStateObject(float acceleration){

    float crashLow=0.3;
    float crashHigh=254;
    float leanLow=0.3;
    float leanHigh=0.96;
    float shaking =1.4;



     Serial.println(acceleration);

    if(acceleration<crashLow||acceleration>crashHigh){
      
        Serial.println("object is fallen");

    }

    if((leanLow<=acceleration)&&(acceleration<=leanHigh)){
      Serial.println("object is leaning");

    }
     if((leanHigh<=acceleration)&&(acceleration<=shaking)){

      Serial.println("object is still standing");
    }


    if((shaking<=acceleration)&&(acceleration<=crashHigh)){

      Serial.println("object is very shaking");
    }



}

