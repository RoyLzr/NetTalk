
#include "ClientCmd.h"
#include "LineTalkReactor.h"


int TestCmd::callback()
{
    char * test = (char *)malloc(41);
    memset(test, '\0', 41);
    for(int i = 0; i < 40; i++)
        test[i] = '1';
    string buf = test;
    string res;
    IM::Test::TestMsg msg;
    msg.set_id(1);
    msg.set_buf(std::move(buf));
    msg.SerializeToString(&res);

    ImPheader_t head;
    head.length = res.size();
    head.command_id = 5;
    head.punch_flag = 0;
    head.user_id    = 0;

    struct msghdr sData;
    memset(&sData, 0, sizeof(sData));
    struct iovec  ve[2];
    ve[0].iov_base = (void *)&head;
    ve[0].iov_len  = sizeof(head);
    ve[1].iov_base = (void *)res.c_str();
    ve[1].iov_len  = head.length;

    sData.msg_iov = ve;
    sData.msg_iovlen = 2;
    //send(ract->getSvrFd(), (char *)&head, sizeof(head), MSG_WAITALL);           
    //send(ract->getSvrFd(), res.c_str(), head.length,  MSG_WAITALL);            
    sendmsg(ract->getSvrFd(), &sData, MSG_WAITALL);
    printf("data length %d\n", head.length);
    //writev(ract->getSvrFd(), ve, 2);

    free(test);
}

int KeepAliveCmd::callback()
{
    ImPheader_t head;
    head.length = 0;
    head.command_id = IM::Base::UTIL_KEEP_ALIVE;
    head.user_id    = 0;
    send(ract->getSvrFd(), (char *)&head, sizeof(head), MSG_WAITALL);

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
        std::unique_ptr<CMD> stopCmd(new StopAudioCmd(ract));
        ract->Signal(std::move(stopCmd));
        return 0;
    }
    

    pthread_join(recvWork->GetThreadId(), &pRes);

    ract->clearAudio();
    Log::NOTICE("USER STOP AUDIO");
    ract->setAudioStatus(LineTalkReactor::AUDIOSTOP);

    return 0;
}

int RegReqCmd::callback()
{
    
}

