#ifndef RELATION_SHIP_H_
#define RELATION_SHIP_H_
/*
 * Use From TeamTalk
 * https://github.com/mogujie/TeamTalk
 * http://tt.mogu.io/
 */




#include <list>
#include "../../../common/MySqlConn.h"

using std::list;

class CRelationModel {
public:
	virtual ~CRelationModel();

	static CRelationModel* getInstance();
    uint32_t getRelationId(uint32_t nUserAId, uint32_t nUserBId, bool bAdd);
    bool removeRelation(uint32_t nRelationId);
    
    void AllBuddyUserId(uint32_t UserId, list<int> &);
    
private:
	CRelationModel();
    uint32_t addRelation(uint32_t nSmallId, uint32_t nBigId);
private:
	static CRelationModel*	m_pInstance;
};


#endif
