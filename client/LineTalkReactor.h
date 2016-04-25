#ifndef  __LINE_TALK_REACTOR_H_
#define  __LINE_TALK_REACTOR_H_

#include "../common/net.h"
#include "../interface/ireactor.h"
#include <atomic>
#include <vector>
#include <queue>
#include "../common/lock.h"
#include "../interface/trans.h"
#include "../interface/dataParse.h"
#include "../interface/cmdWrap.h"
#include "../interface/thread.h"



class ClientSvr;
class LineTalkReactor : public IReactor
{
    public:
        LineTalkReactor(DataParser * svr, 
                        const Section &sec):  _fd(-1),
                                              _status(NONE),
                                              _conPort(-1),
                                              _conTo(-1),
                                              _trans(NULL),
                                              _svrdata(svr)
        {  load(sec); };
                                             

        virtual ~LineTalkReactor();

        virtual int load(const Section &);
        
    public:
        virtual int init();

        virtual int stop();
		
        virtual int run();

		virtual int status();

        virtual int extCmd(const string &);
        
        virtual int setClient(ClientSvr *);

    protected:

        virtual int OnRead();

        virtual int OnWrite();

        virtual int OnWork();

        virtual int ReadData();

        virtual int SendData();
        
        virtual int GetTrans(int );
        
    protected:
        int  _fd;
        int  _status;
        string  _conIP;
        int  _conPort;
        int  _conTo;
        int  _pipe[2];
        MLock _q_lock;
        std::queue<CMD *> _extQueue;

        Trans * _trans;
        int     _transPort;
        Mlock _lock;
        DataParser * _svrdata;
        ClientSvr  * _client;
};

#endif
