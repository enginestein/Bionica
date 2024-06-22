const int DIR_PIN = 2;

void setup()
{   
    Serial.begin(115200);
    pinMode(A14, OUTPUT);
}

int i = 0;
void loop()
{
    pinMode(2, OUTPUT);
    analogWrite(A14, 4096*(2.5/3.3)*sin(i));
    delay(1);
    Serial.println(4096*(2.5/3.3)*sin(i));
}