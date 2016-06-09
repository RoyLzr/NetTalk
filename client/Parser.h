#ifndef   __PARSER_H_
#define   __PARSER_H_

#include "../interface/dataParse.h"
#include "../interface/cmdWrap.h"
#include "ClientCmd.h"
#include <string>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class SvrDataParser : public DataParser
{
    public:
        SvrDataParser() {};
        virtual ~SvrDataParser() {};

        virtual void * Build(CMD * cmd, int * len)
        {
            return 0;
        }
        
        virtual std::unique_ptr<CMD> Parser(const std::string data,void *)
        {};

};

class UserDataParser : public DataParser
{
    public:
        UserDataParser():init("init\n"),
                         run("run\n"),
                         stop("stop\n"),
                         test("test\n"),
                         Register("register\n") 
        {};

        virtual ~UserDataParser() 
        {};

        virtual void * Build(CMD * cmd, int  * len)
        {
            return 0;
        }
        
        virtual std::unique_ptr<CMD> Parser(const std::string data,void *);
    protected:
        const std::string init;
        const std::string run;
        const std::string stop;
        const std::string test;
        const std::string Register;

};


#endif
