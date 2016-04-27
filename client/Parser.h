#ifndef   __PARSER_H_
#define   __PARSER_H_

#include "../interface/dataParse.h"
#include "../interface/cmdWrap.h"

class SvrDataParser : public DataParser
{
    public:
        SvrDataParser() {};
        virtual ~SvrDataParser() {};

        virtual void * Build(CMD * cmd, int * len)
        {
            return 0;
        }
        
        virtual CMD * Parser(void * data, int len)
        {
            return 0;
        }

};

class UserDataParser : public DataParser
{
    public:
        UserDataParser() {};
        virtual ~UserDataParser() {};

        virtual void * Build(CMD * cmd, int  * len)
        {
            return 0;
        }
        
        virtual CMD * Parser(void * data, int len)
        {
            return 0;
        }
};


#endif
