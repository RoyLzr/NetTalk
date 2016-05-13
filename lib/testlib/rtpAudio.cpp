#include "../jrtplib/rtpsession.h"
#include "../jrtplib/rtpudpv4transmitter.h"
#include "../jrtplib/rtpipv4address.h"
#include "../jrtplib/rtpsessionparams.h"
#include "../jrtplib/rtperrors.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace jrtplib; 

class AudioSession : public RTPSession
{
    public:
        AudioSession(int Port1, uint8_t *ip, int Port2) : DesPort(Port1),
                                                          Desip(ip),
                                                          listenPort(Port2)
        {};

        virtual ~AudioSession() {};

        void Init()
        {
            sessionparams.SetOwnTimestampUnit(1.0/8000.0);
            transparams.SetPortbase(listenPort);
            int status;
            if((status = Create(sessionparams, &transparams)) < 0)
            {
                std::cout << RTPGetErrorString(status) << std::endl;
                exit(-1);
            }

            RTPIPv4Address addr(Desip, DesPort);
            AddDestination(addr);
            SetDefaultPayloadType(96);
            SetDefaultMark(false);
            SetDefaultTimestampIncrement(160);
            
        };

        int DesPort;
        int listenPort;
        RTPSessionParams sessionparams;
        RTPUDPv4TransmissionParams  transparams;
       
        uint8_t * Desip;
        

};


int main()
{
    uint8_t ip[] = {127,0,0,1};
    AudioSession sess(1230, ip, 1240);

}
