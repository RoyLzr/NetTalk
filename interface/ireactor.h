#ifndef  _IREACTOR_H_
#define  _IREACTOR_H_

#include "../common/configParser.h"

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

        virtual int extCmd(const string &) = 0;

        virtual int init(); 
        
        virtual int run() = 0;
        
        virtual int stop() = 0;
        
        virtual int status() = 0;

};


#endif

