#ifndef MOTOR_H
#define MOTOR_H


class Motor
{
private:
  int DAC_Pin;
  int directionPin;
  int enablePin;

public:
  Motor();
  Motor(int dacPin, int dirPin, int enPin);
  void Drive(float effort);
  void Stop(void);
  void FreeSpin(void);

};
#endif
