#include <math.h>
#include <kinematics.h>
#include <pwm_server.h>

// puppy description (unit: cm) 
const static double L1 = 4.33;
const static double L2 = 6.4;
const static double L3 = 8;

const static double BX = 17.2;
const static double BY = 10;
const static double BZ = 3.3;

// initial EE(end effector) position (assume 4 legs are in same pos)
// these are VITAL as being the initial point of trajectory
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

void KINE::get_init(void){
  Q2pos(PWM::init_Q1, PWM::init_Q2, PWM::init_Q3);
  show_Ixyz();
}

void KINE::Q2pos(double Q1, double Q2, double Q3){
  // original coordination
  double EE_x = (fabs(Q2) >= fabs(Q3))? L2*Sin(Q2) + L3*Sin(Q2-Q3) : L2*Sin(Q2) - L3*sin(Q3-Q2);
  double EE_y = -(L2*Cos(Q2) + L3*Cos(Q2-Q3));
  double EE_z = L1*Cos(Q1);

  // assign
  Ix = EE_x;
  Iy = EE_y;
  Iz = EE_z;
}

double KINE::Cos(double angle){
  return cos(angle*PI/180);
}

double KINE::Sin(double angle){
  return sin(angle*PI/180);
}



void KINE::show_EE(void){
  Serial.println("=== EE INFO ===");
  Serial.println((String)"RF_EE: "+RF_pos[0]+"\t"+RF_pos[1]+"\t"+RF_pos[2]+"\t");
  Serial.println((String)"RH_EE: "+RH_pos[0]+"\t"+RH_pos[1]+"\t"+RH_pos[2]+"\t");
  Serial.println((String)"LF_EE: "+LF_pos[0]+"\t"+LF_pos[1]+"\t"+LF_pos[2]+"\t");
  Serial.println((String)"LH_EE: "+LH_pos[0]+"\t"+LH_pos[1]+"\t"+LH_pos[2]+"\t");
}

void KINE::show_Q(void){
  Serial.println("=== Q INFO ===");
  Serial.println((String)"RF_Q: "+RF_Q[0]+"\t"+RF_Q[1]+"\t"+RF_Q[2]+"\t");
  Serial.println((String)"RH_Q: "+RH_Q[0]+"\t"+RH_Q[1]+"\t"+RH_Q[2]+"\t");
  Serial.println((String)"LF_Q: "+LF_Q[0]+"\t"+LF_Q[1]+"\t"+LF_Q[2]+"\t");
  Serial.println((String)"LH_Q: "+LH_Q[0]+"\t"+LH_Q[1]+"\t"+LH_Q[2]+"\t");
}

void KINE::show_Ixyz(void){
  Serial.println("=== Ixyz INFO ===");
  Serial.println((String)"Ix: "+Ix);
  Serial.println((String)"Iy: "+Iy);
  Serial.println((String)"Iz: "+Iz);
}