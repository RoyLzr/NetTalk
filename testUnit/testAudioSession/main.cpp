#include "../../client/AudioSession.h"
#include "../../client/AudioThread.h"

int main()
{
    AudioTrans testTrans;
    testTrans.init("127.0.0.1", 1240, 1240);
    AudioShowRecvThread rThread(&testTrans);
    AudioGetSendThread  sThread(&testTrans);
    rThread.Start();
    sThread.Start();
    sleep(1);
    rThread.Stop();
    sThread.Stop();

    pthread_join(rThread.GetThreadId(), NULL);
    pthread_join(sThread.GetThreadId(), NULL);
    
    return 0;
}
