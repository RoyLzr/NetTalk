#include "appConn.h"
#include "appTask.h"

AppConnManager * AppConnManager::_connManager = NULL;

void testAppTaskHandle(ImProto * p, uint32_t connfd)
{
    IM::Log::IMLogInReq req;
    if(!req.ParseFromString(*(p->GetBuffer())))
    {
        Log::ERROR("Parse content data error");
    }

    std::cout << req.name() << std::endl;
    std::cout << req.password() << std::endl;  

}

int 
NetConn::OnRead(void * data, int len)
{
    printf("Read data from NETSVR\n");
    if(data != NULL)
        return -1;
    struct evbuffer * input = _bev->input;
    AppConnManager * cMag = AppConnManager::getInstance();
    int connfd = (_bev->ev_read).ev_fd; 

    if(_ract->isStop())
    {
        bufferevent_free(_bev);
        _bev = NULL;
        return 0; 
    }

    int validLen = 0;
    while(ImProto::IsProtoValid(input->buffer,
                                  input->off,
                                  &validLen))
    {
        
        int userid = ((ImPheader_t *)input->buffer)->user_id;
        validLen += ImProto::_headerlen;
        /*use for test */
        
        unique_ptr<Itask> task(new AppTask(connfd,
                                           _ract,
                                           (void*)input->buffer,
                                           validLen));     
        _ract->post(std::move(task));
        evbuffer_drain(input, validLen);
    }
    return 0; 
}


int
NetConn::OnWrite(void * data, int len)
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

int 
NetConn::DelayWrite(void * data, int len)
{
    struct evbuffer * output = _bev->output;
    evbuffer_add(output, data, len);
    return 0;
}

AppConnManager *
AppConnManager::getInstance()
{
    if(!_connManager)
    {
        _connManager = new AppConnManager();
        _connManager->init(); 
    }
    return _connManager;
}

void 
AppConnManager::init()
{
    _connPool.resize(maxConnected);
}

Iconn * 
AppConnManager::getConn(int idx)
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
AppConnManager::delConn(int idx)
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
AppConnManager::upConn(int idx, unique_ptr<Iconn> up)
{
    _connPool[idx] = std::move(up);
    return;
}

int
AppConnManager::setConn(int idx, unique_ptr<Iconn> up)
{
    if(_connPool[idx])
    {
        Log::WARN("want set %d conn, but exists");
    }
    _connPool[idx] = std::move(up);
    return 0;
}

