/*
 * Auth: Justin Francis
 * Date: 11/9/19
 * Ver: 0.1
 * Sum: Creation and control of inc encoder from teensy 4.0
 * Mod:
 *    
*/

#ifndef INCENCODER_H
#define INCENCODER_H

#include <Arduino.h>
#include <Encoder.h>

#define ENCODER_RES 4096 //cpr
// #define encoderPinA //TODO:
// #define encoderPinB //TODO:
// #define encoderPinZ //TODO:


class IncEncoder
{
    private:
        const int encoderPinA;
        const int encoderPinB;
        //not needed this time around
        // const int encoderPinZ;
        int encReadingNew;
        int encReadingOld;
        Encoder incEnc;

    public:
        IncEncoder();
        ~IncEncoder();
        int getCount();
};

#endif