#include <pwm_server.h>

namespace PWM{
  double init_Q1=0;
  double init_Q2=-45;
  double init_Q3=90;
}

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void PWM::servoWrite(int INDEX, double ANGLE){
  Serial.println((String)"joint :" + INDEX + "\tangle:" + ANGLE);
    double pulse_wide=0;
    double pulse_width=0;

// mapping servo angle (input1, input2, original_ouptut1, original_output2)
  bool flag;
  switch(INDEX){
    case LF_Q1:
      ANGLE = map(ANGLE, 0, 175, -60, 90); // 沒控制
      break;
    case LF_Q2:
      ANGLE = map(ANGLE, 80, -90, 0, 172); // 會跳動
      break;
    case LF_Q3:
      if (ANGLE<44 || ANGLE>140) goto INVALID_ANGLE;
      ANGLE = map(ANGLE, 44, 140, 0, 150); // OKAY!
      break;

    case LH_Q1:
      if (ANGLE<-63 || ANGLE>46) goto INVALID_ANGLE;
      ANGLE = map(ANGLE, -63, 46, 0, 110); // OKAY!
      break;
    case LH_Q2:
      if (ANGLE<-90 || ANGLE>74) goto INVALID_ANGLE;
      ANGLE = map(ANGLE, -90, 74, 168, 0); // OKAY!
      break;
    case LH_Q3:
      if (ANGLE<44 || ANGLE>140) goto INVALID_ANGLE;
      ANGLE = map(ANGLE, 44, 140, 0, 150); // OKAY!
      break;

    case RF_Q1:
      if (ANGLE<-85 || ANGLE>90) goto INVALID_ANGLE;
      ANGLE = map(ANGLE, 90, -85, 0, 180); // OKAY!
      break;
    case RF_Q2:
      if (ANGLE<-80 || ANGLE>90) goto INVALID_ANGLE;
      ANGLE = map(ANGLE, -80, 90, 0, 160); // OKAY!
      break;
    case RF_Q3:
      if (ANGLE<40 || ANGLE>145) goto INVALID_ANGLE; 
      ANGLE = map(ANGLE, 145, 40, 0, 180); // OKAY!
      break;

    case RH_Q1:
      if (ANGLE<-60 || ANGLE>180) goto INVALID_ANGLE; 
      ANGLE = map(ANGLE, -60, 180, 0, 120); // OKAY!
      break;
    case RH_Q2:
      ANGLE = map(ANGLE, 80, -90, 0, 172); // 會跳動
      break;
    case RH_Q3:
      ANGLE = map(ANGLE, 44, 140, 0, 150); // 機構壞掉了
      break;
  }

// PWM angle output

  pulse_wide = map(ANGLE, 0, 180, 544, 2400);
  pulse_width = int(float(pulse_wide) / 1000000 * FREQ * 4096);
  pwm.setPWM(INDEX, 0, pulse_width);

  return;
  
  INVALID_ANGLE:
    Serial.println((String)"== ERROR: JOINT "+INDEX+" GIVEN OUTRANGED ANGLE ! ==");
    return;
}

/* enter angle for a single motor */
void PWM::single_motor_manual(int INDEX){
  static double angle=0;

  Serial.println("... Please enter angle:");
  while(Serial.available()==0);
  angle = Serial.parseInt();
  servoWrite(INDEX, angle);
}

void PWM::all_motor_init(void){
  servoWrite(LH_Q1, init_Q1);
  servoWrite(LF_Q1, init_Q1);
  servoWrite(RF_Q1, init_Q1);
  servoWrite(RH_Q1, init_Q1);

  servoWrite(LH_Q2, init_Q2);
  servoWrite(LF_Q2, init_Q2);
  servoWrite(RF_Q2, init_Q2);
  servoWrite(RH_Q2, init_Q2);

  servoWrite(LH_Q3, init_Q3);
  servoWrite(LF_Q3, init_Q3);
  servoWrite(RF_Q3, init_Q3);
  servoWrite(RH_Q3, init_Q3);
}
