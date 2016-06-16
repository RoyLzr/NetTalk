#include "../UserModel.h"
#include "../RelationModel.h"


int main()
{
    CUserModel * p_user = CUserModel::getInstance();
    DBUserInfo_t cUser, tUser;
    cUser.strName = "jorry3";
    cUser.password = "123";
    //p_user->insertUser(cUser);
    //p_user->getUserByName("jorry", cUser);
    //printf("%d\n", cUser.creatTime);

    
    CRelationModel * p_relate = CRelationModel::getInstance();
    list<int> id;
    p_relate->AllBuddyUserId(2, id);
    std::list<int>::iterator it = id.begin();
    while(it != id.end())
    {
        printf("%d\n", *it);
        it++;
    }  

    return 0;
}
