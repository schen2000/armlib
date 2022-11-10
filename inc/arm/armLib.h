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
    struct Trans{
        Trans(){ t << 0,0,0; }
        vec3 t;
        Euler e;
    };
    //----------
    struct TipSt{
        Trans T;
        double gripper = 0;
    };
    //---
    struct JointSt{
        Trans T;
        // other status, acc, rot speed etc
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
        struct Cfg{
            double maxSpeed = 1;
        }; Cfg cfg_;
        //----
        virtual bool init()=0;
        virtual bool moveTo(const TipSt& t) =0;
        virtual ArmSt getSt()const =0; 
        static Sp<Arm> create(const string& sModel);
        virtual bool test()=0;
    };
}
