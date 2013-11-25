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

void CoalAssayDB::GetCoal(CoalInfo& lCoal
				, const SQLResult *lpSet
				, int nRowIndex)
{
	if(!lpSet || (lpSet->Cols.size() <= 0) || 
		(lpSet->Rows.size() <= 0) || 
		(nRowIndex >= lpSet->Rows.size() ||
		(lpSet->Rows[0].size() <= 0))
		)
		return;
	
	for(int i = 0; i < lpSet->Cols.size(); i++)
	{
		if(!wcscmp(lpSet->Cols[i].c_str(), L"CoalLotNum"))
		{
			lCoal.SetCoalLotNum(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayCode"))
		{
			lCoal.SetAssayCode(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayDate"))
		{
			TIMESTAMP_STRUCT ts;
			swscanf(lpSet->Rows[nRowIndex][i].c_str()
					, TIMEFORMAT
					, &ts.year
					, &ts.month
					, &ts.day);
			lCoal.SetAssayDate(ts);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"SampleDate"))
		{
			TIMESTAMP_STRUCT ts;
			swscanf(lpSet->Rows[nRowIndex][i].c_str()
					, TIMEFORMAT
					, &ts.year
					, &ts.month
					, &ts.day);
			lCoal.SetSampleDate(ts);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayType"))
		{
			lCoal.SetAssayType((AssayType)_wtoi(lpSet->Rows[nRowIndex][i].c_str()));
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayStaff"))
		{
			lCoal.SetAssayStaff(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"SampleStaff"))
		{
			lCoal.SetSampleStaff(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"StageName"))
		{
			lCoal.SetStageName(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"WorksName"))
		{
			lCoal.SetWorksName(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"State"))
		{
			lCoal.SetState(_wtoi(lpSet->Rows[nRowIndex][i].c_str()));
		}
	}		
}

void CoalAssayDB::GetAshFusionPoint(AshFusionPoint_t& lash, 
				const SQLResult* lpSet, 
				int nRowIndex)
{

}

void CoalAssayDB::GetCaloriMeter(CaloriMeter_t& lcm, 
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
	{	//[Qgrd],[Qgrad],[Qnetar],[Qb]
		if(!wcscmp(lpSet->Cols[i].c_str(), L"Qgrd"))
		{
			lcm.m_dQgr_d = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Qgrad"))
		{
			lcm.m_dQgr_a = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Qnetar"))
		{
			lcm.m_dQnet_ar = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Qb"))
		{
			lcm.m_dQb_ad = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Qgr_d"))
		{
			lcm.m_dQgr_d = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Qgr_a"))
		{
			lcm.m_dQgr_a = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Qnet_ar"))
		{
			lcm.m_dQnet_ar = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Qb_ad"))
		{
			lcm.m_dQb_ad = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		//[AssayCode],[DeviceID],[AssayDate],[AssayStaff]
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayCode"))
		{
			wcscpy(lcm.m_szAssayCode, lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"DeviceID"))
		{
			lcm.m_nDeviceID = _wtoi(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayDate"))
		{
			swscanf(lpSet->Rows[nRowIndex][i].c_str()
				   ,L"%4d-%2d-%2d"
				   , &lcm.m_tsAssayDate.year, &lcm.m_tsAssayDate.month, &lcm.m_tsAssayDate.day);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayStaff"))
		{
			wcscpy(lcm.m_szAssayStaff, lpSet->Rows[nRowIndex][i].c_str());
		}
	}
}

void CoalAssayDB::GetElementAnalyzer(ElementAnalyzer_t& lea, 
				const SQLResult* lpSet, 
				int nRowIndex)
{

}

void CoalAssayDB::GetLightWaveMeter(LightWaveMeter_t& llwm, 
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
	{	//[Moisture]
		if(!wcscmp(lpSet->Cols[i].c_str(), L"Moisture"))
		{
			llwm.m_dMar = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"Mar"))
		{
			llwm.m_dMar = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayCode"))
		{
			wcscpy(llwm.m_szAssayCode, lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"DeviceID"))
		{
			llwm.m_nDeviceID = _wtoi(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayDate"))
		{
			swscanf(lpSet->Rows[nRowIndex][i].c_str()
				   ,L"%4d-%2d-%2d"
				   , &llwm.m_tsAssayDate.year, &llwm.m_tsAssayDate.month, &llwm.m_tsAssayDate.day);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayStaff"))
		{
			wcscpy(llwm.m_szAssayStaff, lpSet->Rows[nRowIndex][i].c_str());
		}
	}
}
void CoalAssayDB::GetSulfurDetector(SulfurDetector_t& lsd, 
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
	{	//[空干基全硫],[干基全硫]
		if(!wcscmp(lpSet->Cols[i].c_str(), L"空干基全硫"))
		{
			lsd.m_dSt_ad = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"干基全硫"))
		{
			lsd.m_dSt_d = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"St_ad"))
		{
			lsd.m_dSt_ad = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"St_d"))
		{
			lsd.m_dSt_d = _wtof(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayCode"))
		{
			wcscpy(lsd.m_szAssayCode, lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"DeviceID"))
		{
			lsd.m_nDeviceID = _wtoi(lpSet->Rows[nRowIndex][i].c_str());
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayDate"))
		{
			swscanf(lpSet->Rows[nRowIndex][i].c_str()
				   ,L"%4d-%2d-%2d"
				   , &lsd.m_tsAssayDate.year, &lsd.m_tsAssayDate.month, &lsd.m_tsAssayDate.day);
		}
		else if(!wcscmp(lpSet->Cols[i].c_str(), L"AssayStaff"))
		{
			wcscpy(lsd.m_szAssayStaff, lpSet->Rows[nRowIndex][i].c_str());
		}
	}
}

void CoalAssayDB::GetWorkPointInstrument(WorkPointInstrument_t& lwpi, 
				const SQLResult* lpSet, 
				int nRowIndex)
{

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

int CoalAssayDB::SelectUnChecked(vector<CoalInfo>& arrCoal
								 , vector<MergeTable>& arrMerge)
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
			 L"EXEC [dbo].SelectUnChecked '%s'",
			 m_pcswToken);

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	if(m_pSet->Rows.size() > 0 && m_pSet->Cols.size() > 0)
	{
		nRetCode = m_pSet->Rows.size();
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{			
			CoalInfo ci;
			GetCoal(ci, m_pSet, i);
			arrCoal.push_back(ci);

			SQLResult cmRst;
			SQLResult lwmRst;
			SQLResult sdRst;
			MergeTable mt;

			memset(&mt, 0, sizeof(mt));
			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						 [Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar] FROM CaloriMeter WHERE [AssayCode] = '%s'"
					 , ci.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, &cmRst);
			CaloriMeter_t cm;
			for(int j = 0; j < cmRst.Rows.size(); j++)
			{
				GetCaloriMeter(cm, &cmRst, j);
				mt.m_oCaloriMeter = cm;
			}			

			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						 [Mar] FROM LightWaveMeter WHERE [AssayCode] = '%s'"
					 , ci.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, &lwmRst);
			LightWaveMeter_t lwm;
			for(int j = 0; j < lwmRst.Rows.size(); j++)
			{				
				GetLightWaveMeter(lwm, &lwmRst, j);
				mt.m_oLightWaveMeter = lwm;
			}			

			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						 [St_ad],[St_d] FROM SulfurDetector WHERE [AssayCode] = '%s'"
					, ci.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, &sdRst);
			SulfurDetector_t sd;
			for(int j = 0; j < sdRst.Rows.size(); j++)
			{
				GetSulfurDetector(sd, &sdRst, j);
				mt.m_oSulfurDetector = sd;
			}			
			arrMerge.push_back(mt);
		}
	}
	else
	{
		nRetCode = LOGIC_NODATA;
		SetErrorMsg(_T("No Data"));
	}
	return nRetCode;
}

int CoalAssayDB::CorrespondingConnect(DeviceType enumType
							, LPCWSTR lpszConn)
{
	int nRet = SQL_ERROR;

	switch(enumType)
	{
	case DeviceType::AshFusionPoint:
		nRet = this->m_oDbcAFP.Connect(lpszConn);
		break;
	case DeviceType::CaloriMeter:
		nRet = this->m_oDbcCM.Connect(lpszConn);
		break;
	case DeviceType::ElementAnalyzer:
		nRet = this->m_oDbcEA.Connect(lpszConn);
		break;
	case DeviceType::LightWaveMeter:
		nRet = this->m_oDbcLWM.Connect(lpszConn);
		break;
	case DeviceType::SulfurDetector:
		nRet = this->m_oDbcSD.Connect(lpszConn);
		break;
	case DeviceType::WorkPointInstrument:
		nRet = this->m_oDbcWPI.Connect(lpszConn);
		break;
	default:
		nRet = SQL_ERROR;
		break;
	}

	return nRet;
}

int CoalAssayDB::CorrespondingConnect(DeviceType enumType,
							LPCWSTR lpszDriver,
							LPCWSTR lpszServer,
							LPCWSTR lpszDBName,
							LPCWSTR lpszUid,
							LPCWSTR lpszPwd)
{
	int nRet = SQL_ERROR;

	switch(enumType)
	{
	case DeviceType::AshFusionPoint:
		nRet = this->m_oDbcAFP.Connect(lpszDriver, lpszServer,
									   lpszDBName, lpszUid,
									   lpszPwd);
		break;
	case DeviceType::CaloriMeter:
		nRet = this->m_oDbcCM.Connect(lpszDriver, lpszServer,
									  lpszDBName, lpszUid,
									  lpszPwd);
		break;
	case DeviceType::ElementAnalyzer:
		nRet = this->m_oDbcEA.Connect(lpszDriver, lpszServer,
									  lpszDBName, lpszUid,
									  lpszPwd);
		break;
	case DeviceType::LightWaveMeter:
		nRet = this->m_oDbcLWM.Connect(lpszDriver, lpszServer,
									   lpszDBName, lpszUid,
									   lpszPwd);
		break;
	case DeviceType::SulfurDetector:
		nRet = this->m_oDbcSD.Connect(lpszDriver, lpszServer,
									  lpszDBName, lpszUid,
									  lpszPwd);
		break;
	case DeviceType::WorkPointInstrument:
		nRet = this->m_oDbcWPI.Connect(lpszDriver, lpszServer,
									   lpszDBName, lpszUid,
									   lpszPwd);
		break;
	default:
		nRet = SQL_ERROR;
		break;
	}

	return nRet;
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
	WCHAR wcsQueryString[1024] = L"";
	
	for(int i = 0; i < oTask.Devices.size(); i++)
	{
		switch(oTask.Devices[i])
		{
		case DeviceType::AshFusionPoint:
			// add to the server
			wsprintf(wcsQueryString,
					 L"INSERT INTO [AshFusionPoint] ([AssayCode]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, m_pSet);			
			break;
		case DeviceType::CaloriMeter:
			// add to the client pc
			wsprintf(wcsQueryString, 
					 L"INSERT INTO [win5emdb] ([Number]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->m_oDbcCM.ExecuteQuery(wcsQueryString, m_pSet);
			// add to the server
			wsprintf(wcsQueryString,
					 L"INSERT INTO [CaloriMeter] ([AssayCode]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, m_pSet);
			break;
		case DeviceType::ElementAnalyzer:
			// add to the server
			wsprintf(wcsQueryString,
					 L"INSERT INTO [ElementAnalyzer] ([AssayCode]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, m_pSet);			
			break;
		case DeviceType::LightWaveMeter:
			// add to the client pc
			wsprintf(wcsQueryString, 
					 L"INSERT INTO [TestResult] ([SerialNumber]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->m_oDbcLWM.ExecuteQuery(wcsQueryString, m_pSet);
			// add to the server
			wsprintf(wcsQueryString,
					 L"INSERT INTO [LightWaveMeter] ([AssayCode]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, m_pSet);
			break;
		case DeviceType::SulfurDetector:
			// add to the client pc
			wsprintf(wcsQueryString, 
					 L"INSERT INTO [AnalysisData] ([试样编号]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());		
			nRetCode = this->m_oDbcSD.ExecuteQuery(wcsQueryString, m_pSet);
			// add to the server
			wsprintf(wcsQueryString,
					 L"INSERT INTO [SulfurDetector] ([AssayCode]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, m_pSet);
			break;
		case DeviceType::WorkPointInstrument:
			// add to the client pc
			wsprintf(wcsQueryString, 
					 L"INSERT INTO [win5emdb] ([SerialNumber]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->m_oDbcCM.ExecuteQuery(wcsQueryString, m_pSet);
			// add to the server
			wsprintf(wcsQueryString,
					 L"INSERT INTO [WorkPointInstrument] ([AssayCode]) VALUES('%s')"
					 , oTask.CoalInfo.GetAssayCode());
			nRetCode = this->ExecuteQuery(wcsQueryString, m_pSet);
			break;
		default:
			nRetCode = FALSE;
			break;
		}		
	}

	return nRetCode;
}

int CoalAssayDB::AddCorresponding(AssayTask& loTask, AssayTask *lpTask)
{
	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024] = L"";
	
	for(int i = 0; i < loTask.Devices.size(); i++)
	{
		AssayTask *lpTmp = &lpTask[i];
		switch(lpTmp->CurrentDevice)
		{
		case DeviceType::AshFusionPoint:
			
			break;
		case DeviceType::CaloriMeter:
			{
				for(int j = 0; j < lpTask->DataObjects.size(); j++)
				{
					CaloriMeter_t *pCm = (CaloriMeter_t *)lpTmp->DataObjects[j];
					AddCaloriMeter(*pCm);
				}
				break;
			}
		case DeviceType::ElementAnalyzer:
			
			break;
		case DeviceType::LightWaveMeter:
			{
				for(int j = 0; j < lpTask->DataObjects.size(); j++)
				{
					LightWaveMeter_t *pLwm = (LightWaveMeter_t *)lpTmp->DataObjects[j];
					AddLightWaveMeter(*pLwm);
				}
				break;
			}
		case DeviceType::SulfurDetector:
			{
				for(int j = 0; j < lpTask->DataObjects.size(); j++)
				{
					SulfurDetector_t *pSd = (SulfurDetector_t *)lpTmp->DataObjects[j];
					AddSulfurDetector(*pSd);
				}
				break;
			}
		case DeviceType::WorkPointInstrument:
			{
				for(int j = 0; j < lpTask->DataObjects.size(); j++)
				{
					WorkPointInstrument_t *pWpi = (WorkPointInstrument_t *)lpTmp->DataObjects[j];
					AddWorkPointInstrument(*pWpi);
				}
				break;
			}
		default:
			nRetCode = FALSE;
			break;
		}		
	}

	return nRetCode;
}

int CoalAssayDB::SetCorresponding(const DeviceType& enumDest, vector<LPVOID> arrDataObjects)
{
	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024] = L"";

	switch(enumDest)
	{
	case DeviceType::AshFusionPoint:
			
		break;
	case DeviceType::CaloriMeter:
		{
			for(int j = 0; j < arrDataObjects.size(); j++)
			{
				CaloriMeter_t *pCm = (CaloriMeter_t *)arrDataObjects[j];
				SetCaloriMeter(*pCm);
			}
			break;
		}
	case DeviceType::ElementAnalyzer:
			
		break;
	case DeviceType::LightWaveMeter:
		{
			for(int j = 0; j < arrDataObjects.size(); j++)
			{
				LightWaveMeter_t *pLwm = (LightWaveMeter_t *)arrDataObjects[j];
				SetLightWaveMeter(*pLwm);
			}
			break;
		}
	case DeviceType::SulfurDetector:
		{
			for(int j = 0; j < arrDataObjects.size(); j++)
			{
				SulfurDetector_t *pSd = (SulfurDetector_t *)arrDataObjects[j];
				SetSulfurDetector(*pSd);
			}
			break;
		}
	case DeviceType::WorkPointInstrument:
		{
			for(int j = 0; j < arrDataObjects.size(); j++)
			{
				WorkPointInstrument_t *pWpi = (WorkPointInstrument_t *)arrDataObjects[j];
				SetWorkPointInstrument(*pWpi);
			}
			break;
		}
	default:
		nRetCode = FALSE;
		break;
	}		

	return nRetCode;
}

// submit the assay data to the corresponding database on the server.
// before auditing,there is one blank record on the server when
// you call CoalAssayDB::ExecuteTask().
//int CoalAssayDB::AuditCorresponding(AssayTask& loTask)
//{
//	SQLSMALLINT	nRetCode = SQL_ERROR;
//	WCHAR wcsQueryString[1024] = L"";
//	
//	for(int i = 0; i < loTask.Devices.size(); i++)
//	{
//		switch(loTask.Devices[i])
//		{
//		case DeviceType::AshFusionPoint:
//			
//			break;
//		case DeviceType::CaloriMeter:
//			{
//				wsprintf(wcsQueryString,);
//				break;
//			}
//		case DeviceType::ElementAnalyzer:
//			
//			break;
//		case DeviceType::LightWaveMeter:
//			{
//				break;
//			}
//		case DeviceType::SulfurDetector:
//			{
//				break;
//			}
//		case DeviceType::WorkPointInstrument:
//			{
//				break;
//			}
//		default:
//			nRetCode = FALSE;
//			break;
//		}		
//	}
//
//	return nRetCode;
//}

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

int CoalAssayDB::ExecuteTask(AssayTask& oTask, AssayTask** lppTask)
{
	int nId = -1;
	int nRetCode = 1;	

	if(nRetCode = AddCoalInfo(oTask.CoalInfo, &nId))
		return LOGIC_CREATETASKFAIL;
	

	if((nRetCode = AddCorrespondingBlank(oTask)) < 0)
	{
		return nRetCode;
	}

	// Create Task thread for each related table
	AssayTask *poTaskTmp = new AssayTask[oTask.Devices.size()];
	(*lppTask) = poTaskTmp;
	for(int i = 0; i < oTask.Devices.size(); i++)
	{
		poTaskTmp[i] = oTask;
		switch(oTask.Devices[i])
		{
		case DeviceType::AshFusionPoint:
			poTaskTmp[i].CurrentDevice = DeviceType::AshFusionPoint;
			poTaskTmp[i].SetDataDriver(&this->m_oDbcAFP);
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::CaloriMeter:
			poTaskTmp[i].CurrentDevice = DeviceType::CaloriMeter;
			poTaskTmp[i].SetDataDriver(&this->m_oDbcCM);
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::ElementAnalyzer:
			poTaskTmp[i].CurrentDevice = DeviceType::ElementAnalyzer;
			poTaskTmp[i].SetDataDriver(&this->m_oDbcEA);
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::LightWaveMeter:
			poTaskTmp[i].CurrentDevice = DeviceType::LightWaveMeter;
			poTaskTmp[i].SetDataDriver(&this->m_oDbcLWM);
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::SulfurDetector:
			poTaskTmp[i].CurrentDevice = DeviceType::SulfurDetector;
			poTaskTmp[i].SetDataDriver(&this->m_oDbcSD);
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		case DeviceType::WorkPointInstrument:
			poTaskTmp[i].CurrentDevice = DeviceType::WorkPointInstrument;
			poTaskTmp[i].SetDataDriver(&this->m_oDbcWPI);
			poTaskTmp[i].ThreadHandle = CreateThread(NULL, 0, AssayTaskProc, &poTaskTmp[i], 0, &poTaskTmp[i].ThreadId);
			CloseHandle(poTaskTmp[i].ThreadHandle);
			poTaskTmp[i].ThreadHandle = NULL;
			break;
		default:
			nRetCode = LOGIC_ERRORTASK;
			break;
		}
	}

	HANDLE hWatcher = NULL;
	DWORD ntid = 0;
	WatchThreadParam_t *pWatcher = new WatchThreadParam_t;
	pWatcher->pCoalAssayDB = this;
	pWatcher->pAssayTask = &oTask;
	pWatcher->pAssayResult = poTaskTmp;
	hWatcher = CreateThread(NULL, 0, WatchAssayTaskProc, pWatcher, 0, &ntid);
	CloseHandle(hWatcher);
	
	return nRetCode;
}

int CoalAssayDB::AuditTask(LPCWSTR wcsAssayCode, int lnState)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];

	swprintf(wcsQueryString
			 , L"EXEC [dbo].CheckTask '%s','%s','%d'"
			 , this->m_pcswToken
			 , wcsAssayCode
			 , lnState);

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	if(nRetCode < 0 || m_pSet->nAffected <= 0)
	{
		return LOGIC_NODATA;
	}
	else
	{
		//AddCorresponding(loTask, lpTask);
		//AuditCorresponding(loTask);
	}

	return nRetCode;
}

// unique search by AssayCode
int CoalAssayDB::Search(vector<CoalInfo>& larrci
						, vector<MergeTable>& larrmt
						, LPCWSTR wcsAssayCode)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];

	wsprintf(wcsQueryString
			 , L"SELECT \
					[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],\
					[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],\
					[StageName],[WorksName],[State]\
				FROM [CoalInfo] WHERE [AssayCode] = '%s'"
			 , wcsAssayCode);

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	if(m_pSet->Cols.size() <= 0 || m_pSet->Rows.size() <= 0)
	{
		return LOGIC_NODATA;
	}
	else
	{		
		MergeTable mt;
		memset(&mt, 0, sizeof(mt));
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{
			CoalInfo ci;			
			GetCoal(ci, m_pSet, i);
			larrci.push_back(ci);
		}

		wsprintf(wcsQueryString
				 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
					[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar] FROM CaloriMeter WHERE [AssayCode] = '%s'"
				 , wcsAssayCode);
		nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{
			CaloriMeter_t tmp;
			memset(&tmp, 0, sizeof(tmp));
			GetCaloriMeter(tmp, m_pSet, i);
			mt.m_oCaloriMeter = tmp;
		}

		wsprintf(wcsQueryString
				 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
					[AshFusionT1],[AshFusionT2],[AshFusionT3],[AshFusionT4] FROM AshFusionPoint WHERE [AssayCode] = '%s'"
				 , wcsAssayCode);
		nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{
			AshFusionPoint_t tmp;
			memset(&tmp, 0, sizeof(tmp));
			GetAshFusionPoint(tmp, m_pSet, i);
			mt.m_oAshFusionPoint = tmp;
		}

		wsprintf(wcsQueryString
				 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
					[Had] FROM ElementAnalyzer WHERE [AssayCode] = '%s'"
				 , wcsAssayCode);
		nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{
			ElementAnalyzer_t tmp;
			memset(&tmp, 0, sizeof(tmp));
			GetElementAnalyzer(tmp, m_pSet, i);
			mt.m_oElementAnalyzer = tmp;
		}

		wsprintf(wcsQueryString
				 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
					[Mar] FROM LightWaveMeter WHERE [AssayCode] = '%s'"
				 , wcsAssayCode);
		nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{
			LightWaveMeter_t tmp;
			memset(&tmp, 0, sizeof(tmp));
			GetLightWaveMeter(tmp, m_pSet, i);
			mt.m_oLightWaveMeter = tmp;
		}

		wsprintf(wcsQueryString
				 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
					[St_ad],[St_d] FROM SulfurDetector WHERE [AssayCode] = '%s'"
				 , wcsAssayCode);
		nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{
			SulfurDetector_t tmp;
			memset(&tmp, 0, sizeof(tmp));
			GetSulfurDetector(tmp, m_pSet, i);
			mt.m_oSulfurDetector = tmp;
		}

		wsprintf(wcsQueryString
				 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
					[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar] FROM WorkPointInstrument WHERE [AssayCode] = '%s'"
				 , wcsAssayCode);
		nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{
			WorkPointInstrument_t tmp;
			memset(&tmp, 0, sizeof(tmp));
			GetWorkPointInstrument(tmp, m_pSet, i);
			mt.m_oWorkPointInstrument = tmp;
		}

		larrmt.push_back(mt);
	}

	return nRetCode;
}

// dim search by "AND Condition"
int CoalAssayDB::Search(vector<CoalInfo>& larrci
						, vector<MergeTable>& larrmt
						, LPCWSTR wcsAssayStaff						
						, const TIMESTAMP_STRUCT *tsBegin
						, const TIMESTAMP_STRUCT *tsEnd)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];

	if(wcsAssayStaff == NULL && (tsBegin == NULL || tsEnd == NULL))
	{
		return SQL_BADQUERY;
	}
	else if(tsBegin == NULL || tsEnd == NULL)
	{
		wsprintf(wcsQueryString
				 , L"SELECT \
						[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],\
						[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],\
						[StageName],[WorksName],[State]\
					FROM [CoalInfo] WHERE [AssayStaff] = '%s'"
				 , wcsAssayStaff);	
	}
	else if(wcsAssayStaff == NULL)
	{
		wsprintf(wcsQueryString
				 , L"SELECT \
						[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],\
						[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],\
						[StageName],[WorksName],[State]\
						FROM [CoalInfo] WHERE [AssayDate] <= '%4d-%2d-%2d' AND [AssayDate] >= '%4d-%2d-%2d'"
				 , tsEnd->year, tsEnd->month, tsEnd->day
				 , tsBegin->year, tsBegin->month, tsBegin->day);
	}
	else
	{
		wsprintf(wcsQueryString
				 , L"SELECT \
						[CoalLotNum],[CoalInfo].[AssayCode],[CoalInfo].[AssayDate],\
						[SampleDate],[AssayType],[CoalInfo].[AssayStaff],[SampleStaff],\
						[StageName],[WorksName],[State]\
						FROM [CoalInfo] WHERE [AssayDate] <= '%4d-%2d-%2d' AND [AssayDate] >= '%4d-%2d-%2d' \
						AND [AssayStaff] = '%s'"
				 , tsEnd->year, tsEnd->month, tsEnd->day
				 , tsBegin->year, tsBegin->month, tsBegin->day
				 , wcsAssayStaff);	
	}

	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	if(m_pSet->Cols.size() <= 0 || m_pSet->Rows.size() <= 0)
	{
		return LOGIC_NODATA;
	}
	else
	{
		MergeTable mt;
		memset(&mt, 0, sizeof(mt));
		for(int i = 0; i < m_pSet->Rows.size(); i++)
		{				
			CoalInfo ci;
			GetCoal(ci, m_pSet, i);
			larrci.push_back(ci);

			LPCWSTR wcsAssayCode = ci.GetAssayCode();
			SQLResult set;
			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						,[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar] FROM CaloriMeter WHERE [AssayCode] = '%s'"
					 , wcsAssayCode);
			nRetCode = ExecuteQuery(wcsQueryString, &set);
			for(int i = 0; i < set.Rows.size(); i++)
			{
				CaloriMeter_t tmp;
				memset(&tmp, 0, sizeof(tmp));
				GetCaloriMeter(tmp, &set, i);
				mt.m_oCaloriMeter = tmp;
			}

			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						[AshFusionT1],[AshFusionT2],[AshFusionT3],[AshFusionT4] FROM AshFusionPoint WHERE [AssayCode] = '%s'"
					 , wcsAssayCode);
			nRetCode = ExecuteQuery(wcsQueryString, &set);
			for(int i = 0; i < set.Rows.size(); i++)
			{
				AshFusionPoint_t tmp;
				memset(&tmp, 0, sizeof(tmp));
				GetAshFusionPoint(tmp, &set, i);
				mt.m_oAshFusionPoint = tmp;
			}

			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						[Had] FROM ElementAnalyzer WHERE [AssayCode] = '%s'"
					 , wcsAssayCode);
			nRetCode = ExecuteQuery(wcsQueryString, &set);
			for(int i = 0; i < set.Rows.size(); i++)
			{
				ElementAnalyzer_t tmp;
				memset(&tmp, 0, sizeof(tmp));
				GetElementAnalyzer(tmp, &set, i);
				mt.m_oElementAnalyzer = tmp;
			}

			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						[Mar] FROM LightWaveMeter WHERE [AssayCode] = '%s'"
					 , wcsAssayCode);
			nRetCode = ExecuteQuery(wcsQueryString, &set);
			for(int i = 0; i < set.Rows.size(); i++)
			{
				LightWaveMeter_t tmp;
				memset(&tmp, 0, sizeof(tmp));
				GetLightWaveMeter(tmp, &set, i);
				mt.m_oLightWaveMeter = tmp;
			}

			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						[St_ad],[St_d] FROM SulfurDetector WHERE [AssayCode] = '%s'"
					 , wcsAssayCode);
			nRetCode = ExecuteQuery(wcsQueryString, &set);
			for(int i = 0; i < set.Rows.size(); i++)
			{
				SulfurDetector_t tmp;
				memset(&tmp, 0, sizeof(tmp));
				GetSulfurDetector(tmp, &set, i);
				mt.m_oSulfurDetector = tmp;
			}

			wsprintf(wcsQueryString
					 , L"SELECT [AssayCode],[DeviceID],[AssayDate],[AssayStaff]\
						[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar] FROM WorkPointInstrument WHERE [AssayCode] = '%s'"
					 , wcsAssayCode);
			nRetCode = ExecuteQuery(wcsQueryString, &set);
			for(int i = 0; i < set.Rows.size(); i++)
			{
				WorkPointInstrument_t tmp;
				memset(&tmp, 0, sizeof(tmp));
				GetWorkPointInstrument(tmp, &set, i);
				mt.m_oWorkPointInstrument = tmp;
			}

			larrmt.push_back(mt);
		}		
	}

	return nRetCode;
}

int CoalAssayDB::AddAshFusionPoint(AshFusionPoint_t& lash)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	return nRetCode;
}

int CoalAssayDB::AddCaloriMeter(CaloriMeter_t& lpCm)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString, 
				L"INSERT INTO [CaloriMeter] \
				([AssayCode],[DeviceID],[AssayDate],[AssayStaff],[Qb_ad],[Qgr_d],[Qgr_a],[Qnet_ar]) \
				VALUES('%s','%d','%4d-%2d-%2d','%s','%f','%f','%f','%f')"
				, lpCm.m_szAssayCode
				, lpCm.m_nDeviceID
				, lpCm.m_tsAssayDate.year, lpCm.m_tsAssayDate.month, lpCm.m_tsAssayDate.day
				, lpCm.m_szAssayStaff
				, lpCm.m_dQb_ad							  
				, lpCm.m_dQgr_d
				, lpCm.m_dQgr_a
				, lpCm.m_dQnet_ar);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

int CoalAssayDB::AddElementAnalyzer(ElementAnalyzer_t& lea)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];

	return nRetCode;
}

int CoalAssayDB::AddLightWaveMeter(LightWaveMeter_t& llwm)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString, 
				L"INSERT INTO [LightWaveMeter] \
				([AssayCode],[DeviceID],[AssayDate],[AssayStaff],[Mar]) \
				VALUES('%s','%d','%4d-%2d-%2d','%s','%f')"
				, llwm.m_szAssayCode
				, llwm.m_nDeviceID
				, llwm.m_tsAssayDate.year, llwm.m_tsAssayDate.month, llwm.m_tsAssayDate.day
				, llwm.m_szAssayStaff
				, llwm.m_dMar);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

int CoalAssayDB::AddSulfurDetector(SulfurDetector_t& lsd)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString, 
				L"INSERT INTO [SulfurDetector] \
				([AssayCode],[DeviceID],[AssayDate],[AssayStaff],[St_ad],[St_d]) \
				VALUES('%s','%d','%4d-%2d-%2d','%s','%f','%f')"
				, lsd.m_szAssayCode
				, lsd.m_nDeviceID
				, lsd.m_tsAssayDate.year, lsd.m_tsAssayDate.month, lsd.m_tsAssayDate.day
				, lsd.m_szAssayStaff
				, lsd.m_dSt_ad
				, lsd.m_dSt_d);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

int CoalAssayDB::AddWorkPointInstrument(WorkPointInstrument_t& lwpi)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString, 
				L"INSERT INTO [WorkPointInstrument] \
				([AssayCode],[DeviceID],[AssayDate],[AssayStaff] \
				,[Vd],[Vad],[Var],[Vdaf],[Mad],[Aad],[Aar]) \
				VALUES('%s','%d','%4d-%2d-%2d','%s' \
				,'%f','%f','%f','%f','%f','%f','%f')"
				, lwpi.m_szAssayCode
				, lwpi.m_nDeviceID
				, lwpi.m_tsAssayDate.year, lwpi.m_tsAssayDate.month, lwpi.m_tsAssayDate.day
				, lwpi.m_szAssayStaff
				, lwpi.m_dVd
				, lwpi.m_dVad
				, lwpi.m_dVar
				, lwpi.m_dVdaf
				, lwpi.m_dMad
				, lwpi.m_dAad
				, lwpi.m_dAar);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

int CoalAssayDB::SetAshFusionPoint(AshFusionPoint_t& lash)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	return nRetCode;
}

int CoalAssayDB::SetCaloriMeter(CaloriMeter_t& lpCm)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString 
			 , L"UPDATE [CaloriMeter] \
				 SET [AssayDate]='%4d-%2d-%2d',[AssayStaff]='%s',[Qb_ad]='%f',[Qgr_d]='%f',[Qgr_a]='%f',[Qnet_ar]='%f'\
				 WHERE [AssayCode]='%s'"							  
			 , lpCm.m_tsAssayDate.year, lpCm.m_tsAssayDate.month, lpCm.m_tsAssayDate.day
			 , lpCm.m_szAssayStaff
			 , lpCm.m_dQb_ad							  
			 , lpCm.m_dQgr_d
			 , lpCm.m_dQgr_a
			 , lpCm.m_dQnet_ar
			 , lpCm.m_szAssayCode);
	nRetCode = this->ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

int CoalAssayDB::SetElementAnalyzer(ElementAnalyzer_t& lea)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	return nRetCode;
}

int CoalAssayDB::SetLightWaveMeter(LightWaveMeter_t& llwm)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString
			 , L"UPDATE [LightWaveMeter] \
				 SET [AssayDate]='%4d-%2d-%2d',[AssayStaff]='%s',[Mar]='%f' \
				 WHERE [AssayCode]='%s'"
			 , llwm.m_tsAssayDate.year, llwm.m_tsAssayDate.month, llwm.m_tsAssayDate.day
			 , llwm.m_szAssayStaff
			 , llwm.m_dMar
			 , llwm.m_szAssayCode);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

int CoalAssayDB::SetSulfurDetector(SulfurDetector_t& lsd)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString
			 , L"UPDATE [SulfurDetector] \
				 SET [AssayDate]='%4d-%2d-%2d',[AssayStaff]='%s',[St_ad]='%f',[St_d]='%f'\
				 WHERE [AssayCode]='%s'"
			 , lsd.m_tsAssayDate.year, lsd.m_tsAssayDate.month, lsd.m_tsAssayDate.day
			 , lsd.m_szAssayStaff
			 , lsd.m_dSt_ad
			 , lsd.m_dSt_d
			 , lsd.m_szAssayCode);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

int CoalAssayDB::SetWorkPointInstrument(WorkPointInstrument_t& lwpi)
{
	if(!IsConnected())
		return SQL_NONCONNECTED;
	if(!m_pSet)
		return SQL_NONBINDING;
	if(!m_pcswToken)
		return LOGIC_NOLOGINED;

	SQLSMALLINT	nRetCode = SQL_ERROR;
	WCHAR wcsQueryString[1024];
	swprintf(wcsQueryString
				, L"UPDATE [WorkPointInstrument] \
					SET [AssayDate]='%4d-%2d-%2d',[AssayStaff]='%s'\
						,[Vd]='%f',[Vad]='%f',[Var]='%f',[Vdaf]='%f'\
						,[Mad]='%f',[Aad]='%f',[Aar]='%f')\
					WHERE [AssayCode]='%s'"							 
				, lwpi.m_tsAssayDate.year, lwpi.m_tsAssayDate.month, lwpi.m_tsAssayDate.day
				, lwpi.m_szAssayStaff
				, lwpi.m_dVd
				, lwpi.m_dVad
				, lwpi.m_dVar
				, lwpi.m_dVdaf
				, lwpi.m_dMad
				, lwpi.m_dAad
				, lwpi.m_dAar
				, lwpi.m_szAssayCode);
	nRetCode = ExecuteQuery(wcsQueryString, m_pSet);
	return nRetCode;
}

DWORD WINAPI WatchAssayTaskProc(LPVOID lpParam)
{
	WatchThreadParam_t *pWatcher = (WatchThreadParam_t*)lpParam;

	// wait for all assay task is finish
	while(TRUE)
	{
		BOOL bFinish = TRUE;
		for(int i = 0; i < pWatcher->pAssayTask->Devices.size(); i++)
		{
			if(!pWatcher->pAssayResult[i].Finish)
			{
				bFinish = FALSE;
			}
			else
			{
				pWatcher->pCoalAssayDB->SetCorresponding(pWatcher->pAssayResult[i].CurrentDevice
								 , pWatcher->pAssayResult[i].DataObjects);
			}
		}
		
		if(bFinish)
		{
			pWatcher->pAssayTask->Finish = TRUE;
			break;
		}
		Sleep(pWatcher->pAssayTask->TurnsElapse);
	}

	return 0;
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