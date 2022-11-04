/*
   Author: Sherman Chen
   Create Time: 2022-11-04
   Email: schen@simviu.com
   Copyright(c): Simviu Inc.
   Website: https://www.simviu.com
 */

#pragma once

#include <stdio.h>
#include <iostream>
#include "vsn/vsnLib.h"



namespace arm{
    using namespace std;
    using namespace ut;
    using namespace egn;
    using namespace vsn;

    //----------
    enum{ MOVEJ=0, MOVEL }; 
    //----------
    struct TipSt{
        vsn::Pose pose;
        double gripper = 0;
    };
    //---
    struct JointSt{
        Pose pose;
        float a=0;
    };
    //-----
    struct ArmSt{
        TipSt tip;
        vector<JointSt> joints;
    };
    //----------
    // Arm
    //----------
    class Arm{
    public:
        virtual bool moveTo(const TipSt& t, int type=MOVEJ) =0;
        virtual ArmSt getSt()const =0; 
        static Sp<Arm> create(const string& sModel);
    };
}
