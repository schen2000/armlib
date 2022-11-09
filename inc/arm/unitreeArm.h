#ifndef __UNITREEARM_H
#define __UNITREEARM_H

#include <iostream>
#include "unitree_arm_sdk/unitree_arm_sdk.h"

extern Vec6 PosturetoVec6(const Posture p);

extern Posture Vec6toPosture(const Vec6 p);

//----
class unitreeArm{
public:
    unitreeArm();
    ~unitreeArm();
    void UDPSendRecv();
    void InitCmdData(SendCmd& sendCmd);
    void setFsm(ArmFSMState fsm);
    void backToStart();
    void labelRun(std::string label);
    void labelSave(std::string label);
    void MoveJ(Vec6 moveJCmd);
    void MoveJ(Vec6 moveJCmd, double gripperPos);
    void MoveL(Vec6 moveLCmd);
    void MoveC(Vec6 middleP, Vec6 endP);
    void getJointState(JointState* jointstate);
    void getGripperState(Posture& gripperState);
    void setTraj(TrajCmd trajCmd);
    
    RecvState _recvState; // the arm state receive from udp
    JointState _jointState[7]; // 6 joint angles and one gripper angle
    SendCmd _sendCmd; // command to control the arm
    TrajCmd _trajCmd;

private:
    UDPPort _udp;
    float deltaTime = 4000; //us
    LoopFunc *_udpThread;
};

#endif
