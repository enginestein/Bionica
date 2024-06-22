#include "IncEncoder.h"
#include <Encoder.h>

IncEncoder::IncEncoder()
{
    incEnc = Encoder(encoderPinA, encoderPinB)
    encReadingOld = 0;
}

//not necesary with this lib Encoder.h from pjrc
// void IncEncoder::~IncEncoder()
// {
//     delete encReadings;
// }

int IncEncoder::getCount()
{
    encReadingNew = incEnc.read();

    return encReadingNew

    //TODO: return velocity or position, or whatever we want really
}