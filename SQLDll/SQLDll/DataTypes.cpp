#ifndef SOLIOEXPORT
#define SOLIOEXPORT
#endif

#include "DataTypes.h"

Staff::Staff() :
	m_strStaffNum(NULL), m_strStaffName(NULL),
	m_strPosition(NULL), m_strPermission(NULL),
	m_strPassword(NULL)
{
	memset(&m_tsStaffBirthday, 0, sizeof(m_tsStaffBirthday));
	m_enumStaffSex = SQLSex::Male;
}
Staff::~Staff()
{
	if(m_strStaffNum)
		delete m_strStaffNum;
	if(m_strStaffName)
		delete m_strStaffName;
	if(m_strPosition)
		delete m_strPosition;
	if(m_strPermission)
		delete m_strPermission;
	if(m_strPassword)
		delete m_strPassword;
}
void Staff::Copy(Staff& lstaff)
{
	WCHAR wcsQueryString[1024];
	WCHAR wcsStaffNum[50];
	WCHAR wcsStaffName[50];
	TIMESTAMP_STRUCT tsBirthday;
	SQLSex enumStaffSex;
	WCHAR wcsPosition[50];
	WCHAR wcsPermission[50];
	WCHAR wcsPassword[50];

	lstaff.GetPassword(wcsPassword);
	lstaff.GetPermission(wcsPermission);
	lstaff.GetPosition(wcsPosition);
	lstaff.GetStaffBirthday(tsBirthday);
	lstaff.GetStaffName(wcsStaffName);
	lstaff.GetStaffNum(wcsStaffNum);
	lstaff.GetStaffSex(enumStaffSex);

	this->SetPassword(wcsPassword);
	this->SetPermission(wcsPermission);
	this->SetPosition(wcsPosition);
	this->SetStaffBirthday(tsBirthday.year, tsBirthday.month, tsBirthday.day);
	this->SetStaffName(wcsStaffName);
	this->GetStaffNum(wcsStaffNum);
	this->GetStaffSex(enumStaffSex);

}
void Staff::SetStaffNum(LPCWSTR lpszStaffNum)
{
	if(m_strStaffNum)
		delete m_strStaffNum;
	m_strStaffNum = new WCHAR[wcslen(lpszStaffNum) + 1];
	wcscpy(m_strStaffNum, lpszStaffNum);
}
void Staff::SetStaffName(LPCWSTR lpszStaffName)
{
	if(m_strStaffName)
		delete m_strStaffName;
	m_strStaffName = new WCHAR[wcslen(lpszStaffName) + 1];
	wcscpy(m_strStaffName, lpszStaffName);
}
void Staff::SetStaffSex(const SQLSex& lsex)
{
	m_enumStaffSex = lsex;
}
void Staff::SetStaffBirthday(int nYear, int nMonth, int nDay)
{
	m_tsStaffBirthday.year = nYear;
	m_tsStaffBirthday.month = nMonth;
	m_tsStaffBirthday.day = nDay;
}
void Staff::SetPosition(LPCWSTR lpszPosition)
{
	if(m_strPosition)
		delete m_strPosition;
	m_strPosition = new WCHAR[wcslen(lpszPosition) + 1];
	wcscpy(m_strPosition, lpszPosition);
}
void Staff::SetPermission(LPCWSTR lpszPermission)
{
	if(m_strPermission)
		delete m_strPermission;
	m_strPermission = new WCHAR[wcslen(lpszPermission) + 1];
	wcscpy(m_strPermission, lpszPermission);
}
void Staff::SetPassword(LPCWSTR lpszPassword)
{
	if(m_strPassword)
		delete m_strPassword;
	m_strPassword = new WCHAR[wcslen(lpszPassword) + 1];
	wcscpy(m_strPassword, lpszPassword);
}

void Staff::GetStaffNum(LPWSTR lpszStaffNum)
{
	if(lpszStaffNum)
		wcscpy(lpszStaffNum, m_strStaffNum);
}
void Staff::GetStaffName(LPWSTR lpszStaffName)
{
	if(lpszStaffName)
		wcscpy(lpszStaffName, m_strStaffName);
}
void Staff::GetStaffSex(SQLSex& lsex)
{
	lsex = m_enumStaffSex;
}
void Staff::GetStaffBirthday(TIMESTAMP_STRUCT& ltsBirthday)
{
	ltsBirthday = m_tsStaffBirthday;
}
void Staff::GetPosition(LPWSTR lpszPosition)
{
	if(lpszPosition)
		wcscpy(lpszPosition, m_strPosition);
}
void Staff::GetPermission(LPWSTR lpszPermission)
{
	if(lpszPermission)
		wcscpy(lpszPermission, m_strPermission);
}
void Staff::GetPassword(LPWSTR lpszPassword)
{
	if(lpszPassword)
		wcscpy(lpszPassword, m_strPassword);
}