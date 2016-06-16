#include "appHandler.h"


HandlerManager * HandlerManager::_managerInstance = NULL;


HandlerManager * HandlerManager::getInstance()
{
    if(!_managerInstance)
    {
        _managerInstance = new HandlerManager();
        _managerInstance->init();
    }
    return _managerInstance;
}


void 
HandlerManager::init()
{
    _handleMap.insert(make_pair(int(IM::Base::CID_LOGIN_REQ_USERLOGIN),
                                AppHandler::doLogin));
}


handler_t 
HandlerManager::GetHandler(int commandId)
{
    HandlerMap_t::iterator it = _handleMap.find(commandId);
    if(it != _handleMap.end())
      return it->second;
    else
      return NULL;  
}


namespace AppHandler
{
    void doLogin(ImProto * imdata, AppReactor * ract, uint32_t connfd)
    {
        IM::Log::IMLogInReq req;
        if(!req.ParseFromString(*(imdata->GetBuffer())))
        {
            printf("parse login req error]n");
            return;
        }
        CUserModel * pUser = CUserModel::getInstance();
        DBUserInfo_t cUser;
        if(!pUser)
        {
            return;
        }
        pUser->getUserByName(req.name(), cUser);
        
        std::unique_ptr<ImProto> imRes(new ImProto());
        std::string * buf = imRes->GetBuffer();
        IM::Log::IMLogRes resProto;
        
        if(cUser.password == req.password())
        {
            printf("login Succ\n");

            resProto.set_logres(IM::Base::RESULT_LOGIN_SUCC);
            resProto.SerializeToString(buf);

            imRes->SetLength(buf->size());
            imRes->SetCommandID(uint16_t(IM::Base::CID_LOGIN_RES_USERLOGIN));
            imRes->SetUserID(cUser.nId);
            imRes->SetPunch(imdata->GetPunch());
            
        }
        else
        {
            printf("login error\n");
            resProto.set_logres(IM::Base::RESULT_LOGIN_FAIL);
            resProto.SerializeToString(buf);

            imRes->SetLength(uint32_t(buf->size()));
            imRes->SetCommandID(uint16_t(IM::Base::CID_LOGIN_RES_USERLOGIN));
            imRes->SetUserID(0);
            imRes->SetPunch(uint16_t(imdata->GetPunch()));
        }
        
        SPacket_t sendPacket;
        sendPacket.imData = std::move(imRes);
        sendPacket.connfd = connfd;

        ract->postSendPacket(sendPacket);
        ract->Signal();
        return;
    }
}


