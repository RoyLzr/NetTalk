#ifndef   __DATA_PARSE_H_
#define   __DATA_PARSE_H_

#include "cmdWrap.h"
#include <memory>
#include <string>

class DataParser
{
    public:
        DataParser() {};
        virtual ~DataParser() {};

        virtual void * Build(CMD * cmd, int * len) = 0;

        virtual std::unique_ptr<CMD> Parser(const std::string input,void *args) = 0;
};


#endif
