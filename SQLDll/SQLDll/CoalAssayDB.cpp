#ifndef SOLIOEXPORT
#define SOLIOEXPORT
#endif

#include "CoalAssayDB.h"

CoalAssayDB::CoalAssayDB(void) :
	m_pcswToken(NULL)
{
}


CoalAssayDB::~CoalAssayDB(void)
{
}

int CoalAssayDB::Login(Staff& lStaff)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;

	SQLSMALLINT	nRetCode;
	WCHAR wcsQueryString[1024];

	wsprintf(wcsQueryString, 
			 L"EXEC dbo.Login '%s', '%s'",
			 lStaff.strStaffNum, lStaff.strPassword);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	if(nRetCode >= 0)
		GetStaff(lStaff, m_pSet);
	return nRetCode;
}

void CoalAssayDB::GetStaff(Staff& lStaff, const SQLResult* lpSet)
{
	if(!lpSet || (lpSet->Cols.size() < 0) || 
		(lpSet->Rows.size() < 0) || 
		(lpSet->Rows[0].size() < 0))
		return;
	
	for(int i = 0; i < lpSet->Cols.size(); i++)
	{
		if(!wcscmp(lpSet->Cols[i].c_str(), L"Token"))
		{
			SetToken(lpSet->Rows[0][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffName"))
		{
			lStaff.strStaffName = new WCHAR[wcslen(lpSet->Rows[0][i].c_str()) + 1];
			wcscpy((WCHAR*)lStaff.strStaffName, lpSet->Rows[0][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffSex"))
		{
			lStaff.enumStaffSex =  _wtoi(lpSet->Rows[0][i].c_str()) == 0? 
								   SQLSex::Female : SQLSex::Male;
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffBirthday"))
		{
			swscanf(lpSet->Rows[0][i].c_str(), L"%d-%d-%d", 
					&lStaff.tsStaffBirthday.year, 
					&lStaff.tsStaffBirthday.month, 
					&lStaff.tsStaffBirthday.day);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Position"))
		{
			lStaff.strPosition = new WCHAR[wcslen(lpSet->Rows[0][i].c_str()) + 1];
			wcscpy((WCHAR*)lStaff.strPosition, lpSet->Rows[0][i].c_str());		
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Permission"))
		{
			lStaff.strPermission = new WCHAR[wcslen(lpSet->Rows[0][i].c_str()) + 1];
			wcscpy((WCHAR*)lStaff.strPermission, lpSet->Rows[0][i].c_str());		
		}
	}
}
//bool CoalAssayDB::Login(const LPCWSTR szStaffNum, const LPCWSTR szPassword)
//{
//	int nRet = 0;
//
//	if ( m_driverSqlServer.Connect( _T("Sql Server"),
//									_T("Solio-PC\\SOLIOENTERPRISE"),
//									_T("COALASSAY"),
//									_T("sa"),
//									_T("Xzd091217")) != SQL_ERROR )
//	{
//		
//		WCHAR wcsQueryString[1024];
//
//		wsprintf(wcsQueryString, 
//				 _T("SELECT * FROM Staff WHERE StaffNum='%s' and Password='%s'"), 
//				 szStaffNum,
//				 szPassword);
//		if(m_pSet)
//			nRet = m_driverSqlServer.ExecuteQuery(wcsQueryString, m_pSet);
//	}
//	if(m_pSet->Rows.size() > 0)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}