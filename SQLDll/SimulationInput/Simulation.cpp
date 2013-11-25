#include "Windows.h"

#include "../SQLDll/Def.h"
#include "../SQLDll/CoalAssayDB.h"
#pragma comment(lib, "../Debug/SQLDLL.lib")

int main(int argc, char **argv)
{
	SQLSMALLINT nRetCode = -1;
	OdbcDriver odbcLwm;
	OdbcDriver odbcSd;
	OdbcDriver odbcCm;
	SQLResult lwmRst;
	SQLResult sdRst;
	SQLResult cmRst;
	if(((nRetCode = odbcLwm.Connect(
			L"Driver={Microsoft Access Driver (*.mdb)}; \
			Dbq=H:\\project\\CoalAssay\\Data\\database\\lightwavemeter.Mdb;")) < 0)
		|| ((nRetCode = odbcSd.Connect(
			L"Driver={Microsoft Access Driver (*.mdb)}; \
			Dbq=H:\\project\\CoalAssay\\Data\\database\\sulfurdetector.Mdb;")) < 0)
		|| ((nRetCode = odbcCm.Connect(
			L"Driver={Microsoft Access Driver (*.mdb)}; \
			Dbq=H:\\project\\CoalAssay\\Data\\database\\calorimeter.Mdb;")) < 0))
	{
		wprintf(L"Connect fail!\n");
		return 0;
	}
	nRetCode = odbcLwm.ExecuteQuery(
		L"UPDATE [TestResult] SET [Moisture]='10.12',[Operator]='夏治道',[EndDate]='2013-11-20' \
		WHERE [Index] IN (SELECT MAX([Index]) FROM [TestResult])"
		, &lwmRst);
	nRetCode = odbcSd.ExecuteQuery(
		L"UPDATE [AnalysisData] SET [空干基全硫]='0.67',[干基全硫]='0.68',[化验员]='夏治道',[测试日期]='2013-11-20' \
		WHERE [nID] IN (SELECT MAX([nID]) FROM [AnalysisData])"
		, &sdRst);
	nRetCode = odbcCm.ExecuteQuery(
		L"UPDATE [win5emdb] SET [Qgrd]='0.1',[Qgrad]='0.1',[Qnetar]='0.1',[Qb]='0.1',[Testman]='夏治道',[Testtime]='2013-11-20' \
			WHERE Qgrd IS NULL AND Qgrad IS NULL AND Qnetar IS NULL AND Qb IS NULL "
		, &cmRst);
	wprintf(L"Simulate assay procedure\n");
	
	getchar();
	return 0;
}