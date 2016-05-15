#ifndef   __CMD_H_
#define   __CMD_H_

#include <stdio.h>


class CMD
{
    public:
        CMD() {};
        virtual ~CMD() {};
        enum
        {
            VIDEO,
            TEXT,
            AUDIO,
            OWNUSER,
            CLASSCOUNT,
        };

        enum
        {
            BUILD,
            SEND,
            RECV,
            BYE,
            SHOW,
            OPCOUNT
        };

        virtual int excute() = 0;
};


#endif
