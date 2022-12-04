#include "arm/armLib.h"


using namespace arm;

namespace{
    struct LCfg{
        string sArmDefault = "z1";
    }; LCfg lc_;
}


//-------
ArmCmd::ArmCmd()
{
    p_arm_ = Arm::create(lc_.sArmDefault);
    p_arm_->init();

    //----
    {
        add("moveto", mkSp<Cmd>("set coord <x,y,z,rx,ry,rz>",
        [&](CStrs& args)->bool{ return moveto(args); }));
    }
}
//----
bool ArmCmd::moveto(CStrs& args)
{
    assert(p_arm_!=nullptr);
    auto& arm = *p_arm_;

    StrTbl kv; parseKV(args, kv);
    string sxyz = lookup(kv, string("xyz"));
    string srvec = lookup(kv, string("rvec"));
    string sgrip = lookup(kv, string("grip"));

    //----
    TipSt st;
    
    bool ok = true;
    ok &= st.T.e.parse(srvec);
    ok &= s2v(sxyz, st.T.t);
    ok &= s2d(sgrip, st.gripper);
    if(!ok)
    {
        log_e("Error parsing args");
        return false;
    }
    log_i("run cmd moveto:"+st.str());

    //---- run
    arm.moveTo(st);

    return true;
}
