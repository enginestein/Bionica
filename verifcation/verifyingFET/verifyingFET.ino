const int motEnPin = 4;

void setup()
{
    Serial.begin(115200);
    pinMode(motEnPin, OUTPUT);
    delay(50);
}

void loop()
{
    Serial.println("voltage high");
    digitalWrite(motEnPin, HIGH);
    delay(5000);
    
    Serial.println("voltage low");
    digitalWrite(motEnPin, LOW);
    delay(5000);
}