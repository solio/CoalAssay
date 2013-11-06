#ifndef DATATYPES_HEADER
#define DATATYPES_HEADER

#include "Def.h"

enum SOLIOEXPORT SQLSex { Female = 0, Male};

typedef struct SOLIOEXPORT SQLConnection
{
	LPCWSTR strDriver;
	LPCWSTR strServer;
	LPCWSTR strDBName;
	LPCWSTR strUserId;
	LPCWSTR strPassword;
}SQLConnection;

typedef struct SOLIOEXPORT SQLRow
{	
	LPCWSTR strColValue;
	struct SQLRow *pNext;
}SQLRow;

typedef struct SOLIOEXPORT SQLCol
{
	LPCWSTR strColName;
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
	LPCWSTR strStaffNum;
	LPCWSTR strStaffName;
	SQLSex enumStaffSex;
	TIMESTAMP_STRUCT tsStaffBirthday;
	LPCWSTR strPosition;
	LPCWSTR	strPermission;
	LPCWSTR strPassword;
}Staff;

#endif