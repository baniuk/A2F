// Test_Run.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>

BOOL WaitForProcess(TCHAR *nazwa);
BOOL PrintProcessNameAndID( DWORD processID, TCHAR* nazwa);
BOOL WaitForStart(TCHAR *nazwa,unsigned int obrot, unsigned int czas);

int _tmain(int argc, _TCHAR* argv[])
{
// test okienka


	BOOL ret;
	BOOL ret1;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

// create process
	si.lpDesktop = NULL;
// uruchamianie dziala - 	
	CComBSTR ff = " 3ddp";
	CComBSTR gg = "g:\\ANSYS Inc\\v120\\fluent\\ntbin\\ntx86\\fluent.exe";
	ret1 = CreateProcess(gg,
					ff,
					NULL,
					NULL,
					FALSE,
					0,
					NULL,
					NULL,
					&si,
					&pi);

	if(ret1)	{
		ret = WaitForStart(TEXT("fl12016s.exe"),5, 1);
		printf("%d\n",ret);
	} else
		return 1;

	return 0;
}

BOOL WaitForStart(TCHAR *nazwa,unsigned int obrot, unsigned int czas)
{
	// czeka czas sekund na start i pozniej zwraca b³¹d. Proboje "obrot" razy
	unsigned int licz = 0;
	BOOL ret;

	while(licz<obrot)
	{
		ret = WaitForProcess(nazwa);
		if(ret==FALSE)
			Sleep(czas*1000);
		else
			return TRUE;
		licz++;
	}
	return FALSE;	// nie uruchomi³o siê
}

BOOL WaitForProcess(TCHAR *nazwa)	// FLASE - jakis b³¹d
{
	BOOL ret = FALSE;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return FALSE;

	cProcesses = cbNeeded / sizeof(DWORD);

	for ( i = 0; i < cProcesses; i++ )	{
		if( aProcesses[i] != 0)	{
			ret = PrintProcessNameAndID( aProcesses[i], nazwa);
			if(ret==TRUE)	{
				break;
			}
		}
	}
	return ret;
}

BOOL PrintProcessNameAndID( DWORD processID, TCHAR* nazwa)
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	DWORD d;

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ|SYNCHRONIZE,
                                   TRUE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }
 

	if(wcscmp(szProcessName,nazwa)==0)	{
		d = WaitForSingleObject( hProcess, INFINITE );
		CloseHandle( hProcess );
		return TRUE;
	}
	else	{
		CloseHandle( hProcess );
		return FALSE;
	}
}

/*
 LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
	LPTSTR lpszFunction = TEXT("TEST");

	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	si.lpDesktop = NULL;
	
	BOOL ret = CreateProcess(TEXT("e:\\FluentInc\\ntbin\\ntx86\\fluent.exe"),
					NULL,
					NULL,
					NULL,
					FALSE,
					0,
					NULL,
					NULL,
					&si,
					&pi);
	Sleep(100);
/*
	DWORD dw = GetLastError(); 
	 FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);

	WaitForSingleObject( pi.hProcess, INFINITE );

	printf("Finito!\n");

	*/