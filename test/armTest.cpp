#include "arm/armTest.h"

using namespace test; 
//----------
// test_movej
//----------
bool ArmTest::test_basic()const
{
    auto p_arm = Arm::create("z1");
    assert(p_arm!=nullptr);
    auto& arm = *p_arm;

    arm.init();

 //   arm.test();

    if(1)
    {
        TipSt s;
        s.gripper = 0.5;
        s.T.t << 0,0,0.2;
        arm.moveTo(s);
        sys::sleepMS(2000);
    }
    return true;
}


//----------
// run
//----------
bool ArmTest::run()
{
    log_i("Arm test running...");
    test_basic();
    return true;
}
