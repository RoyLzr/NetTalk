#include "AudioSession.h"

int AudioSession::init(std::string dip, 
                       int dport, 
                       int lport,
                       int rate)
{
    uint32_t bufIp = inet_addr(dip.c_str());
    bufIp = ntohl(bufIp);
    
    transparams.SetPortbase(lport);
    sessionparams.SetAcceptOwnPackets(true);
    sessionparams.SetOwnTimestampUnit(1.0/(double)rate);

    int status;

    if((status = Create(sessionparams, &transparams)) < 0)
    {
        std::cout << RTPGetErrorString(status) << std::endl;
        return -1;
    }
    
    RTPIPv4Address addr(bufIp, dport);
    AddDestination(addr);
    SetDefaultPayloadType(96);
    SetDefaultMark(false);
    //TODO : init timestamp uint and timestampIncrement
    return 0;
}


AudioTrans::AudioTrans() 
{
    memset((void *)&playParams, 0, sizeof(AudioParams));
    memset((void *)&recordParams, 0, sizeof(AudioParams));
}
        
AudioTrans::~AudioTrans()
{
    snd_pcm_drain(handlePlay);  
    snd_pcm_close(handlePlay);  
    snd_pcm_drain(handleRecord);  
    snd_pcm_close(handleRecord);  
}

int AudioTrans::init(std::string ip, int dport, int lport)
{
   
    /* init auido params*/
    recordParams.rate    = 8000;
    recordParams.channel = 1;
    recordParams.frameSize = 2*recordParams.channel;
    recordParams.frames    = 64;
    
    /* init transmitter */
    DestIP     = ip;
    DestPort   = dport;
    ListenPort = lport;
    session.init(ip, dport, lport, recordParams.rate);


    if ((err = snd_pcm_open(&handlePlay, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0) 
    {
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }

    if ((err = snd_pcm_open(&handleRecord, "default", SND_PCM_STREAM_CAPTURE, 0)) < 0) 
    {                
        printf("capture open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);

    }

    /* set record*/
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(handleRecord, params);
    snd_pcm_hw_params_set_access(handleRecord, params,
        SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(handleRecord,params,SND_PCM_FORMAT_U8);
    snd_pcm_hw_params_set_channels(handleRecord, params, recordParams.channel);
    int dir;
    snd_pcm_hw_params_set_rate_near(handleRecord, params, &recordParams.rate, &dir);

    snd_pcm_hw_params_set_period_size_near(handleRecord, params, &recordParams.frames, &dir);
        
    int res = snd_pcm_hw_params(handleRecord, params);

    buffSize = 20*(recordParams.frames * recordParams.frameSize);  

    if(playParams.rate == 0)
       playParams = recordParams;

    /* set play */
    if ((err = snd_pcm_set_params(handlePlay,
                              SND_PCM_FORMAT_U8,
                              SND_PCM_ACCESS_RW_INTERLEAVED,
                              playParams.channel,
                              playParams.rate,
                              1,
                              500000)) < 0) 
    {   
        printf("Playback open error: %s\n", snd_strerror(err));
        exit(EXIT_FAILURE);
    }
    
    /* session timestamp*/
    session.SetDefaultTimestampIncrement(2*recordParams.frames); 


    /*init buffer*/
    std::unique_ptr<char[]> tmpSend(new char[buffSize]);
    sendBuffer = std::move(tmpSend);
    
    if(!sendBuffer)
    {
        std::cout << "init malloc error" << std::endl;    
        return -1;
    }
    
    //std::unique_ptr<char[]> tmpPlay(new char[buffSize]);
    //playBuffer = std::move(tmpPlay);
    /*
    if(!playBuffer)
    {
        std::cout << "init malloc error" << std::endl;    
        return -1;
    }
    */

    return 0;
}

int AudioTrans::SendData(void * data, int len)
{
    if(data != NULL)
        return -1;
    
    int status = session.SendPacket(sendBuffer.get(), 
                                    recordGetSize*recordParams.frameSize);

    if(status < 0)
    {
        std::cout << RTPGetErrorString(status) << std::endl;
        return -1;
    }
    return 0;
}

int AudioTrans::RecvData(void * data)
{
    if(data != NULL)
        return -1;
    RTPTime rtcpdelay = session.GetRTCPDelay();
    int status;
    if(status = session.WaitForIncomingData(rtcpdelay) < 0)
    {
        std::cout << "None data coming, timeout" << std::endl;
           return -1;
    }
    else
    {
        if((status = session.Poll()) < 0)
        {
            std::cout << "get data error" << std::endl;
            return -1;
        }
    }
    return 0;
}

int AudioTrans::GetLocalData(void * data)
{
    if(data != NULL)
        return -1;
    int rc = snd_pcm_readi(handleRecord,sendBuffer.get(),2*recordParams.frames);

    if(rc == -EPIPE)
    {
        snd_pcm_prepare(handleRecord);
    }
    else if(rc < 0)
    {
        std::cout << snd_strerror(rc) << std::endl;
    }
    else if(rc != (2*recordParams.frames))
    {
        std::cout << "short read " << rc << std::endl;
    }
    recordGetSize = rc;
    return rc;
}

int AudioTrans::ShowLocalData(void * data, int len)
{
    if(data != NULL)
        return -1;
    if(session.GotoFirstSourceWithData())
    {
        do
        {
            RTPPacket * pack;
            while((pack = session.GetNextPacket()) != 0)
            {
                playBuffer = pack->GetPayloadData();
                playSize   = pack->GetPayloadLength();
                
                printf("play %d\n", playSize);

                int prc = snd_pcm_writei(handlePlay, 
                                  playBuffer,
                                 (playSize/playParams.frameSize));
                
                if(prc == -EPIPE)
                {
                    snd_pcm_prepare(handlePlay);
                    std::cout << "play xrun error" << std::endl;
                }
                else if(prc < 0)
                {
                    std::cout << snd_strerror(prc) << std::endl;
                }
                session.DeletePacket(pack);
           }
       }while(session.GotoNextSourceWithData());
   }
    return 0;
}

int AudioTrans::Bye() { return 0;}

int AudioTrans::Clear() {return 0;}
        
int AudioTrans::setExtendInfo(void *) {return 0;}

bool AudioTrans::checkParams() {return 0;}

