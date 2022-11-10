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
   //----
   Trans conv(const Posture& p)
   {
       Trans T;
       T.t << p.x, p.y, p.z;
       T.e.y = p.yaw;
       T.e.r = p.roll;
       T.e.p = p.pitch;
       return T;
   }
}

//-----
bool ArmZ1::init()
{
    log_i("Init Arm Z1...");
    backToStart();
    sys::sleepMS(1000);
    log_i("Init Arm Z1 done");
    return true;
}


//-----
bool ArmZ1::moveTo(const TipSt& t)
{
    
    //posture[0] << 0,0,0,0.45,-0.2,0.2;
    auto& T = t.T;
    //Vec6 v = PosturetoVec6(conv(T));
    //MoveL(v);
    //----

    // No.1 trajectory
    _trajCmd.trajOrder = 1;
    _trajCmd.trajType = TrajType::MoveL;
    _trajCmd.maxSpeed = 1.0;// angular velocity
    _trajCmd.gripperPos = 0.0;
    //posture[0] << 0.5,0.1,0.1,0.5,-0.2,0.5;
    _trajCmd.posture[0] = conv(T);
    setTraj(_trajCmd);
    usleep(10000);


    //run trajectory
    setFsm(ArmFSMState::TRAJECTORY);

    
    return true;
}
//-----
ArmSt ArmZ1::getSt()const
{
    ArmSt st;
    auto& rs = _recvState;
    st.tip.T = conv(rs.cartesianState);
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
