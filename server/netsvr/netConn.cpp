#include "netConn.h"

NetConnManager * NetConnManager::_connManager = NULL;

bool
UserConn::CheckSetUserId(int userId)
{
    return true;
}

int
NetConnManager::getAppConnFd()
{
    if(_appConnIdx.size() == 0)
        return -1;
    static int flag = -1;
    if(flag == _appConnIdx.size())
        flag = 0;
    else
        flag++;
    return _appConnIdx[flag];
}


int 
UserConn::OnRead(void * data, int len)
{
    if(data != NULL)
        return -1;
    struct evbuffer * input = _bev->input;
    NetConnManager * cMag = NetConnManager::getInstance();
    int connfd = (_bev->ev_read).ev_fd; 

    if(_ract->isStop())
    {
        bufferevent_free(_bev);
        _bev = NULL; 
    }

    int validLen = 0;
    if(!ImProto::IsProtoValid(input->buffer,
                              input->off,
                              &validLen))
        return 0;

    if(IsKeepAlivePacket(input->buffer))
    {
        Log::DEBUG("RECV Client keep alive packet");
        evbuffer_drain(input, ImProto::_headerlen);
        return 0;
    }
    
    validLen += ImProto::_headerlen;
    printf("write = %d buff=%d\n" ,validLen,input->off);
    if(_appFd < 0)
    {
        _appFd = cMag->getAppConnFd();
        Log::DEBUG("User first attack netSVr, is alloc to appSvr %d ", _appFd);
    } 
    
    Iconn * appConn = cMag->getConn(_appFd);
    appConn->OnWrite(input->buffer, validLen);
    evbuffer_drain(input, validLen);
    
    return 0; 
}


int
UserConn::OnWrite(void * data, int len)
{
    bufferevent_write(_bev,
                     (char *)data,
                     len);
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


