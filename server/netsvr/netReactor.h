#ifndef  _NETSVR_H_
#define  _NETSVR_H_

#include "../../interface/ireactor.h"
#include "../../common/net.h"
#include "../../common/asynLog.h"
#include <event.h>
#include <vector>

#define MINWRITEDATA 0

class NetReactor
{
    public:
        NetReactor(const Section &sec);
        virtual ~NetReactor();
    public:
        
        virtual int extCmd(const std::string ) {};

        virtual int init(); 
        
        virtual int run();
        
        virtual int Stop();
        
        virtual bool isStop();
        
        virtual int status();
        
        struct bufferevent ** getFdPool()
        {
            return _fdPool;
        }
        int getMaxConnected()
        {
            return _maxConnected;
        }
        
        event getListenEv()
        {
            return _listener;
        }

    protected:
        
        struct event          _listener;
        struct bufferevent ** _fdPool;
        int                   _listenFd;
        int                   _status;
       
        int                   _port;
        std::vector<string>   _logicIP;
        int                   _maxConnected;
};


void ReactorAccept(int, short, void *);

void EvReadCallback(struct bufferevent *, void *);

void EvWriteCallback(struct bufferevent *,void *);

void EvErrorCallback(struct bufferevent *,short, void *);

#endif
