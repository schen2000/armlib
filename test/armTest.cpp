#include "arm/armTest.h"

using namespace test; 
//----------
// test_movej
//----------
bool ArmTest::test_movej()const
{
    auto p_arm = Arm::create("z1");
    assert(p_arm!=nullptr);
    auto& arm = *p_arm;

    arm.init();

    arm.test();

    if(0)
    {
        TipSt s;
        s.gripper = 0.5;
        s.T.t << 0,0,0.2;
        arm.moveTo(s);
    }
    return true;
}


//----------
// run
//----------
bool ArmTest::run()
{
    log_i("Arm test running...");
    return true;
}
