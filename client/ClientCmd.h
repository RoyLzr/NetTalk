#ifndef   __CLIENT_CMD_H_
#define   __CLIENT_CMD_H_

#include "../interface/cmdWrap.h"
#include <string>
#include "../common/asynLog.h"
#include "../common/asynLog.h"
#include "AudioSession.h"
#include "AudioThread.h"
#include "../common/IMProto.h"
#include "../proto/IM.Test.pb.h"
#include "../proto/IM.Base.pb.h"
#include "../proto/IM.Log.pb.h"
#include <memory>
#include <stdlib.h>
#include <stdio.h>


using std::string;
using std::vector;


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


class RegReqCmd : public CMD
{
    public:
        RegReqCmd(LineTalkReactor *r, const char * data):ract(r),
                                                         cmdData(data)
        {};
        
        virtual ~RegReqCmd() {};

        virtual int callback();

    private:
        LineTalkReactor * ract;
        const char      * cmdData;
};

class KeepAliveCmd : public CMD
{
    public:
        KeepAliveCmd(LineTalkReactor * r):ract(r)
        {};

        virtual ~KeepAliveCmd() {};
        
        virtual int callback();

    private:
        LineTalkReactor * ract;
};


class LogInputCmd : public CMD
{
    public:
        LogInputCmd(LineTalkReactor * r, const string data):ract(r),
                                                            cmd(data)
        {};
        virtual ~LogInputCmd() {};
        virtual int callback();
    private:
        LineTalkReactor * ract;
        const std::string cmd;
};


#endif
