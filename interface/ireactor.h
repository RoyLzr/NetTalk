#ifndef  _IREACTOR_H_
#define  _IREACTOR_H_

#include "../common/configParser.h"
#include "../interface/cmdWrap.h"

class IReactor 
{
    public:
        enum 
        {
            NONE,
            INIT,
            STOP,
            RUNNING,
            PAUSE,
        };

    public:
        IReactor() {};
        virtual ~IReactor() {};
    
    public:

        virtual int extCmd(const std::string &) = 0;

        virtual int init() = 0; 
        
        virtual int run() = 0;
        
        virtual int Stop() = 0;
        
        virtual bool isStop() = 0;
        
        virtual int status() = 0;

};


#endif

