#ifndef COALASSAYDB_HEADER
#define COALASSAYDB_HEADER

#include "OdbcDriver.h"
#include "SqlServerQueryBuilder.h"

class SOLIOEXPORT CoalAssayDB : public OdbcDriver, public SqlServerQueryBuilder
{
private:
	OdbcDriver	m_oDbcAFP;		// odbc for AshFusionPoint		"智能灰熔点分析仪"
	OdbcDriver	m_oDbcCM;		// odbc for ColoriMeter			"量热仪"
	OdbcDriver	m_oDbcEA;		// odbc for Element Analyzer	"元素分析仪器"
	OdbcDriver	m_oDbcLWM;		// odbc for LightWaveMeter		"光波仪"
	OdbcDriver	m_oDbcSD;		// odbc for SulfurDetector		"测硫仪"
	OdbcDriver	m_oDbcWPI;		// odbc for WorkPointInstrument	"工分仪"
	SQLResult*	m_pSet;
	WCHAR*		m_pcswToken;
public:
	CoalAssayDB(void);
	~CoalAssayDB(void);

	//bool Login(const LPCWSTR szStaffNum, const LPCWSTR szPassword);	
	int Login(Staff& lStaff);
	int AddStaff(Staff& lStaff);
	int EditUser(Staff& lStaff);
	int DeleteStaff(LPCWSTR lpcsStaffNum);
	int SelectAllStaff(StaffArray& arrStaff);

	int CorrespondingConnect(DeviceType enumType,
							 LPCWSTR lpszDriver,
							 LPCWSTR lpszServer,
							 LPCWSTR lpszDBName,
							 LPCWSTR lpszUid,
							 LPCWSTR lpszPwd);
	int AddCoalInfo(const CoalInfo& lCoalInfo, int *lpnCoalId);	
	int AddCorrespondingBlank(const AssayTask& oTask);
	BOOL IsCorrespondingConnected(const DeviceType enumType);

	int CreateNewTask(const AssayTask& oTask);
	
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