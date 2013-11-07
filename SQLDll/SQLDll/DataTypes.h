#ifndef DATATYPES_HEADER
#define DATATYPES_HEADER

#include "Def.h"

enum SOLIOEXPORT SQLSex { Female = 0, Male};

typedef struct SOLIOEXPORT SQLConnection
{
	LPWSTR strDriver;
	LPWSTR strServer;
	LPWSTR strDBName;
	LPWSTR strUserId;
	LPWSTR strPassword;
}SQLConnection;

typedef struct SOLIOEXPORT SQLRow
{	
	LPCWSTR strColValue;
	struct SQLRow *pNext;
}SQLRow;

typedef struct SOLIOEXPORT SQLCol
{
	LPWSTR strColName;
	//WCHAR*	strColName;
	struct SQLCol *pNext;
}SQLCol;

typedef struct SOLIOEXPORT SQLResult
{
	wstring szMsg;
	int nAffected;
	vector<wstring> Cols;
	vector<vector<wstring>> Rows;
}SQLResult;

typedef struct SOLIOEXPORT Staff
{
	LPWSTR strStaffNum;
	LPWSTR strStaffName;
	SQLSex enumStaffSex;
	TIMESTAMP_STRUCT tsStaffBirthday;
	LPWSTR strPosition;
	LPWSTR	strPermission;	
	LPWSTR strPassword;
}Staff;

#endif