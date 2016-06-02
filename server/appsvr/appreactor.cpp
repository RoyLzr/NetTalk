#include "netReactor.h"

void ReactorAccept(int listenFd, short listenEv, void * arg)
{
    NetReactor * nrc = (NetReactor *)arg;
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

    struct bufferevent ** pool;
    pool = nrc->getFdPool();
    int maxConnected = nrc->getMaxConnected(); 
    in_addr ipaddr = ((struct sockaddr_in *)&sa)->sin_addr;
    char *peer_ip = inet_ntoa(ipaddr);

    if(connfd > maxConnected)
    {
        Log::ERROR("Too much user, connfd : %d", connfd);
        close(connfd);
        return;
    }
    
    if(pool[connfd] != NULL)
    {
        Log::ERROR("assign a working fd, connfd : %d, will clean it", 
                   connfd);
        bufferevent_free(pool[connfd]);
        pool[connfd] = NULL;
    }

    struct bufferevent * bev;
    set_fd_noblock(connfd);
    bev = bufferevent_new(connfd, 
                          EvReadCallback, 
                          NULL, 
                          EvErrorCallback, 
                          nrc);
    
    bev->timeout_read = 1800;
    bev->timeout_write = 1800;

    bufferevent_enable(bev, EV_READ|EV_WRITE);    
    pool[connfd] = bev;

    Log::NOTICE("ACCEPT Connect SUCC, connfd : %d, UserIP : %s", connfd, peer_ip); 
}

void EvReadCallback(struct bufferevent * bev, void * arg)
{
    NetReactor * nrc = (NetReactor *)arg;
    struct bufferevent ** pool;
    pool = nrc->getFdPool();

    if(nrc->isStop())
    {
        int connfd = (bev->ev_read).ev_fd;
        bufferevent_free(bev);
        pool[connfd] = NULL;
    }
    struct evbuffer * input = bev->input;
    if(EVBUFFER_LENGTH(input) > MINWRITEDATA)
        bufferevent_write_buffer(bev, input); 
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
    NetReactor * nrc = (NetReactor *)arg;
    struct bufferevent ** pool;
    pool = nrc->getFdPool();
    
    if(error & EVBUFFER_EOF)
    {
        Log::NOTICE("Client close connection connfd: %d", connfd);
        if(pool[connfd] != NULL)
        {
            bufferevent_free(pool[connfd]);
            pool[connfd] = NULL;
        }
        close(connfd);
    }
    else if(error & EVBUFFER_ERROR)
    {
        Log::WARN("connection error connfd: %d error: ", connfd, strerror(errno));
        if(pool[connfd] != NULL)
        {
            bufferevent_free(pool[connfd]);
            pool[connfd] = NULL;
        }
        close(connfd);
    }
    else if(error & EVBUFFER_TIMEOUT)
    {
        Log::WARN("connection Timeout connfd: %d", connfd);
        shutdown(connfd, SHUT_WR);
    }
    return ;
}



NetReactor::NetReactor(const Section &sec)
{
    _fdPool = NULL;
    _status = IReactor::NONE;
    _port = (int)atoi((sec.get("listenPort").c_str()));
    _maxConnected = (int)atoi((sec.get("maxConnect").c_str()));
    _logicIP.push_back(sec.get("logicSvr")); 
}


NetReactor::~NetReactor()
{
    if(_fdPool == NULL)
        return;

    for(int i = 0; i <_maxConnected; i++)
        if(_fdPool[i] != NULL)
        {
            bufferevent_free(_fdPool[i]);
            _fdPool[i] = NULL;
        }
    
    free(_fdPool);
}

int 
NetReactor::NetReactor::init()
{
    event_init();
    _fdPool = (struct bufferevent **) malloc(_maxConnected * 
                             sizeof(struct bufferevent *));

    for(int i = 0; i < _maxConnected; i++)
        _fdPool[i] = NULL;

    if(_fdPool == NULL) 
        return -1;
   
    Log::NOTICE("Listen Port %d", _port);

    _listenFd = net_tcplisten(_port, 100);
    set_fd_noblock(_listenFd);

    event_set(&_listener, _listenFd, EV_READ|EV_PERSIST, ReactorAccept, this);
    event_add(&_listener, NULL);
}

int
NetReactor::run()
{
    event_dispatch();
    _status = IReactor::RUNNING;
}

int
NetReactor::Stop()
{
    _status = IReactor::STOP;
}

bool
NetReactor::isStop()
{
    if(_status == IReactor::STOP)
        return true;
    return false;
}

int
NetReactor::status()
{
    return _status;
}
