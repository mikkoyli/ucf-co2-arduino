/***************************************************************************
  This is a library for the CCS811 air 

  This sketch reads the sensor

  Designed specifically to work with the Adafruit CCS811 breakout
  ----> http://www.adafruit.com/products/3566

  These sensors use I2C to communicate. The device's I2C address is 0x5A

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
 
#include "MQ135.h"
#include "Adafruit_CCS811.h"
MQ135 gasSensor = MQ135(A6); 
Adafruit_CCS811 ccs;

int val; 
int sensorPin = A0; 
int sensorValue = 0; 

void setup() {
  Serial.begin(9600);
  
  Serial.println("CCS811 test");
  
  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}

void loop() {
  val = analogRead(A0); 
  if(ccs.available()){
    float temp = ccs.calculateTemperature();
    if(!ccs.readData()){
      Serial.print("CCS811");
      Serial.print(" ");
      Serial.print(ccs.geteCO2());
      Serial.print(" ");
      Serial.print("Temp ");
      Serial.print(temp);
      Serial.print(" ");
      Serial.print("MQ135");
      Serial.print(" ");
      float ppm = gasSensor.getPPM(); 
      Serial.print (ppm);
      Serial.print(" ");
      Serial.print("rzero");
      Serial.print(" ");
      float rzero = gasSensor.getRZero();
      Serial.print(rzero);
      Serial.println("");
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  
  delay(1000);
}
