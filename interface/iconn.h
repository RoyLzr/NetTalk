#ifndef  _ICONN_H_
#define  _ICONN_H_

#include "ireactor.h"


class Iconn
{
    public:
        virtual int OnRead(void *, int) = 0;

        virtual int OnWrite(void *, int) = 0;

        virtual ~Iconn() {};

        Iconn() {};

};




#endif
