#include "arm/armLib.h"
#include "arm/armZ1.h"
#include "arm/armTcp.h"

using namespace arm;


//---- factory
Sp<Arm> Arm::create(const string& sModel)
{
    // only "z1" supported
    if(sModel=="z1")
        return mkSp<unitree::ArmZ1>();
    
    log_e("Unkonw Arm type:'"+sModel+"'");
    return nullptr;

}

