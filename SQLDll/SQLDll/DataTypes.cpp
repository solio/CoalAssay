#ifndef SOLIOEXPORT
#define SOLIOEXPORT
#endif

#include "DataTypes.h"

Staff::Staff()
{
	memset(&m_tsStaffBirthday, 0, sizeof(m_tsStaffBirthday));
	memset(&m_strStaffNum, 0, sizeof(m_strStaffNum));
	memset(&m_strStaffName, 0, sizeof(m_strStaffName));
	memset(&m_strPosition, 0, sizeof(m_strPosition));
	memset(&m_strPermission, 0, sizeof(m_strPermission));
	memset(&m_strPassword, 0, sizeof(m_strPassword));
	m_enumStaffSex = SQLSex::Male;
}
Staff::Staff(const Staff& lstaff)
{
	wcscpy(m_strStaffNum, lstaff.m_strStaffNum);
	wcscpy(m_strStaffName, lstaff.m_strStaffName);
	wcscpy(m_strPosition, lstaff.m_strPosition);
	wcscpy(m_strPermission, lstaff.m_strPermission);
	wcscpy(m_strPassword, lstaff.m_strPassword);	

	m_enumStaffSex = lstaff.m_enumStaffSex;
	m_tsStaffBirthday.year = lstaff.m_tsStaffBirthday.year;
	m_tsStaffBirthday.month = lstaff.m_tsStaffBirthday.month;
	m_tsStaffBirthday.day = lstaff.m_tsStaffBirthday.day;
}
Staff::~Staff()
{

}
void Staff::Copy(Staff& lstaff)
{
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
	this->SetStaffNum(wcsStaffNum);
	this->SetStaffSex(enumStaffSex);

}
void Staff::SetStaffNum(LPCWSTR lpszStaffNum)
{
	wcscpy(m_strStaffNum, lpszStaffNum);
}
void Staff::SetStaffName(LPCWSTR lpszStaffName)
{
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
	wcscpy(m_strPosition, lpszPosition);
}
void Staff::SetPermission(LPCWSTR lpszPermission)
{
	wcscpy(m_strPermission, lpszPermission);
}
void Staff::SetPassword(LPCWSTR lpszPassword)
{
	wcscpy(m_strPassword, lpszPassword);
}

void Staff::GetStaffNum(LPCWSTR lpszStaffNum)
{
	if(lpszStaffNum)
		wcscpy((WCHAR*)lpszStaffNum, m_strStaffNum);
}
void Staff::GetStaffName(LPCWSTR lpszStaffName)
{
	if(lpszStaffName)
		wcscpy((WCHAR*)lpszStaffName, m_strStaffName);
}
void Staff::GetStaffSex(SQLSex& lsex)
{
	lsex = m_enumStaffSex;
}
void Staff::GetStaffBirthday(TIMESTAMP_STRUCT& ltsBirthday)
{
	ltsBirthday = m_tsStaffBirthday;
}
void Staff::GetPosition(LPCWSTR lpszPosition)
{
	if(lpszPosition)
		wcscpy((WCHAR*)lpszPosition, m_strPosition);
}
void Staff::GetPermission(LPCWSTR lpszPermission)
{
	if(lpszPermission)
		wcscpy((WCHAR*)lpszPermission, m_strPermission);
}
void Staff::GetPassword(LPCWSTR lpszPassword)
{
	if(lpszPassword)
		wcscpy((WCHAR*)lpszPassword, m_strPassword);
}

CoalInfo::CoalInfo()
{
	memset(m_wcsCoalLotNum, 0, sizeof(m_wcsCoalLotNum));
	memset(m_wcsAssayCode,	0, sizeof(m_wcsAssayCode));
	memset(&m_tsAssayDate,	0, sizeof(m_tsAssayDate));
	memset(&m_tsSampleDate,	0, sizeof(m_tsSampleDate));
	memset(&m_nAssayType,	0, sizeof(m_nAssayType));					//0入厂化验、1入炉化验、2矿方化验、3第三方化验
	memset(m_wcsAssayStaff, 0, sizeof(m_wcsAssayStaff));
	memset(m_wcsSampleStaff, 0, sizeof(m_wcsSampleStaff));
	memset(m_wcsStageName,	0, sizeof(m_wcsStageName));
	memset(m_wcsWorksName,	0, sizeof(m_wcsWorksName));

	m_tsAssayDate.year = 1970;
	m_tsAssayDate.month = 1;
	m_tsAssayDate.day = 1;

	m_tsSampleDate.year = 1970;
	m_tsSampleDate.month = 1;
	m_tsSampleDate.day = 1;
}

CoalInfo::~CoalInfo()
{

}

void CoalInfo::SetCoalLotNum(LPCWSTR lwcsCoalLotNum)
{
	wcscpy(m_wcsCoalLotNum, lwcsCoalLotNum);
}

void CoalInfo::SetAssayCode(LPCWSTR lwcsAssayCode)
{
	wcscpy(m_wcsAssayCode, lwcsAssayCode);
}

void CoalInfo::SetAssayDate(TIMESTAMP_STRUCT& ltsAssayDate)
{
	m_tsAssayDate = ltsAssayDate;
}

void CoalInfo::SetSampleDate(TIMESTAMP_STRUCT& ltsSampleDate)
{
	m_tsSampleDate = ltsSampleDate;
}

void CoalInfo::SetAssayType(AssayType	lnAssayType)
{
	m_nAssayType = lnAssayType;
}

void CoalInfo::SetAssayStaff(LPCWSTR lwcsAssayStaff)
{
	wcscpy(m_wcsAssayStaff, lwcsAssayStaff);
}

void CoalInfo::SetSampleStaff(LPCWSTR lwcsSampleStaff)
{
	wcscpy(m_wcsSampleStaff, lwcsSampleStaff);
}

void CoalInfo::SetStageName(LPCWSTR lwcsStageName)
{
	wcscpy(m_wcsStageName, lwcsStageName);
}

void CoalInfo::SetWorksName(LPCWSTR lwcsWorksName)
{
	wcscpy(m_wcsWorksName, lwcsWorksName);
}

LPCWSTR CoalInfo::GetCoalLotNum() const
{
	return this->m_wcsCoalLotNum;
}

LPCWSTR CoalInfo::GetAssayCode() const
{
	return this->m_wcsAssayCode;
}

const TIMESTAMP_STRUCT CoalInfo::GetAssayDate() const
{
	return this->m_tsAssayDate;
}

const TIMESTAMP_STRUCT CoalInfo::GetSampleDate() const
{
	return this->m_tsSampleDate;
}

const AssayType	CoalInfo::GetAssayType() const
{
	return this->m_nAssayType;
}

LPCWSTR CoalInfo::GetAssayStaff() const
{
	return this->m_wcsAssayStaff;
}

LPCWSTR CoalInfo::GetSampleStaff() const
{
	return this->m_wcsSampleStaff;
}

LPCWSTR CoalInfo::GetStageName() const
{
	return this->m_wcsStageName;
}

LPCWSTR CoalInfo::GetWorksName() const
{
	return this->m_wcsWorksName;
}