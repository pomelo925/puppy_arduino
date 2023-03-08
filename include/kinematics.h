#ifndef _KINEMATICS_H_
#define _KINEMEAICS_H_

// 這邊所有函式內所給出的點都是絕對座標
// 而相對於機器狗最初的原點
namespace KINE{
    void get_init();

    /**
     * FORWARD kinemetics
     * @param xyz is relative to its Q1
     * @note this contains tranformation and movement
     *       only used in get_init()
     */
    void Q2pos(int idx, double Q1, double Q2, double Q3);
    
    /**
     * BACKWARD kinemetics
     * @param xyz is relative to its Q1
     * @note this contains tranformation and movement
     */
    void pos2Q(int idx, double x, double y, double z);

    void show_EE(void);
    void show_Q(void);
}



#endif