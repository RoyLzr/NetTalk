#ifndef   __TRANS_H_
#define   __TRANS_H_

#include <string>


class Trans
{
    public:
        Trans() {};
        virtual ~Trans() {};
        //Dest ip, Dest port, listen port
        virtual int init(std::string, int , int) = 0;

        virtual int SendData(void * data, int len) = 0;
        
        virtual int RecvData(void * data) = 0;
        
        virtual int GetLocalData(void * data) = 0;
        
        virtual int ShowLocalData(void * data, int len) = 0;

        virtual int Bye() = 0;
        
        virtual int Clear() = 0;
        
        virtual int setExtendInfo(void *) = 0;
};


#endif
