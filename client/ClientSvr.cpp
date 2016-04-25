#include "ClientSvr.h"

ClientSvr::~ClientSvr()
{
    if(_coreAct != NULL)
        delete _coreAct;
    if(_listenUserThread != NULL)
        delete _listenUserThread;
}

    
int ClientSvr::init(IReactor * ir, WorkerThread * wh)
{
    _coreAct = ir;
    _listenUserThread = wh;
}

int ClientSvr::run()
{
    if(_listenUserThread)
        _listenUserThread->Start();
    if(_coreAct)
        _coreAct->run();
}

int ClientSvr::stop()
{
    if(_listenUserThread)
        _listenUserThread->Stop();
    if(_coreAct)
        _coreAct->stop();
}
        
int ClientSvr::destroy()
{
    if(!_listenUserThread->isStop())
        _listenUserThread->Stop();
    pthread_join(_listenUserThread->GetThreadId(), NULL); 
    printf("join listen User input OK\n");
    
}

int ClientSvr::extUserInput(void * data, int len)
{
    char * end = (char *)data + len;
    *end = '\0';
    printf("result :: %s", data);
}




