#ifndef _CLIENT_H
#define _CLIENT_H

#include "../interface/thread.h"
#include "../interface/ireactor.h"
#include "../interface/trans.h"
#include "../common/asynLog.h"

class ClientSvr
{

    public:
        ClientSvr(): _listenUserThread(NULL),
                     _coreAct(NULL),
                     _audio(NULL)
        {};

        virtual ~ClientSvr();
    
        virtual int init(IReactor *, WorkerThread *);
        
        virtual int openLog(const Section &);

        virtual int run();

        virtual int stop();
        
        virtual int destroy();

        virtual int extUserInput(void * data, int len);
        
        virtual int setAudioTrans(Trans *);
        

    protected:
        WorkerThread * _listenUserThread;
        IReactor     * _coreAct;
        Trans        * _audio; 
};

#endif
