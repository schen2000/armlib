#include "arm/armTcp.h"

using namespace arm;

ArmTcp::ArmTcp(const string& sHost, int port)
{
    auto& cntx = client_.cntx_;
    cntx.sHost = sHost;
    cntx.port = port;
}

//-----
bool ArmTcp::init()
{
    auto& cntx = client.cntx_;
    client.setRcv([](const char& buf, int len){
        onRecv(buf, len);
    });
    bool ok = client.connect(cntx.sHost, cntx.port); 
    return ok;
}

//----
void ArmTcp::onRecv(const char* buf, int len)
{
    string s(buf, len);
    log_d("socket recv:"+s);

}

//-----
bool ArmTcp::moveTo(const TipSt& ts) 
{
    string s = "moveto ";
    s += "xyz=" + str(ts.T.t) + " ";
    s += "rvec=" + ts.T.e.str()+ " ";
    s += "grip=" + str(ts.T.gripper);

    bool ok = client.send(s);
    return ok;

}

ArmSt ArmTcp::getSt()const 
{
    return true;

}

bool ArmTcp::test()
{
    return true;

}