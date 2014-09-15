/**
* \file C_FluentStarter.cpp
* \brief C_FluentStarter class definitions
* \author PB
* \date 2014/02/05
*/
#include "stdafx.h"
#include "C_FluentStarter.h"
#include <atlstr.h>
#include <Psapi.h>

using namespace std;

/**
* \brief Starts fluent process
* \details Runs fluent. Before run calls CreateJournal to create required journal. The journal file is passed
* as parameter during Fluent start.
* \param[in] configScript - full path of the config script. Typically read from registry
* \return Status of the operation
* \retval HRESULT
* - S_OK if Fluent starts
* - E_FAIL if not started
* \author PB
* \date 2014/02/06
* \pre CreateJournal() must be called before to create journal
* \exception std::exception from C_A2FInterpreter class
*/
HRESULT C_FluentStarter::StartFluent( const std::string& configScript )
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

	// ask for Fluent path and other params
	std::unique_ptr<C_A2FInterpreter> cfg(new C_A2FInterpreter()); // smart pointer in case of exception
	cfg->A2FOpenAndValidate(configScript.c_str());	// search for script

	// prepare command line parametrs CString because the need of LPSTR (no const)
	ATL::CString par_PARNAME(cfg->A2Flookup4String("COMMAND_LINE")); // contains full parameters with journal name and path
	par_PARNAME += cfg->A2Flookup4String("DATA_PATH");
	par_PARNAME += "journal.jou";

	// prepare path to fluent
	string par_PROCNAME(cfg->A2Flookup4String("FLUENT_PATH"));

	// prepare subprocess name
	string par_SUBPROCNAME(cfg->A2Flookup4String("PROCESS_NAME"));

	PANTHEIOS_TRACE_DEBUG(PSTR("Fluent path: "), par_PARNAME,PSTR(" Proc name"), par_SUBPROCNAME);

	ret1 = CreateProcess(par_PROCNAME.c_str(),
		par_PARNAME.GetBuffer(par_PARNAME.GetLength()),
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
		err = WaitForStart(par_SUBPROCNAME.c_str(),3, 6);
	else
		err = E_FAIL;

	PANTHEIOS_TRACE_DEBUG(PSTR("WaitForStart returned value: "), winstl::error_desc_a(err));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return err;
}

/**
* \brief Waits as process start
* \details Wait specified time until process starts. Important to left some time to load program. Total time is czas*obrot
* \param[in] nazwa
* \param[in] obrot How many times wait
* \param[in] czas How many seconds to wai
* \return Status of teh operation
* \retval HRESULT:
* - S_OK if process started
* - E_FAIL otherwise
* \author PB
* \date 2014/02/06
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

/**
* \details Creates starter file for Fluent. This file is named \b<journal> and its only one task is to run other file named \b<starter.scm>
* Files are created in \c configScript directory. This method crates only \b journal file.
* \param[in] configScript - path of the config script. Typically read from registry. This is not working dir
* \return nothing
* \retval \c void
* \author PB
* \date 2014/02/21
* \see http://aerojet.engr.ucdavis.edu/fluenthelp/html/ug/node23.htm
* \exception std::exception from C_A2FInterpreter class.
* \exception std::invalid_argument on wrong path in cfg file for storing scm
* \warning Path must end with \
*/
void C_FluentStarter::CreateJournal( const std::string& configScript )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// ask for journal path
	std::unique_ptr<C_A2FInterpreter> cfg(new C_A2FInterpreter()); // smart pointer in case of exception
	cfg->A2FOpenAndValidate(configScript.c_str());	// search for script
	string path_to_journal(cfg->A2Flookup4String("DATA_PATH")); // gets path

	path_to_journal += _T("journal.jou"); // adding file name to TMP path
	PANTHEIOS_TRACE_DEBUG(PSTR("Trying to open: "), path_to_journal);
	std::ofstream journal;
	journal.open(path_to_journal.c_str(),std::ios::out| std::ios::trunc);
	if(journal.is_open())
	{
		journal << "(load \"" << cfg->A2Flookup4String("DATA_PATH") << "_starter.scm\")" << endl;
		journal.close();
		PANTHEIOS_TRACE_DEBUG(path_to_journal,PSTR(" openned and created!"));
	}
	else
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Cant open file, check if DATA_PATH is correct in cfg file"));
		throw std::invalid_argument("FluentStarter::CreateJournal Cant open file, check if DATA_PATH is correct in cfg file");
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}