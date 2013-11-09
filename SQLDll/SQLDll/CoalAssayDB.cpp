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
	WCHAR wcsStaffNum[50];
	WCHAR wcsPassword[50];

	lStaff.GetStaffNum(wcsStaffNum);
	lStaff.GetPassword(wcsPassword);
	wsprintf(wcsQueryString, 
			 L"EXEC dbo.Login '%s', '%s'",
			 wcsStaffNum, wcsPassword);

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	if(nRetCode >= 0)
		GetStaff(lStaff, m_pSet);
	return nRetCode;
}

void CoalAssayDB::GetStaff(Staff& lStaff, const SQLResult* lpSet)
{
	if(!lpSet || (lpSet->Cols.size() <= 0) || 
		(lpSet->Rows.size() <= 0) || 
		(lpSet->Rows[0].size() <= 0))
		return;
	
	for(int i = 0; i < lpSet->Cols.size(); i++)
	{
		if(!wcscmp(lpSet->Cols[i].c_str(), L"Token"))
		{
			SetToken(lpSet->Rows[0][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffName"))
		{
			lStaff.SetStaffName(lpSet->Rows[0][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffSex"))
		{
			SQLSex ls =  _wtoi(lpSet->Rows[0][i].c_str()) == 0? 
							SQLSex::Female : SQLSex::Male;
			lStaff.SetStaffSex(ls);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffBirthday"))
		{
			int nYear = 0, nMonth = 0, nDay = 0;
			swscanf(lpSet->Rows[0][i].c_str(), L"%d-%d-%d", 
					&nYear, &nMonth, &nDay);
			lStaff.SetStaffBirthday(nYear, nMonth, nDay);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Position"))
		{
			lStaff.SetPosition(lpSet->Rows[0][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Permission"))
		{
			lStaff.SetPermission(lpSet->Rows[0][i].c_str());
		}
	}
}

int CoalAssayDB::AddStaff(Staff& lStaff)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	WCHAR wcsStaffNum[50];
	WCHAR wcsStaffName[50];
	TIMESTAMP_STRUCT tsBirthday;
	SQLSex enumStaffSex;
	WCHAR wcsPosition[50];
	WCHAR wcsPermission[50];
	WCHAR wcsPassword[50];

	lStaff.GetStaffNum(wcsStaffNum);
	lStaff.GetStaffName(wcsStaffName);
	lStaff.GetStaffSex(enumStaffSex);
	lStaff.GetStaffBirthday(tsBirthday);
	lStaff.GetPosition(wcsPosition);
	lStaff.GetPassword(wcsPassword);
	lStaff.GetPermission(wcsPermission);
	wsprintf(wcsQueryString,
			//@Token, @StaffNum, @StaffName, @StaffSex, @StaffBirthday, @Position, @Password, @Permission
			 L"EXEC [dbo].AddStaff '%s','%s','%s','%s','%4d-%2d-%2d','%s','%s','%s'",
			 this->m_pcswToken,
			 wcsStaffNum,
			 wcsStaffName,
			 (enumStaffSex == SQLSex::Female? L"0" : L"1"),
			 tsBirthday.year, tsBirthday.month, tsBirthday.day,
			 wcsPosition,
			 wcsPassword,
			 wcsPermission);

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);

	if(m_pSet->nAffected > 0)
		nRetCode = m_pSet->nAffected;
	else
	{
		nRetCode = LOGIC_NODATA;
		SetErrorMsg(_T("No Data"));
	}
	//if(m_pSet->Cols.size() <= 0 ||
	//   m_pSet->Rows.size() <= 0 ||
	//   m_pSet->Rows[0].size() <= 0)
	//{
	//	nRetCode = SQL_ERROR;
	//}
	//else if(!wcscmp(m_pSet->Cols[0].c_str(), L"AddedResult") && 
	//		!wcscmp(m_pSet->Rows[0][0].c_str(), L"SUCCESS"))
	//{
	//	nRetCode = 1;
	//}
	//else
	//{
	//	nRetCode = LOGIC_PERMISSIONDENIED;
	//	this->SetErrorMsg((WCHAR*)m_pSet->Rows[0][0].c_str());
	//}
	return nRetCode;
}

// AddStaff the version of using SQLBindParameter
//int CoalAssayDB::AddStaff(Staff& lStaff)
//{
//	if(!IsConnected())
//		return SQL_NONCONNECTED;
//	if(!m_pSet)
//		return SQL_NONBINDING;
//
//	SQLSMALLINT	nRetCode = SQL_ERROR;
//	WCHAR wcsQueryString[1024];
//	WCHAR wcsStaffNum[50];
//	WCHAR wcsStaffName[50];
//	WCHAR wcsStaffSex[50];
//	WCHAR wcsStaffBirthday[50];
//	TIMESTAMP_STRUCT tsBirthday;
//	SQLSex enumStaffSex;
//	WCHAR wcsPosition[50];
//	WCHAR wcsPermission[50];
//	WCHAR wcsPassword[50];
//	WCHAR wcsMsg[50] = L"";
//
//	lStaff.GetStaffNum(wcsStaffNum);
//	lStaff.GetStaffName(wcsStaffName);
//	lStaff.GetStaffSex(enumStaffSex);
//	lStaff.GetStaffBirthday(tsBirthday);
//	lStaff.GetPosition(wcsPosition);
//	lStaff.GetPassword(wcsPassword);
//	lStaff.GetPermission(wcsPermission);
//	
//	SetStatement();
//	SQLINTEGER cbSnum = 0, cbSname = 0;
//
//	wcscpy(wcsStaffSex, L"1");
//	wcscpy(wcsStaffBirthday, L"2013-11-09");
//
//	nRetCode = SQLPrepareW(m_hStatement, L"{call AddStaff(?,?,?,?,?,?,?,?,?)}", SQL_NTS);
//	SQLBindParameter( m_hStatement, 1, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"Token") + 1, 1, m_pcswToken, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 2, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"StaffNum") + 1, 1, wcsStaffNum, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 3, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"StaffName") + 1, 1, wcsStaffName, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 4, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"StaffSex") + 1, 1, wcsStaffSex, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 5, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"StaffBirthday") + 1, 1, wcsStaffBirthday, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 6, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"Position") + 1, 1, wcsPosition, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 7, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"Password") + 1, 1, wcsPassword, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 8, SQL_PARAM_INPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"Permission") + 1, 1, wcsPermission, 0, &cbSnum);
//	SQLBindParameter( m_hStatement, 9, SQL_PARAM_OUTPUT, SQL_C_WCHAR,
//		SQL_VARCHAR , wcslen(L"Msg") + 1, 1, wcsMsg, 0, &cbSnum);
//	nRetCode = SQLExecute(m_hStatement);
//
//	if(nRetCode != 0)
//		HandleDiagnosticRecord(m_hStatement, SQL_HANDLE_STMT, nRetCode);
//	SQLFreeStmt(m_hStatement, SQL_CLOSE);
//	m_hStatement = NULL;
//	return nRetCode;
//}

int CoalAssayDB::DeleteStaff(LPCWSTR lpcsStaffNum)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];

	wsprintf(wcsQueryString,
			 L"EXEC [dbo].DeleteStaff '%s', '%s'",
			 m_pcswToken,
			 lpcsStaffNum);

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);

	if(m_pSet->nAffected > 0)
		nRetCode = m_pSet->nAffected;
	else
	{
		nRetCode = LOGIC_NODATA;
		SetErrorMsg(_T("No Data"));
	}
	//if(m_pSet->Cols.size() <= 0 ||
	//   m_pSet->Rows.size() <= 0 ||
	//   m_pSet->Rows[0].size() <= 0)
	//{
	//	nRetCode = SQL_ERROR;
	//}
	//else if(!wcscmp(m_pSet->Cols[0].c_str(), L"DeletedResult") && 
	//		!wcscmp(m_pSet->Rows[0][0].c_str(), L"SUCCESS"))
	//{
	//	nRetCode = 1;
	//}
	//else
	//{
	//	nRetCode = LOGIC_PERMISSIONDENIED;
	//	this->SetErrorMsg((WCHAR*)m_pSet->Rows[0][0].c_str());
	//}
	return nRetCode;
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