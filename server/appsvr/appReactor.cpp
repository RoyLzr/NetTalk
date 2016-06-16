#include "appReactor.h"
#include "appConn.h"

void ReactorAccept(int listenFd, short listenEv, void * arg)
{
    AppReactor * nrc = (AppReactor *)arg;
    if(nrc->isStop())
    {
        event lis = nrc->getListenEv();
        event_del(&lis);
        Log::NOTICE("SVR is STOP, don not accept");
        return;
    }

    struct sockaddr sa;
    socklen_t slen = sizeof(sa);
    int connfd = net_accept(listenFd, &sa, &slen);

    int maxConnected = nrc->getMaxConnected(); 
    in_addr ipaddr = ((struct sockaddr_in *)&sa)->sin_addr;
    char *peer_ip = inet_ntoa(ipaddr);

    if(connfd > maxConnected)
    {
        Log::ERROR("Too much user, connfd : %d", connfd);
        close(connfd);
        return;
    }
   
    AppConnManager * cMag = AppConnManager::getInstance();  

    if(cMag->IsConnExist(connfd))
    {
        Log::ERROR("assign a working fd, connfd : %d, will clean it", 
                   connfd);
    }

    struct bufferevent * bev;
    set_fd_noblock(connfd);
    bev = bufferevent_new(connfd, 
                          EvReadCallback, 
                          NULL, 
                          EvErrorCallback, 
                          nrc);
    bev->timeout_read = nrc->getReadTo();
    bev->timeout_write = nrc->getWriteTo();
    
    //bev->timeout_read = 1800;
    //bev->timeout_write = 1800; 
    bufferevent_enable(bev, EV_READ|EV_WRITE);    


    std::unique_ptr<Iconn> con(new NetConn(nrc, bev)); 
    cMag->setConn(connfd, std::move(con));

    /* use for test */
    //cMag->addAppConnFd(connfd); 

    Log::NOTICE("ACCEPT Connect SUCC, connfd : %d, UserIP : %s", connfd, peer_ip); 
}

void SendPacketRun(int fd, short event, void * arg)
{
    AppReactor * r = (AppReactor *)arg;
    r->SignalDeal();
}


void EvReadCallback(struct bufferevent * bev, void * arg)
{
    AppReactor * nrc = (AppReactor *)arg;
    int connfd = (bev->ev_read).ev_fd;
    AppConnManager * cMag = AppConnManager::getInstance();
    Iconn * conn =  cMag->getConn(connfd);
    if(conn != NULL) 
        conn->OnRead(NULL, 0);
    else
        Log::ERROR("buffer %d conn not exists match userconn", connfd);

    return;
}

void EvWriteCallback(struct bufferevent * bev,void * arg)
{
    printf("write callback %d\n", (bev->output)->off);
}

void EvErrorCallback(struct bufferevent * bev,
                     short  error, 
                     void * arg)
{
    int connfd = (bev->ev_read).ev_fd;
    AppReactor * nrc = (AppReactor *)arg;
    AppConnManager * cmag = AppConnManager::getInstance();

    if(error & EVBUFFER_EOF)
    {
        Log::NOTICE("Client close connection connfd: %d", connfd);
        if(cmag->IsConnExist(connfd))
            cmag->delConn(connfd);
        close(connfd);
    }
    else if(error & EVBUFFER_ERROR)
    {
        Log::WARN("connection error connfd: %d error: ", connfd, strerror(errno));
        if(cmag->IsConnExist(connfd))
            cmag->delConn(connfd);
        close(connfd);
    }
    else if(error & EVBUFFER_TIMEOUT)
    {
        printf("connection Timeout connfd %d\n", connfd);
        Log::WARN("connection Timeout connfd: %d", connfd);
        if(cmag->IsConnExist(connfd))
        { 
            cmag->delConn(connfd);
            printf("del succ connfd %d\n",connfd);
        }
        close(connfd);
    }
    return ;
}



AppReactor::AppReactor(const Section &sec) : _condWorkList(_lockWrokList)
{
    _status = IReactor::NONE;
    _port = (int)atoi((sec.get("listenPort").c_str()));
    _maxConnected = (int)atoi((sec.get("maxConnect").c_str()));
    maxConnected  = _maxConnected;
    _readTimeout = ((int)atoi(sec.get("readTimeout").c_str())); 
    _writeTimeout = ((int)atoi(sec.get("writeTimeout").c_str()));
    _threadnum   = ((int)atoi(sec.get("workThreadNum").c_str())); 
}


AppReactor::~AppReactor()
{}

int 
AppReactor::AppReactor::init()
{
    event_init();

    Log::NOTICE("Listen Port %d", _port);

    _listenFd = net_tcplisten(_port, 100);
    set_fd_noblock(_listenFd);

    event_set(&_listener, _listenFd, EV_READ|EV_PERSIST, ReactorAccept, this);
    event_add(&_listener, NULL);
   
    /*   listen send packet    */ 
    if(::pipe(_pipe) < 0)
    {
        Log::WARN("init send event error");
    }

    if(set_fd_noblock(_pipe[0]) < 0)
    {
        Log::WARN("PIPE NOBlock Error");    
        return -1;
    }
    if(set_fd_noblock(_pipe[1]) < 0)
    {
        Log::WARN("PIPE NOBlock Error");    
    }
    event_set(&_sendPacketEvent, _pipe[0], EV_READ|EV_PERSIST, SendPacketRun, this);
    event_add(&_sendPacketEvent, NULL);

}

int
AppReactor::run()
{
    printf("work thread num %d\n",_threadnum);
    _workThreadMa.run(_threadnum, TCALLBACK, this);
    _status = IReactor::RUNNING;
    event_dispatch();
}

int
AppReactor::Stop()
{
    _status = IReactor::STOP;
}

bool
AppReactor::isStop()
{
    AutoLock<MLock> l(_lockStatus);
    if(_status == IReactor::STOP)
        return true;
    return false;
}

int
AppReactor::status()
{
    return _status;
}

void
AppReactor::post(unique_ptr<Itask> task)
{
    _condWorkList.lock();
    while(IsTaskListFull())
    {
        Log::WARN("Block Queue is full :%d\n", _workTaskList.size());
        _condWorkList.wait(NULL);
    }
    _workTaskList.push_back(std::move(task));
    if(_condWorkList.waits() == 1)
        _condWorkList.signal();
    else if(_condWorkList.waits() > 1)
        _condWorkList.signalAll();

    _condWorkList.unlock();    
}

unique_ptr<Itask> 
AppReactor::pop()
{
    _condWorkList.lock();
    while(_workTaskList.size() == 0)
    {
        Log::DEBUG("Block Queue is empty\n");
        _condWorkList.wait(NULL);
    }
    unique_ptr<Itask> task = std::move(_workTaskList.front());
    _workTaskList.pop_front();
    if(_condWorkList.waits() == 1)
        _condWorkList.signal();
    else if(_condWorkList.waits() > 1)
        _condWorkList.signalAll();
    _condWorkList.unlock();

    return task;
}

void * 
AppReactor::TCALLBACK(void *p) 
{
    AppReactor * r = (AppReactor *)p;
    printf("one work thread start\n");
    r->workThreadCallBack();
    return NULL;
}


void 
AppReactor::workThreadCallBack()
{
    while(!isStop())
    {
        unique_ptr<Itask> task = std::move(pop());
        task->run();
    }
}

void
AppReactor::postSendPacket(SPacket_t packet)
{
    _lockSendList.lock();
    _sendPacketList.push_back(packet);
    _lockSendList.unlock(); 
}

SPacket_t
AppReactor::GetSendPacket()
{
    SPacket_t tmp;
    _lockSendList.lock();
    tmp = _sendPacketList.front();
    _sendPacketList.pop_front();
    _lockSendList.unlock();
    return tmp;
}

void
AppReactor::SignalDeal()
{
    do
    {
        char buf[64];
        int ret = ::read(_pipe[0],buf,sizeof(buf));
        if(ret < (int)sizeof(buf))
            break;
    }while(true);
    while(true)
    {
        _lockSendList.lock();
        if(_sendPacketList.empty())
        {
            _lockSendList.unlock();
            break;
        }
        SPacket_t p = _sendPacketList.front();
        _sendPacketList.pop_front();
        _lockSendList.unlock();
        /* begin send data */
        int connfd = p.connfd;
        AppConnManager * cMag = AppConnManager::getInstance();
        Iconn * conn =  cMag->getConn(connfd);
        if(conn != NULL) 
        {
            ImProto * tmp = (p.imData).get();
            conn->DelayWrite((void *)tmp->GetHeader(), ImProto::_headerlen);
            /*  for test */
            /*
            printf(" len %d \n", uint32_t(tmp->GetLength()));
            printf(" command %d \n", uint16_t(tmp->GetCommandID()));
            printf(" punch %d \n", uint16_t(tmp->GetPunch()));
            printf(" userid %d \n", uint32_t(tmp->GetUserID()));
            */
            
            string * data = tmp->GetBuffer();
            conn->DelayWrite((void *)data->c_str(), data->size()); 
            conn->OnWrite(NULL, 0); 
        }
    }
    
}


