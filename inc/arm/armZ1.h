#pragma once

#include "arm/armLib.h"
#include "arm/unitreeArm.h"

namespace unitree{
    using namespace arm;
    //----
    class ArmZ1 : public Arm, unitreeArm
    {
    public:
        virtual bool init()override;
        virtual bool moveTo(const TipSt& t) override;
        virtual ArmSt getSt()const override; 
        virtual bool test()override;
    protected:
        //unitreeArm uarm_;
    };
}
