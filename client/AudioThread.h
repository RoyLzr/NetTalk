#ifndef _AUDIO_THREAD_H_
#define _AUDIO_THREAD_H_

#include "../interface/thread.h"
#include "../interface/trans.h"

class AudioGetSendThread : public WorkerThread
{
    public:
        AudioGetSendThread(Trans * tran):audio(tran)
        {};
       
        virtual ~AudioGetSendThread() {};

        virtual void Start();
        
        virtual void Execute();

    protected:
        Trans * audio;
};


class AudioShowRecvThread : public WorkerThread
{
    public:
        AudioShowRecvThread(Trans * tran):audio(tran)
        {};
       
        virtual ~AudioShowRecvThread() {};

        virtual void Start();
        
        virtual void Execute();

    protected:
        Trans * audio;
};




#endif
