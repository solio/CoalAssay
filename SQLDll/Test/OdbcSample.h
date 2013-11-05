#ifndef ODBCSAMPLE_HEADER
#define ODBCSAMPLE_HEADER

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <stdlib.h>
#include <sal.h>

/*******************************************/
/* Macro to call ODBC functions and        */
/* report an error on failure.             */
/* Takes handle, handle type, and stmt     */
/*******************************************/

#define TRYODBC(h, ht, x)   {   RETCODE rc = x;\
                                if (rc != SQL_SUCCESS) \
                                { \
                                    HandleDiagnosticRecord (h, ht, rc); \
                                } \
                                if (rc == SQL_ERROR) \
                                { \
                                    fwprintf(stderr, L"Error in " L#x L"\n"); \
                                    goto Exit;  \
                                }  \
                            }
/******************************************/
/* Structure to store information about   */
/* a column.
/******************************************/

typedef struct STR_BINDING {
    SQLSMALLINT         cDisplaySize;           /* size to display  */
    WCHAR               *wszBuffer;             /* display buffer   */
    SQLLEN              indPtr;                 /* size or null     */
    BOOL                fChar;                  /* character col?   */
    struct STR_BINDING  *sNext;                 /* linked list      */
} BINDING;



/******************************************/
/* Forward references                     */
/******************************************/

void HandleDiagnosticRecord (SQLHANDLE      hHandle,    
                 SQLSMALLINT    hType,  
                 RETCODE        RetCode);

void DisplayResults(HSTMT       hStmt,
                    SQLSMALLINT cCols);

void AllocateBindings(HSTMT         hStmt,
                      SQLSMALLINT   cCols,
                      BINDING**     ppBinding,
                      SQLSMALLINT*  pDisplay);


void DisplayTitles(HSTMT    hStmt,
                   DWORD    cDisplaySize,
                   BINDING* pBinding);

void SetConsole(DWORD   cDisplaySize,
                BOOL    fInvert);

/*****************************************/
/* Some constants                        */
/*****************************************/


#define DISPLAY_MAX 50          // Arbitrary limit on column width to display
#define DISPLAY_FORMAT_EXTRA 3  // Per column extra display bytes (| <data> )
#define DISPLAY_FORMAT      L"%c %*.*s "
#define DISPLAY_FORMAT_C    L"%c %-*.*s "
#define NULL_SIZE           6   // <NULL>
#define SQL_QUERY_SIZE      1000 // Max. Num characters for SQL Query passed in.

#define PIPE                L'|'

SHORT   gHeight = 80;       // Users screen height

//int __cdecl wmain(int argc, _In_reads_(argc) WCHAR **argv)
int OdbcSample(int argc, WCHAR **argv);

#endif