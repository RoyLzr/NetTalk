#ifndef __STRAGY_MODEL__
#define __STRAGY_MODEL__

#include "userModel.h"

class UserStragy
{
    public:
        static UserModel * getInstance()
        {
            return _instance;
        }
        static void * setInstance(UserModel * ins)
        {
            _instance = ins;
        }
        ~UserStragy() {};
    private:
        UserModel() {};
        static UserModel * _instance;
};





#endif
