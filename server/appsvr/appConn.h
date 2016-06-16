#ifndef  _NETCONN_H_
#define  _NETCONN_H_


#include "../../interface/iconn.h"
#include "../../proto/IM.Base.pb.h"
#include "../../proto/IM.Log.pb.h"
#include "model/RelationModel.h"
#include "model/UserModel.h"
#include "appReactor.h"
#include <memory>


using namespace std;

class NetConn : public Iconn
{
    public:
        NetConn(AppReactor *r,
                 struct bufferevent * b) : _ract(r),
                                           _bev(b)
        {};

        virtual int OnRead(void *, int);

        virtual int OnWrite(void *, int);
        
        virtual int DelayWrite(void *, int);
        
        virtual ~NetConn() 
        {
            if(!_bev)
                bufferevent_free(_bev);
            _bev = NULL;
        };

    protected:

        AppReactor          *   _ract;
        struct bufferevent  *   _bev;
};


class AppConnManager
{
    public:
        virtual ~AppConnManager() {};
       
        static AppConnManager * getInstance();

        Iconn * getConn(int );
        
        void    init();

        int  delConn(int );  
        
        void  upConn(int , unique_ptr<Iconn>);  
        
        int  setConn(int , unique_ptr<Iconn>);  
        
        bool IsConnExist(int idx)
        {
            if(_connPool[idx])
                return true;
            return false;
        }

    private:
        AppConnManager() {};
        vector<unique_ptr<Iconn> > _connPool;
        static AppConnManager * _connManager; 
};





#endif
