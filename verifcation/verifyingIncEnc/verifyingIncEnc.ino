#include <Encoder.h>

Encoder incEnc(2,3);

void setup()
{
    Serial.begin(115200);
    delay(100);
}

void loop()
{
    Serial.print("counts: ");Serial.println(incEnc.read());
    delay(500);
}