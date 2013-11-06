#ifndef COALASSAYDB_HEADER
#define COALASSAYDB_HEADER

#include "OdbcDriver.h"
#include "SqlServerQueryBuilder.h"

class SOLIOEXPORT CoalAssayDB
{
private:
	OdbcDriver m_driverSqlServer;
public:
	CoalAssayDB(void);
	~CoalAssayDB(void);

	bool Login(const LPCWSTR szStaffNum, const LPCWSTR szPassword);
};

#endif