#include "appConn.h"

NetConnManager * NetConnManager::_connManager = NULL;

bool
UserConn::CheckSetUserId(int userId)
{
    if(_userId <= 0)
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
    if(flag == _appConnIdx.size())
        flag = 0;
    else
        flag++;
    return _appConnIdx[flag];
}


int 
UserConn::OnRead(void * data, int len)
{
    printf("Read data from NETSVR\n");
    if(data != NULL)
        return -1;
    struct evbuffer * input = _bev->input;
    NetConnManager * cMag = NetConnManager::getInstance();
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
        ImProto data;
        data.InitByHeaderAddBuf((void *)input->buffer,
                                validLen);

        IM::Log::IMLogInReq req;
        if(!req.ParseFromString(*(data.GetBuffer())))
        {
            Log::ERROR("Parse content data error");
        }

        std::cout << req.name() << std::endl;
        std::cout << req.password() << std::endl;  
           
        evbuffer_drain(input, validLen);
    }
    return 0; 
}


int
UserConn::OnWrite(void * data, int len)
{
    printf("write data to user conn\n");
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
            if(userConn->getUserId() != userid && userid>0) 
            {
                sendCloseFlag = 1;
                Log::WARN("AppSvr req userId error");
            }
        }

        if(!sendCloseFlag)
        {
            userConn->OnWrite(input->buffer, validLen);
            evbuffer_drain(input, validLen);
        }
        else
        {
            Log::NOTICE("This Conn closed, close userid %d", userid);
            
            ImPheader_t head;
            head.length = 0;
            head.command_id = IM::Base::CID_LOGIN_REQ_USERLOGOUT;
            head.punch_flag = userFd;
            head.user_id    = userid;
            
            OnWrite((void *)&head, sizeof(head)); 
        }

    }
    return 0;
}

int 
AppConn::OnWrite(void * data, int len)
{
    printf("write data to appConn\n");
    bufferevent_write(_bev,
                     (char *)data,
                      len);
    return 0;
}


