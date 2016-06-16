#ifndef  _APPTASK_H_
#define  _APPTASK_H_

#include "../../common/IMProto.h"
#include "../../interface/itask.h"
#include <memory>

using std::unique_ptr;

class AppReactor;
typedef void (*handler_t)(ImProto *, AppReactor *, uint32_t connfd);

class AppTask : public Itask
{
    public:
        AppTask(int connfd, AppReactor *, void *data, int len);
        virtual ~AppTask() {};
        virtual void run();

    protected:
        int _connfd;
        handler_t _handle;
        unique_ptr<ImProto> _imData;
        AppReactor * _ract;
};





#endif
