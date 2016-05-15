#ifndef   __AUDIO_SESSION_H_
#define   __AUDIO_SESSION_H_

#include "../interface/trans.h"
#include "../lib/jrtplib/rtpsession.h"
#include "../lib/jrtplib/rtpudpv4transmitter.h"
#include "../lib/jrtplib/rtpipv4address.h"
#include "../lib/jrtplib/rtpsessionparams.h"
#include "../lib/jrtplib/rtperrors.h"
#include "../lib/jrtplib/rtppacket.h"
#include "../lib/jrtplib/rtpsourcedata.h"
#include <alsa/asoundlib.h>  
#include <iostream>  
#include <unistd.h>  
#include <sys/types.h>   
#include <sys/socket.h>     
#include <string>     
#include <netinet/in.h>     


using namespace jrtplib;

struct AudioParams
{
    unsigned int rate;
    int channel;
    int frameSize;
    snd_pcm_uframes_t frames;
};

class AudioSession : public RTPSession
{
    public:
        AudioSession() : IncTimeStamp(1)
        {};

        virtual ~AudioSession() {};
        
        virtual int init(std::string, int, int,int);

    private:
        RTPSessionParams sessionparams;
        RTPUDPv4TransmissionParams  transparams;
        int IncTimeStamp;        
};

class AudioTrans : public Trans
{
    public:
        AudioTrans(); 
        
        virtual ~AudioTrans();

        virtual int init(std::string, int, int);
        
        virtual int SendData(void * data=NULL, int len=0);

        virtual int RecvData(void * data=NULL);

        virtual int GetLocalData(void * data=NULL);

        virtual int ShowLocalData(void * data=NULL, int len=0);

        virtual int Bye();

        virtual int Clear();
        
        virtual int setExtendInfo(void *);

        virtual bool checkParams();

    private:
        AudioSession session;
        AudioParams  playParams;
        AudioParams  recordParams;
        void * sendBuffer;
        void * playBuffer;
        int    buffSize;

        int  recordGetSize;
        int  playSize;

        int err;
        snd_pcm_t * handlePlay;
        snd_pcm_t * handleRecord;
        snd_pcm_hw_params_t * params;        
        
        std::string DestIP;
        int         DestPort;
        int         ListenPort;
};


#endif
