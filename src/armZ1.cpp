#include "arm/armZ1.h"

using namespace arm;
using namespace unitree;

namespace{
   Posture conv(const Trans& T)
   {
      Posture p;
      p.pitch = T.e.p;
      p.roll = T.e.r;
      p.yaw = T.e.y;
      p.x = T.t.x();
      p.y = T.t.y();
      p.z = T.t.z();
      return p;
   }
}

//-----
bool ArmZ1::init()
{
    backToStart();
    sys::sleepMS(1000);
    return true;
}

//-----
bool ArmZ1::moveTo(const TipSt& t)
{
    
    //posture[0] << 0,0,0,0.45,-0.2,0.2;
    auto& T = t.T;
    MoveL(PosturetoVec6(conv(T)));

    return true;
}
//-----
ArmSt ArmZ1::getSt()const
{
    ArmSt st;
    return st;
}


bool ArmZ1::test()
{
    Vec6 posture[2];
    int order=1;

    labelRun("forward");

    // No.1 trajectory
    _trajCmd.trajOrder = order++;
    _trajCmd.trajType = TrajType::MoveJ;
    _trajCmd.maxSpeed = 1.0;// angular velocity
    _trajCmd.gripperPos = 0.0;
    posture[0] << 0.5,0.1,0.1,0.5,-0.2,0.5;
    _trajCmd.posture[0] = Vec6toPosture(posture[0]);
    setTraj(_trajCmd);
    usleep(10000);

    // No.2 trajectory
    _trajCmd.trajOrder = order++;
    _trajCmd.trajType = TrajType::Stop;
    _trajCmd.stopTime = 1.0;
    _trajCmd.gripperPos = -1.0;
    setTraj(_trajCmd);
    usleep(10000);

    // No.3 trajectory
    _trajCmd.trajOrder = order++;
    _trajCmd.trajType = TrajType::MoveL;
    _trajCmd.maxSpeed = 0.3; // Cartesian velocity
    _trajCmd.gripperPos = 0.0;
    posture[0] << 0,0,0,0.45,-0.2,0.2;
    _trajCmd.posture[0] = Vec6toPosture(posture[0]);
    setTraj(_trajCmd);
    usleep(10000);

    // No.4 trajectory
    _trajCmd.trajOrder = order++;
    _trajCmd.trajType = TrajType::Stop;
    _trajCmd.stopTime = 1.0; 
    _trajCmd.gripperPos = -1.0;
    setTraj(_trajCmd);
    usleep(10000);

    // No.5 trajectory
    _trajCmd.trajOrder = order++;
    _trajCmd.trajType = TrajType::MoveC;
    _trajCmd.maxSpeed = 0.3; // Cartesian velocity
    _trajCmd.gripperPos = 0.0;
    posture[0] << 0,0,0,0.45,0,0.4;
    posture[1] << 0,0,0,0.45,0.2,0.2;
    _trajCmd.posture[0] = Vec6toPosture(posture[0]);
    _trajCmd.posture[1] = Vec6toPosture(posture[1]);
    setTraj(_trajCmd);
    usleep(10000);

    //run trajectory
    setFsm(ArmFSMState::TRAJECTORY);

    // wait for trajectory completion
    while (_recvState.state != ArmFSMState::JOINTCTRL){
        usleep(4000);
    }

    return true;
}
