#ifndef COALASSAYDB_HEADER
#define COALASSAYDB_HEADER

#include "OdbcDriver.h"
#include "Task.h"
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
	int SelectUnChecked(vector<CoalInfo>& arrCoal
						, vector<MergeTable>& arrMerge);
	int CorrespondingConnect(DeviceType enumType
							 , LPCWSTR lpszConn);
	int CorrespondingConnect(DeviceType enumType,
							 LPCWSTR lpszDriver,
							 LPCWSTR lpszServer,
							 LPCWSTR lpszDBName,
							 LPCWSTR lpszUid,
							 LPCWSTR lpszPwd);
	int AddCoalInfo(const CoalInfo& lCoalInfo, int *lpnCoalId);	
	int AddCorrespondingBlank(const AssayTask& oTask);
	int AddCorresponding(AssayTask& loTask, AssayTask *lpTask);
	int SetCorresponding(const DeviceType& enumDest, vector<LPVOID> arrDataObjects);
	//int AuditCorresponding(AssayTask& loTask);
	BOOL IsCorrespondingConnected(const DeviceType enumType);

	int ExecuteTask(AssayTask& oTask, AssayTask** lppTask);
	int AuditTask(LPCWSTR wcsAssayCode, int lnState);

	int Search(vector<CoalInfo>& larrci
			   , vector<MergeTable>& larrmt
			   , LPCWSTR wcsAssayCode);
	int Search(vector<CoalInfo>& larrci
			   , vector<MergeTable>& larrmt
			   , LPCWSTR wcsAssayStaff			   
			   , const TIMESTAMP_STRUCT *tsBegin
			   , const TIMESTAMP_STRUCT *tsEnd);
	
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
	void GetCoal(CoalInfo& lCoal
				 , const SQLResult *lpSet
				 , int nRowIndex);
	void GetAshFusionPoint(AshFusionPoint_t& lash, 
				  const SQLResult* lpSet, 
				  int nRowIndex);
	void GetCaloriMeter(CaloriMeter_t& lStaff, 
				  const SQLResult* lpSet, 
				  int nRowIndex);
	void GetElementAnalyzer(ElementAnalyzer_t& lea, 
				  const SQLResult* lpSet, 
				  int nRowIndex);
	void GetLightWaveMeter(LightWaveMeter_t& llwm, 
				  const SQLResult* lpSet, 
				  int nRowIndex);
	void GetSulfurDetector(SulfurDetector_t& lsd, 
				  const SQLResult* lpSet, 
				  int nRowIndex);
	void GetWorkPointInstrument(WorkPointInstrument_t& lwpi, 
				  const SQLResult* lpSet, 
				  int nRowIndex);

	int AddAshFusionPoint(AshFusionPoint_t& lash);
	int AddCaloriMeter(CaloriMeter_t& lpCm);
	int AddElementAnalyzer(ElementAnalyzer_t& lea);
	int AddLightWaveMeter(LightWaveMeter_t& llwm);
	int AddSulfurDetector(SulfurDetector_t& lsd);
	int AddWorkPointInstrument(WorkPointInstrument_t& lwpi);

	int SetAshFusionPoint(AshFusionPoint_t& lash);
	int SetCaloriMeter(CaloriMeter_t& lpCm);
	int SetElementAnalyzer(ElementAnalyzer_t& lea);
	int SetLightWaveMeter(LightWaveMeter_t& llwm);
	int SetSulfurDetector(SulfurDetector_t& lsd);
	int SetWorkPointInstrument(WorkPointInstrument_t& lwpi);
};

typedef struct WatchThreadParam_t
{
	CoalAssayDB *pCoalAssayDB;
	AssayTask	*pAssayTask;
	AssayTask	*pAssayResult;
}WatcherThreadParam_t;

DWORD WINAPI WatchAssayTaskProc(LPVOID lpParam);
#endif