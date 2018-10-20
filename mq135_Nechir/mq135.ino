#include "SparkFunCCS811.h"




//---------------------------------------------------------------------------------------------------------------
//                                                   DEFINES
//---------------------------------------------------------------------
#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address

#define co2Zero     55                        //calibrated CO2 0 level

CCS811 mySensor(CCS811_ADDR);
// select the input pin for the MQ-135 sensor
int sensorPinA = A0;
int sensorPinB = A1; 
// variable to store the value coming from the sensor.
int valA = 0; 
int valB = 0;
void setup() {
  CCS811Core::status returnCode = mySensor.begin();
  Serial.begin(9600);
}
void loop() {
  int co2now[10];                               //int array for co2 readings
  int co2raw = 0;                               //int for raw value of co2
  int co2comp = 0;                              //int for compensated co2 
  int co2ppm = 0;                               //int for calculated ppm
  int zzz = 0;                                  //int for averaging
  int grafX = 0;                                //int for x value of graph

    for (int x = 0;x<10;x++){                   //samplpe co2 10x over 2 seconds
    co2now[x]=analogRead(sensorPinA);
    delay(200);
  }
  for (int x = 0;x<10;x++){                     //add samples together
    zzz=zzz + co2now[x];
    
  }
  
  co2raw = zzz/10;                            //divide samples by 10
  co2comp = co2raw - co2Zero;                 //get compensated value
  co2ppm = map(co2comp,0,1023,400,5000);      //map value for atmospheric levels

    if (mySensor.dataAvailable())
  {
    //If so, have the sensor read and calculate the results.
    //Get them later
    mySensor.readAlgorithmResults();
    
    Serial.print("CCS811");
    Serial.print(" ");
  
    Serial.print(mySensor.getCO2());
    

  }
  Serial.print(" ");
  
  Serial.print("MQ135");
  Serial.print(" ");
  
  Serial.println (co2ppm);
  delay(1000);
}
