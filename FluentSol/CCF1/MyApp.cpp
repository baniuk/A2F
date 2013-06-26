#include "StdAfx.h"
#include "MyApp.h"
#include "resource.h"
#include "CCF1_i.h"
#include "dllmain.h"
#include "compreg.h"

CMyApp::CMyApp(void)
{
	CCCF1Module _AtlModule;
}

CMyApp::~CMyApp(void)
{
}

BOOL CMyApp::InitInstance()
      {
		  return _AtlModule.DllMain(ObjectMap, lpReserved); 
 //        _Module.Init(ObjectMap, m_hInstance);
   //      return CWinApp::InitInstance();
      }

int CMyApp::ExitInstance()
{
    // MFC's class factories registration is
    // automatically revoked by MFC itself.
  //  if (m_bRun)
    //    _ModuleRevokeClassObjects();
 }