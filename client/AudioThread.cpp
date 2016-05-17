#include "AudioThread.h"


void AudioGetSendThread::Start()
{
    m_status = THREADRUN;
    (void)pthread_create(&m_thread_id, NULL, StartRoutine, this); 
}

void AudioGetSendThread::Execute()
{
    if(audio == NULL)
        return;

    while(true)
    {
        if(isStop())
            break;
        audio->GetLocalData();
        audio->SendData(); 
    }
    audio->Bye();
}


void AudioShowRecvThread::Start()
{
    m_status = THREADRUN;
    (void)pthread_create(&m_thread_id, NULL, StartRoutine, this); 
}

void AudioShowRecvThread::Execute()
{
    if(audio == NULL)
        return;

    while(true)
    {
        if(isStop())
            break;
        audio->RecvData();
        audio->ShowLocalData(); 
    }
}

