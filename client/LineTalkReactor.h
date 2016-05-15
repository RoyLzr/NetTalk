#ifndef  __LINE_TALK_REACTOR_H_
#define  __LINE_TALK_REACTOR_H_

#include "../common/net.h"
#include "../interface/ireactor.h"
#include "../common/lock.h"
#include "../interface/trans.h"
#include "../interface/dataParse.h"
#include "../interface/cmdWrap.h"
#include "../interface/thread.h"
#include <atomic>
#include <vector>
#include <queue>



class ClientSvr;
class LineTalkReactor : public IReactor
{
    public:
        LineTalkReactor(DataParser * svr,
                        DataParser * user, 
                        const Section &sec):  _fd(-1),
                                              _status(NONE),
                                              _conPort(-1),
                                              _conTo(-1),
                                              _trans(NULL),
                                              _svrdata(svr),
                                              _userdata(user),
                                              _client(NULL)
        {  load(sec); }
                                             
        virtual ~LineTalkReactor();

        virtual int load(const Section &);
        
    public:
        virtual int init();

        virtual int Stop();
		
        virtual int run();

		virtual int status();

        virtual int extCmd(const string &);
        
        virtual bool isStop();
        
        virtual int setClient(ClientSvr *);

    protected:

        virtual int OnRead() {}; 

        virtual int OnWrite() {};

        virtual int OnWork() {};

        virtual int ReadData() {};

        virtual int SendData() {};
        
        virtual int GetTrans(int ) {};
        
    protected:
        int  _fd;
        size_t  _status;
        string  _conIP;
        size_t  _conPort;
        size_t  _conTo;
        int  _pipe[2];
        MLock _q_lock;
        std::queue<CMD *> _extQueue;

        MLock _lock;
        DataParser * _svrdata;
        DataParser * _userdata;
        ClientSvr  * _client;
};

#endif
