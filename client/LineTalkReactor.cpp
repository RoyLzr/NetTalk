#include "LineTalkReactor.h"
#include "ClientSvr.h"

int 
LineTalkReactor::load(const Section & sec)
{
   _conTo     = (size_t)atoi((sec.get("connectTo").c_str()));
   _conPort   = (size_t)atoi((sec.get("svrPort").c_str()));
   _audioPort = (size_t)atoi((sec.get("AudioLocalPort").c_str()));
   _conIP     =  sec.get("svrIP");
   printf("con = %d\n", _conTo);
   printf("conP = %d\n", _conPort);
   std::cout << _conIP << std::endl;
} 

int
LineTalkReactor::Stop()
{
    AutoLock<MLock> l(_lock);
    _status = IReactor::STOP;
   if(_AudioSendThread!=NULL)
   {
       Log::NOTICE("Rector stop, AudioSendThread run, stop it!");
       _AudioSendThread->Stop();
       pthread_join(_AudioSendThread->GetThreadId(),
                    NULL);
       delete _AudioSendThread;
       _AudioSendThread = NULL;
       Log::NOTICE("End audio send thread ok");
   }

   if(_AudioRecvThread!=NULL)
   {
       Log::NOTICE("Rector stop, AudioRecvThread run, stop it!");
       _AudioRecvThread->Stop();
       pthread_join(_AudioRecvThread->GetThreadId(),
                    NULL);
       delete _AudioRecvThread;
       _AudioRecvThread = NULL;
       Log::NOTICE("End audio recv thread ok");
       delete _audio;
       _audio = NULL;
       Log::NOTICE("End audio session ok");
   }
    
}

int 
LineTalkReactor::clearAudio()
{
    if(_audio != NULL)
    {
        delete _audio;
        _audio = NULL;
    }
    if(_AudioRecvThread != NULL)
    {
        delete _AudioRecvThread;
        _AudioRecvThread = NULL;
    }
    if(_AudioSendThread != NULL)
    {
        delete _AudioSendThread;
        _AudioSendThread = NULL;
    }
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
    struct timeval tv;
    int sec  =  _conTo/1000;
    int usec = (_conTo%1000) *1000;

    while(true)
    {
        if(isStop())
            break;
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(_pipe[0], &fdset);
        int res;
        tv.tv_sec  = sec;
        tv.tv_usec = usec;

        if((res=select(FD_SETSIZE, &fdset, 0, 0, &tv))<=0) 
        {
            if(res == 0)
                Log::NOTICE("User input nothing %d s", sec);
            else
                Log::WARN("Core Reactor Select Error %s", strerror(errno));
        }
        if(FD_ISSET(_pipe[0], &fdset))
        {
            SignalDeal(); 
        }
    } 
    return 0;
}


int 
LineTalkReactor::extCmd(const string input)
{
    Log::NOTICE("User ORG INPUT DATA: %s", input.c_str()); 
    
    if(input == "init\n")
    {
        CMD * cmd = new InitAudioCmd(this);
        Signal(cmd);
    }
    else if(input == "run\n")
    {
        CMD * cmd = new RunAudioCmd(this);
        Signal(cmd);
    }
    else if(input == "stop\n")
    {
        CMD * cmd = new StopAudioCmd(this);
        Signal(cmd);
    }
    else
    {
        Log::WARN("USER INPUT ERROR");
    }
    return 0;
}

int
LineTalkReactor::setAudioSession(Trans * t)
{
    if(_audio != NULL)
    {
        Log::ERROR("set audio but  audio exist");
        return -1;
    }
    _audio = t;
    return 0;
}

Trans *
LineTalkReactor::getAudioSession()
{
    return _audio;
}

int
LineTalkReactor::setAudioSendThread(WorkerThread * t)
{
    if(_AudioSendThread != NULL)
    {
        Log::ERROR("set audio send thread but audio exist");
        return -1;
    }
    _AudioSendThread = t;
    return 0;
}

WorkerThread *
LineTalkReactor::getAudioSendThread()
{
    return _AudioSendThread;
}

int
LineTalkReactor::setAudioRecvThread(WorkerThread * t)
{
    if(_AudioRecvThread != NULL)
    {
        Log::ERROR("set audio recv thread but  audio exist");
        return -1;
    }
    _AudioRecvThread = t;
    return 0;
}

WorkerThread *
LineTalkReactor::getAudioRecvThread()
{
    return _AudioRecvThread;
}

int 
LineTalkReactor::init()
{
    if(::pipe(_pipe) < 0)
    {
        Log::WARN("Create Pipe error : %s ",strerror(errno));
        return -1;
    }

    if(set_fd_noblock(_pipe[0]) < 0)
    {
        Log::WARN("PIPE NOBlock Error");    
        return -1;
    }
    if(set_fd_noblock(_pipe[1]) < 0)
    {
        Log::WARN("PIPE NOBlock Error");    
        return -1;
    }

    return 0;
}

void LineTalkReactor::Signal(CMD * extCmd)
{
    ::write(_pipe[1], "a", 1);
    AutoLock<MLock> l(_q_lock);
    _extQueue.push(extCmd);
}

void LineTalkReactor::SignalDeal()
{
    do
    {
        char buf[64];
        int ret = ::read(_pipe[0],buf,sizeof(buf));
        if(ret < (int)sizeof(buf))
            break;
    }while(true);
    CMD * extCmd;
    while(true)
    {
        _q_lock.lock();
        if(_extQueue.empty())
        {
            _q_lock.unlock();
            break;
        }
        extCmd = _extQueue.front();
        _extQueue.pop();
        _q_lock.unlock();
        extCmd->callback();
        delete extCmd;
    } 
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
    if(_svrdata!=NULL)
        delete _svrdata;
    if(_userdata!=NULL)
        delete _userdata;
    if(_audio!=NULL)
        delete _audio;
    if(_AudioSendThread!=NULL)
        delete _AudioSendThread;
    if(_AudioRecvThread!=NULL)
        delete _AudioRecvThread;
    if(_pipe[0]>=0)
    {
        ::close(_pipe[0]);
        ::close(_pipe[1]);
        _pipe[0] = _pipe[1] = -1;
    }

}

