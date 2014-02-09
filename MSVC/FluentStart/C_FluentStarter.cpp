/**
 * \file C_FluentStarter.cpp
 * \brief C_FluentStarter class definitions
 * \author PB
 * \date 2014/02/05
 */
#include "stdafx.h"
#include "C_FluentStarter.h"
#include "C_Properties.h"
#include <Psapi.h>



/**
 * \brief Starts fluent process
 * \details Runs fluent
 * \return Status of the operation
 * \retval HRESULT
 * - S_OK if Fluent starts
 * - E_FAIL if not started
 * \author PB
 * \date 2014/02/06
*/
HRESULT C_FluentStarter::StartFluent( void )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err;
	BOOL ret1;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	si.lpDesktop = NULL;

	PANTHEIOS_TRACE_DEBUG(PSTR("Fluent path: "),C_Properties::PAR_PROCNAME, C_Properties::PAR_PARNAME);

	ret1 = CreateProcess(C_Properties::PAR_PROCNAME,
		C_Properties::PAR_PARNAME.GetBuffer(C_Properties::PAR_PARNAME.GetLength()),
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi);
	PANTHEIOS_TRACE_DEBUG(PSTR("CreateProcess returned: "), pantheios::integer(ret1),PSTR(" Error desc: "), winstl::error_desc(GetLastError()));
	
	if(ret1!=0)
		err = WaitForStart(C_Properties::PAR_SUBPROCNAME,3, 6);
	else
		err = E_FAIL;

	PANTHEIOS_TRACE_DEBUG(PSTR("WaitForStart returned value: "), winstl::error_desc_a(err));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return err;
}

/**
 * \brief Waits as process start
 * \details Wait specified time until process starts. Important to left some time to load program. Total time is czas*obrot
 * \param nazwa
 * \param obrot How many times wait
 * \param czas How many seconds to wai
 * \return Status of teh operation
 * \retval HRESULT:
 * - S_OK if process started
 * - E_FAIL otherwise
 * \author PB
 * \date 2014/02/06
 * \note
 * \warning
 * \see StartFluent
*/
HRESULT C_FluentStarter::WaitForStart( const TCHAR* nazwa, unsigned int obrot, unsigned int czas )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// czeka czas sekund na start i pozniej zwraca b³¹d. Proboje "obrot" razy
	unsigned int licz = 0;
	BOOL err;
	PANTHEIOS_TRACE_DEBUG(PSTR("WaitForStart - waitning for "), nazwa);
	while(licz<obrot)
	{
		err = CheckProcess(nazwa);
		if(err==E_FAIL)
			Sleep(czas*1000);
		else
		{
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return S_OK;
		}
		licz++;
	}
	PANTHEIOS_TRACE_ERROR(PSTR("Process not startred"));
	return E_FAIL;	// nie uruchomi³o siê
}

/**
 * \brief Verify if process started
 * \details Check in windows processes if selected process is on list. Gets only the list of processes and then use PrintProcessNameAndID to check names of 
 * the processes.
 * \param nazwa Name of the process to check
 * \return Status of the operation
 * \retval HRESULT
 * - S_OK if process started
 * - E_FAIL if not started
 * \author PB
 * \date 2014/02/06
 * \note Name of the process with extension
 * \see WaitForStart
*/
HRESULT C_FluentStarter::CheckProcess(const TCHAR* nazwa )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err = E_FAIL;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
	{
		PANTHEIOS_TRACE_ERROR(PSTR("EnumProcesses failed"));
		return E_FAIL;
	}
	cProcesses = cbNeeded / sizeof(DWORD);

	for ( i = 0; i < cProcesses; i++ )	{
		if( aProcesses[i] != 0)	{
			err = PrintProcessNameAndID( aProcesses[i], nazwa);
			if(err==S_OK)
				break;
		}
	}
	PANTHEIOS_TRACE_DEBUG(PSTR("Returned value: "), winstl::error_desc_a(err));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return err;
}

/**
 * \brief Check if process of given id is on list
 * \details Prints details of the process. For given id comapre if this process has releval name.
 * \param processID ID of process to check
 * \param nazwa Name of the process
 * \return Status of the operation
 * \retval HRESULT
 * - S_OK if roces of given name found
 * - E_FAIL if not found
 * \author PB
 * \date 2014/02/06
 * \see CheckProcess
*/
HRESULT C_FluentStarter::PrintProcessNameAndID( DWORD processID, const TCHAR* nazwa )
{
	// method called in loop - no logging
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
	PANTHEIOS_TRACE_DEBUG(PSTR("EnumProcess: "),szProcessName);
	// compares two string _tcscmp  is macro that invokes wcscmp or strcmp depending on the type of characters
	if(_tcscmp(szProcessName,nazwa)==0)	{
		d = WaitForSingleObject( hProcess, INFINITE );
		CloseHandle( hProcess );
		return S_OK;
	}
	else	{
		CloseHandle( hProcess );
		return E_FAIL;
	}
}


