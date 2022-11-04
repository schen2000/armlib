#pragma once

#include "arm/armLib.h"
#include "unitreeArm.h"

namespace z1{
    using namespace arm;
    //----
    class ArmZ1 : public Arm
    {
    public:
        virtual bool moveTo(const TipSt& t, int type=MOVEJ) override;
        virtual ArmSt getSt()const override; 
    protected:
        unitreeArm uarm_;
    };
}
