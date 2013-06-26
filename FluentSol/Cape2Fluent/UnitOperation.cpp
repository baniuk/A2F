// UnitOperation.cpp : Implementation of CUnitOperation

#include "stdafx.h"
#include "UnitOperation.h"


// CUnitOperation

CUnitOperation::CUnitOperation()
{	
	err = new C_Error("CUnitOperation");
	my_params = new C_Params(err);
	runfluent = new C_myRunProcess(err,my_params);
	czyASPEN = TRUE;
	czyValidate = FALSE;
	err->Node_Init();
	SetOaNoCache();
	LONG lResult;
	HKEY hKey;
	DWORD dwSize = sizeof(dirp) - 1;
	TCHAR dirptmp[MAX_STRING];
	filename = "params.txt";
	mydialog = NULL;
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
		my_params->sERR = 1;
		strcpy_s(my_params->bERR,MAX_STRING,"Registry key not found. Install C2P again");
		err->AddError("Registry key not found. Install C2P again");
	} else	{
//		lResult = RegGetValue(hKey,NULL,"InstallDir",RRF_RT_REG_SZ,NULL,dirp,&dwSize);
		lResult = RegQueryValueEx(hKey,L"InstallDir",NULL,NULL,(LPBYTE)dirptmp,&dwSize);
		if (lResult != ERROR_SUCCESS) 
		{
			MessageBox(NULL,L"Registry key not found. Install C2P again",L"ERROR",MB_OK);
			my_params->sERR = 1;
			strcpy_s(my_params->bERR,MAX_STRING,"Registry key not found. Install C2P again");
			err->AddError("Registry key not found. Install C2P again");
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
//	pout.CreateInstance(__uuidof(Port),NULL,CLSCTX_INPROC_SERVER);//pout.AddRef();
	CoCreateInstance(CLSID_Port,NULL,CLSCTX_INPROC_SERVER,IID_IPort,(void**)&p);
	CoCreateInstance(CLSID_Port,NULL,CLSCTX_INPROC_SERVER,IID_IPort,(void**)&p1);
	CoCreateInstance(CLSID_Port,NULL,CLSCTX_INPROC_SERVER,IID_IPort,(void**)&pout);
	myports.CreateInstance(__uuidof(PortCollection),NULL,CLSCTX_INPROC_SERVER);// myports->AddRef();
	myparams.CreateInstance(__uuidof(ParameterCollection),NULL,CLSCTX_INPROC_SERVER);

#ifdef PRINTOUT
	p->debugfile(&dopliku);
	if(NUM_OF_INPUTS==2)
		p1->debugfile(&dopliku);
	pout->debugfile(&dopliku);
	myports->debugfile(&dopliku);
	myparams->debugfile(&dopliku);
#endif

	/// \warning zmiana iloœci portów musi byæ tu uwzglêdniona
	VariantInit(&varerr);
	dopliku.vt = VT_BYREF;
	dopliku.byref = (void*)err;

	p->AddError(&varerr);
	if(NUM_OF_INPUTS==2)
		p1->AddError(&varerr);
	pout->AddError(&varerr);
	myports->AddError(&varerr);
	myparams->AddError(&varerr);

	myName = L"Cape2Fluent Port";
	myDesc = L"FLUENT CAPE-OPEN unit operation implemented in CPP";
	rep[0] = L"Report 1";
	rep[1] = L"Report 2";
		

/// nazwy portów s¹ wa¿ne
	myvalStatus = CAPE_NOT_VALIDATED;
	p->put_direction(CAPE_INLET);
	p->put_myDesc(L"Inlet port 1");
	p->put_myName(L"Inlet port 1");
	p->put_unit((BYTE*)&myvalStatus);
	myports->AddPort2(p);

	if(NUM_OF_INPUTS==2)
	{
		p1->put_direction(CAPE_INLET);
		p1->put_myDesc(L"Inlet port 2");
		p1->put_myName(L"Inlet port 2");
		p1->put_unit((BYTE*)&myvalStatus);
		myports->AddPort2(p1);
	}

	pout->put_direction(CAPE_OUTLET);
	pout->put_myDesc(L"Outlet port for test unit operation");
	pout->put_myName(L"Outlet port 1");
	pout->put_unit((BYTE*)&myvalStatus);
	myports->AddPort2(pout);

	p->Release();
	if(NUM_OF_INPUTS==2)
		p1->Release();
	pout->Release();
// -----------------------------------------------------------------------------------------
#ifdef NO_CONFIG
	my_params.sERR = 0;
	ileportow = NUM_OF_INPUTS;
#else
	if(my_params->Creadfile(dirp)==FAIL)	{	// wszystkie b³êdy skrytpu s¹ zwracane tutaj
		MessageBox(NULL,L"UnitOperation::Creadfile problem",L"ERROR",MB_OK);
		err->AddError("CUnitOperation::Creadfile problem");
		return;
	} else
		my_params->sERR = 0;	// czyœcimy jakieœ stare b³êdy jeœli by³y

	ICapeCollection *ptrcc;
	myports->QueryInterface(IID_ICapeCollection,(void**)&ptrcc);
	ptrcc->Count(&ileportow);
	ptrcc->Release();
	/// \bug mozliwy problem jesli bedie wiecej wyjsc!!!
	ileportow--; // odejmujemy wyjscia

	// jesli trzeba to usuwam niepotrzebne porty
	if(my_params->sNUMOFPORTS==1)	// cos wpisane jest
	{
		if(my_params->bNUMOFPORTS<ileportow)	{
			int delta = ileportow-my_params->bNUMOFPORTS;
			int stp = NUM_OF_INPUTS;	// numer ostatniego wekscia
			for(int a=0;a<delta;a++)
				myports->RemovePort(stp--);	// usuwam od ostatniego wejscia (wa¿ne ze by od koñca ze wzglêdu na dzia³anie funkcji removeports
			ileportow-=delta;
		}
	}

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

	err->PrintAll();
	myName.Empty();
	myDesc.Empty();
	rep[0].Empty();
	rep[1].Empty();
	errDesc.Empty();
	errInterface.Empty();
	errScope.Empty();

//	SafeArrayDestroy(rep1);
//	p->Release();
//	pout->Release();
//	myports->Release();
//	myparams->Release();

	myports = NULL;
	p->Release();
	if(NUM_OF_INPUTS==2)
		p1->Release();
	pout->Release();
	myparams = NULL;
	
	delete err;
	delete my_params;
	delete runfluent;
	if(mydialog!=NULL)
		delete mydialog;

#ifdef PRINTOUT
	fclose( mystream );
#endif
}

STDMETHODIMP CUnitOperation::InvalidateUnit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

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


/*!
	Z Aspena zawsze wychodz¹ mieszaniny jeœli jest wiêcej ni¿ jeden materia³, co najwy¿ej mo¿na ustawiæ udzia³ molowy 0-1 jeœli chcemy mieæ strumieñ 
	pojedyñczego materia³u.
*/

/*!
	W tej funkcji nastêpuje tak¿e nagranie parametrów na dysk w katalogu c:

*/
STDMETHODIMP CUnitOperation::Calculate()
/// \return Funkcja wywo³uje wyj¹tek w przypadku jakiegokolwiek b³êdu zwróconego przez funkcje przez ni¹ wywo³ywane. Wyj¹tek jest obs³ugiwany lokalnie (nagranie b³êdu do pliku) oraz jest wypychany dalej do ASPENA 
/// \exception CComBSTR W przypadku b³êdu w ci¹gu znajduje siê opis b³êdu, który jest nastêpnie nagrywany na dysk do logu i przekazywany dalej do ASPENA
{
#ifdef PRINTOUT
	fprintf(mystream,"CUnitOperation::STDMETHOD(Calculate)()\n");
#endif
	ICapeThermoMaterialObject* inletMaterials[MAX_INPUTS];
	ICapeThermoMaterialObject* outletMaterial;
	IATCapeXDiagnostic* ASPEN_diag;
/// \warning 
	ICapeUnitPort *inletPort[MAX_INPUT_PORTS];	// maksymalan ilosc portow do obslugi
//	ICapeUnitPort* inletPort2;
	ICapeUnitPort* outletPort;
	IDispatch* disp; 
	IDispatch* disp2; 
	IDispatch* disp3; 
	IDispatch* disp4; 
	CComBSTR s;
	CComBSTR tmp;
	CComBSTR myproperty;
	CComBSTR myphase;
	CComBSTR mole;
	CComBSTR numery_portow;
	CComBSTR nazwa_port;
	ICapeCollection* capecol;
	VARIANT id;
	VARIANT compIds;		// nazwy zwi¹zków wg aspena
	VARIANT avialprops;
	VARIANT T;
	VARIANT p;
	VARIANT X;
	VARIANT f;
// kopie tablic ale ju¿ o rozmiarze odpowiadaj¹cym iloœci komponentów (ka¿da komórka dla ka¿dego komponentu)
	VARIANT newT;
	VARIANT newp;
	VARIANT newX;
	VARIANT newf;
	SAFEARRAYBOUND siz[1];

	VARIANT phases;	// fazy rozpoznane z aspena
	LONG num;		// ilosc zwiazków w strumieniu
	HRESULT herr;
	double temperature, pressure, flow;	// zmienne tymczasowe
	double fraction[MAX_EXPORTS];	// maxymlna ilosc skladników
	int a;
	LONG b;
/// \bug Moze byc problem tu przy wiekszej ilosci portow
	char nbuff[2];
/// Zmiana iloœci portów musi byæ uwzglêdniona tu
/// \code
	VariantInit(&id);
	VariantInit(&avialprops);
	herr = simulationContext->QueryInterface(IID_IATCapeXDiagnostic,(void**)&ASPEN_diag);
	myports->QueryInterface(IID_ICapeCollection,(void**)&capecol);
	for(a=0;a<ileportow;a++)	{
		sprintf_s(nbuff,2,"%d",a+1);
		numery_portow = nbuff;
		nazwa_port = "Inlet port ";
		nazwa_port.Append(numery_portow);
		id.vt = VT_BSTR; id.bstrVal = nazwa_port;
		capecol->Item(id,&disp); disp->QueryInterface(IID_ICapeUnitPort,(void**)&inletPort[a]); disp->Release();
		inletPort[a]->get_connectedObject(&disp3);
		disp3->QueryInterface(IID_ICapeThermoMaterialObject,(void**)&inletMaterials[a]); disp3->Release();


		numery_portow.Empty();
	}

	CComBSTR nazwa_port_out = "Outlet port 1";
	id.vt = VT_BSTR; id.bstrVal = nazwa_port_out;
	capecol->Item(id,&disp2); disp2->QueryInterface(IID_ICapeUnitPort,(void**)&outletPort); disp2->Release();

	outletPort->get_connectedObject(&disp4);
	disp4->QueryInterface(IID_ICapeThermoMaterialObject,(void**)&outletMaterial); disp4->Release();

/// \endcode

	VariantInit(&newT); newT.vt = VT_R8|VT_ARRAY;
	VariantInit(&newp); newp.vt = VT_R8|VT_ARRAY;
	VariantInit(&newX); newX.vt = VT_R8|VT_ARRAY;
	VariantInit(&newf); newf.vt = VT_R8|VT_ARRAY;

	try
	{
		/* po wszyskich wejœciach (materia³y pobrane z ka¿dego wejœcia) oraz
		wype³nianie klas trzymaj¹cych dane */
		for(unsigned int materialy=0;materialy<ileportow;materialy++)	
		{
			herr = inletMaterials[materialy]->AvailableProps(&avialprops);
			herr = inletMaterials[materialy]->GetNumComponents(&num);
			VariantInit(&phases);
			herr = inletMaterials[materialy]->get_PhaseIds(&phases);
			VariantInit(&compIds);
			herr = inletMaterials[materialy]->get_ComponentIds(&compIds);
			if(num>MAX_EXPORTS)	{
				CComBSTR errorin(L"More components passed than allowed ");
				throw errorin;
			}
			// sprawdzam zgodnoœæ nazw faz
			BOOL test;
			BSTR Ids;
			CComBSTR cIds;
			char *ctmp;
			for(a=0;a<num;a++)	{
				test = FAIL;
				ctmp = my_params->bCOMPONENTS.GetSubString(a,COMPONENTS_NAZWA);
				if(ctmp==NULL)	{
					CComBSTR errorin(L"Check if number of components in PHASE matches number of components in ASPEN");
					throw errorin;
				} else
					tmp = ctmp;
				tmp.ToLower();
				for(b=0;b<num;b++)	{
					SafeArrayGetElement(compIds.parray,&b,&Ids);
					cIds.AssignBSTR(Ids);
					cIds.ToLower();
					if(tmp==cIds)	{
						test = OK;	// dla danego a jest pasuj¹ce b
						break;
					}
				}
				if(test==FAIL)	{	// jesli test ma wci¹¿ FAIL to znaczy ¿e ¿adan z nazw ASPENA nie pasuje do danej nazwy ze skryptu
					CComBSTR errorin(L"Check if components names in COMPONENTS match to names in ASPEN");
					throw errorin;
				}
			}

			CComBSTR Liquid(L"Liquid"); CComBSTR Mixture(L"Mixture"); CComBSTR Vapor(L"Vapor");

			myproperty = L"Temperature";
			myphase = L"overall";
			mole = L"mole";
			//		VariantInit(&compIds);
			VariantInit(&T);
			herr = inletMaterials[materialy]->GetPropW(myproperty,myphase,compIds,Mixture,L"",&T);
			if(FAILED(herr))
			{
				CComBSTR errorin(L"Error in GetPropW ");
				errorin.AppendBSTR(myproperty);
				throw errorin;
			}

			myproperty = L"Pressure";
			//		VariantInit(&compIds);
			VariantInit(&p);
			herr = inletMaterials[materialy]->GetPropW(myproperty,myphase,compIds,L"",L"",&p);
			if(FAILED(herr))
			{
				CComBSTR errorin(L"Error in GetPropW ");
				errorin.AppendBSTR(myproperty);
				throw errorin;
			}

			myproperty = L"Fraction";
			//		VariantInit(&compIds);
			VariantInit(&X);
			herr = inletMaterials[materialy]->GetPropW(myproperty,myphase,compIds,L"",mole,&X); // tu zawsze w molach. Jesli w aspenie jest mole frac to tu mamy dok³adnie to samo. JEœli co innego to jest przeliczone
			if(FAILED(herr))
			{
				CComBSTR errorin(L"Error in GetPropW ");
				errorin.AppendBSTR(myproperty);
				throw errorin;
			}

			myproperty = L"TotalFlow";
			//		VariantInit(&compIds);
			VariantInit(&f);
			herr = inletMaterials[materialy]->GetPropW(myproperty,myphase,compIds,L"",mole,&f); // mol/sec
			if(FAILED(herr))
			{
				CComBSTR errorin(L"Error in GetPropW ");
				errorin.AppendBSTR(myproperty);
				throw errorin;
			}

			// ------------------------------------------------------------------------------------------------------------------------------	

			if(T.vt==(VT_ARRAY|VT_R8) && p.vt==(VT_ARRAY|VT_R8) && X.vt==(VT_ARRAY|VT_R8) && f.vt==(VT_ARRAY|VT_R8))	{
				LONG index = 0;
				/// \todo usun¹æ to
				SafeArrayGetElement(T.parray, &index, &temperature);
				SafeArrayGetElement(p.parray, &index, &pressure);
				SafeArrayGetElement(f.parray, &index, &flow);
				for(;index<num;index++)
					SafeArrayGetElement(X.parray, &index, &fraction[index]);

				herr = runfluent->PutParams(T.parray,X.parray,f.parray,p.parray,compIds.parray,materialy);
				if(herr==FAIL)	{
					my_params->sERR = 1;
					CComBSTR errorin(L"Calculate::PutParams problem ");
					throw errorin;
				}
			} else {
				myvalStatus = CAPE_INVALID;
				my_params->sERR=1;
				CComBSTR errorin(L"Calculate::Internal error ");
				throw errorin;
			}
		} // koniec po wszytkich wejœciach

		/// zrzut wszystkich parametrów wejœciowych przechowywanych w obiekcie C_myRunProcess::Parameters
		/// \code
		runfluent->PrintPutParameters("c:\\inParameters.txt");
		/// \endcode

		if(my_params->ValidateParams(BASIC) && my_params->ValidateParams(CASE) && my_params->ValidateParams(EXPORTS))
		{
			herr = runfluent->CreateEnv();
			if(herr==FAIL)	{
				my_params->sERR = 1;
				CComBSTR errorin(L"Calculate::CreateEnv problem ");
				throw errorin;
			}

			herr = runfluent->StartFluent();
			if(herr==FAIL)	{
				my_params->sERR = 1;
				CComBSTR errorin(L"Calculate::StartFluent problem ");
				throw errorin;
			}
			herr = runfluent->ImportData();
			if(herr==FAIL)	{
				my_params->sERR = 1;
				CComBSTR errorin(L"Calculate::ImportData problem ");
				throw errorin;
			}
		} else	{
			my_params->sERR = 1;
			CComBSTR errorin(L"Script Parser: BASIC_CASE_DATA problem ");
			throw errorin;
		}
/// \warning Tablice o rozmiarze odpowiadaj¹cym ilosci komponentów
/// \code
		siz[0].lLbound = 0;
		siz[0].cElements = num;
		newT.parray = SafeArrayCreate(VT_R8, 1, siz);
		newp.parray = SafeArrayCreate(VT_R8, 1, siz);
		newX.parray = SafeArrayCreate(VT_R8, 1, siz);
		newf.parray = SafeArrayCreate(VT_R8, 1, siz);

/// \endcode
		herr = runfluent->GetParams(newT.parray,newX.parray,newf.parray,newp.parray,compIds.parray);
		if(herr==FAIL)	{
			my_params->sERR = 1;
			CComBSTR errorin(L"Calculate::GetParams problem ");
			throw errorin;
		}
		
/// zrzut wszystkich parametrów wyjœciowych przechowywanych w obiekcie C_myRunProcess::Parameters
/// \code
		runfluent->PrintGetParameters("c:\\outParameters.txt");
/// \endcode


		myproperty = L"Temperature";
		//		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",L"",newT);
		if(FAILED(herr))
		{
			CComBSTR errorin(L"Error in SetPropW ");
			errorin.AppendBSTR(myproperty);
			throw errorin;
		}

		myproperty = L"Pressure";
		//		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",L"",newp);
		if(FAILED(herr))
		{
			CComBSTR errorin(L"Error in SetPropW ");
			errorin.AppendBSTR(myproperty);
			throw errorin;
		}

		myproperty = L"Fraction";
		//		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",mole,newX);
		if(FAILED(herr))
		{
			CComBSTR errorin(L"Error in SetPropW ");
			errorin.AppendBSTR(myproperty);
			throw errorin;
		}

		myproperty = L"TotalFlow";
		//		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",mole,newf);
		if(FAILED(herr))
		{
			CComBSTR errorin(L"Error in SetPropW ");
			errorin.AppendBSTR(myproperty);
			throw errorin;
		}

		// flash the outlet material (all outlet ports must be flashed by a CAPE-OPEN unit operation)
		VARIANT props;
		VariantInit(&props);

		CComBSTR tp = "TP";
		herr = outletMaterial->CalcEquilibrium(tp,props);
		if(FAILED(herr))
		{
			CComBSTR errorin(L"Error in SetPropW ");
			errorin.AppendBSTR(myproperty);
			throw errorin;
		}
	}	// try
	
	catch(CComBSTR errorin) {
		capecol->Release();
		for(a=0;a<ileportow;a++)
			inletPort[a]->Release();
		outletPort->Release();
		for(a=0;a<ileportow;a++)
			inletMaterials[a]->Release();
		outletMaterial->Release();
		SetError(errorin,L"ICapeUnit",L"Calculate");
		CComBSTR calc(L"Calculate::");
		calc.Append(errorin);
		CW2A pszB(calc);
		err->AddError(pszB);
		err->PrintAll();
		C_Error *etmp = err;
		CComBSTR btmp;
		if(czyASPEN)	{
			ASPEN_diag->SendMsgToHistory(errorin);
			ASPEN_diag->SendMsgToHistory(L"---------- LOG DUMP: ----------------");
			for(int a=0;a<err->Get_Num_of_Nodes();a++)
			{
				btmp = etmp->data;
				ASPEN_diag->SendMsgToHistory(btmp);
				etmp = (C_Error*)etmp->Get_Next();
			}
			ASPEN_diag->SendMsgToHistory(L"---------- END OF LOG DUMP------------");
			CComBSTR raisederror(L"C2F ERROR");
			ASPEN_diag->RaiseError(ErrorSeverityError,L"ICapeUnit",raisederror);	ASPEN_diag->Release();
		}
		return ECapeUnknownHR;
	}


	capecol->Release();
	for(a=0;a<ileportow;a++)
		inletPort[a]->Release();
	outletPort->Release();
	for(a=0;a<ileportow;a++)
		inletMaterials[a]->Release();
	outletMaterial->Release();
	ASPEN_diag->Release();

	return S_OK;
}
