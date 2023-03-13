#include <description.h>
#include <vector>

// Length Data (unit: cm)
const double L1 = 4.33;
const double L2 = 6.4;
const double L3 = 8;
const double BX = 17.2;
const double BY = 10;
const double BZ = 3.3;


// initial Joint Angle
const double init_Q1 = 0;
const double init_Q2 = -45;
const double init_Q3 = 45;


/** Denavit_hartenberg Convention Parameters 
 ** param in the vector listed below in order
 * @param theta the rotation about Z axis
 * @param alpha the rotation about X axis
 * @param d the displacement of two frmaes in Z direction
 * @param r the displacement of two frames in X-direction
 */
const std::vector<double> RF_param({0, 0, 0, 0});
const std::vector<double> RH_param({0, 0, 0, 0});
const std::vector<double> LF_param({0, 0, 0, 0});
const std::vector<double> LH_param({0, 0, 0, 0});