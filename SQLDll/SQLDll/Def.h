#ifndef DEF_HEADER
#define DEF_HEADER

#ifdef SOLIOEXPORT
#define SOLIOEXPORT _declspec(dllexport)
#else
#define SOLIOEXPORT _declspec(dllimport)
#endif

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>
#include <string.h>
#include <vector>
using namespace std;

#define PARAMOUT  

/************************************************/
/*
/* Error defination
/*
/************************************************/
#define SQL_ERROR_BASE			-2000
#define SQL_NONCONNECTED		SQL_ERROR_BASE - 1
#define SQL_NONBINDING			SQL_ERROR_BASE - 2
#define SQL_NONDATA				SQL_ERROR_BASE - 3
#define SQL_NOAFFECTED			SQL_ERROR_BASE - 4
#define LOGIC_BASE				-2500
#define LOGIC_USERERROR			LOGIC_BASE - 1
#define LOGIC_PERMISSIONDENIED	LOGIC_BASE - 2
#define LOGIC_NODATA			LOGIC_BASE - 3
#define LOGIC_STAFFNUMSHORT		LOGIC_BASE - 4
#define LOGIC_PASSWORDSHORT		LOGIC_BASE - 5
#define LOGIC_PASSWORDSIMPLE	LOGIC_BASE - 6
#define LOGIC_NOLOGINED			LOGIC_BASE - 7

#endif