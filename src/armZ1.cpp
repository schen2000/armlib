#include "arm/armZ1.h"

using namespace arm;
using namespace unitree;




//-----
bool ArmZ1::moveTo(const TipSt& t, int type)
{
    
    //posture[0] << 0,0,0,0.45,-0.2,0.2;
    auto& T = t.T;
  //  Euler e(T.q);
  //  MoveL(posture[0]);

    return true;
}
//-----
ArmSt ArmZ1::getSt()const
{
    ArmSt st;
    return st;
}

