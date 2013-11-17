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

enum SOLIOEXPORT AssayType {Factory = 0, Stove = 1, Mine = 2, ThirdPart = 3};

class SOLIOEXPORT CoalInfo
{
public:
	CoalInfo();
	~CoalInfo();
	void SetCoalLotNum(LPCWSTR lwcsCoalLotNum);
	void SetAssayCode(LPCWSTR lwcsAssayCode);
	void SetAssayDate(TIMESTAMP_STRUCT& ltsAssayDate);
	void SetSampleDate(TIMESTAMP_STRUCT& ltsSampleDate);
	void SetAssayType(AssayType	lnAssayType);
	void SetAssayStaff(LPCWSTR lwcsAssayStaff);
	void SetSampleStaff(LPCWSTR lwcsSampleStaff);
	void SetStageName(LPCWSTR lwcsStageName);
	void SetWorksName(LPCWSTR lwcsWorksName);

	LPCWSTR GetCoalLotNum() const;
	LPCWSTR GetAssayCode() const;
	const TIMESTAMP_STRUCT GetAssayDate() const;
	const TIMESTAMP_STRUCT GetSampleDate() const;
	const AssayType	GetAssayType() const;
	LPCWSTR GetAssayStaff() const;
	LPCWSTR GetSampleStaff() const;
	LPCWSTR GetStageName() const;
	LPCWSTR GetWorksName() const;

private:
	WCHAR m_wcsCoalLotNum[20];
	WCHAR m_wcsAssayCode[20];
	TIMESTAMP_STRUCT m_tsAssayDate;
	TIMESTAMP_STRUCT m_tsSampleDate;
	AssayType	m_nAssayType;					//0入厂化验、1入炉化验、2矿方化验、3第三方化验
	WCHAR m_wcsAssayStaff[20];
	WCHAR m_wcsSampleStaff[20];
	WCHAR m_wcsStageName[50];
	WCHAR m_wcsWorksName[50];
};

enum SOLIOEXPORT DeviceType {	AshFusionPoint = 0		//"智能灰熔点分析仪"
								,CaloriMeter			//"量热仪"
								,ElementAnalyzer		//"元素分析仪器"
								,LightWaveMeter			//"光波仪"
								,SulfurDetector			//"测硫仪"
								,WorkPointInstrument	//"工分仪"
};

typedef struct SOLIOEXPORT AshFusionPoint_t
{
public:
	int m_nAssayID;
	int m_nDeviceID;
	TIMESTAMP_STRUCT m_tsAssayDate;
	int m_nAssayStaffID;
	double m_dAshFusionT1;			// numeric(8, 2)
	double m_dAshFusionT2;			// numeric(8, 2)
	double m_dAshFusionT3;			// numeric(8, 2)
	double m_dAshFusionT4;			// numeric(8, 2)
}AshFusionPoint_t;

typedef struct SOLIOEXPORT CaloriMeter_t
{
public:
	int m_nAssayID;
	int m_nDeviceID;
	TIMESTAMP_STRUCT m_tsAssayDate;
	int m_nAssayStaffID;
	double m_dQb_ad;				//numeric(8, 3) NOT NULL,
	double m_dQgr_d;				//numeric(8, 3) NOT NULL,
	double m_dQgr_a;				//numeric(8, 3) NOT NULL,
	double m_dQnet_ar;				//numeric(8, 3) NOT NULL,
}CaloriMeter_t;

typedef struct SOLIOEXPORT ElementAnalyzer_t
{
public:
	int m_nAssayID;
	int m_nDeviceID;
	TIMESTAMP_STRUCT m_tsAssayDate;
	int m_nAssayStaffID;
	double m_dHad;					// numeric(8, 2)
}ElementAnalyzer_t;

typedef struct SOLIOEXPORT LightWaveMeter_t
{
public:
	int m_nAssayID;
	int m_nDeviceID;
	TIMESTAMP_STRUCT m_tsAssayDate;
	int m_nAssayStaffID;
	double m_dMar;					//[numeric](8, 2) NOT NULL,
	double m_dMad;					//[numeric](8, 2) NOT NULL,
}LightWaveMeter_t;

typedef struct SOLIOEXPORT SulfurDetector_t
{
public:
	int m_nAssayID;
	int m_nDeviceID;
	TIMESTAMP_STRUCT m_tsAssayDate;
	int m_nAssayStaffID;
	double m_dSt_ad;				//[numeric](8, 2) NOT NULL,
	double m_dSt_d;					//[numeric](8, 2) NOT NULL,
}SulfurDetector_t;

typedef struct SOLIOEXPORT WorkPointInstrument_t
{
public:
	int m_nAssayID;
	int m_nDeviceID;
	TIMESTAMP_STRUCT m_tsAssayDate;
	int m_nAssayStaffID;
	double m_dVd;					//numeric(8, 2) NOT NULL,
	double m_dVad;					//numeric(8, 2) NOT NULL,
	double m_dVar;					//numeric(8, 2) NOT NULL,
	double m_dVdaf;					//numeric(8, 2) NOT NULL,
	double m_dMar;					//numeric(8, 2) NOT NULL,
	double m_dMad;					//numeric(8, 2) NOT NULL,
	double m_dAad;					//numeric(8, 2) NOT NULL,
	double m_dAar;					//numeric(8, 2) NOT NULL,
}WorkPointInstrument_t;

class SOLIOEXPORT AssayTask
{
public:
	AssayTask()
	{
		ThreadHandle = NULL;
		ThreadId = -1;  
		TurnsElapse = 2 * 60 * 1000;
		Finish = FALSE;
	}
public:
	CoalInfo				CoalInfo;
	DeviceType				CurrentDevice;
	vector<DeviceType>		Devices;	
	vector<wstring>			Cols;
	vector<vector<wstring>> Rows;
	HANDLE					ThreadHandle;
	DWORD					ThreadId;
	DWORD					TurnsElapse;
	BOOL					Finish;
};
#endif