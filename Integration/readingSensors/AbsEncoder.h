#ifndef ABSENCODER_H
#define ABSENCODER_H

#include <Arduino.h>
#include <SPI.h>

#define DEBUG //debug statement
#define ABSPIN 10 //abs enc cs pin
#define ANGLECOM 0x3FFF //abs enc register that returns measured angle with dynmic angle err compensation

class AbsEncoder
{
    private:
        unsigned int rawData;
        float angleDeg;

    public: 
        AbsEncoder();
        ~AbsEncoder();
        float getAngleDeg();
};
#endif