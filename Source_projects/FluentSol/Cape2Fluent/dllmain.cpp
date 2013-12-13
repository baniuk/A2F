// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "Cape2Fluent_i.h"
#include "dllmain.h"
#include "compreg.h"

CCape2FluentModule _AtlModule;

class CCape2FluentApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CCape2FluentApp, CWinApp)
END_MESSAGE_MAP()

CCape2FluentApp theApp;

BOOL CCape2FluentApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CCape2FluentApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
