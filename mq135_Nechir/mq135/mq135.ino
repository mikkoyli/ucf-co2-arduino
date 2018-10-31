#include "SparkFunCCS811.h"

#include "MQ135.h"



//---------------------------------------------------------------------------------------------------------------
//                                                   DEFINES
//---------------------------------------------------------------------
#define CCS811_ADDR 0x5B //Default I2C Address

CCS811 mySensor(CCS811_ADDR);
// select the input pin for the MQ-135 sensor

MQ135 gasSensor = MQ135(A6); 
int sensorPin = A0;
int val = 0;
void setup() {
  CCS811Core::status returnCode = mySensor.begin();
  Serial.begin(9600);
}
void loop() {
  
  val = analogRead(A0);
  
  float rzero = gasSensor.getRZero();
  float ppm = gasSensor.getPPM(); 
    if (mySensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    //Get them later
    mySensor.readAlgorithmResults();
    
    Serial.print("CCS811");
    Serial.print(" ");
  
    Serial.print(mySensor.getCO2());
      
    Serial.print(" ");
    
    Serial.print("MQ135");
    Serial.print(" ");
    Serial.println (ppm); 
    

  }
  delay(1000);
}
