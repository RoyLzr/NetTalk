#ifdef   __CMD_H_
#define  __CMD_H_

#include <stdio.h>


class CMD
{
    public:
        CMD();
        virtual ~CMD();
        enum
        {
            VIDEO,
            TEXT,
            AUDIO,
            COUNT,
        };

        enum
        {
            BUILD,
            SEND,
            RECV,
            BYE,
            COUNT
        };

        virtual int GetObject() = 0;
        
        virtual int GetOperate() = 0;

        virtual int ParseCMD() = 0;

};


#endif
