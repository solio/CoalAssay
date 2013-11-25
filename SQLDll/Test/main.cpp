#include "Windows.h"
#include "OdbcSample.h"

#include "../SQLDll/Def.h"
#include "../SQLDll/CoalAssayDB.h"

//#pragma comment(lib, "../Debug/SQLDLL.lib")

//#ifdef SOLIOEXPORT
//#define solio "solio"
//#else
//#define solio "not solio"
//#endif

void ExportSQLDll()
{
	char szFileList[][64] = {
		"../SQLDll/CoalAssayDB.h"
		, "../SQLDll/DataTypes.h"
		, "../SQLDll/Def.h"
		, "../SQLDll/IDriver.h"
		, "../SQLDll/OdbcDriver.h"
		, "../SQLDll/QueryBuilder.h"
		, "../SQLDll/SqlServerQueryBuilder.h"
		, "../SQLDll/Task.h"
		, "../Debug/SQLDll.dll"
		, "../Debug/SQLDll.lib"
		, "Q"
	};

	char szDestList[][64] = {
		"H:\\project\\CoalAssay\\SQLDll\\Export\\CoalAssayDB.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\DataTypes.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\Def.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\IDriver.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\OdbcDriver.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\QueryBuilder.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\SqlServerQueryBuilder.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\Task.h"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\SQLDll.dll"
		, "H:\\project\\CoalAssay\\SQLDll\\Export\\SQLDll.lib"
		, "Q"	
	};

	int nIndex = 0;
	WCHAR szDirectory[128] = L"";
	GetCurrentDirectory(128, szDirectory);
	while(strcmp(szFileList[nIndex], "Q"))
	{
		FILE *fpSrc = NULL;
		FILE *fpDst = NULL;

		fpSrc = fopen(szFileList[nIndex], "r");
		if(fpSrc == NULL)
		{
			printf("copy library fail!%d\n", GetLastError());
			return;
		}

		fpDst = fopen(szDestList[nIndex], "r+");
		if(fpDst == NULL)
		{
			fclose(fpSrc);
			printf("copy library fail!%d\n", GetLastError());
			return;
		}

		_unlink(szDestList[nIndex]);
		while(!feof(fpSrc))
		{
			int ch = fgetc(fpSrc);	
			fputc(ch, fpDst);
		}

		fclose(fpSrc);
		fclose(fpDst);
		nIndex++;
	}

	printf("copy library.\n");
}

void PrintResultSet(const SQLResult& lSet)
{
	wprintf(L"Cols:\n");
	for(int i = 0; i < lSet.Cols.size(); i++)
	{
		wprintf(L"%ls ", lSet.Cols[i].c_str());
	}
	wprintf(L"\n");

	for(int i = 0; i < lSet.Rows.size(); i++)
	{
		wprintf(L"Row:");
		for(int j = 0; j < lSet.Rows[i].size(); j++)
		{
			wprintf(L"%ls ", lSet.Rows[i][j].c_str());
		}
		wprintf(L"\n");
	}
}

void PrintStaff(const Staff& lStaff)
{
	//wprintf(L"\n");
	//wprintf(L"Name:%s\n", lStaff.strStaffName);
	//wprintf(L"Birthday:%4d-%2d-%2d\n", 
	//		lStaff.tsStaffBirthday.year, 
	//		lStaff.tsStaffBirthday.month, 
	//		lStaff.tsStaffBirthday.day);
	//wprintf(L"Position:%s\n", lStaff.strPosition);
	//wprintf(L"Sex:%d\n", lStaff.enumStaffSex);
	//wprintf(L"Permision:%s\n", lStaff.strPermission);
	//wprintf(L"\n");
}

int main(int argc, char **argv)
{
	//OdbcSample();
	int nRetCode = 0;
	SQLResult set;
	CoalAssayDB db;
	SYSTEMTIME tsNow;
	double debug = _wtof(L".12adf");
	GetSystemTime(&tsNow);

	ExportSQLDll();
	db.SetBindingSet(&set);
	// SQL Server test
	if((nRetCode = db.Connect(L"SQL Server", 
							  L"SOLIO-PC\\SOLIOENTERPRISE", 
							  L"CoalAssay", 
							  L"sa", 
							  L"Xzd091217")) < 0)
	{
		wprintf(L"Connect fail!\n");
		return 0;
	}

	Staff lstaff;
	WCHAR wcsStaffNum[50], wcsPassword[50];
	wscanf(L"%s %s", wcsStaffNum, wcsPassword);
	lstaff.SetStaffNum(wcsStaffNum);
	lstaff.SetPassword(wcsPassword);

	// test login
	if ((nRetCode = db.Login(lstaff) < 0))
	{
		WCHAR wcsMsg[1024];
		wsprintf(wcsMsg, L"%ls", db.GetErrorMsg());
		wprintf(L"%ls", db.GetErrorMsg());
		return -1;
	}
	else
	{
		PrintResultSet(set);
		PrintStaff(lstaff);
	}

	//// add Coal Info
	//int id = 0;
	//CoalInfo ci;
	//ci.SetAssayCode(L"12314");
	//if( (nRetCode = db.AddCoalInfo(ci, &id)) < 0)
	//{
	//	wprintf(L"add coal error");
	//	return 0;
	//}

	//// test add staff
	//Staff lNewStaff;
	//lNewStaff.SetStaffNum(L"041030234");
	//lNewStaff.SetStaffName(L"NewStaff");
	//lNewStaff.SetStaffBirthday(2013, 11, 9);
	//lNewStaff.SetStaffSex(SQLSex::Male);
	//lNewStaff.SetPassword(L"w36308458");
	//lNewStaff.SetPermission(L"B");
	//lNewStaff.SetPosition(L"一般员工");
	//if ((nRetCode = db.AddStaff(lNewStaff)) < 0)
	//{
	//	WCHAR wcsMsg[1024];
	//	wsprintf(wcsMsg, L"%ls", db.GetErrorMsg());
	//	wprintf(L"ERROR : %ls\n", db.GetErrorMsg());
	//}
	//else
	//{
	//	wprintf(L"ADD SUCCESS\n");
	//}

	//if ((nRetCode = db.DeleteStaff(L"041030234")) < 0)
	//{
	//	WCHAR wcsMsg[1024];
	//	wsprintf(wcsMsg, L"%ls", db.GetErrorMsg());
	//	wprintf(L"ERROR : %ls\n", db.GetErrorMsg());
	//}
	//else
	//{
	//	wprintf(L"DELETE SUCCESS\n");
	//}

	//StaffArray arrStaffs;
	//if ((nRetCode = db.SelectAllStaff(arrStaffs)) < 0)
	//{
	//	WCHAR wcsMsg[1024];
	//	wsprintf(wcsMsg, L"%ls", db.GetErrorMsg());
	//	wprintf(L"ERROR : %ls\n", db.GetErrorMsg());
	//}
	//else
	//{
	//	wprintf(L"SELECT SUCCESS\n");
	//}

	// Access 
	// 提交化验任务测试
	//int id = 0;
	//CoalInfo ci;
	//AssayTask oTask;
	//AssayTask *pTaskResult;
	//vector<CoalInfo> arrUnCheckedCi;
	//vector<MergeTable> arrUnCheckedMt;
	//TIMESTAMP_STRUCT tsDate;
	//WCHAR szNewTaskCode[50] = L"";

	//swprintf(szNewTaskCode, L"%d%d%d%d%d", tsNow.wMonth, tsNow.wDay, tsNow.wHour, tsNow.wMinute, tsNow.wSecond);
	//tsDate.year = 2013;
	//tsDate.month = 11;
	//tsDate.day = 18;
	//ci.SetCoalLotNum(L"B7602321");
	//ci.SetAssayCode(szNewTaskCode);
	//ci.SetAssayDate(tsDate);
	//ci.SetAssayStaff(L"夏治道");
	//ci.SetAssayType(AssayType::Factory);

	//oTask.CoalInfo = ci;
	//oTask.TurnsElapse = 10 * 1000;
	//oTask.Devices.push_back(DeviceType::CaloriMeter);
	//oTask.Devices.push_back(DeviceType::LightWaveMeter);
	//oTask.Devices.push_back(DeviceType::SulfurDetector);
	//if(((nRetCode = db.CorrespondingConnect(DeviceType::CaloriMeter,
	//		L"Driver={Microsoft Access Driver (*.mdb)}; \
	//		Dbq=H:\\project\\CoalAssay\\Data\\database\\calorimeter.Mdb;")) < 0)
	//	|| ((nRetCode = db.CorrespondingConnect(DeviceType::LightWaveMeter,
	//		L"Driver={Microsoft Access Driver (*.mdb)}; \
	//		Dbq=H:\\project\\CoalAssay\\Data\\database\\lightwavemeter.Mdb;")) < 0)
	//	|| ((nRetCode = db.CorrespondingConnect(DeviceType::SulfurDetector,
	//		L"Driver={Microsoft Access Driver (*.mdb)}; \
	//		Dbq=H:\\project\\CoalAssay\\Data\\database\\sulfurdetector.Mdb;")) < 0))
	//{
	//	wprintf(L"Connect fail!\n");
	//	return 0;
	//}
	//else if((nRetCode = db.ExecuteTask(oTask, &pTaskResult)) < 0)
	//{
	//	wprintf(L"Task fail! %d \n", nRetCode);
	//	return 0;
	//}
	//else
	//{
	//	wprintf(L"Task end.\n");
	//	wprintf(L"Enter any key to audit assay task");
	//	getch();
	//	oTask.CoalInfo.SetState(1);
	//	
	//	nRetCode = db.AuditTask(oTask.CoalInfo.GetAssayCode(), 1);	
	//}
	//nRetCode = db.SelectUnChecked(arrUnCheckedCi, arrUnCheckedMt);
	// 长连接测试
	//if((nRetCode = db.Connect(L"SQL Server", 
	//						  L"dasfaf", 
	//						  L"CoalAssay", 
	//						  L"sa", 
	//						  L"Xzd091217")) < 0)
	//{
	//	wprintf(L"Connect fail!\n");
	//	return 0;
	//}

	// 工分仪数据库连接测试 （带密码）
	if((nRetCode = db.CorrespondingConnect(DeviceType::WorkPointInstrument,
			L"Driver={Microsoft Access Driver (*.mdb)}; \
			Dbq=H:\\project\\CoalAssay\\Data\\database\\workpointinstrument.Mdb;\
			pwd=CSKY;")) < 0)
	{
		wprintf(L"Connect fail!\n");
		return 0;
	}

	//OdbcDriver odbcLwm;
	//OdbcDriver odbcSd;
	//OdbcDriver odbcCm;
	//SQLResult lwmRst;
	//SQLResult sdRst;
	//SQLResult cmRst;
	//if(((nRetCode = odbcLwm.Connect(
	//		L"Driver={Microsoft Access Driver (*.mdb)}; \
	//		Dbq=H:\\project\\CoalAssay\\Data\\database\\lightwavemeter.Mdb;")) < 0)
	//	|| ((nRetCode = odbcSd.Connect(
	//		L"Driver={Microsoft Access Driver (*.mdb)}; \
	//		Dbq=H:\\project\\CoalAssay\\Data\\database\\sulfurdetector.Mdb;")) < 0)
	//	|| ((nRetCode = odbcCm.Connect(
	//		L"Driver={Microsoft Access Driver (*.mdb)}; \
	//		Dbq=H:\\project\\CoalAssay\\Data\\database\\calorimeter.Mdb;")) < 0))
	//{
	//	wprintf(L"Connect fail!\n");
	//	return 0;
	//}
	//else
	//{
	//	nRetCode = odbcLwm.ExecuteQuery(
	//		L"UPDATE [TestResult] SET [Moisture]='10.12',[Operator]='夏治道',[EndDate]='2013-11-20' \
	//		WHERE [Index] IN (SELECT MAX([Index]) FROM [TestResult])"
	//		, &lwmRst);
	//	nRetCode = odbcSd.ExecuteQuery(
	//		L"UPDATE [AnalysisData] SET [空干基全硫]='0.67',[干基全硫]='0.68',[化验员]='夏治道',[测试日期]='2013-11-20' \
	//		WHERE [nID] IN (SELECT MAX([nID]) FROM [AnalysisData])"
	//		, &sdRst);
	//	nRetCode = odbcCm.ExecuteQuery(
	//		L"UPDATE [win5emdb] SET [Qgrd]='0.1',[Qgrad]='0.1',[Qnetar]='0.1',[Qb]='0.1',[Testman]='夏治道',[Testtime]='2013-11-20' \
	//		 WHERE Qgrd IS NULL AND Qgrad IS NULL AND Qnetar IS NULL AND Qb IS NULL "
	//		, &cmRst);
	//}

	// 查询 
	vector<CoalInfo> arrci;
	vector<MergeTable> arrmt;
	TIMESTAMP_STRUCT ts1, ts2;
	ts1.year = ts2.year = 2013;
	ts1.month = ts2.month = 11;
	ts1.day = 10;
	ts2.day = 26;
	if((nRetCode = db.Search(arrci, arrmt, NULL, &ts1, &ts2)) < 0)
	{
	
	}
	getchar();
	return 0;
}