#ifndef  _NETCONN_H_
#define  _NETCONN_H_

#include "../../interface/iconn.h"
#include "../../proto/IM.Base.pb.h"
#include "netReactor.h"
#include <memory>
#include <list>

using namespace std;

class NetConnManager
{
    public:

        virtual ~NetConnManager() {};
       
        static NetConnManager * getInstance();

        Iconn * getConn(int );
        
        void    init();

        int  delConn(int );  
        
        void  upConn(int , unique_ptr<Iconn>);  
        
        int  setConn(int , unique_ptr<Iconn>);  

        int getAppConnFd();
        
        int addAppConnFd(int fd)
        {
            _appConnIdx.push_back(fd);
        }

        bool IsUserConnExist(int idx)
        {
            if(_connPool[idx])
                return true;
            return false;
        }

        bool eraseAppConn(int idx)
        {
            std::vector<int>::iterator it = _appConnIdx.begin();
            for(; it != _appConnIdx.end(); it++)
                if(*it == idx)
                    break;
            if(it != _appConnIdx.end())
                _appConnIdx.erase(it);
            return true;
        }

    private:
        NetConnManager() {};
        vector<unique_ptr<Iconn> > _connPool;
        vector<int>                _appConnIdx;
        static NetConnManager *    _connManager; 
};



class UserConn : public Iconn
{
    public:
        UserConn(NetReactor *r,
                 struct bufferevent * b) : _ract(r),
                                           _userId(-1),
                                           _bev(b),
                                           _appFd(-1)
        {};

        virtual int OnRead(void *, int);

        virtual int OnWrite(void *, int);
        
        virtual int DelayWrite(void *, int);
        
        virtual bool IsKeepAlivePacket(void *);

        virtual bool CheckSetUserId(int userId);

        virtual void setAppFd(int fd) {_appFd = fd;} 

        virtual int release() {return 0;}

        int getUserId() {return _userId;}
        virtual ~UserConn() 
        {
            if(!_bev)
                bufferevent_free(_bev);
            _bev = NULL;
        };

    protected:

        NetReactor          *   _ract;
        int                     _userId;
        int                     _appFd;
        struct bufferevent  *   _bev;
};

class AppConn : public UserConn
{
    public:
        AppConn(NetReactor *r,
                struct bufferevent *b,
                string ip,
                int    port) : UserConn(r,b),
                               _ip(ip),
                               _port(port)
        {};
        virtual int OnRead(void *, int);

        virtual int OnWrite(void *, int);
        
        virtual int DelayWrite(void *, int);
        
        virtual int release();
        
        virtual int SendLogOutToApp();

    protected:
        string _ip;
        int    _port;
};


#endif
