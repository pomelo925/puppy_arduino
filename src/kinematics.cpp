#include <type_traits>
#include <cassert>

#include <kinematics.h>
#include <pwm_server.h>
#include <description.h>


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
  Q2pos(init_Q1, init_Q2, init_Q3);
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

std::vector<double> KINE::homo_transformation(std::vector<double> parent_frame, std::vector<std::vector<double>> homo_tf){
  if (parent_frame.size() != 3) Serial.println("== ERROR : Invalid parent frame position ==");
  if (homo_tf.size() != 4) Serial.println("== ERROR : Invalid params matrix ==");
  
  const std::vector<double> parent{
    parent_frame[0], parent_frame[1], parent_frame[2], 1
  };

  return KINE::multiply(homo_tf, parent);
}

std::vector<std::vector<double>> KINE::generate_homo_matrix(std::vector<double> DH_param){
  if(DH_param.size()!=4) Serial.println("== ERROR: Invalid Parameters Matrix!");

  const double the = DH_param[0], alp = DH_param[1];
  const double d = DH_param[2], r = DH_param[3];

  const std::vector<std::vector<double>> homo{
    {Cos(the) , -Sin(the)*Cos(alp) , sin(the)*sin(alp)  , r*cos(the)},
    {sin(the) , cos(the)*cos(alp)  , -cos(the)*sin(alp) , r*sin(the)},
    {0        , sin(alp)           , cos(alp)           , d         },
    {0        , 0                  , 0                  , 1         }
  };

  return homo;
}


std::vector<double> KINE::multiply(const std::vector<std::vector<double>>& homo_tf, const std::vector<double>& pos){
  const std::size_t H_cols = homo_tf[0].size();
  const std::size_t P_rows = pos.size();
  assert(H_cols == P_rows);

  std::vector<double> result;
  result.reserve(H_cols);
  
  for(const auto& M:homo_tf){
    result.push_back(unit_inner_product(M, pos));
  }

  return result;
}

double KINE::unit_inner_product(const std::vector<double>& mat1, const std::vector<double>& mat2){
  assert(mat1.size() == mat2.size());

  double result = 0.0;
  for(int i=0; i<int(mat1.size()); i++){
    result += mat1[i]*mat2[i];
  }

  return result;
}
