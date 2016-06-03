
#include "ClientCmd.h"
#include "LineTalkReactor.h"


int TestCmd::callback()
{
    ImPheader_t head;
    head.length = 40;
    head.command_id = 5;
    head.punch_flag = 0;
    head.user_id    = 0;
    char * test = (char *)malloc(head.length);
    for(int i = 0; i < head.length; i++)
        test[i] = '1';
            
    send(ract->getSvrFd(), (char *)&head, sizeof(head), MSG_WAITALL);            
    send(ract->getSvrFd(), test, head.length,  MSG_WAITALL);            

    free(test);
}


int 
InitAudioCmd::callback()
{
    int staus = ract->getAudioStatus();
    if(staus != LineTalkReactor::AUDIOSTOP)
    {
        Log::WARN("AUDIO HAS BEEN INITED");
        return 0;
    }
    Trans * audio = new AudioTrans();
    audio->init("127.0.0.1",
                1240,
                1240);
    Log::NOTICE("USER INIT AUDIO");
    ract->setAudioStatus(LineTalkReactor::AUDIOINIT);

    return ract->setAudioSession(audio); 
}

int
RunAudioCmd::callback()
{
    int staus = ract->getAudioStatus();
    if(staus != LineTalkReactor::AUDIOINIT)
    {
        Log::WARN("AUDIO IS NOT INIT OR HAS BEEN RUN");
        return 0;
    }
    Trans * audio = ract->getAudioSession();
    WorkerThread * sendWork = new AudioGetSendThread(audio);
    WorkerThread * recvWork = new AudioShowRecvThread(audio);
    
    sendWork->Start();
    recvWork->Start();

    Log::NOTICE("USER RUN AUDIO");
    ract->setAudioSendThread(sendWork);
    ract->setAudioRecvThread(recvWork);

    ract->setAudioStatus(LineTalkReactor::AUDIORUN);

    return 0;
}

int
StopAudioCmd::callback()
{
    Trans * audio = ract->getAudioSession();
    WorkerThread * sendWork = ract->getAudioSendThread();
    WorkerThread * recvWork = ract->getAudioRecvThread();
    
    int staus = ract->getAudioStatus();
    if(staus != LineTalkReactor::AUDIORUN)
    {
        if(staus == LineTalkReactor::AUDIOINIT)
            ract->clearAudio();
        else if(staus == LineTalkReactor::AUDIOSTOP)
            Log::WARN("audio is stopped can not stop again");
        return 0;
    }

    sendWork->Stop();
    recvWork->Stop();

    struct timespec ts;
    int rc = clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 1;
    int res;
    void * pRes;
    
    if((res=pthread_timedjoin_np(sendWork->GetThreadId(),&pRes,&ts))==ETIMEDOUT)
    {
        Log::WARN("Try join sendThread error, will try again");
        CMD * stopCmd = new StopAudioCmd(ract);
        ract->Signal(stopCmd);
        return 0;
    }
    pthread_join(recvWork->GetThreadId(), &pRes);

    ract->clearAudio();
    Log::NOTICE("USER STOP AUDIO");
    ract->setAudioStatus(LineTalkReactor::AUDIORUN);

    return 0;
}


