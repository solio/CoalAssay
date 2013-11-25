#include "Def.h"
#include "DataTypes.h"
#include "OdbcDriver.h"
#include "Task.h"

DWORD WINAPI AssayTaskProc(LPVOID lpParam)
{
	DWORD dwRet = 0;
	AssayTask *pTask = (AssayTask*)lpParam;

	switch(pTask->CurrentDevice)
	{
	case DeviceType::AshFusionPoint:
		Task_AshFusionPoint(pTask);
		break;
	case DeviceType::CaloriMeter:
		Task_CaloriMeter(pTask);
		break;
	case DeviceType::ElementAnalyzer:
		Task_ElementAnalyzer(pTask);
		break;
	case DeviceType::LightWaveMeter:
		Task_LightWaveMeter(pTask);
		break;
	case DeviceType::SulfurDetector:
		Task_SulfurDetector(pTask);
		break;
	case DeviceType::WorkPointInstrument:
		Task_WorkPointInstrument(pTask);
		break;
	default:

		break;
	}	
	return dwRet;
}

void Task_AshFusionPoint(AssayTask* pTask)
{
	WCHAR wcsQueryString[1024] = L"";
	int nCount = pTask->TimeOut / pTask->TurnsElapse + 1;
	int nRetCode = SQL_ERROR;

	while(nCount > 0)
	{
		wsprintf(wcsQueryString
				 , L""
				 , pTask->CoalInfo.GetAssayCode());
		nRetCode = pTask->GetDataDriver()->ExecuteQuery(wcsQueryString, &pTask->DataSet);
		if(nRetCode >= 0 
		   && pTask->DataSet.Cols.size() > 0
		   && pTask->DataSet.Rows.size() > 0)
		{
			for(int i = 0; i < pTask->DataSet.Rows.size(); i++)
			{

			}
			pTask->Success = TRUE;
			break;
		}
		Sleep(pTask->TurnsElapse);
		nCount--;
	}
	pTask->Finish = TRUE;
}

void Task_CaloriMeter(AssayTask* pTask)
{
	WCHAR wcsQueryString[1024] = L"";
	int nCount = pTask->TimeOut / pTask->TurnsElapse + 1;
	int nRetCode = SQL_ERROR;

	while(nCount > 0)
	{
		wsprintf(wcsQueryString
				 , L"SELECT [Qgrd],[Qgrad],[Qnetar],[Qb],[Testman],[Testtime] FROM [win5emdb] WHERE [Number] = '%s'\
				   AND Qgrd IS Not NULL AND Qgrad IS Not NULL AND Qnetar IS Not NULL AND Qb IS Not NULL \
				   AND Testman <> '' AND Testtime IS Not NULL"
				 , pTask->CoalInfo.GetAssayCode());
		nRetCode = pTask->GetDataDriver()->ExecuteQuery(wcsQueryString, &pTask->DataSet);
		if(nRetCode >= 0 
		   && pTask->DataSet.Cols.size() > 0
		   && pTask->DataSet.Rows.size() > 0)
		{
			for(int i = 0; i < pTask->DataSet.Rows.size(); i++)
			{
				CaloriMeter_t *pCm = new CaloriMeter_t;		
				pCm->m_dQgr_d = _wtof(pTask->DataSet.Rows[i][0].c_str());
				pCm->m_dQgr_a = _wtof(pTask->DataSet.Rows[i][1].c_str());
				pCm->m_dQnet_ar = _wtof(pTask->DataSet.Rows[i][2].c_str());
				pCm->m_dQb_ad = _wtof(pTask->DataSet.Rows[i][3].c_str());
				pCm->m_nDeviceID = DeviceType::CaloriMeter;
				wcscpy(pCm->m_szAssayCode, pTask->CoalInfo.GetAssayCode());
				wcscpy(pCm->m_szAssayStaff, pTask->DataSet.Rows[i][4].c_str());
				swscanf(pTask->DataSet.Rows[i][5].c_str()
						, TIMEFORMAT
						, &pCm->m_tsAssayDate.year
						, &pCm->m_tsAssayDate.month
						, &pCm->m_tsAssayDate.day);
				pTask->DataObjects.push_back(pCm);
			}
			pTask->Success = TRUE;
			break;
		}
		Sleep(pTask->TurnsElapse);
		nCount--;
	}
	pTask->Finish = TRUE;
}

void Task_ElementAnalyzer(AssayTask* pTask)
{
	WCHAR wcsQueryString[1024] = L"";
	int nCount = pTask->TimeOut / pTask->TurnsElapse + 1;
	int nRetCode = SQL_ERROR;

	while(nCount > 0)
	{
		wsprintf(wcsQueryString
				 , L""
				 , pTask->CoalInfo.GetAssayCode());
		nRetCode = pTask->GetDataDriver()->ExecuteQuery(wcsQueryString, &pTask->DataSet);
		if(nRetCode >= 0 
		   && pTask->DataSet.Cols.size() > 0
		   && pTask->DataSet.Rows.size() > 0)
		{
			for(int i = 0; i < pTask->DataSet.Rows.size(); i++)
			{

			}
			pTask->Success = TRUE;
			break;
		}
		Sleep(pTask->TurnsElapse);
		nCount--;
	}
	pTask->Finish = TRUE;
}

void Task_LightWaveMeter(AssayTask* pTask)
{
	WCHAR wcsQueryString[1024] = L"";
	int nCount = pTask->TimeOut / pTask->TurnsElapse + 1;
	int nRetCode = SQL_ERROR;

	while(nCount > 0)
	{
		wsprintf(wcsQueryString
				 , L"SELECT [Moisture],[Operator],[EndDate] FROM [TestResult] WHERE [SerialNumber] = '%s'\
				   AND [Moisture] IS Not NULL AND [Operator] <> '' AND [EndDate] IS NOT NULL"
				 , pTask->CoalInfo.GetAssayCode());
		nRetCode = pTask->GetDataDriver()->ExecuteQuery(wcsQueryString, &pTask->DataSet);
		if(nRetCode >= 0 
		   && pTask->DataSet.Cols.size() > 0
		   && pTask->DataSet.Rows.size() > 0)
		{
			for(int i = 0; i < pTask->DataSet.Rows.size(); i++)
			{
				LightWaveMeter_t *pLwm = new LightWaveMeter_t;
				pLwm->m_dMar = _wtof(pTask->DataSet.Rows[i][0].c_str());
				pLwm->m_nDeviceID = pTask->CurrentDevice;
				wcscpy(pLwm->m_szAssayCode, pTask->CoalInfo.GetAssayCode());
				wcscpy(pLwm->m_szAssayStaff, pTask->DataSet.Rows[i][1].c_str());
				swscanf(pTask->DataSet.Rows[i][2].c_str()
					, TIMEFORMAT
					, &pLwm->m_tsAssayDate.year
					, &pLwm->m_tsAssayDate.month
					, &pLwm->m_tsAssayDate.day);
				pTask->DataObjects.push_back(pLwm);
			}
			pTask->Success = TRUE;
			break;
		}
		Sleep(pTask->TurnsElapse);
		nCount--;
	}
	pTask->Finish = TRUE;
}

void Task_SulfurDetector(AssayTask* pTask)
{
	WCHAR wcsQueryString[1024] = L"";
	int nCount = pTask->TimeOut / pTask->TurnsElapse + 1;
	int nRetCode = SQL_ERROR;

	while(nCount > 0)
	{
		wsprintf(wcsQueryString
				 , L"SELECT [空干基全硫],[干基全硫],[化验员],[测试日期] FROM [AnalysisData] WHERE [试样编号] = '%s'\
					AND [空干基全硫] IS NOT NULL AND [干基全硫] IS NOT NULL \
					AND [化验员] <> '' AND [测试日期] IS NOT NULL"
				 , pTask->CoalInfo.GetAssayCode());
		nRetCode = pTask->GetDataDriver()->ExecuteQuery(wcsQueryString, &pTask->DataSet);
		if(nRetCode >= 0 
		   && pTask->DataSet.Cols.size() > 0
		   && pTask->DataSet.Rows.size() > 0)
		{
			for(int i = 0; i < pTask->DataSet.Rows.size(); i++)
			{
				SulfurDetector_t *pSd = new SulfurDetector_t;
				pSd->m_dSt_ad = _wtof(pTask->DataSet.Rows[i][0].c_str());
				pSd->m_dSt_d = _wtof(pTask->DataSet.Rows[i][1].c_str());
				pSd->m_nDeviceID = DeviceType::SulfurDetector;
				wcscpy(pSd->m_szAssayCode, pTask->CoalInfo.GetAssayCode());
				wcscpy(pSd->m_szAssayStaff, pTask->DataSet.Rows[i][2].c_str());
				swscanf(pTask->DataSet.Rows[i][3].c_str()
					, TIMEFORMAT
					, &pSd->m_tsAssayDate.year
					, &pSd->m_tsAssayDate.month
					, &pSd->m_tsAssayDate.day);
				pTask->DataObjects.push_back(pSd);
			}
			pTask->Success = TRUE;
			break;
		}
		Sleep(pTask->TurnsElapse);
		nCount--;
	}
	pTask->Finish = TRUE;
}

void Task_WorkPointInstrument(AssayTask* pTask)
{
	WCHAR wcsQueryString[1024] = L"";
	int nCount = pTask->TimeOut / pTask->TurnsElapse + 1;
	int nRetCode = SQL_ERROR;

	while(nCount > 0)
	{
		wsprintf(wcsQueryString
				 , L"SELECT [Ad],[Aad],[Vad],[Vd],[Vdaf],[Mad],[Operator],[Date] FROM [win5emdb] WHERE [SerialNumber] = '%s'\
				   AND [Aad] IS NOT NULL AND [Vad] IS NOT NULL AND [Vd] IS NOT NULL AND [Vdaf] IS NOT NULL AND [Mad] IS NOT NULL\
				   AND Testman <> '' AND Testtime IS Not NULL"
				 , pTask->CoalInfo.GetAssayCode());
		nRetCode = pTask->GetDataDriver()->ExecuteQuery(wcsQueryString, &pTask->DataSet);
		if(nRetCode >= 0 
		   && pTask->DataSet.Cols.size() > 0
		   && pTask->DataSet.Rows.size() > 0)
		{
			for(int i = 0; i < pTask->DataSet.Rows.size(); i++)
			{
				WorkPointInstrument_t *pWpi = new WorkPointInstrument_t;
				pWpi->m_dAd = _wtof(pTask->DataSet.Rows[i][0].c_str());
				pWpi->m_dAad = _wtof(pTask->DataSet.Rows[i][1].c_str());
				pWpi->m_dAar = pWpi->m_dAad;
				pWpi->m_dVad = _wtof(pTask->DataSet.Rows[i][2].c_str());
				pWpi->m_dVd = _wtof(pTask->DataSet.Rows[i][3].c_str());
				pWpi->m_dVdaf = _wtof(pTask->DataSet.Rows[i][4].c_str());
				pWpi->m_dMad = _wtof(pTask->DataSet.Rows[i][5].c_str());
				wcscpy(pWpi->m_szAssayStaff, pTask->DataSet.Rows[i][6].c_str());
				wcscpy(pWpi->m_szAssayCode, pTask->CoalInfo.GetAssayCode());
				swscanf(pTask->DataSet.Rows[i][6].c_str()
					, TIMEFORMAT
					, &pWpi->m_tsAssayDate.year
					, &pWpi->m_tsAssayDate.month
					, &pWpi->m_tsAssayDate.day);				
				pWpi->m_nDeviceID = DeviceType::WorkPointInstrument;
			}
			pTask->Success = TRUE;
			break;
		}
		Sleep(pTask->TurnsElapse);
		nCount--;
	}
	pTask->Finish = TRUE;
}