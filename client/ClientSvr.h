#ifndef _CLIENT_H
#define _CLIENT_H

#include "../interface/thread.h"
#include "../interface/ireactor.h"
#include "../interface/trans.h"
#include "../common/asynLog.h"
#include "../common/util.h"
#include <unistd.h>
#include <memory>

class ClientSvr : public Uncopyable
{

    public:
        ClientSvr()
        {};

        virtual ~ClientSvr();
    
        virtual int init(std::unique_ptr<IReactor>, 
                         std::unique_ptr<WorkerThread>);
        
        virtual int openLog(const Section &);

        virtual int run();

        virtual int stop();
        
        virtual int destroy();

        virtual int extUserInput(void * data, int len);
        
    protected:
        std::unique_ptr<WorkerThread> _listenUserThread;
        std::unique_ptr<IReactor>     _coreAct;
};

#endif
