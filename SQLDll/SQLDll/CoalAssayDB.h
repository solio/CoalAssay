#ifndef COALASSAYDB_HEADER
#define COALASSAYDB_HEADER

#include "OdbcDriver.h"
#include "SqlServerQueryBuilder.h"

class SOLIOEXPORT CoalAssayDB : public OdbcDriver, public SqlServerQueryBuilder
{
private:
	SQLResult*	m_pSet;
	WCHAR*		m_pcswToken;
public:
	CoalAssayDB(void);
	~CoalAssayDB(void);

	//bool Login(const LPCWSTR szStaffNum, const LPCWSTR szPassword);s	
	int Login(Staff& lStaff);
	int AddStaff(Staff& lStaff);
	int EditUser(Staff& lStaff);
	int DeleteStaff(LPCWSTR lpcsStaffNum);
	int SelectAllStaff(StaffArray& arrStaff);

	void SetBindingSet(SQLResult *lpSet)
	{
		m_pSet = lpSet;
	}
protected:
	void SetToken(const WCHAR *lpszToken)
	{
		if(m_pcswToken)
			delete m_pcswToken;
		m_pcswToken = new WCHAR[wcslen(lpszToken) + 1];
		wcscpy(m_pcswToken, lpszToken);
	}
protected:
	void GetStaff(Staff& lStaff, 
				  const SQLResult* lpSet, 
				  int nRowIndex);
};

#endif