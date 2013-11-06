#ifndef SOLIOEXPORT
#define SOLIOEXPORT
#endif

#include "CoalAssayDB.h"

CoalAssayDB::CoalAssayDB(void)
{
}


CoalAssayDB::~CoalAssayDB(void)
{
}

bool CoalAssayDB::Login(const LPCWSTR szStaffNum, const LPCWSTR szPassword)
{
	int nRet = 0;
	SQLResult sqlResult;

	if ( m_driverSqlServer.Connect( _T("Sql Server"),
									_T("Solio-PC\\SOLIOENTERPRISE"),
									_T("COALASSAY"),
									_T("sa"),
									_T("Xzd091217")) != SQL_ERROR )
	{
		
		WCHAR wcsQueryString[1024];

		wsprintf(wcsQueryString, 
				 _T("SELECT * FROM Staff WHERE StaffNum='%s' and Password='%s'"), 
				 szStaffNum,
				 szPassword);
		nRet = m_driverSqlServer.ExecuteQuery(wcsQueryString, &sqlResult);
	}
	if(sqlResult.Rows.size() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}