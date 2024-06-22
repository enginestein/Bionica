// #include <Arduino.h>
#include <Encoder.h>

//empirically determined speed curve (x = thetaDotDes [rad/s], y = command voltage[rad/s])
#define MOT_CONTROL_CURVE (0.67 - 0.148*log(abs(thetaDotDes))) 
// #define DEBUG

//control vars
float P = 17.5; //proportional gain
float D = .01; //derivative gain
float I = .05; //integral gain
float k; //conversion factor for theta dot to voltage for the controller output
float motCmd;
float err;
float errOld = 0;
float dErr;
float errAccum = 0;
float thetaDes = 0;
float theta, thetaDotDes, inputV;
const int POT_PIN = 33; //A14 to get thetaDes
int startTime = 0;
elapsedMicros eTime;

#ifdef DEBUG
elapsedMicros printTime;
#endif

//motor vars
int DAC_Pin = A22;
int directionPin = 35;
int enablePin = 14;

//inc Encoder
Encoder inc(2,3);
int counts, countsOld = 0;
const float INC_RES = 4096.0; //cpr

void setup()
{
    Serial.begin(115200);
    pinMode(DAC_Pin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    delay(50);
    Serial.println("theta thetaDes");

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

    motCmd = MOT_CONTROL_CURVE; //[V]
    motCmd = constrain(motCmd, 0.0, .75);

    analogWrite(DAC_Pin, (int)(motCmd*1024/3.3));
}

float i = 0;
void loop()
{
    //read sensor
    counts = inc.read();
    inputV = analogRead(POT_PIN) * (3.3/1024); //V
    // Serial.print("counts: ");Serial.println(counts);


    //convert to theta
    theta = (((float)counts/INC_RES))*2*PI; //rad
  
    thetaDes = inputV * (2*PI/3.24) - PI; //rad
    //sine wave thetaDes
    // thetaDes = (PI*sin(i));
    // i += 0.0001;

    //find err
    err = thetaDes - theta; //rad
    dErr = (err - errOld)/(eTime*1e-6); //[rad/s]
    errAccum += err;
    eTime = 0;

    #ifdef DEBUG
    if(printTime >= 5e5)
    {
        Serial.print("Kd*derr: ");Serial.println(D*dErr, 6);
        Serial.print("Kp*err: ");Serial.println(P*err, 6);
        Serial.print("controller out: ");Serial.println(P*err + D*dErr, 6);
        Serial.println();
        printTime = 0;
    }
    #endif
    

    //calc correction
    thetaDotDes = P * err + I* constrain(errAccum, -P, P) + D * dErr; //[rad/s]

    Serial.print(theta*.25);Serial.print("\t");Serial.print(thetaDes*.25);Serial.println();
    // Serial.print((P*err)*.1);Serial.print("\t");Serial.println(thetaDotDes*.1);

    // Serial.print("thetaDotDes: ");Serial.println(thetaDotDes, 6);

    MotorDrive(thetaDotDes);

    //feedback (not needed for P controller)
    errOld = err;
    // delay(1000);
}