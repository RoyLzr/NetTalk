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
    _coreAct->init();
    _listenUserThread = wh;
}

int ClientSvr::run()
{
    if(_listenUserThread)
        _listenUserThread->Start();
    if(_coreAct)
        _coreAct->run();
}

int ClientSvr::openLog(const Section & sec)
{
    Log::init(sec.get("logPath").c_str());
    Log::set_level(atoi(sec.get("logLevel").c_str()));
    Log::NOTICE("LOG INIT SUCCES");
}

int ClientSvr::stop()
{
    if(_listenUserThread)
        _listenUserThread->Stop();
    Log::NOTICE("STOP listen user thread"); 
    if(_coreAct)
        _coreAct->Stop();
    Log::NOTICE("STOP client core reactor"); 
}
        
int ClientSvr::destroy()
{
    if(!_listenUserThread->isStop())
        _listenUserThread->Stop();
    if(!_coreAct->isStop())
        _coreAct->Stop();
    pthread_join(_listenUserThread->GetThreadId(), NULL);
    Log::NOTICE("Listen user op thread is finished"); 
    
}

int ClientSvr::extUserInput(void * data, int len)
{
    std::string userInput((char *)data, len);
    _coreAct->extCmd(userInput);
}

