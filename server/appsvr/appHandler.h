#ifndef  _APPHANDLER_H_
#define  _APPHANDLER_H_

#include "../../interface/iconn.h"
#include "../../proto/IM.Base.pb.h"
#include "../../proto/IM.Log.pb.h"
#include "appTask.h"
#include "model/RelationModel.h"
#include "model/UserModel.h"
#include "appReactor.h"
#include <memory>
#include <map>
#include <utility>
    
using std::map;
using std::pair;
using std::make_pair;

typedef map<int, handler_t> HandlerMap_t;


class HandlerManager
{
    public:
        virtual ~HandlerManager() {};

        static HandlerManager * getInstance();
        
        void init();
        
        handler_t GetHandler(int handlerId);

     private:
        HandlerManager() {};
        static HandlerManager * _managerInstance;
        HandlerMap_t            _handleMap;

};


namespace AppHandler
{
    void doLogin(ImProto * imdata, AppReactor * ract, uint32_t connfd);
}








#endif
