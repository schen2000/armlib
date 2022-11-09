#pragma once

#include "arm/armLib.h"
#include "arm/unitreeArm.h"

namespace unitree{
    using namespace arm;
    //----
    class ArmZ1 : public Arm
    {
    public:
        virtual bool moveTo(const TipSt& t, int type=MOVEL) override;
        virtual ArmSt getSt()const override; 
    protected:
        unitreeArm uarm_;
    };
}
