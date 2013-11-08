#ifndef SOLIOEXPORT
#define SOLIOEXPORT
#endif

#include "OdbcDriver.h"
#include <exception>
using namespace std;

OdbcDriver::OdbcDriver(void) :
	m_bConnected(false)
{
	this->m_hEnvironment = NULL;
	this->m_hOdbc = NULL;
	this->m_hStatement = NULL;
	this->m_pCols  = NULL;
	this->m_pRow = NULL;
	this->m_pcswQueryString = new WCHAR[1024];

    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnvironment) == SQL_ERROR)
    {        
        throw exception("Unable to allocate an environment handle");
		exit(-1);
    }
	if (SQLSetEnvAttr(m_hEnvironment, 
					  SQL_ATTR_ODBC_VERSION,
					  (SQLPOINTER)SQL_OV_ODBC3,
					  0) == SQL_ERROR)
	{
        throw exception("Unable to set odbc driver environment");
		exit(-1);		
	}
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnvironment, &m_hOdbc) == SQL_ERROR)
	{
        throw exception("Unable to allocate odbc driver connection");
		exit(-1);				
	}
}


OdbcDriver::~OdbcDriver(void)
{
	Disconnect();
	FreeResult();
}

int OdbcDriver::Connect(LPCWSTR lpszConnectedString)
{
	//WCHAR lwcsConn[1024];

	//wcscpy(lwcsConn, lpszConnectedString);

	SQLSMALLINT retVal;
	if( (retVal = SQLDriverConnectW(m_hOdbc, GetDesktopWindow(),
						(WCHAR*)lpszConnectedString, SQL_NTS,
						NULL, 0,
						NULL, SQL_DRIVER_COMPLETE)) == SQL_ERROR)
	{
		//throw exception("Unable to connect to the odbc driver");
		this->SetErrorMsg(_T("Unable to connect to the odbc driver"));
		return SQL_ERROR;
	}
	else if (retVal == SQL_SUCCESS_WITH_INFO)
	{
		HandleDiagnosticRecord (m_hOdbc, SQL_HANDLE_DBC, retVal);
		m_bConnected = true;
	}
	else
	{
		m_bConnected = true;
	}
	return retVal;
}

int OdbcDriver::ExecuteQuery(LPCWSTR lpszQueryString, SQLResult* lpSqlResult)
{
	SQLSMALLINT RetCode;
	if (!m_hStatement)
	{
		if ( (RetCode = SQLAllocHandle(SQL_HANDLE_STMT, m_hOdbc, &m_hStatement)) == SQL_ERROR)
		{
			HandleDiagnosticRecord (m_hOdbc,    
									SQL_HANDLE_DBC,  
									RetCode);
			return SQL_ERROR;
		}
	}

	wcscpy(m_pcswQueryString, lpszQueryString);
	RetCode = SQLExecDirectW(m_hStatement, m_pcswQueryString, SQL_NTS);

	SQLSMALLINT nNumResults = 0;
	SQLINTEGER nRowCount = 0;
	int retVal = SQL_ERROR;
	switch(RetCode)
    {
    case SQL_SUCCESS_WITH_INFO:
        {                
            // fall through
			HandleDiagnosticRecord(m_hStatement, SQL_HANDLE_STMT, RetCode);
			lpSqlResult->szMsg.assign(this->m_pcswErrorMsg);
			break;
        }
    case SQL_SUCCESS:
        {
            // If this is a row-returning query, display
            // results
			//SQLRowCount(m_hStatement, &nRowCount);
            SQLNumResultCols(m_hStatement, &nNumResults);

			//retVal = nRowCount;
            if (nNumResults > 0)
            {
                //DisplayResults(hStmt,sNumResults);				
				nRowCount = FetchResults(nNumResults, lpSqlResult);
				lpSqlResult->nAffected =  nRowCount;
            }
            
			if(nRowCount > 0)
				retVal = nRowCount;
			else
				retVal = SQL_NONDATA;
            break;
        }

    case SQL_ERROR:
        {            
			HandleDiagnosticRecord(m_hStatement, SQL_HANDLE_STMT, RetCode);
			lpSqlResult->szMsg.assign(this->m_pcswErrorMsg);
            break;
        }

    default:
		{
			char msg[1024] = "";
			sprintf(msg, "Unexpected return code %d!", RetCode);
			throw exception(msg);
		}
    }

	SQLFreeStmt(m_hStatement, SQL_CLOSE);
	return nRowCount;
}

int OdbcDriver::Disconnect()
{
    if (m_hStatement)
    {
        SQLFreeHandle(SQL_HANDLE_STMT, m_hStatement);
		m_hStatement = NULL;
    }

    if (m_hOdbc)
    {
        SQLDisconnect(m_hOdbc);
        SQLFreeHandle(SQL_HANDLE_DBC, m_hOdbc);
		m_hOdbc = NULL;
    }

    if (m_hEnvironment)
    {
        SQLFreeHandle(SQL_HANDLE_ENV, m_hEnvironment);
		m_hEnvironment = NULL;
    }
	if(m_pcswQueryString)
	{
		delete m_pcswQueryString;
		m_pcswQueryString;
	}
	return 0;
}

int OdbcDriver::Connect(SQLConnection lsqlConn)
{
	int nLen = 0;
	nLen += wcslen(lsqlConn.strDBName) + 1;
	nLen += wcslen(lsqlConn.strServer) + 1;
	nLen += wcslen(lsqlConn.strDriver) + 1;
	nLen += wcslen(lsqlConn.strUserId) + 1;
	nLen += wcslen(lsqlConn.strPassword) + 1;

	WCHAR szConnStr[1024] = _T("");
	wsprintf(szConnStr, L"Driver={%s};Server=%s;Database=%s;Uid=%s;Pwd=%s",
			 lsqlConn.strDriver,
			 lsqlConn.strServer,
			 lsqlConn.strDBName,
			 lsqlConn.strUserId,
			 lsqlConn.strPassword);

	return Connect(szConnStr);
}

int OdbcDriver::Connect(LPCWSTR lpszDriver,
	LPCWSTR lpszServer,
	LPCWSTR lpszDBName,
	LPCWSTR lpszUid,
	LPCWSTR lpszPwd)
{
	WCHAR szConnStr[1024] = _T("");
	wsprintf(szConnStr, L"Driver={%s};Server=%s;Database=%s;Uid=%s;Pwd=%s",
			 lpszDriver,
			 lpszServer,
			 lpszDBName,
			 lpszUid,
			 lpszPwd);

	return Connect(szConnStr);
}

int OdbcDriver::FetchResults(int nCols, SQLResult* lpSqlResult)
{
	if(!lpSqlResult)
		return 0;

	int nRetCode = SQL_ERROR;
	int iCol = 0, nRows = 0;
	
	BindingTitle(&this->m_pCols, nCols);
	BindingData(&this->m_pRow, nCols);
	
	SQLCol *pFirstBinding, *pThisBinding;

	pFirstBinding = this->m_pCols;
	for (pThisBinding = pFirstBinding;
		pThisBinding;
		pThisBinding = pThisBinding->pNext,
		iCol++)
	{
		wstring strTemp(pThisBinding->strColName);
		lpSqlResult->Cols.push_back(strTemp);
	}

	bool bDataNotFounded = false;
	do
	{
		nRetCode = SQLFetch(m_hStatement);
        if (nRetCode == SQL_NO_DATA_FOUND)
        {
            bDataNotFounded = true;
        }
        else 
        {			
			SQLRow *pFirstBinding, *pThisBinding;
			vector<wstring> rowTemp;	

			pFirstBinding = this->m_pRow;
			iCol = 0;
            for (pThisBinding = pFirstBinding;
                pThisBinding;
                pThisBinding = pThisBinding->pNext,
				iCol++)
            {
				wstring strTemp(pThisBinding->strColValue);
				rowTemp.push_back(strTemp);
            }
			nRows++;
			lpSqlResult->Rows.push_back(rowTemp);
		}
	}while(!bDataNotFounded);
	FreeResult();

	return nRows;
}

void OdbcDriver::BindingTitle(SQLCol **ppBinding, int nCols)
{
	SQLSMALLINT     iCol;    
    SQLSMALLINT     nColumnNameLength;
	SQLCol       *pThisBinding, *pLastBinding = NULL;


    for (iCol = 1; iCol <= nCols; iCol++)
    {
        pThisBinding = new SQLCol;
        if (!(pThisBinding))
        {
            fwprintf(stderr, L"Out of memory!\n");
            exit(-100);
        }

        if (iCol == 1)
        {
            *ppBinding = pThisBinding;
        }
        else
        {			
            pLastBinding->pNext = pThisBinding;
        }
		pThisBinding->pNext = NULL;
        pLastBinding = pThisBinding;


        // Now set the display size that we will use to display
        // the data.   Figure out the length of the column name

        SQLColAttributeW(m_hStatement,
						 iCol,
						 SQL_DESC_NAME,
						 NULL,
						 0,
						 &nColumnNameLength,
						 NULL);

		pThisBinding->strColName = new WCHAR[(nColumnNameLength + 1) * sizeof(WCHAR)];
		
        // Map this buffer to the driver's buffer.As above do.

        SQLColAttributeW(m_hStatement,
						 iCol,
						 SQL_DESC_NAME,
						 (WCHAR*)pThisBinding->strColName,
						 (nColumnNameLength + 1) * sizeof(WCHAR),
						 &nColumnNameLength,
						 NULL);
    }	
}

void OdbcDriver::BindingData(SQLRow **ppBinding, int nCols)
{
    SQLSMALLINT     iCol;    
    SQLLEN          nDisplay;
	SQLRow       *pThisBinding, *pLastBinding = NULL;


    for (iCol = 1; iCol <= nCols; iCol++)
    {
        pThisBinding = new SQLRow;
        if (!(pThisBinding))
        {
            fwprintf(stderr, L"Out of memory!\n");
            exit(-100);
        }

        if (iCol == 1)
        {
            *ppBinding = pThisBinding;
        }
        else
        {			
            pLastBinding->pNext = pThisBinding;
        }
		pThisBinding->pNext = NULL;
        pLastBinding = pThisBinding;


        // Figure out the display length of the column (we will
        // bind to char since we are only displaying data, in general
        // you should bind to the appropriate C type if you are going
        // to manipulate data since it is much faster...)

        SQLColAttribute(m_hStatement,
            iCol,
            SQL_DESC_DISPLAY_SIZE,
            NULL,
            0,
            NULL,
            &nDisplay);

        pThisBinding->pNext = NULL;

        // Allocate a buffer big enough to hold the text representation
        // of the data.  Add one character for the null terminator

		pThisBinding->strColValue = new WCHAR[nDisplay + 1];

        if (!(pThisBinding->strColValue))
        {
			this->SetErrorMsg(L"Out of memory!");
            exit(-100);
        }

        // Map this buffer to the driver's buffer.   At Fetch time,
        // the driver will fill in this data.  Note that the size is 
        // count of bytes (for Unicode).  All ODBC functions that take
        // SQLPOINTER use count of bytes; all functions that take only
        // strings use count of characters.

        SQLBindCol(m_hStatement,
            iCol,
            SQL_C_TCHAR,
			(SQLPOINTER) pThisBinding->strColValue,
            (nDisplay + 1) * sizeof(WCHAR),
            NULL);
    }	
}

void OdbcDriver::FreeResult()
{
	while(this->m_pCols)
	{
		SQLCol* tmpBinding;
		tmpBinding = this->m_pCols;
		this->m_pCols = this->m_pCols->pNext;
		delete tmpBinding->strColName;
		delete tmpBinding;
	}
	while(this->m_pRow)
	{
		SQLRow* tmpBinding;
		tmpBinding = this->m_pRow;
		this->m_pRow = this->m_pRow->pNext;
		delete tmpBinding->strColValue;
		delete tmpBinding;
	}	
	this->m_pCols = NULL;
	this->m_pRow = NULL;
}

void OdbcDriver::HandleDiagnosticRecord (SQLHANDLE      hHandle,    
                             SQLSMALLINT    hType,  
                             RETCODE        RetCode)
{
    SQLSMALLINT iRec = 0;
    SQLINTEGER  iError;
    WCHAR       wszMessage[1000];
    WCHAR       wszState[SQL_SQLSTATE_SIZE+1];


    if (RetCode == SQL_INVALID_HANDLE)
    {
        fwprintf(stderr, L"Invalid handle!\n");
        return;
    }

    while (SQLGetDiagRecW(hType,
                         hHandle,
                         ++iRec,
                         wszState,
                         &iError,
                         wszMessage,
                         (SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)),
                         (SQLSMALLINT *)NULL) == SQL_SUCCESS)
    {
        // Hide data truncated..
        if (wcsncmp(wszState, L"01004", 5))
        {
			WCHAR pcswMsg[1024];
            wsprintf(pcswMsg, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
			this->SetErrorMsg(pcswMsg);
        }
    }

}