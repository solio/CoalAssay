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
	WCHAR m_strStaffNum[50];
	WCHAR m_strStaffName[20];
	SQLSex m_enumStaffSex;
	TIMESTAMP_STRUCT m_tsStaffBirthday;
	WCHAR m_strPosition[50];
	WCHAR m_strPermission[50];
	WCHAR m_strPassword[50];
public:
	Staff();
	Staff(const Staff& lstaff);
	void Copy(Staff& lstaff);
	void SetStaffNum(LPCWSTR lpszStaffNum);
	void SetStaffName(LPCWSTR lpszStaffName);
	void SetStaffSex(const SQLSex& lsex);
	void SetStaffBirthday(int nYear, int nMonth, int nDay);
	void SetPosition(LPCWSTR lpszPosition);
	void SetPermission(LPCWSTR lpszPermission);
	void SetPassword(LPCWSTR lpszPassword);


	void GetStaffNum(LPCWSTR lpszStaffNum);
	void GetStaffName(LPCWSTR lpszStaffName);
	void GetStaffSex(SQLSex& lsex);
	void GetStaffBirthday(TIMESTAMP_STRUCT& ltsBirthday);
	void GetPosition(LPCWSTR lpszPosition);
	void GetPermission(LPCWSTR lpszPermission);
	void GetPassword(LPCWSTR lpszPassword);
	~Staff();
};

class SOLIOEXPORT StaffArray
{
public:
	StaffArray() : pStaffs(NULL), count(0)
	{}
	~StaffArray()
	{
		if(pStaffs)
			delete[] pStaffs;
	}
public:
	Staff *pStaffs;
	int count;
};
#endif