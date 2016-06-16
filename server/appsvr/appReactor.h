#ifndef  _NETSVR_H_
#define  _NETSVR_H_

#include "../../interface/ireactor.h"
#include "../../common/net.h"
#include "../../common/asynLog.h"
#include "../../common/IMProto.h"
#include "../../common/lock.h"
#include "../../common/ThreadManager.h"
#include "../../interface/itask.h"
#include "../../proto/IM.Base.pb.h"
#include <event.h>
#include <vector>
#include <string>
#include <list>

#define MINWRITEDATA 0

using std::unique_ptr;

static int maxConnected = 500000;


typedef struct SPacket_t
{
    unique_ptr<ImProto> imData;
    int connfd;
    SPacket_t & operator=(SPacket_t &rhs)
    {
        if(this != &rhs)
        {
            imData = std::move(rhs.imData);
            connfd = rhs.connfd;
        }
        return *this;
    }
    SPacket_t() {}; 
    // bad choice
    SPacket_t(const SPacket_t &rhs)
    {
        SPacket_t * hack = const_cast<SPacket_t *>(&rhs);
        if(this != hack)
        {
            imData = std::move(hack->imData);
            connfd = rhs.connfd;
        }
        
    } 
} SPacket_t;



class AppReactor : public IReactor
{
    public:
        AppReactor(const Section &sec);
        virtual ~AppReactor();
    public:
        
        virtual int extCmd(const std::string ) {};

        virtual int init(); 
        
        virtual int run();
        
        virtual int Stop();
        
        virtual bool isStop();
        
        virtual int status();

        virtual void post(unique_ptr<Itask>);
        
        virtual void postSendPacket(SPacket_t);
        
        virtual SPacket_t GetSendPacket();
        
        virtual unique_ptr<Itask> pop();


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

        void Signal()
        {
            ::write(_pipe[1], "a", 1);
        }

        void SignalDeal(); 

        bool IsTaskListFull()
        {
           if(_workTaskList.size() > _maxTaskNum)
              return true;
          return false; 
        }

    protected:
        
        struct event          _listener;
        int                   _listenFd;
        MLock                 _lockStatus;
        int                   _status;
                                
        int                   _port;
        int                   _maxConnected;
        int                   _readTimeout;
        int                   _writeTimeout;
       
        /*  work Thread */
        MLock                 _lockWrokList; 
        MCondition            _condWorkList;
        std::list<unique_ptr<Itask> >  _workTaskList;
        ThreadManager _workThreadMa;
        int _threadnum;
        int _maxTaskNum;
        

        /* send list */
        MLock                 _lockSendList;
        std::list<SPacket_t>  _sendPacketList;
        int                   _pipe[2];
        struct event          _sendPacketEvent;



        static void * TCALLBACK(void *);
        virtual void workThreadCallBack();

};


void ReactorAccept(int, short, void *);

void SendPacketRun(int, short, void *);

void EvReadCallback(struct bufferevent *, void *);

void EvWriteCallback(struct bufferevent *,void *);

void EvErrorCallback(struct bufferevent *,short, void *);

#endif
