#include <SPI.h>
#include "encoder_functions.h"

void spi_init() {
  pinMode(CSN, OUTPUT);
  pinMode(SI, OUTPUT);
  pinMode(SO, INPUT);
  pinMode(CLK, OUTPUT);
  
  
  digitalWrite(CSN, HIGH);
  SPI.begin();
}

float get_angle() {
  unsigned int angle;
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE1));
  
  
  digitalWrite(CSN, LOW);
  delayMicroseconds(1);
  SPI.transfer16(0xFFFF);
  digitalWrite(CSN,HIGH);

  
  digitalWrite(CSN, LOW);
  delayMicroseconds(1);
  angle = SPI.transfer16(0xC000);
  digitalWrite(CSN, HIGH);
  SPI.endTransaction();

  angle = (angle & (0x3FFF)); 
  float pos = ( (float) angle) * 360.0 / 16384.0;
  return pos;
}
