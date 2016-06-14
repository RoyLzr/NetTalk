#ifndef  _NETCONN_H_
#define  _NETCONN_H_


#include "../../interface/iconn.h"
#include "../../proto/IM.Base.pb.h"
#include "../../proto/IM.Log.pb.h"
#include "appReactor.h"
#include <memory>


using namespace std;

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
        
        virtual bool IsKeepAlivePacket(void *);

        virtual bool CheckSetUserId(int userId);

        virtual void setAppFd(int fd) {_appFd = fd;} 

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
                struct bufferevent *b) : UserConn(r,b)
        {};
        virtual int OnRead(void *, int);

        virtual int OnWrite(void *, int);
};


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

    private:
        NetConnManager() {};
        vector<unique_ptr<Iconn> > _connPool;
        vector<int>                _appConnIdx;
        static NetConnManager * _connManager; 
};





#endif
