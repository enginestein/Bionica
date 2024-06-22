#include <SD.h>
#include <SPI.h>
#include <Encoder.h>

#define _DAC_RESOLUTION 4096 
#define _ALLOWED_VOLTAGE_MAX 2.5 
#define _TEENSY_VOLTAGE_MAX 3.3 

Encoder inc(2,3);
int counts, countsOld = 0;
const int INC_RES = 4096; 


int DAC_Pin = A22;
int directionPin = 35;
int enablePin = 34;

elapsedMicros eTime;
int startTime;
const int chipSelect = BUILTIN_SDCARD;

void setup()
{
 
  Serial.begin(115200);


  Serial.print("Initializing SD card...");
  
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    
    return;
  }
  Serial.println("card initialized.");
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

    delay(2000);
    pinMode(DAC_Pin, OUTPUT);
  eTime = 0;
  startTime = 0;
  
}


float voltageCmd = 1.0; 

void loop()
{
    if((eTime - startTime) >= 50e3)
    {
        analogWrite(DAC_Pin, (voltageCmd*(1024/3.3)));
        voltageCmd -= .01;
        startTime = eTime;
    }


    
  
  String dataString = "";

  dataString += String(eTime); 
  dataString += String(","); 
  dataString += String(voltageCmd); 
  dataString += String(",");
  dataString += String(inc.read()); 


  
  
  File dataFile = SD.open("DATALOG.txt", FILE_WRITE);

  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    
    Serial.println(dataString);
  }  
  
  else {
    Serial.println("Error opening datalog.txt");
  } 
}