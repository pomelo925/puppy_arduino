#ifndef _PWM_SERVER_H_
#define _PWM_SERVER_H_

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define LH_Q1 0
#define LH_Q2 1
#define LH_Q3 2
#define LF_Q1 3
#define LF_Q2 4
#define LF_Q3 5
#define RF_Q1 6
#define RF_Q2 7
#define RF_Q3 8
#define RH_Q1 9
#define RH_Q2 10
#define RH_Q3 11

#define FREQ 30

extern Adafruit_PWMServoDriver pwm;

namespace PWM{
  void servoWrite(int INDEX, double ANGLE);
  void single_motor_manual(int INDEX);
  void all_motor_init(void);
}


#endif