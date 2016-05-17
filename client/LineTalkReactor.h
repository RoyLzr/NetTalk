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
#include "ClientCmd.h"
#include <atomic>
#include <vector>
#include <queue>



class ClientSvr;
class LineTalkReactor : public IReactor
{
    public:
        enum
        {
            AUDIOINIT,
            AUDIORUN,
            AUDIOSTOP,
        };

        LineTalkReactor(DataParser * svr,
                        DataParser * user, 
                        const Section &sec):  _fd(-1),
                                              _status(NONE),
                                              _audioStatus(AUDIOSTOP),
                                              _conPort(-1),
                                              _conTo(-1),
                                              _svrdata(svr),
                                              _userdata(user),
                                              _client(NULL),
                                              _audio(NULL),
                                              _AudioRecvThread(NULL),
                                              _AudioSendThread(NULL),
                                              _audioPort(0)
        {  load(sec); }
                                             
        virtual ~LineTalkReactor();

        virtual int load(const Section &);
        
    public:
        virtual int init();

        virtual int Stop();
		
        virtual int run();

		virtual int status();

        virtual int extCmd(const string );
        
        virtual bool isStop();
        
        virtual int setClient(ClientSvr *);
        
        virtual void Signal(CMD *);
        
        virtual void SignalDeal();
        
        virtual int setAudioSession(Trans *);
        virtual Trans * getAudioSession();
        
        virtual int setAudioSendThread(WorkerThread *);
        virtual WorkerThread* getAudioSendThread();
        
        virtual int setAudioRecvThread(WorkerThread *);
        virtual WorkerThread * getAudioRecvThread();

        virtual int clearAudio();
        virtual int getAudioStatus() {return _audioStatus;}
        virtual int setAudioStatus(int s) {_audioStatus = s;}

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
        std::queue<CMD *> _extQueue;
        
        Trans        * _audio;
        WorkerThread * _AudioSendThread;
        WorkerThread * _AudioRecvThread;
        int            _audioPort;
        int            _audioStatus;

        MLock _lock;
        DataParser * _svrdata;
        DataParser * _userdata;
        ClientSvr  * _client;
};

#endif
