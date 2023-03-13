#ifndef _KINEMATICS_H_
#define _KINEMEAICS_H_

#include <vector>

namespace KINE{
    /**
     * assign Ix, Iy, Iz corresponding to given initial Q 
     */
    void get_init(void);

    /**
     * @brief FORWARD kinemetics
     * @param xyz is relative to its Q1
     * @note this contains tranformation and movement
     *       only used in get_init()
     */
    void Q2pos(double Q1, double Q2, double Q3);

    
    /**
     * @brief BACKWARD kinemetics
     * @param xyz is relative to its Q1
     * @note this contains tranformation and movement
     */
    void pos2Q(int idx, double x, double y, double z);

    
    /**
     * @brief the homogeneous transformation in Denavit_Hartenberg Convention
     * @param parent_frame is the XYZ position of the frame
     * @param homo_tf the 4x4 homogeneuous transformation matrix
     * */
    std::vector<double> homo_transformation(std::vector<double> parent_frame, std::vector<std::vector<double>> homo_tf);
    
    /**
     * generate the homogeneous transformation by given parameters
     * @param DH_param the parameters matrix which arguments shall be in the order listed below
     */
    std::vector<std::vector<double>> generate_homo_matrix(std::vector<double> DH_param);


    /**
     * matrix multiplication 
     * @param homo_tf the homogeneous transformation matrix
     * @param pos the parent frame position
     */
    std::vector<double> multiply(const std::vector<std::vector<double>>& homo_tf, const std::vector<double>& pos);


    /**
     * the inner prodect og 1xN and Nx1 matrix
     */
    double unit_inner_product(const std::vector<double>& mat1, const std::vector<double>& mat2);
   
   
   /*
     * return the value in degree
    */
    double Cos(double angle);
    double Sin(double angle);

    void show_Ixyz(void);
    void show_EE(void);
    void show_Q(void);
}

#endif