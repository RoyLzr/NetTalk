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
        FD_SET(_fd,      &fdset);

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
        if(FD_ISSET(_fd, &fdset))
        {
            Log::DEBUG("RECV NETSVR data, will parse it");
            if(extSvrRes() < 0)
                break;
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
    else if(input == "test\n")
    {
        CMD * cmd = new TestCmd(this);
        Signal(cmd); 
    }
    else
    {
        Log::WARN("USER INPUT ERROR");
    }
    return 0;
}

int LineTalkReactor::extSvrRes()
{
    int res = readSvrRes();
    if(res < 0)
        return -1;  
    else if(res == 0)
        return 0;
   
    _svrData.InitByHeaderAddBuf(_svrBuf, _svrBufLen);
    string * content = _svrData.GetBuffer();
    Log::DEBUG("Recv Svr Data, header: len:%d, command:%d,punch:%d,user:%d", 
                _svrData.GetLength(),
                _svrData.GetCommandID(),
                _svrData.GetPunch(),
                _svrData.GetUserID());
    
    std::cout << *content << std::endl;
    _svrBufLen = 0;
}

int LineTalkReactor::dealSvrError(int res)
{
    if(res == 0)
        Log::ERROR("SVR CLOSE FD , CLIENT DOWN");
    if(res < 0)
        Log::ERROR("CONNECT NETSVR error, reconnect");
    
    close(_fd);
    _fd = -1;
}

int LineTalkReactor::expandSvrBuf()
{
    int dataLen = ((ImPheader_t *)_svrBuf)->length;
    int totalLen = ImProto::_headerlen + dataLen;

    int newBufCap = (2*_svrBufCap)>totalLen?(2*_svrBufCap):totalLen;

    void * tmp = malloc(newBufCap);
    memcpy((char *)tmp, (char *)_svrBuf, _svrBufLen);
           
    Log::NOTICE("expand SVR Buf SUCC ORI : %d, NOW: %d",
            _svrBufCap, newBufCap);

    _svrBufCap = newBufCap;
    free(_svrBuf);
    _svrBuf = tmp; 

}

/*
 * -1, read error
 *  0, read unfinish
 *  1, buf can be ext
 */
int LineTalkReactor::readSvrRes()
{
    int res;
    if(_svrBufLen < ImProto::_headerlen) 
    {
        int headleft = ImProto::_headerlen - _svrBufLen;
        res = recv(_fd,
                   (char *)_svrBuf+_svrBufLen,
                   headleft,
                   MSG_DONTWAIT);
        if(res <= 0)
        {
            dealSvrError(res);
            return -1;
        }
        _svrBufLen += res;
    }
    else if(_svrBufLen >= ImProto::_headerlen)
    {
        int dataLen = ((ImPheader_t *)_svrBuf)->length;
        int totalLen = ImProto::_headerlen + dataLen;
        int dataleft = totalLen - _svrBufLen;
        
        if(_svrBufCap < totalLen) 
        {
            expandSvrBuf();
        }

        res = recv(_fd,
                   (char *)_svrBuf+_svrBufLen,
                   dataleft,
                   MSG_DONTWAIT);
        if(res <= 0)
        {
            dealSvrError(res);
            return -1;
        }
        _svrBufLen += res;
        
        printf("read data %d total%d buf%d\n", 
                res, totalLen, _svrBufLen);

        if(_svrBufLen == totalLen)
            return 1;
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
    struct sockaddr_in svr_address;
    set_tcp_sockaddr(_conIP.c_str(),
                     _conPort,
                     &svr_address);
    _fd = socket(AF_INET, SOCK_STREAM, 0); 
    int res = net_connect_to_ms(_fd, 
                           (struct sockaddr *)&svr_address,
                           sizeof(svr_address),
                           _conTo, 1);
    if(res < 0)
    {
        Log::ERROR("INIT ERROR: CAN not connect to netSvr");
        close(_fd);
        _fd = -1;
        return -1;
    }
    Log::NOTICE("INIT netSvr Succ, _fd : %d", _fd);
    
    _svrBuf    = malloc(ImProto::_headerlen); 
    if(_svrBuf == NULL)
    {
        Log::WARN("INIT recv Svr buf error");
        return -1;
    }
    _svrBufCap = ImProto::_headerlen;
    _svrBufLen = 0;

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
    if(_fd > 0)
        ::close(_fd);

}

