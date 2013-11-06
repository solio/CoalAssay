#ifndef DRIVER_HEADER
#define DRIVER_HEADER

#include "Def.h"
#include "DataTypes.h"

/************************************************************************************
/*
/* This is a interface for database using.
/* Please implement this interface when you use specific database such as "SQL Server"
/*
/*************************************************************************************/

class SOLIOEXPORT IDriver
{
protected:
	WCHAR *m_pcswErrorMsg;
public:
	IDriver(void);
	virtual int Connect(LPCWSTR lpszConnectedString) = 0;
	virtual int ExecuteQuery(LPCWSTR lpszQueryString, SQLResult* lpSqlResult) = 0;
	virtual int Disconnect() = 0;
	virtual ~IDriver(void);
protected:
	void SetErrorMsg(WCHAR *lpszMsg)
	{
		if(!m_pcswErrorMsg)
		{
			m_pcswErrorMsg = new WCHAR[wcslen(lpszMsg) + 1];
		}
		else
		{
			delete m_pcswErrorMsg;
			m_pcswErrorMsg = new WCHAR[wcslen(lpszMsg) + 1];
		}
		wcscpy(m_pcswErrorMsg, lpszMsg);
	}
public:
	LPCWSTR GetErrorMsg()
	{
		return this->m_pcswErrorMsg;
	}
};

#endif