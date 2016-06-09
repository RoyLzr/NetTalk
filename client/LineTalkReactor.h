#ifndef  __LINE_TALK_REACTOR_H_
#define  __LINE_TALK_REACTOR_H_

#include "../common/net.h"
#include "../interface/ireactor.h"
#include "../common/lock.h"
#include "../interface/trans.h"
#include "../interface/thread.h"
#include "../interface/dataParse.h"
#include "../interface/cmdWrap.h"
#include "../interface/thread.h"
#include "../common/IMProto.h"
#include "../proto/IM.Test.pb.h"
#include "ClientCmd.h"
#include <atomic>
#include <vector>
#include <queue>
#include <event.h>
#include <memory>



class ClientSvr;
class LineTalkReactor : public IReactor,public Uncopyable
{
    public:
        enum
        {
            AUDIOINIT,
            AUDIORUN,
            AUDIOSTOP,
        };
        enum
        {
            UNUSE,
            USERREGINPUT,
            USERREGING,
            USERLOGINPUT,
            USERLOGING,
            USERLOGED,
        };

        LineTalkReactor(std::shared_ptr<DataParser> svr,
                        std::shared_ptr<DataParser> user, 
                        const Section &sec):  _fd(-1),
                                              _status(NONE),
                                              _audioStatus(AUDIOSTOP),
                                              _conPort(-1),
                                              _conTo(-1),
                                              _svrdata(std::move(svr)),
                                              _userdata(std::move(user)),
                                              _client(NULL),
                                              _audio(NULL),
                                              _AudioRecvThread(NULL),
                                              _AudioSendThread(NULL),
                                              _audioPort(0),
                                              _svrBufLen(0),
                                              _svrBufCap(0),
                                              _userStatus(UNUSE)
        {  load(sec); }
                                             
        virtual ~LineTalkReactor();

        virtual int load(const Section &);
        
    public:
        virtual int init();

        virtual int Stop();
		
        virtual int run();

		virtual int status();

        virtual int extCmd(const string );
        
        virtual int extSvrRes();
        virtual int readSvrRes();
        virtual int dealSvrError(int);
        
        virtual bool isStop();
        
        virtual int setClient(ClientSvr *);
        
        virtual void Signal(unique_ptr<CMD>);
        
        virtual void SignalDeal();
        
        virtual int setAudioSession(Trans *);
        virtual Trans * getAudioSession();
        
        virtual int setAudioSendThread(WorkerThread *);
        virtual WorkerThread* getAudioSendThread();
        
        virtual int setAudioRecvThread(WorkerThread *);
        virtual WorkerThread * getAudioRecvThread();

        virtual int clearAudio();
        virtual int expandSvrBuf();
        
        virtual int getAudioStatus() {return _audioStatus;}
        virtual int setAudioStatus(int s) {_audioStatus = s;}

        virtual int getSvrFd()  {return _fd;}
        
        virtual int getUserStatus() {return _userStatus;}

        virtual void setUserStatus(int s) {_userStatus = s;}
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
        int  _conTo;
        int  _pipe[2];
        MLock _q_lock;
        std::queue<std::unique_ptr<CMD> > _extQueue;
        int            _userStatus;

        Trans        * _audio;
        WorkerThread * _AudioSendThread;
        WorkerThread * _AudioRecvThread;
        int            _audioPort;
        int            _audioStatus;


        std::unique_ptr<char[]>   _svrBuf;
        int                     _svrBufLen; 
        int                     _svrBufCap;
        ImProto                 _svrData; 

        MLock _lock;
        shared_ptr<DataParser>  _svrdata;
        shared_ptr<DataParser>  _userdata;
        ClientSvr  * _client;
};

#endif
