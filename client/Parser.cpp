#include "Parser.h"
#include "LineTalkReactor.h"


std::unique_ptr<CMD> UserDataParser::Parser(const std::string data,
                                            void * args)
{
    std::unique_ptr<CMD> res;
    LineTalkReactor * arg = (LineTalkReactor *)args;
    int ust = arg->getUserStatus();
    if(ust == LineTalkReactor::USERLOGINPUT)
    {
        std::unique_ptr<CMD> cmd(new LogInputCmd(arg, data));
        res = std::move(cmd);
        arg->setUserStatus(LineTalkReactor::USERLOGING);
        return res;
    }
    else if(ust == LineTalkReactor::USERLOGING)
    {
        printf("Client is Logging can not excute other cmd\n");
        return res;
    }

    if(!strcmp(init.c_str(), data.c_str()))
    {
        std::unique_ptr<CMD> cmd(new InitAudioCmd(arg));
        res = std::move(cmd); 
    }
    else if(!strcmp(run.c_str(), data.c_str()))
    {
        std::unique_ptr<CMD> cmd(new RunAudioCmd(arg));
        res = std::move(cmd);
    }
    else if(!strcmp(stop.c_str(), data.c_str()))
    {
        std::unique_ptr<CMD> cmd(new StopAudioCmd(arg));
        res = std::move(cmd);
    }
    else if(!strcmp(test.c_str(), data.c_str()))
    {
        std::unique_ptr<CMD> cmd(new TestCmd(arg));
        res = std::move(cmd);
    }
    else if(!strcmp(Register.c_str(), data.c_str()))
    {
        arg->setUserStatus(LineTalkReactor::USERREGINPUT);
        printf("please input name and password, split by:\nexamples lili:123123\n");

    }
    else if(!strcmp(login.c_str(), data.c_str()))
    {
        arg->setUserStatus(LineTalkReactor::USERLOGINPUT);
        printf("please input name and password, split by:\nexamples lili:123123\n");
    }
    else
    {
        Log::WARN("USER INPUT ERROR");
    }

    return std::move(res);
}

