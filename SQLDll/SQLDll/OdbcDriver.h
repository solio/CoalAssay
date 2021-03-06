#ifndef ODBCDRIVER_HEADER
#define ODBCDRIVER_HEADER

#include "Def.h"
#include "DataTypes.h"
#include "IDriver.h"

class SOLIOEXPORT OdbcDriver : public IDriver
{
protected:
    SQLHENV     m_hEnvironment;
    SQLHDBC     m_hOdbc;
    SQLHSTMT    m_hStatement;
	WCHAR*		m_pcswQueryString;
	SQLCol*		m_pCols;
	SQLRow*		m_pRow;
	BOOL		m_bConnected;
public:
	OdbcDriver(void);
	virtual int Connect(LPCWSTR lpszConnectedString);
	virtual int ExecuteQuery(LPCWSTR lpszQueryString, SQLResult* lpSqlResult);
	virtual int Disconnect();

	int Connect(SQLConnection lsqlConn);
	int Connect(LPCWSTR lpszDriver,
				LPCWSTR lpszServer,
				LPCWSTR lpszDBName,
				LPCWSTR lpszUid,
				LPCWSTR lpszPwd);

	void HandleDiagnosticRecord (SQLHANDLE hHandle,    
								 SQLSMALLINT hType,  
								 RETCODE RetCode);
	BOOL IsConnected()
	{
		return m_bConnected;
	}
	int SetStatement() 
	{
		int nRetCode;
		if(!m_hStatement)
		{
			if ( (nRetCode = SQLAllocHandle(SQL_HANDLE_STMT, m_hOdbc, &m_hStatement)) == SQL_ERROR)
			{
				HandleDiagnosticRecord (m_hOdbc,    
										SQL_HANDLE_DBC,  
										nRetCode);
				return SQL_ERROR;
			}
		}	
	}
	~OdbcDriver(void);
protected:
	void Initial();
	int FetchResults(int nCols, SQLResult* lpSqlResult);
	void BindingTitle(SQLCol **ppBinding, int nCols);
	void BindingData(SQLRow **ppBinding, int nCols);
	void FreeResult();
};

#endif