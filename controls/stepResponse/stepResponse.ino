#include <Encoder.h>
#include <SD.h>
#include <SPI.h>

#define MOT_CONTROL_CURVE (0.67 - 0.148*log(abs(thetaDotDes))) 

const int chipSelect = BUILTIN_SDCARD;


float P = 10; 
float k; 
float motCmd;
float err;
float errOld;
float thetaDes = 0.0f;
float theta, thetaDotDes, inputV;
const int POT_PIN = 33; 
elapsedMicros eTime;


int DAC_Pin = A22;
int directionPin = 35;
int enablePin = 14;


Encoder inc(2,3);
int counts, countsOld = 0;
const float INC_RES = 4096.0; 

void setup()
{
    Serial.begin(115200);
    pinMode(DAC_Pin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(enablePin, OUTPUT);

    
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    
    return;
  }
  Serial.println("card initialized.");

  eTime = 0;
}

void MotorDrive(float thetaDotDes)
{
    if(thetaDotDes >= 0.0)
    {
        digitalWrite(directionPin, HIGH);
    }
    else
    {
        digitalWrite(directionPin, LOW);
    }

    motCmd = MOT_CONTROL_CURVE; 
    motCmd = constrain(motCmd, 0.0, .75);

    analogWrite(DAC_Pin, (int)(motCmd*1024/3.3));
}

void loop()
{
    
    if(eTime >= 1e6)
    {
        thetaDes = 3.0f;
    }

    
    counts = inc.read();

    
    theta = (((float)counts/INC_RES))*2*PI; 

    
    err = thetaDes - theta; 

    
    thetaDotDes = P * err; 

    
    MotorDrive(thetaDotDes);

     
  String dataString = "";

  dataString += String(eTime); 
  dataString += String(","); 
  dataString += String(thetaDes); 
  dataString += String(","); 
  dataString += String(theta); 


  
  
  File dataFile = SD.open("DATALOG.txt", FILE_WRITE);

  
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
        
    Serial.println(dataString);
  }  
  else {
    Serial.println("error opening datalog.txt");
  } 

    
}