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

/************************************************/
/*
/* Error defination
/*
/************************************************/
#define SQL_ERROR_BASE			-10086
#define SQL_NONCONNECTED		SQL_ERROR_BASE - 1
#define SQL_NONBINDING			SQL_ERROR_BASE - 2
#define LOGIC_BASE				-12000
#define LOGIC_USERERROR			LOGIC_BASE - 1

#endif