#include "appTask.h"
#include "appReactor.h"
#include "../../common/IMProto.h"
#include "appHandler.h"

AppTask::AppTask(int connfd, AppReactor *r, void * buf,  int len) : _connfd(connfd),
                                                                    _handle(NULL),
                                                                    _ract(r)
{
    unique_ptr<ImProto> data(new ImProto());
    _imData = std::move(data);
    _imData->InitByHeaderAddBuf(buf, len); 
}


void
AppTask::run()
{
    HandlerManager * hmag = HandlerManager::getInstance();
    ImProto * imp = _imData.get();
    _handle = hmag->GetHandler(imp->GetCommandID());

    if(_handle != NULL)
        _handle(imp, _ract, _connfd);
    else
    {
        printf("command id %d not exist\n", imp->GetCommandID());
    }
}
