#ifndef TASK_HEADER
#define TASK_HEADER

class SOLIOEXPORT AssayTask
{
public:
	AssayTask()
	{
		m_pDriver =	NULL;
		ThreadHandle = NULL;
		ThreadId = -1;  
		TurnsElapse = 5 * 60 * 1000;
		TimeOut = 30 * 60 * 1000;
		Finish = FALSE;
		Success = FALSE;
	}
	~AssayTask()
	{
		for(int i = 0; i < DataObjects.size(); i++)
		{
			delete DataObjects[i];
		}
		DataObjects.clear();
	}
	void SetDataDriver(OdbcDriver *pDriver)
	{
		m_pDriver = pDriver;
	}
	OdbcDriver* GetDataDriver()
	{
		return m_pDriver;
	}
public:
	CoalInfo				CoalInfo;
	DeviceType				CurrentDevice;
	vector<DeviceType>		Devices;
	SQLResult				DataSet;
	vector<PVOID>			DataObjects;
	HANDLE					ThreadHandle;
	DWORD					ThreadId;
	DWORD					TurnsElapse;
	DWORD					TimeOut;
	BOOL					Finish;
	BOOL					Success;
protected:
	OdbcDriver				*m_pDriver;	
};

DWORD WINAPI AssayTaskProc(LPVOID lpParam);

void Task_AshFusionPoint(AssayTask* pTask);
void Task_CaloriMeter(AssayTask* pTask);
void Task_ElementAnalyzer(AssayTask* pTask);
void Task_LightWaveMeter(AssayTask* pTask);
void Task_SulfurDetector(AssayTask* pTask);
void Task_WorkPointInstrument(AssayTask* pTask);

#endif