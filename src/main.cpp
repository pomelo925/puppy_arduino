#include <pwm_server.h>

extern Adafruit_PWMServoDriver pwm;

void setup() {
  pwm.begin();
  pwm.setPWMFreq(FREQ);  // This is the maximum PWM frequency
  Serial.begin(115200);
  
  all_motor_init();
}

void loop(){
  single_motor_manual(RH_Q2);
}
