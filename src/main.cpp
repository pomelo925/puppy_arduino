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

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void servoWrite(int INDEX, double ANGLE);

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);  // This is the maximum PWM frequency
  Serial.begin(115200);
}

void loop(){
  double angle = 0;
  if(Serial.available()) {
    angle = Serial.parseInt();
    servoWrite(LH_Q3, angle);
  }
}

void servoWrite(int INDEX, double ANGLE){
  Serial.println((String)"joiny :" + INDEX + "\tangle:" + ANGLE);
  
// mapping servo angle
  switch(INDEX){
    case LF_Q1:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;
    case LF_Q2:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;
    case LF_Q3:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;

    case LH_Q1:
      ANGLE = map(ANGLE, -63, 46, 0, 110);
      break;
    case LH_Q2:
      ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;
    case LH_Q3:
      ANGLE = map(ANGLE, 44, 140, 0, 150);
      break;

    case RF_Q1:
      // ANGLE = map(ANGsLE, -90, 74, 168, 0);
      break;
    case RF_Q2:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;
    case RF_Q3:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;

    case RH_Q1:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;
    case RH_Q2:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;
    case RH_Q3:
      // ANGLE = map(ANGLE, -90, 74, 168, 0);
      break;
  }

// mapping PWM and angle output
  double pulse_wide = map(ANGLE, 0, 180, 544, 2400);
  double pulse_width = int(float(pulse_wide) / 1000000 * 50 * 4096);
  pwm.setPWM(INDEX, 0, pulse_width);
}
