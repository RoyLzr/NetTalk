#include "ClientSvr.h"

ClientSvr::~ClientSvr()
{
    Log::NOTICE("CORE REACTOR FINISH");
}

    
int ClientSvr::init(std::unique_ptr<IReactor> ir,
                    std::unique_ptr<WorkerThread> wh)
{
    _coreAct = std::move(ir);
    while(true)
    {
        if(_coreAct->init() >=0)
            break;
        sleep(1);
    }
    _listenUserThread = std::move(wh);
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
    _coreAct->extCmd(std::move(userInput));
}

