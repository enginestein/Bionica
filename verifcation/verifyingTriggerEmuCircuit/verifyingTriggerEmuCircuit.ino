#include <Motor.h>
 
void setup()
{   
    Serial.begin(115200);
    // analogWriteResolution(12);
    // pinMode(A14, OUTPUT);
}

Motor motor;
float i = 0;
void loop()
{
    // int val = (int) (4096/2*(.5/3.3)*sin(i)+(4096/2*(3/3.3)));
    // pinMode(3, OUTPUT);
    // analogWrite(A14, val);
    // delay(10);
    // Serial.println(val);
    // i += .01;
    float effort = (.25*sin(i));
    i += 0.0001;
    Serial.println(effort*5);
    // motor.Drive(effort);
}
