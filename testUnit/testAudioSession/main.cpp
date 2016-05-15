#include "../../client/AudioSession.h"

int main()
{
    AudioTrans testTrans;
    testTrans.init("127.0.0.1", 1240, 1240);
    while(true)
    {
        testTrans.GetLocalData();
        testTrans.SendData();
        testTrans.RecvData();
        testTrans.ShowLocalData();
    }
    return 0;
}
