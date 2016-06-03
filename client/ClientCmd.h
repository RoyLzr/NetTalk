#ifndef   __CLIENT_CMD_H_
#define   __CLIENT_CMD_H_

#include "../interface/cmdWrap.h"
#include <string>
#include "../common/asynLog.h"
#include "../common/asynLog.h"
#include "AudioSession.h"
#include "AudioThread.h"
#include "../common/IMProto.h"


class LineTalkReactor;

class TestCmd : public CMD
{
    public:
        TestCmd(std::string s):input(s)
        {};
        
        TestCmd(LineTalkReactor * r):ract(r)
        {};

        virtual ~TestCmd() {};
        
        virtual int callback();

    private:
        std::string input;
        LineTalkReactor * ract;
};

class InitAudioCmd : public CMD
{
    public:
        InitAudioCmd(LineTalkReactor * r):ract(r)
        {};

        virtual ~InitAudioCmd() {};
        
        virtual int callback();


    private:
        LineTalkReactor * ract;
};

class RunAudioCmd : public CMD
{
    public:
        RunAudioCmd(LineTalkReactor * r):ract(r)
        {};

        virtual ~RunAudioCmd() {};
        
        virtual int callback();

    private:
        LineTalkReactor * ract;
};

class StopAudioCmd : public CMD
{
    public:
        StopAudioCmd(LineTalkReactor * r):ract(r)
        {};

        virtual ~StopAudioCmd() {};
        
        virtual int callback();

    private:
        LineTalkReactor * ract;
};





#endif
