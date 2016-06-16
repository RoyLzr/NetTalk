#include "netConn.h"

NetConnManager * NetConnManager::_connManager = NULL;

bool
UserConn::CheckSetUserId(int userId)
{
    if(_userId < 0)
    {
        if(userId>0)
            _userId = userId;
    }
    else
    {
        if(userId != _userId)
            return false;    
    }
    return true;
}

int
NetConnManager::getAppConnFd()
{
    if(_appConnIdx.size() == 0)
        return -1;
    static int flag = -1;
    if(flag < _appConnIdx.size()-1)
        flag ++;
    else
        flag = 0;
    return _appConnIdx[flag];
}



/* userID control transfer, APPSVR send data to control userID */

int 
UserConn::OnRead(void * data, int len)
{
    printf("Read data from userConn\n");
    if(data != NULL)
        return -1;
    struct evbuffer * input = _bev->input;
    struct evbuffer * output = _bev->output;
    NetConnManager * cMag = NetConnManager::getInstance();
    int connfd = (_bev->ev_read).ev_fd; 

    if(_ract->isStop())
    {
        bufferevent_free(_bev);
        _bev = NULL;
        return 0; 
    }

    if(_appFd < 0)
    {
        _appFd = cMag->getAppConnFd();
        Log::DEBUG("User first attack netSVr, is alloc to appSvr %d ", _appFd);
    } 
    Iconn * appConn = cMag->getConn(_appFd);

    int validLen = 0;
    int dealNum = 0;
    while(ImProto::IsProtoValid(input->buffer,
                                  input->off,
                                  &validLen))
    {
        dealNum++;
        if(IsKeepAlivePacket(input->buffer))
        {
            Log::DEBUG("RECV Client keep alive packet");
            evbuffer_drain(input, ImProto::_headerlen);
            return 0;
        }
        
        int userid = ((ImPheader_t *)input->buffer)->user_id;
        ((ImPheader_t *)input->buffer)->punch_flag = connfd;
        validLen += ImProto::_headerlen;
        
        //printf("write = %d buff=%d\n" ,validLen,input->off);
          
        appConn->DelayWrite(input->buffer, validLen);
        evbuffer_drain(input, validLen);
      
    }
    if(dealNum > 0)
        appConn->OnWrite(NULL, 0);

    return 0; 
}

int
UserConn::DelayWrite(void *data, int len)
{
    struct evbuffer * output = _bev->output;
    evbuffer_add(output, data, len);
}

int
UserConn::OnWrite(void * data, int len)
{
    printf("write data to user conn\n");
    if(data == NULL && (_bev->output)->off > 0)
    {
        int res = write((_bev->ev_read).ev_fd,
                        (char *)(_bev->output)->buffer,
                        (_bev->output)->off);
        if(res > 0)
            evbuffer_drain(_bev->output, res);

        if((_bev->output)->off > 0)
        {
            struct timeval tv, *ptv = NULL;
            if(_bev->timeout_write)
            {
                tv.tv_sec = _bev->timeout_write;
                tv.tv_usec = 0;
                ptv = &tv;
            }
            event_add(&_bev->ev_write, ptv);
        }
        else
        {
            printf("user once send success\n");
            return 0;
        }
    }
    else
        bufferevent_write(_bev,(char *)data,len);

    return 0;
}

NetConnManager *
NetConnManager::getInstance()
{
    if(!_connManager)
    {
        _connManager = new NetConnManager();
        _connManager->init(); 
    }
    return _connManager;
}

void 
NetConnManager::init()
{
    _connPool.resize(maxConnected);
}

Iconn * 
NetConnManager::getConn(int idx)
{
    Iconn * res = NULL;
    if(!_connPool[idx])
    {
        Log::WARN("want get %d conn, but it is empty");
    }
    else
        res = (_connPool[idx]).get();

    return res;
}

int 
NetConnManager::delConn(int idx)
{
    if(!_connPool[idx])
    {
        Log::WARN("want del %d conn, but it is empty");
        return -1;
    }
    if(_connPool[idx]->release() > 0)
        return 1;
    _connPool[idx].reset();
    return 0;
}

void
NetConnManager::upConn(int idx, unique_ptr<Iconn> up)
{
    _connPool[idx] = std::move(up);
    return;
}

int
NetConnManager::setConn(int idx, unique_ptr<Iconn> up)
{
    if(_connPool[idx])
    {
        Log::WARN("want set %d conn, but exists");
    }
    _connPool[idx] = std::move(up);
    return 0;
}

bool
UserConn::IsKeepAlivePacket(void * imhead)
{
    if(((ImPheader_t *)imhead)->length == 0&&
      ((ImPheader_t *)imhead)->command_id==IM::Base::UTIL_KEEP_ALIVE) 
        return true;
    return false;
}

void 
AppConn::SendLogOutToApp()
{
    return;
}

int
AppConn::OnRead(void * data, int len)
{

    printf("read data from appConn\n");

    if(data != NULL)
        return -1;
    struct evbuffer * input = _bev->input;
    NetConnManager * cMag = NetConnManager::getInstance();

    if(_ract->isStop())
    {
        bufferevent_free(_bev);
        _bev = NULL;
        return 0; 
    }

    int validLen = 0;
    int dealUserNum = 0;
    int dealAppNum = 0;
    while(ImProto::IsProtoValid(input->buffer,
                              input->off,
                              &validLen))
    {
    
        int userid = ((ImPheader_t *)input->buffer)->user_id;
        validLen += ImProto::_headerlen;
        int userFd = ((ImPheader_t *)input->buffer)->punch_flag;
        int sendCloseFlag = 0;
        UserConn * userConn = NULL;

        if(!cMag->IsUserConnExist(userFd))
        {
            Log::WARN("User conn %d has benn closed", userFd);
            sendCloseFlag = 1;
        }
        else
        {
            userConn = (UserConn *)cMag->getConn(userFd);
        }

        if(!sendCloseFlag)
        {
            /* flag need OnWrite */
            userConn->DelayWrite(input->buffer, validLen);
            userConn->OnWrite(NULL, 0);
            evbuffer_drain(input, validLen);
        }
        else
        {
            Log::NOTICE("This Conn closed, close userid %d", userid);
            /*flag need app OnWrite*/
            dealAppNum++; 
            ImPheader_t head;
            head.length = 0;
            head.command_id = IM::Base::CID_LOGIN_REQ_USERLOGOUT;
            head.punch_flag = userFd;
            head.user_id    = userid;
            
            DelayWrite((void *)&head, sizeof(head)); 
        }

    }
    if(dealAppNum > 0)
        OnWrite(NULL, 0);
    
    return 0;
}


int
AppConn::DelayWrite(void *data, int len)
{
    struct evbuffer * output = _bev->output;
    evbuffer_add(output, data, len);
}

int
AppConn::OnWrite(void * data, int len)
{
    printf("write data to appSVR conn\n");
    if(data == NULL && (_bev->output)->off > 0)
    {
        int res = write((_bev->ev_read).ev_fd,
                        (char *)(_bev->output)->buffer,
                        (_bev->output)->off);
        if(res > 0)
            evbuffer_drain(_bev->output, res);

        if((_bev->output)->off > 0)
        {
            struct timeval tv, *ptv = NULL;
            if(_bev->timeout_write)
            {
                tv.tv_sec = _bev->timeout_write;
                tv.tv_usec = 0;
                ptv = &tv;
            }
            event_add(&_bev->ev_write, ptv);
        }
        else
        {
            printf("send to app once success\n");
            return 0;
        }
    }
    else
        bufferevent_write(_bev,(char *)data,len);

    return 0;
}

int
AppConn::release()
{
    int fd = (_bev->ev_read).ev_fd;
    close(fd);
    int reFd = socket(AF_INET, SOCK_STREAM, 0);
    fd = dup2(reFd, fd);
   
    struct sockaddr_in appAddress;
    set_tcp_sockaddr(_ip.c_str(),
                     _port,
                     &appAddress); 

    std::cout << _ip <<std::endl;
    std::cout << _port << std::endl;

    printf("begin try to reconnected %d\n", fd);
    int res = net_connect_to_ms(fd,
                               (struct sockaddr *)&appAddress,
                                sizeof(appAddress),
                               1000, 1); 
    if(res < 0)
    {
       printf("FAIL try to reconnect appSvr fail %s\n", strerror(errno));
       NetConnManager * cmag = NetConnManager::getInstance();
       cmag->eraseAppConn(fd);

       return 0;
    }

    /*fresh  bufferevent*/
    bufferevent_free(_bev);
    _bev = bufferevent_new(fd,
                           EvReadCallback,
                           NULL,
                           EvErrorCallback,
                           _ract);
    
    _bev->timeout_read = 1800;
    _bev->timeout_write = 1800;
    bufferevent_enable(_bev, EV_READ|EV_WRITE); 
    printf("reconnect appSvr succ %d\n", res);
    return 1; 
}

