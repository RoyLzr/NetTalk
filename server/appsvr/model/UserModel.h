#ifndef __USERMODEL_H__
#define __USERMODEL_H__

#include "../../../common/MySqlConn.h"

typedef struct DBUserInfo_t
{
    uint32_t nId;
    string strName;
    string password;
    uint32_t creatTime;
    uint32_t LastloginTime;
    
    DBUserInfo_t& operator=(const DBUserInfo_t& rhs)
    {
        if(this != &rhs)
        {
            nId = rhs.nId;
            strName = rhs.strName;
            creatTime = rhs.creatTime;
            LastloginTime = rhs.LastloginTime;
            password = rhs.password;
        }
        return *this;
    }
    
} DBUserInfo_t;

class CUserModel
{
public:
    static CUserModel* getInstance();
    ~CUserModel();
    
    bool getUserById(uint32_t nUserId, DBUserInfo_t& cUser);
    bool getUserByName(string , DBUserInfo_t& cUser);
    bool insertUser(DBUserInfo_t &cUser);

private:
    CUserModel();
    bool internalQuery(string &sql, DBUserInfo_t &cUser);

private:
    static CUserModel* m_pInstance;
};

#endif
