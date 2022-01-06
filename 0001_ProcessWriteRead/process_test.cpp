#include <windows.h>  
#include <Psapi.h>  
#include <iostream>  
#include <tchar.h>  

//#pragma comment(lib, "Psapi.lib")

using std::cout;  
using std::endl;  

  
HANDLE hDesProcess = NULL;  
//根据进程的名字（image name）来查找该进程是否是打开的  
bool FindProcess( LPCTSTR lpszProcessName )  
{  
    DWORD dwProcessIdentify[MAX_PATH] = { 0 };  
    DWORD dwTrueBytes = 0;  
    HANDLE hProcess = NULL;  
    if ( !EnumProcesses( dwProcessIdentify, MAX_PATH*sizeof(DWORD), &dwTrueBytes ))  
    {  
        cout << "enum process fail " << endl;  
        return false;  
    }  
    int nProcessNum = dwTrueBytes/sizeof(DWORD);  
    HMODULE hModuleInProcess[MAX_PATH] = { 0 };  
    DWORD dwModuleBytes = 0;  
    TCHAR moduleBaseName[MAX_PATH] = { 0 };  
    for ( int nIndex = 0; nIndex < nProcessNum; ++nIndex )  
    {  
        hProcess = OpenProcess(  PROCESS_ALL_ACCESS, false, dwProcessIdentify[nIndex] );  
//      if ( hProcess == NULL )  
//      {  
//          continue;  
//      }  
//      memset( hModuleInProcess, 0, MAX_PATH*sizeof(HMODULE));  
//      dwModuleBytes = 0;  
//      if ( !EnumProcessModules( hProcess, hModuleInProcess, MAX_PATH*sizeof(HMODULE),&dwModuleBytes ))  
//      {  
//          cout << "Enum modules in process failed " << endl;  
//          DWORD dwErrorCode = GetLastError();  
//          //return false;  
//          continue;  
//      }  
        //int nModulesNumInProcess = dwModuleBytes/sizeof(DWORD);  
        memset( moduleBaseName, 0, MAX_PATH*sizeof(TCHAR));  
        //for ( int nModuleIndex = 0; nModuleIndex < nModulesNumInProcess; ++nModuleIndex )  
        {  
            cout<<nIndex;
            if(GetModuleBaseName( hProcess, NULL,moduleBaseName,MAX_PATH )){
                cout<<": "<<moduleBaseName<<endl;
            }else{
                cout<< ": error: " << GetLastError()<<endl;
            }

            
            if ( !_tcscmp( moduleBaseName, lpszProcessName))  
            {  
                cout << "查找的进程存在" << endl;  
                hDesProcess = hProcess;  
                return true;  
            }  
  
        }  
          
  
    }  
    return false;  
      
}  
const LPCTSTR lpszProcessName = _T("DriveTheLife.exe");  
int main()  
{  
    if ( !FindProcess( lpszProcessName ))  
    {  
        cout << "no such process" << endl;  
        return EXIT_FAILURE;  
    }  
  
    //终止目标进程  
    UINT unExitCode = 0;  
    if ( hDesProcess != NULL )  
    {  
        BOOL bRet = TerminateProcess( hDesProcess, unExitCode );  
        if ( !bRet )  
        {  
            DWORD dwErrorCode = GetLastError();  
            cout << "can't stop this: "<< lpszProcessName << endl;  
        }  
    }  
    DWORD dw = WaitForSingleObject( hDesProcess, INFINITE );  
    switch ( dw )  
    {  
    case WAIT_OBJECT_0:  
        cout << 1 << endl;  
        break;  
    case WAIT_FAILED:  
        {  
            DWORD dw1 = GetLastError();  
            cout << 2 << endl;  
        }  
          
        break  ;  
    default:  
        cout << 3 << endl;  
    }  
    return EXIT_SUCCESS;  
}  