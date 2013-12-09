// UnitOperation.cpp : Implementation of CUnitOperation

#include "stdafx.h"
#include "UnitOperation.h"

// CUnitOperation

CUnitOperation::CUnitOperation()
{	
	err = new C_Error("CUnitOperation");
	my_params = new C_Params(err);
	runfluent = new C_myRunProcess(err,my_params);
	err->Node_Init();
	SetOaNoCache();
	LONG lResult;
	HKEY hKey;
	DWORD dwSize = sizeof(dirp) - 1;
	TCHAR dirptmp[MAX_STRING];
	filename = "params.txt";
#ifdef PRINTOUT
	char timeline[26];
	struct _timeb timebuffer;
	_ftime_s( &timebuffer );
	ctime_s( timeline, 26, & ( timebuffer.time ) );
	fopen_s(&mystream,"CCF1Debug1.txt","a+");
	fprintf(mystream,"\n-- %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[18] );
	VariantInit(&dopliku);
	dopliku.vt = VT_BYREF;
	dopliku.byref = (void*)mystream;
	fprintf(mystream,"CUnitOperation::CUnitOperation()\n");
	fprintf(mystream,"	- %p\n",this);
#endif
	externalError.Empty();
#ifndef NO_REGISTRY
	char *ttmp = "f:\\FluentSol\\parsertest\\Matlab\\params.txt";	// to mo¿na z rejestru, katalog instalacyjny na przyk³ad
	strcpy_s(dirp,MAX_STRING,ttmp);
#else
	dirptmp[0] = 0;
	lResult = RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Cape2Fluent"), 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS) 
    {
		MessageBox(NULL,L"Registry key not found. Install C2P again",L"ERROR",MB_OK);
		my_params.sERR = 1;
		strcpy_s(my_params.bERR,MAX_STRING,"Registry key not found. Install C2P again");
	} else	{
//		lResult = RegGetValue(hKey,NULL,"InstallDir",RRF_RT_REG_SZ,NULL,dirp,&dwSize);
		lResult = RegQueryValueEx(hKey,L"InstallDir",NULL,NULL,(LPBYTE)dirptmp,&dwSize);
		if (lResult != ERROR_SUCCESS) 
		{
			MessageBox(NULL,L"Registry key not found. Install C2P again",L"ERROR",MB_OK);
			my_params.sERR = 1;
			strcpy_s(my_params.bERR,MAX_STRING,"Registry key not found. Install C2P again");
		}
	}
	RegCloseKey(hKey);
	CW2A pszA(dirptmp);
// dodawanie drugiej / oraz dopisanie nazwy pliku z parametrami
	unsigned int a,licznik = 0;
	for(a=0;a<strlen(pszA);a++)
		if(pszA[a]!='\\')
			dirp[licznik++] = pszA[a];
		else {
			dirp[licznik++] = '\\';
			dirp[licznik++] = pszA[a];
		}
	dirp[licznik++] = '\\';
	dirp[licznik++] = '\\';
	for(a=licznik;a<licznik+strlen(filename);a++)
		dirp[a] = filename[a-licznik];
	dirp[a] = 0;
// -----------------------------------------------
#endif

//	p.CreateInstance(__uuidof(Port),NULL,CLSCTX_INPROC_SERVER);//p->AddRef();
//	p1.CreateInstance(__uuidof(Port),NULL,CLSCTX_INPROC_SERVER);//p1.AddRef();
	CoCreateInstance(CLSID_Port,NULL,CLSCTX_INPROC_SERVER,IID_IPort,(void**)&p);
	CoCreateInstance(CLSID_Port,NULL,CLSCTX_INPROC_SERVER,IID_IPort,(void**)&p1);
	myports.CreateInstance(__uuidof(PortCollection),NULL,CLSCTX_INPROC_SERVER);// myports->AddRef();
	myparams.CreateInstance(__uuidof(ParameterCollection),NULL,CLSCTX_INPROC_SERVER);

#ifdef PRINTOUT
	p->debugfile(&dopliku);
	p1->debugfile(&dopliku);
	myports->debugfile(&dopliku);
	myparams->debugfile(&dopliku);
#endif

	VariantInit(&varerr);
	dopliku.vt = VT_BYREF;
	dopliku.byref = (void*)err;

	p->AddError(&varerr);
	p1->AddError(&varerr);
	myports->AddError(&varerr);
	myparams->AddError(&varerr);

	myName = L"Cape2Fluent Port";
	myDesc = L"FLUENT CAPE-OPEN unit operation implemented in CPP";
	rep[0] = L"Report 1";
	rep[1] = L"Report 2";
		


	myvalStatus = CAPE_NOT_VALIDATED;
	p->put_mydirection(CAPE_INLET);
	p->put_myDesc(L"Inlet port for test unit operation");
	p->put_myName(L"Inlet port");

	p->put_unit(&myvalStatus);
	myports->AddPort2(p);

	p1->put_mydirection(CAPE_OUTLET);
	p1->put_myDesc(L"Outlet port for test unit operation");
	p1->put_myName(L"Outlet port");
	p1->put_unit(&myvalStatus);
	myports->AddPort2(p1);
	p->Release();
	p1->Release();
// -----------------------------------------------------------------------------------------
#ifdef NO_CONFIG
	my_params.sERR = 0;
#else
	if(my_params->Creadfile(dirp)==FAIL)	{	// wszystkie b³êdy skrytpu s¹ zwracane tutaj
		MessageBox(NULL,L"UnitOperation::Creadfile problem",L"ERROR",MB_OK);
		err->AddError("CUnitOperation::Creadfile problem");
		return;
	} else
		my_params->sERR = 0;	// czyœcimy jakieœ stare b³êdy jeœli by³y

#endif
// do testów tylko, normalnie w calculate powinno byc oraz w okienku parametrów
/* jak bêdzie obs³uga okienek to okienko bêdzie zwraca³o sERR i na tej podstawie validate bedzie okresla³o validacjê ca³oœci*/
// obs³uga bledow raczej na tym poziomie a nie na poziomie funkcji c_myrun...
/*	if(!my_params.ValidateParams(BASIC) && !my_params.ValidateParams(CASE) && !my_params.ValidateParams(EXPORTS))
	{
		my_params.sERR = 1;
		strcpy_s(my_params.bERR,MAX_STRING,"BASIC problem");
		MessageBox(NULL,L"UnitOperation::Validation pramas file problem",L"ERROR",MB_OK);
		return;
	} */
//	runfluent.CreateEnv(&my_params);
}

CUnitOperation::~CUnitOperation()
{
#ifdef PRINTOUT
	fprintf(mystream,"CUnitOperation::~CUnitOperation()\n");
#endif	

	myName.Empty();
	myDesc.Empty();
	rep[0].Empty();
	rep[1].Empty();
	errDesc.Empty();
	errInterface.Empty();
	errScope.Empty();

//	SafeArrayDestroy(rep1);
//	p->Release();
//	p1->Release();
//	myports->Release();
//	myparams->Release();

	myports = NULL;
	p->Release();
	p1->Release();
	myparams = NULL;
	
	delete err;
	delete my_params;
	delete runfluent;

#ifdef PRINTOUT
	fclose( mystream );
#endif
}


STDMETHODIMP CUnitOperation::InvalidateUnit(void)
{
#ifdef PRINTOUT
	fprintf(mystream,"STDMETHODIMP CUnitOperation::InvalidateUnit(void)\n");
#endif	
	myvalStatus = CAPE_NOT_VALIDATED;
	return S_OK;
}

void CUnitOperation::SetError(BSTR desc, BSTR interf, BSTR scope)
{
#ifdef PRINTOUT
	fprintf(mystream,"CUnitOperation::SetError(BSTR desc, BSTR interf, BSTR scope)\n");
#endif
	errDesc.Empty(); errDesc = desc;
	errInterface.Empty(); errInterface = interf;
	errScope.Empty(); errScope = scope;
}