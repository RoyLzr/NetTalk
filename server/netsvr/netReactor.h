#ifndef  _NETSVR_H_
#define  _NETSVR_H_

#include "../../interface/ireactor.h"
#include "../../common/net.h"
#include "../../common/asynLog.h"
#include "../../common/IMProto.h"
#include "../../proto/IM.Base.pb.h"
#include <event.h>
#include <vector>
#include <string>

#define MINWRITEDATA 0

static int maxConnected = 500000;


class NetReactor : public IReactor
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
        int getReadTo()
        {
            return _readTimeout;
        }
        int getWriteTo()
        {
            return _writeTimeout;
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
        std::vector<string>   _fdUserName;
                                
        int                   _port;
        std::vector<string>   _logicIP;
        int                   _maxConnected;
        int                   _readTimeout;
        int                   _writeTimeout;
};


void ReactorAccept(int, short, void *);

void EvReadCallback(struct bufferevent *, void *);

void EvWriteCallback(struct bufferevent *,void *);

void EvErrorCallback(struct bufferevent *,short, void *);

#endif
