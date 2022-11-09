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
bool ArmZ1::moveTo(const TipSt& t, int type)
{
    
    //posture[0] << 0,0,0,0.45,-0.2,0.2;
    auto& T = t.T;
    uarm_.MoveL(PosturetoVec6(conv(T)));

    return true;
}
//-----
ArmSt ArmZ1::getSt()const
{
    ArmSt st;
    return st;
}

