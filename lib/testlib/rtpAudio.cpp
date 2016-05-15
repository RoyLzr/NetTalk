#include "../jrtplib/rtpsession.h"
#include "../jrtplib/rtpudpv4transmitter.h"
#include "../jrtplib/rtpipv4address.h"
#include "../jrtplib/rtpsessionparams.h"
#include "../jrtplib/rtperrors.h"
#include "../jrtplib/rtppacket.h"
#include "../jrtplib/rtpsourcedata.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <alsa/asoundlib.h>  
#include <unistd.h>  
#include <sys/types.h> /* basic system data types */  
#include <sys/socket.h>   /* basic socket definitions */  
#include <netinet/in.h>   /* sockaddr_in{} and other Internet defns */  
#include <arpa/inet.h>    /* inet(3) functions */  

using namespace jrtplib; 

class AudioSession : public RTPSession
{
    public:
        AudioSession(int Port1, std::string ip, int Port2) : DesPort(Port1),
                                                          Desip(ip),
                                                          listenPort(Port2)
        {};

        virtual ~AudioSession() {};

        void Init()
        {

            /* base params*/
            rate = 8000;
            channel = 1;
            frameSize = 2*channel;
            frames = 64;
            sendBuffer = NULL;
            playBuffer = NULL;

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
        
            /* set record params*/
            snd_pcm_hw_params_alloca(&params);
            snd_pcm_hw_params_any(handleRecord, params);
            snd_pcm_hw_params_set_access(handleRecord, params,
                SND_PCM_ACCESS_RW_INTERLEAVED);
            snd_pcm_hw_params_set_format(handleRecord,params,SND_PCM_FORMAT_U8);
            snd_pcm_hw_params_set_channels(handleRecord, params, channel);
            int dir;
             
            snd_pcm_hw_params_set_rate_near(handleRecord, params, &rate, &dir);

            snd_pcm_hw_params_set_period_size_near(handleRecord, params, &frames, &dir);
            
            
            int res = snd_pcm_hw_params(handleRecord, params);
            buffSize = 2 * (frames * frameSize); /* two period */
            std::cout << "test buffSize = " << buffSize << std::endl;
            std::cout << "test rate = " << rate << std::endl;
            std::cout << "period size = " << frames << std::endl;


            /* set play params */
            if ((err = snd_pcm_set_params(handlePlay,
                                      SND_PCM_FORMAT_U8,
                                      SND_PCM_ACCESS_RW_INTERLEAVED,
                                      channel,
                                      rate,
                                      1,
                                      500000)) < 0) 
            {   
                printf("Playback open error: %s\n", snd_strerror(err));
                exit(EXIT_FAILURE);
            }

            /*set net communite */
            uint32_t bufIp = inet_addr(Desip.c_str());
            bufIp = ntohl(bufIp);
            

            sessionparams.SetOwnTimestampUnit(1.0/(double)rate);
            transparams.SetPortbase(listenPort);
            sessionparams.SetAcceptOwnPackets(true);
            
            int status;
            if((status = Create(sessionparams, &transparams)) < 0)
            {
                std::cout << RTPGetErrorString(status) << std::endl;
                exit(-1);
            }

            unsigned int incTimeStamp = 2*frames;

            RTPIPv4Address addr(bufIp, DesPort);
            AddDestination(addr);
            SetDefaultPayloadType(96);
            SetDefaultMark(false);
            SetDefaultTimestampIncrement(incTimeStamp);
            
            sendBuffer = malloc(buffSize);
            if(sendBuffer == NULL)
            {
                std::cout << "init buffer error" << std::endl;
                return;
            }
            playBuffer = malloc(buffSize);
            if(playBuffer == NULL)
            {
                std::cout << "init buffer error" << std::endl;
                return;
            }

        };

        void testLocalAudio()
        {
           while(true)
           {
               int rc = snd_pcm_readi(handleRecord, sendBuffer,2*frames);
               if(rc == -EPIPE)
               {
                   snd_pcm_prepare(handleRecord);
               }
               else if(rc < 0)
               {
                   std::cout << snd_strerror(rc) << std::endl;
               }
               else if(rc != (2*frames))
               {
                    std::cout << "short read " << rc << std::endl;
               }

               int prc = snd_pcm_writei(handlePlay, sendBuffer, rc);
               if(prc == -EPIPE)
               {
                   snd_pcm_prepare(handlePlay);
               }
               else if(prc < 0)
               {
                   std::cout << snd_strerror(prc) << std::endl;
               }
           }             
        }

    public:
        int DesPort;
        int listenPort;
        RTPSessionParams sessionparams;
        RTPUDPv4TransmissionParams  transparams;
        
        unsigned int rate;
        int channel;
        void * sendBuffer;
        void * playBuffer;  
        int buffSize;
        
        int err; 
        snd_pcm_t *handlePlay;
        snd_pcm_t *handleRecord;
        snd_pcm_uframes_t frames;
        int frameSize;
        snd_pcm_hw_params_t *params;

        std::string Desip;
        

};


void testNetAudio(AudioSession & sess)
{
   while(true)
   {
       /* get audio data */
       int rc = snd_pcm_readi(sess.handleRecord, sess.sendBuffer,2*sess.frames);
       if(rc == -EPIPE)
       {
           snd_pcm_prepare(sess.handleRecord);
           std::cout << "record xrun error" << std::endl;
       }
       else if(rc < 0)
       {
           std::cout << snd_strerror(rc) << std::endl;
       }
       else if(rc != (2*sess.frames))
       {
            std::cout << "short read " << rc << std::endl;
       }

       /* send to net */
       int status = sess.SendPacket(sess.sendBuffer, rc*sess.frameSize);
       if(status < 0)
       {
           std::cout << RTPGetErrorString(status) << std::endl;
           return;
       }
       
       /* get audio data from net */
       RTPTime rtcpdelay = sess.GetRTCPDelay();
       if(status = sess.WaitForIncomingData(rtcpdelay) < 0)
       {
           std::cout << "None data coming, timeout" << std::endl;
           return;
       }
       else
       {
           if((status = sess.Poll()) < 0)
           {
               std::cout << "get data error" << std::endl;
               return;
           }
       }
       
       /* play audio */
       if(sess.GotoFirstSourceWithData())
       {
           do
           {
               RTPPacket * pack;
               while((pack = sess.GetNextPacket()) != 0)
               {
                    std::cout << "pack sequence number" <<
                        pack->GetSequenceNumber() << std::endl;
                    void *playBuffer = pack->GetPayloadData();
                    int   playSize   = pack->GetPayloadLength();
  
                    printf("%d \n", playSize);

                    int prc = snd_pcm_writei(sess.handlePlay, playBuffer,
                            (playSize/sess.frameSize));
                    
                    if(prc == -EPIPE)
                    {
                        snd_pcm_prepare(sess.handlePlay);
                        std::cout << "play xrun error" << std::endl;
                    }
                    else if(prc < 0)
                    {
                        std::cout << snd_strerror(prc) << std::endl;
                    }
                    sess.DeletePacket(pack);
               }
           }while(sess.GotoNextSourceWithData());
       }
   }             
}

int main()
{
    std::string ip = "127.0.0.1";
    AudioSession sess(1240, ip, 1240);
    sess.Init();
    //sess.testLocalAudio();
    testNetAudio(sess);
}
