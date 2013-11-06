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

#endif