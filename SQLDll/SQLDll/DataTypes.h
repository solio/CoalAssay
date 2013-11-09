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
	LPWSTR strColValue;
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

class SOLIOEXPORT Staff
{
private:
	LPWSTR m_strStaffNum;
	LPWSTR m_strStaffName;
	SQLSex m_enumStaffSex;
	TIMESTAMP_STRUCT m_tsStaffBirthday;
	LPWSTR m_strPosition;
	LPWSTR m_strPermission;
	LPWSTR m_strPassword;
public:
	Staff();
	void Copy(Staff& lstaff);
	void SetStaffNum(LPCWSTR lpszStaffNum);
	void SetStaffName(LPCWSTR lpszStaffName);
	void SetStaffSex(const SQLSex& lsex);
	void SetStaffBirthday(int nYear, int nMonth, int nDay);
	void SetPosition(LPCWSTR lpszPosition);
	void SetPermission(LPCWSTR lpszPermission);
	void SetPassword(LPCWSTR lpszPassword);
	void GetStaffNum(LPWSTR lpszStaffNum);
	void GetStaffName(LPWSTR lpszStaffName);
	void GetStaffSex(SQLSex& lsex);
	void GetStaffBirthday(TIMESTAMP_STRUCT& ltsBirthday);
	void GetPosition(LPWSTR lpszPosition);
	void GetPermission(LPWSTR lpszPermission);
	void GetPassword(LPWSTR lpszPassword);
	~Staff();
};

#endif