#ifndef _WORK_THREAD_H_
#define _WORK_THREAD_H_


#include "../interface/thread.h"
#include "ClientSvr.h"
#include "../common/net.h"


class ReadLineUserInput : public WorkerThread
{
    
    public:
        ReadLineUserInput():buffSize(0),
                            client(NULL)
        {};

        ReadLineUserInput(ClientSvr * cli, int size):WorkerThread(),
                                                     buffSize(size),
                                                     client(cli)
        {};
       
        virtual void Start();

        virtual void Execute();

        void setClient(ClientSvr * cli)
        {  client = cli; }

        void setBuffSize(int size)
        {  buffSize = size; }
       
        int readLineOnce();  

    protected:
        int buffSize;
        ClientSvr * client;
        
};

#endif
