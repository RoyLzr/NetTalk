#include "RelationModel.h"
#include "../../../common/net.h"



using namespace std;

#define INVALID_VALUE   -1

CRelationModel* CRelationModel::m_pInstance = NULL;

CRelationModel::CRelationModel()
{

}

CRelationModel::~CRelationModel()
{

}

CRelationModel* CRelationModel::getInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CRelationModel();
	}

	return m_pInstance;
}

uint32_t CRelationModel::getRelationId(uint32_t nUserAId, uint32_t nUserBId, bool bAdd)
{
    uint32_t nRelationId = INVALID_VALUE;
    if (nUserAId == 0 || nUserBId == 0) {
        printf("invalied user id:%u->%u\n", nUserAId, nUserBId);
        return nRelationId;
    }
    CDBManager* pDBManager = CDBManager::getInstance();
    CDBConn* pDBConn = pDBManager->GetDBConn("slave");
    if (pDBConn)
    {
        uint32_t nBigId = nUserAId > nUserBId ? nUserAId : nUserBId;
        uint32_t nSmallId = nUserAId > nUserBId ? nUserBId : nUserAId;
        string strSql = "select id from IMRelationShip where smallUser=" + int2string(nSmallId) + " and bigUser="+ int2string(nBigId) + " and status = 0";
        
        CResultSet* pResultSet = pDBConn->ExecuteQuery(strSql.c_str());
        if (pResultSet)
        {
            while (pResultSet->Next())
            {
                nRelationId = pResultSet->GetInt("id");
            }
            delete pResultSet;
        }
        else
        {
            printf("there is no result for sql:%s", strSql.c_str());
        }
        pDBManager->RelDBConn(pDBConn);
        if (nRelationId == INVALID_VALUE && bAdd)
        {
            nRelationId = addRelation(nSmallId, nBigId);
        }
    }
    else
    {
        printf("no db connection for slave\n");
    }
    return nRelationId;
}

uint32_t CRelationModel::addRelation(uint32_t nSmallId, uint32_t nBigId)
{
    uint32_t nRelationId = INVALID_VALUE;
    CDBManager* pDBManager = CDBManager::getInstance();
    CDBConn* pDBConn = pDBManager->GetDBConn("slave");
    if (pDBConn)
    {
        string strSql = "select id from IMRelationShip where smallUser=" + int2string(nSmallId) + " and bigUser="+ int2string(nBigId);
        CResultSet* pResultSet = pDBConn->ExecuteQuery(strSql.c_str());
        if(pResultSet && pResultSet->Next())
        {
            nRelationId = pResultSet->GetInt("id");
            strSql = "update IMRelationShip set status=0 where id=" + int2string(nRelationId);
            bool bRet = pDBConn->ExecuteUpdate(strSql.c_str());
            if(!bRet)
            {
                nRelationId = INVALID_VALUE;
            }
            printf("has relation ship set status");
            delete pResultSet;
        }
        else
        {
            strSql = "insert into IMRelationShip (`smallUser`,`bigUser`,`status`) values(?,?,?)";
            CPrepareStatement* stmt = new CPrepareStatement();
            if (stmt->Init(pDBConn->GetMysql(), strSql))
            {
                uint32_t nStatus = 0;
                uint32_t index = 0;
                stmt->SetParam(index++, nSmallId);
                stmt->SetParam(index++, nBigId);
                stmt->SetParam(index++, nStatus);
                bool bRet = stmt->ExecuteUpdate();
                if (bRet)
                {
                    nRelationId = pDBConn->GetInsertId();
                }
                else
                {
                    printf("insert relation failed. %s\n", strSql.c_str());
                }
            }
            delete stmt;
        }
        pDBManager->RelDBConn(pDBConn);
    }
    else
    {
        printf("no db connection for slave\n");
    }
    return nRelationId;
}

bool CRelationModel::removeRelation(uint32_t nRelationId)
{
    bool bRet = false;
    CDBManager* pDBManager = CDBManager::getInstance();
    CDBConn* pDBConn = pDBManager->GetDBConn("slave");
    if (pDBConn)
    {
        string strSql = "update IMRelationShip set status = 1 where id=" + int2string(nRelationId);
        bRet = pDBConn->ExecuteUpdate(strSql.c_str());
        pDBManager->RelDBConn(pDBConn);
    }
    else
    {
        printf("no db connection for slave\n");
    }
    return bRet;
}


void
CRelationModel::AllBuddyUserId(uint32_t UserId, list<int> &res)
{
    bool bRet = false;
    int buddyUserId; 
    CDBManager* pDBManager = CDBManager::getInstance();
    CDBConn* pDBConn = pDBManager->GetDBConn("slave");
    if (pDBConn)
    {
        string strSql = "select * from IMRelationShip where (smallUser=" + int2string(UserId) + " or bigUser=" + int2string(UserId) + ") and status=0";
        CResultSet* pResultSet = pDBConn->ExecuteQuery(strSql.c_str());
        if(pResultSet) 
        {
            while(pResultSet->Next())
            {   
                int bigId = pResultSet->GetInt("bigUser");
                int smallId = pResultSet->GetInt("smallUser");
                if(bigId == UserId)
                    buddyUserId = smallId;
                else
                    buddyUserId = bigId;
                res.push_back(buddyUserId);
            }
        }
        delete pResultSet;
    }
    else
    {
        printf("open db slave error\n");
    }
    return;

}
