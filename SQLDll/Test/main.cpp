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
	// SQL Server test
	//if((nRetCode = db.Connect(L"SQL Server", 
	//						  L"SOLIO-PC\\SOLIOENTERPRISE", 
	//						  L"CoalAssay", 
	//						  L"sa", 
	//						  L"Xzd091217")) < 0)
	//{
	//	wprintf(L"Connect fail!\n");
	//	return 0;
	//}

	//Staff lstaff;
	//WCHAR wcsStaffNum[50], wcsPassword[50];
	//wscanf(L"%s %s", wcsStaffNum, wcsPassword);
	//lstaff.SetStaffNum(wcsStaffNum);
	//lstaff.SetPassword(wcsPassword);

	//// test login
	//if ((nRetCode = db.Login(lstaff) < 0))
	//{
	//	WCHAR wcsMsg[1024];
	//	wsprintf(wcsMsg, L"%ls", db.GetErrorMsg());
	//	wprintf(L"%ls", db.GetErrorMsg());
	//	return -1;
	//}
	//else
	//{
	//	PrintResultSet(set);
	//	PrintStaff(lstaff);
	//}

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
	//if((nRetCode = db.Connect(L"Driver={Microsoft Access Driver (*.mdb)}; \
	//						   Dbq=D:\\长沙开源\\量热仪\\当前运行5E-2500A\\5E-ACNew\\Data\\win5e.Mdb;\
	//						   charset=gbk")) < 0)
	//{
	//	wprintf(L"Connect fail!\n");
	//	return 0;
	//}

	//if((nRetCode = db.ExecuteQuery(L"SELECT top 5 [Number],[Standard] FROM Win5eMdb;", &set)) < 0)
	//{
	//	
	//}
	//if((nRetCode = db.Connect(L"Driver={Microsoft Access Driver (*.mdb)}; \
	//						   Dbq=D:\\长沙开源\\测硫仪\\新建文件夹\\Data\\KY8SA.mdb;")) < 0)
	//{
	//	wprintf(L"Connect fail!\n");
	//	return 0;
	//}

	//if((nRetCode = db.ExecuteQuery(L"SELECT top 5 [试样编号],[试样名称] FROM AnalysisData;", &set)) < 0)
	//{
	//	
	//}

	if((nRetCode = db.Connect(L"SQL Server", 
							  L"dasfaf", 
							  L"CoalAssay", 
							  L"sa", 
							  L"Xzd091217")) < 0)
	{
		wprintf(L"Connect fail!\n");
		return 0;
	}
	getchar();
	return 0;
}