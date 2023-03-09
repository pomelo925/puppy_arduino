#ifndef _KINEMATICS_H_
#define _KINEMEAICS_H_

namespace KINE{
    /**
     * assign Ix, Iy, Iz corresponding to given initial Q 
     */
    void get_init(void);

    /**
     * FORWARD kinemetics
     * @param xyz is relative to its Q1
     * @note this contains tranformation and movement
     *       only used in get_init()
     */
    void Q2pos(double Q1, double Q2, double Q3);

    
    /**
     * BACKWARD kinemetics
     * @param xyz is relative to its Q1
     * @note this contains tranformation and movement
     */
    void pos2Q(int idx, double x, double y, double z);

    double Cos(double angle);
    double Sin(double angle);

    void show_Ixyz(void);
    void show_EE(void);
    void show_Q(void);
}

#endif