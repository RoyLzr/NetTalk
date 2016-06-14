#include "../UserModel.h"


int main()
{
    CUserModel * p_user = CUserModel::getInstance();
    DBUserInfo_t cUser, tUser;
    cUser.strName = "jorry2";
    cUser.password = "123";
    p_user->insertUser(cUser);


    return 0;
}
