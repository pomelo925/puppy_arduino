#include <pwm_server.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void servoWrite(int INDEX, double ANGLE){
  Serial.println((String)"joint :" + INDEX + "\tangle:" + ANGLE);
  
// mapping servo angle (input1, input2, original_ouptut1, original_output2)
  switch(INDEX){
    case LF_Q1:
      ANGLE = map(ANGLE, 0, 175, -60, 90); // 沒控制
      break;
    case LF_Q2:
      ANGLE = map(ANGLE, 80, -90, 0, 172); // 會跳動
      break;
    case LF_Q3:
      ANGLE = map(ANGLE, 44, 140, 0, 150); // OKAY!
      break;

    case LH_Q1:
      ANGLE = map(ANGLE, -63, 46, 0, 110); // OKAY!
      break;
    case LH_Q2:
      ANGLE = map(ANGLE, -90, 74, 168, 0); // OKAY!
      break;
    case LH_Q3:
      ANGLE = map(ANGLE, 44, 140, 0, 150); // OKAY!
      break;

    case RF_Q1:
      ANGLE = map(ANGLE, 90, -85, 0, 180); // OKAY!
      break;
    case RF_Q2:
      ANGLE = map(ANGLE, -80, 90, 0, 160); // OKAY!
      break;
    case RF_Q3:
      ANGLE = map(ANGLE, 145, 40, 0, 180); // OKAY!
      break;

    case RH_Q1:
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
  double pulse_wide = map(ANGLE, 0, 180, 544, 2400);
  double pulse_width = int(float(pulse_wide) / 1000000 * FREQ * 4096);
  pwm.setPWM(INDEX, 0, pulse_width);
}

/* enter angle for a single motor */
void single_motor_manual(int INDEX){
  static double angle=0;

  Serial.println("... Please enter angle:");
  while(Serial.available()==0);
  angle = Serial.parseInt();
  servoWrite(INDEX, angle);
}

void all_motor_init(void){
  servoWrite(LH_Q1, 0);
  servoWrite(LF_Q1, 0);
  servoWrite(RF_Q1, 0);
  servoWrite(RH_Q1, 0);

  servoWrite(LH_Q2, 0);
  servoWrite(LF_Q2, 0);
  servoWrite(RF_Q2, 0);
  servoWrite(RH_Q2, 0);

  servoWrite(LH_Q3, 90);
  servoWrite(LF_Q3, 90);
  servoWrite(RF_Q3, 90);
  servoWrite(RH_Q3, 90);
}
