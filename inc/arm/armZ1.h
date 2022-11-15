#pragma once

#include "arm/armLib.h"
#include "control/unitreeArm.h"

namespace unitree{
    using namespace arm;
    //----
    class ArmZ1 : public Arm
    {
    public:
        ArmZ1()
        {
            pCtrlComp_ = new CtrlComponents(0.002);
            p_uarm_ = new unitreeArm(pCtrlComp_);
        }

        virtual bool init()override;
        virtual bool moveTo(const TipSt& ts) override;
        virtual ArmSt getSt()const override; 
        virtual bool test()override;
     //   virtual bool done()const override;
    protected:
        CtrlComponents* pCtrlComp_ = nullptr;
        unitreeArm* p_uarm_ = nullptr;
    };
}
