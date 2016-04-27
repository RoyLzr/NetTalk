#include "LineTalkReactor.h"
#include "ClientSvr.h"

int 
LineTalkReactor::load(const Section & sec)
{
   _conTo     = (size_t)atoi((sec.get("connectTo").c_str()));
   _conPort   = (size_t)atoi((sec.get("svrPort").c_str()));
   _transPort = (size_t)atoi((sec.get("audioPort").c_str()));
   _conIP     =  sec.get("svrIP");
} 

int
LineTalkReactor::Stop()
{
    AutoLock<MLock> l(_lock);
    _status = IReactor::STOP;  
}

bool
LineTalkReactor::isStop()
{
    AutoLock<MLock> l(_lock);
    if(_status == IReactor::STOP)
        return true;
    return false;
} 

int
LineTalkReactor::status()
{
    AutoLock<MLock> l(_lock);
    return _status;
}

int
LineTalkReactor::setClient(ClientSvr * cs)
{
    _client = cs;
    return 0;
}

int
LineTalkReactor::run()
{
    return 0;
}


int 
LineTalkReactor::extCmd(const string &input)
{
    Log::NOTICE("USER INPUT OP: %s", input.c_str());
}

int 
LineTalkReactor::init()
{
    return 0;
}

LineTalkReactor::~LineTalkReactor()
{
    AutoLock<MLock> l(_q_lock);
    while(!_extQueue.empty())
    {
        CMD * tmp = _extQueue.front();
        _extQueue.pop();
        delete tmp;
    }
    delete _svrdata;
    delete _userdata;

}

