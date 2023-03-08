#include <math.h>
#include <kinematics.h>
#include <pwm_server.h>

// puppy description (unit: cm) 
const static double L1 = 4.33;
const static double L2 = 4.33;
const static double L3 = 4.33;

const static double BX = 17.2;
const static double BY = 10;
const static double BZ = 3.3;

// initial EE(end effector) position (assume 4 legs are in same pos)
double Ix=0, Iy=0, Iz=0;

// each legs current EE position
double RF_pos[3]={0,0,0};
double RH_pos[3]={0,0,0};
double LF_pos[3]={0,0,0};
double LH_pos[3]={0,0,0};

// each legs current Q angle
double RF_Q[3]={0,0,0};
double RH_Q[3]={0,0,0};
double LF_Q[3]={0,0,0};
double LH_Q[3]={0,0,0};

void KINE::get_init(){
  double q1 = PWM::init_Q1;
  double q2 = PWM::init_Q2;
  double q3 = PWM::init_Q3;

  Q2pos(1, q1,q2,q3);
  Q2pos(2, q1,q2,q3);
  Q2pos(3, q1,q2,q3);
  Q2pos(4, q1,q2,q3);
  Q2pos(5, q1,q2,q3);
  Q2pos(6, q1,q2,q3);
  Q2pos(7, q1,q2,q3);
  Q2pos(8, q1,q2,q3);
  Q2pos(9, q1,q2,q3);
  Q2pos(10, q1,q2,q3);
  Q2pos(11, q1,q2,q3);
}

void KINE::Q2pos(int idx, double Q1, double Q2, double Q3){

}

void KINE::show_EE(void){
  Serial.println((String)"RF_EE: "+RF_pos[0]+"\t"+RF_pos[1]+"\t"+RF_pos[2]+"\t");
  Serial.println((String)"RH_EE: "+RH_pos[0]+"\t"+RH_pos[1]+"\t"+RH_pos[2]+"\t");
  Serial.println((String)"LF_EE: "+LF_pos[0]+"\t"+LF_pos[1]+"\t"+LF_pos[2]+"\t");
  Serial.println((String)"LH_EE: "+LH_pos[0]+"\t"+LH_pos[1]+"\t"+LH_pos[2]+"\t");
}

void KINE::show_Q(void){
  Serial.println((String)"RF_Q: "+RF_Q[0]+"\t"+RF_Q[1]+"\t"+RF_Q[2]+"\t");
  Serial.println((String)"RH_Q: "+RH_Q[0]+"\t"+RH_Q[1]+"\t"+RH_Q[2]+"\t");
  Serial.println((String)"LF_Q: "+LF_Q[0]+"\t"+LF_Q[1]+"\t"+LF_Q[2]+"\t");
  Serial.println((String)"LH_Q: "+LH_Q[0]+"\t"+LH_Q[1]+"\t"+LH_Q[2]+"\t");
}