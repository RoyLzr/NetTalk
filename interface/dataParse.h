#ifndef   __DATA_PARSE_H_
#define   __DATA_PARSE_H_

#include "cmdWrap.h"

class DataParser
{
    public:
        DataParser() {};
        virtual ~DataParser() {};

        virtual void * Build(CMD * cmd, int * len) = 0;

        virtual CMD * Parser(void * data, int len) = 0;

};


#endif
