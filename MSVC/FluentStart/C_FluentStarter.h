/**
* \file C_FluentStarter.h
* \brief C_FluentStarterClass headers
* \author PB
* \date 2014/02/05
*/
#ifndef C_FluentStarter_h__
#define C_FluentStarter_h__

#include "..\Common_utilities\Pantheios_header.h"
#include <atlbase.h>
#include <atlsafe.h>
#include <atlcom.h>
#include <atlctl.h>
#include <iostream>
#include <fstream>
#include <string.h>

/**
* \class C_FluentStarter
* \brief Run fluent process and control it.
* \details Contains various method for starting fluent process.
* \author PB
* \date 2014/02/05
*/
class C_FluentStarter
{
public:
	/// Starts fluent
	static HRESULT StartFluent(const std::string& configDir);
	/// Creates starter file for Fluent
	static void CreateJournal(const std::string& configDir);
private:
	/// Private constructor. It is not possible to create instance of this class
	C_FluentStarter(void) {};
	~C_FluentStarter(void) {};
	/// Waits until process starts
	static HRESULT WaitForStart(const TCHAR* nazwa, unsigned int obrot, unsigned int czas);
	/// Check if process started
	static HRESULT CheckProcess(const TCHAR* nazwa);
	/// Gets list of processes
	static HRESULT PrintProcessNameAndID(DWORD processID, const TCHAR* nazwa);
};
#endif // C_FluentStarter_h__
