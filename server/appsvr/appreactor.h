#ifndef  _APPREACTOR_H_
#define  _APPREACTOR_H_

#include "../../interface/ireactor.h"
#include "../../common/net.h"
#include "../../common/asynLog.h"
#include "../../common/lock.h"
#include <event.h>
#include <vector>
#include <map>

#define MINWRITEDATA 0

/* use for record user addr and user login status*/
/* only online user exists in this map */
typedef map<string, string> UserAddrMap_t;

struct MutexBufferEvent
{
    bufferevent * bev;
    MLock         _writeLock; 
};

class APPReactor
{
    public:
        APPReactor(const Section &sec);
        virtual ~APPReactor();
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
        int                   _listenFd;
        int                   _status;
       
        int                   _port;
        int                   _maxConnected;
        int                   _threadNum;
};


void ReactorAccept(int, short, void *);

void EvReadCallback(struct bufferevent *, void *);

void EvWriteCallback(struct bufferevent *,void *);

void EvErrorCallback(struct bufferevent *,short, void *);

#endif
