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

	db.SetBindingSet(&set);
	if(db.Connect(L"SQL Server", 
				  L"SOLIO-PC\\SOLIOENTERPRISE", 
				  L"CoalAssay", 
				  L"sa", 
				  L"Xzd091217") < 0)
	{
		wprintf(L"Connect fail!\n");
		return 0;
	}
	//if(db.Login(_T("1232"), _T("afdg23")))
	//{
	//	printf("Login Success!");
	//}
	//else
	//{
	//	wprintf(_T("%s"), db.GetMsg());
	//}
	Staff lstaff;
	//lstaff.strStaffNum = new WCHAR[wcslen(_T("1232")) + 1];
	//lstaff.strPassword = new WCHAR[wcslen(_T("afdg23")) + 1];
	//wcscpy((WCHAR*)lstaff.strStaffNum, _T("1232"));
	//wcscpy((WCHAR*)lstaff.strPassword, _T("afdg23"));
	lstaff.SetStaffNum(L"1232");
	lstaff.SetPassword(L"afdg23");


	if ((nRetCode = db.Login(lstaff) < 0))
	{
		WCHAR wcsMsg[1024];
		wsprintf(wcsMsg, L"%ls", db.GetErrorMsg());
		wprintf(L"%ls", db.GetErrorMsg());
	}
	else
	{
		PrintResultSet(set);
		PrintStaff(lstaff);
	}
	getchar();
	return 0;
}