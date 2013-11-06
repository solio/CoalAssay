#ifndef SQLSERVERQUERYBUILDER_HEADER
#define SQLSERVERQUERYBUILDER_HEADER

#include "QueryBuilder.h"

class SOLIOEXPORT SqlServerQueryBuilder : public QueryBuilder
{
public:
	SqlServerQueryBuilder(void);
	~SqlServerQueryBuilder(void);
};

#endif