#include "AbsEncoder.h"

AbsEncoder::AbsEncoder()
{
    SPI.begin(); //this inits all spi pins on teensy and pulls sck/mosi low and ss HIGH
    pinMode(ABSPIN, OUTPUT); //set CS pin
    digitalWrite(ABSPIN, HIGH); //deselect chip //does not seem to pull with SPI.begin()
}

AbsEncoder::~AbsEncoder()
{
    //TODO: remove. Unecessary
}

float AbsEncoder::getAngleDeg()
{
    SPI.beginTransaction(SPISettings(10e6, MSBFIRST, SPI_MODE1));
  
    digitalWrite(ABSPIN, LOW);
    rawData = SPI.transfer16(ANGLECOM);
    digitalWrite(ABSPIN,HIGH);

    rawData = (rawData & (0x3FFF)); //offset data to 14 bit
    angleDeg = ( (float) rawData) * 360.0 / 16384.0; //convert to degrees
    
    return angleDeg;
}