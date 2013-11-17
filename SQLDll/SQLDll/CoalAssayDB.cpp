#ifndef SOLIOEXPORT
#define SOLIOEXPORT
#endif

#include "CoalAssayDB.h"
#include "Task.h"

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
	if(m_pSet->Rows.size() > 0 && m_pSet->Cols.size() > 1)
	{
		nRetCode = m_pSet->Rows.size();
		GetStaff(lStaff, m_pSet, 0);
	}
	else
		nRetCode = LOGIC_USERERROR;
	return nRetCode;
}

void CoalAssayDB::GetStaff(Staff& lStaff, 
						   const SQLResult* lpSet, 
						   int nRowIndex)
{
	if(!lpSet || (lpSet->Cols.size() <= 0) || 
		(lpSet->Rows.size() <= 0) || 
		(nRowIndex >= lpSet->Rows.size() ||
		(lpSet->Rows[0].size() <= 0))
		)
		return;
	
	for(int i = 0; i < lpSet->Cols.size(); i++)
	{
		if(!wcscmp(lpSet->Cols[i].c_str(), L"Token"))
		{
			SetToken(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffNum"))
		{
			lStaff.SetStaffNum(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffName"))
		{
			lStaff.SetStaffName(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffSex"))
		{
			SQLSex ls =  _wtoi(lpSet->Rows[nRowIndex][i].c_str()) == 0? 
							SQLSex::Female : SQLSex::Male;
			lStaff.SetStaffSex(ls);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StaffBirthday"))
		{
			int nYear = 0, nMonth = 0, nDay = 0;
			swscanf(lpSet->Rows[nRowIndex][i].c_str(), L"%d-%d-%d", 
					&nYear, &nMonth, &nDay);
			lStaff.SetStaffBirthday(nYear, nMonth, nDay);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Position"))
		{
			lStaff.SetPosition(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Permission"))
		{
			lStaff.SetPermission(lpSet->Rows[nRowIndex][i].c_str());
		}
	}
}

int CoalAssayDB::AddStaff(Staff& lStaff)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

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
	return nRetCode;
}

int CoalAssayDB::EditUser(Staff& lStaff)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

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
			 //@StaffNum, @StaffName, @StaffSex, @StaffBirthday, @Position, @Password, @Permission
			 L"EXEC [dbo].EditStaff '%s','%s','%s','%4d-%2d-%2d','%s','%s','%s'",
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
}

int CoalAssayDB::DeleteStaff(LPCWSTR lpcsStaffNum)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

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
	return nRetCode;
}

int CoalAssayDB::SelectAllStaff(StaffArray& arrStaff)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];

	wsprintf(wcsQueryString,
			 L"EXEC [dbo].SelectAllStaff '%s'",
			 m_pcswToken);

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);

	if(m_pSet->Rows.size() > 0 && m_pSet->Cols.size() == 6)
	{
		nRetCode = m_pSet->Rows.size();
		Staff *pStaffs = new Staff[m_pSet->Rows.size()];
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{			
			Staff lStaff;
			GetStaff(pStaffs[i], m_pSet, i);
		}
		arrStaff.pStaffs = pStaffs;
		arrStaff.count = m_pSet->Rows.size();
	}
	else
	{
		nRetCode = LOGIC_NODATA;
		SetErrorMsg(_T("No Data"));
	}
	return nRetCode;
}

int CoalAssayDB::CorrespondingConnect(DeviceType enumType,
							LPCWSTR lpszDriver,
							LPCWSTR lpszServer,
							LPCWSTR lpszDBName,
							LPCWSTR lpszUid,
							LPCWSTR lpszPwd)
{
	BOOL bRet = FALSE;

	switch(enumType)
	{
	case DeviceType::AshFusionPoint:
		bRet = this->m_oDbcAFP.Connect(lpszDriver, lpszServer,
									   lpszDBName, lpszUid,
									   lpszPwd);
		break;
	case DeviceType::CaloriMeter:
		bRet = this->m_oDbcCM.Connect(lpszDriver, lpszServer,
									  lpszDBName, lpszUid,
									  lpszPwd);
		break;
	case DeviceType::ElementAnalyzer:
		bRet = this->m_oDbcEA.Connect(lpszDriver, lpszServer,
									  lpszDBName, lpszUid,
									  lpszPwd);
		break;
	case DeviceType::LightWaveMeter:
		bRet = this->m_oDbcLWM.Connect(lpszDriver, lpszServer,
									   lpszDBName, lpszUid,
									   lpszPwd);
		break;
	case DeviceType::SulfurDetector:
		bRet = this->m_oDbcSD.Connect(lpszDriver, lpszServer,
									  lpszDBName, lpszUid,
									  lpszPwd);
		break;
	case DeviceType::WorkPointInstrument:
		bRet = this->m_oDbcWPI.Connect(lpszDriver, lpszServer,
									   lpszDBName, lpszUid,
									   lpszPwd);
		break;
	default:
		bRet = FALSE;
		break;
	}

	return bRet;
}

BOOL CoalAssayDB::IsCorrespondingConnected(const DeviceType enumType)
{
	BOOL bRet = FALSE;

	switch(enumType)
	{
	case DeviceType::AshFusionPoint:
		bRet = this->m_oDbcAFP.IsConnected();
		break;
	case DeviceType::CaloriMeter:
		bRet = this->m_oDbcCM.IsConnected();
		break;
	case DeviceType::ElementAnalyzer:
		bRet = this->m_oDbcEA.IsConnected();
		break;
	case DeviceType::LightWaveMeter:
		bRet = this->m_oDbcLWM.IsConnected();
		break;
	case DeviceType::SulfurDetector:
		bRet = this->m_oDbcSD.IsConnected();
		break;
	case DeviceType::WorkPointInstrument:
		bRet = this->m_oDbcWPI.IsConnected();
		break;
	default:
		bRet = FALSE;
		break;
	}

	return bRet;
}

// there are several table is contact to the CoalInfo table.
// when add a new CoalInfo you need to specify the corresponding table
// insert a blank record to .
int CoalAssayDB::AddCorrespondingBlank(const AssayTask& oTask)
{
	SQLSMALLINT	nRetCode = SQL_ERROR;

	for(int i = 0; i < oTask.Devices.size(); i++)
	{
		switch(oTask.Devices[i])
		{
		case DeviceType::AshFusionPoint:
			nRetCode = this->m_oDbcAFP.ExecuteQuery(L"", m_pSet);
			break;
		case DeviceType::CaloriMeter:
			nRetCode = this->m_oDbcCM.ExecuteQuery(
				L"INSERT INTO win5emdb (Standard) VALUES('0')", m_pSet);
			break;
		case DeviceType::ElementAnalyzer:
			nRetCode = this->m_oDbcEA.ExecuteQuery(L"", m_pSet);
			break;
		case DeviceType::LightWaveMeter:
			nRetCode = this->m_oDbcLWM.ExecuteQuery(L"", m_pSet);
			break;
		case DeviceType::SulfurDetector:
			nRetCode = this->m_oDbcSD.ExecuteQuery(L"", m_pSet);
			break;
		case DeviceType::WorkPointInstrument:
			nRetCode = this->m_oDbcWPI.ExecuteQuery(L"", m_pSet);
			break;
		default:
			nRetCode = FALSE;
			break;
		}		
	}

	return nRetCode;
}

int CoalAssayDB::AddCoalInfo(const CoalInfo& lCoalInfo, int *lpnCoalId)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];

	wsprintf(wcsQueryString,
			 //Token,[CoalLotNum],[AssayCode],[AssayDate],[SampleDate],[AssayType],[AssayStaff],[SampleStaff],[StageName],[WorksName]
			 L"EXEC [dbo].AddCoalInfo '%s','%s','%s','%4d-%2d-%2d','%4d-%2d-%2d','%d','%s','%s','%s','%s'",
			 m_pcswToken,
			 lCoalInfo.GetCoalLotNum(),
			 lCoalInfo.GetAssayCode(),
			 lCoalInfo.GetAssayDate().year, lCoalInfo.GetAssayDate().month, lCoalInfo.GetAssayDate().day,
			 lCoalInfo.GetSampleDate().year, lCoalInfo.GetSampleDate().month, lCoalInfo.GetSampleDate().day,
			 (int)lCoalInfo.GetAssayType(),
			 lCoalInfo.GetAssayStaff(),
			 lCoalInfo.GetSampleStaff(),
			 lCoalInfo.GetStageName(),
			 lCoalInfo.GetWorksName());

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	if(m_pSet->nAffected > 0)
	{
		nRetCode = m_pSet->nAffected;	
		wsprintf(wcsQueryString, L"SELECT TOP 1 [ID],[CoalLotNum] FROM [CoalInfo] ORDER BY [ID] DESC", m_pSet);
		nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
		if(m_pSet->Rows.size() > 0 && m_pSet->Rows[0].size())
			(*lpnCoalId) = _wtoi(m_pSet->Rows[0][0].c_str());
	}
	else
		nRetCode = LOGIC_NODATA;
	return nRetCode;
}

int CoalAssayDB::CreateNewTask(const AssayTask& oTask)
{
	int nId = -1;
	int nRetCode = 0;
	AssayTask *poTaskTmp = new AssayTask[oTask.Devices.size()];

	if(nRetCode = AddCoalInfo(oTask.CoalInfo, &nId))
		return LOGIC_CREATETASKFAIL;
	
	for(int i = 0; i < oTask.Devices.size(); i++)
	{
		AddCorrespondingBlank(oTask);
	}

	// Create Task thread for each related table
	for(int i = 0; i < oTask.Devices.size(); i++)
	{
		poTaskTmp[i] = oTask;
		switch(oTask.Devices[i])
		{
		case DeviceType::AshFusionPoint:
			poTaskTmp[i].CurrentDevice = DeviceType::AshFusionPoint;
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::CaloriMeter:
			poTaskTmp[i].CurrentDevice = DeviceType::CaloriMeter;
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::ElementAnalyzer:
			poTaskTmp[i].CurrentDevice = DeviceType::ElementAnalyzer;
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::LightWaveMeter:
			poTaskTmp[i].CurrentDevice = DeviceType::LightWaveMeter;
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::SulfurDetector:
			poTaskTmp[i].CurrentDevice = DeviceType::SulfurDetector;
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::WorkPointInstrument:
			poTaskTmp[i].CurrentDevice = DeviceType::WorkPointInstrument;
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		default:

			break;
		}
	}

	// wait for all assay task is finish
	while(TRUE)
	{
		BOOL bFinish = TRUE;
		for(int i = 0; i < oTask.Devices.size(); i++)
		{
			if(!poTaskTmp[i].Finish)
				bFinish = FALSE;
		}
		
		if(bFinish)
			break;

		Sleep(oTask.TurnsElapse);
	}

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