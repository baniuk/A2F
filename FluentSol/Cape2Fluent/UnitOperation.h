// UnitOperation.h : Declaration of the CUnitOperation
#pragma once
#include "resource.h"       // main symbols

#include "Cape2Fluent_i.h"

#ifdef PRINTOUT
	FILE *mystream;
#endif

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

extern "C" void SetOaNoCache(void); 

//_COM_SMARTPTR_TYPEDEF(IPort, __uuidof(IPort));
_COM_SMARTPTR_TYPEDEF(IPortCollection, __uuidof(IPortCollection));
_COM_SMARTPTR_TYPEDEF(IParameterCollection, __uuidof(IParameterCollection));

//! Klasa implementuj¹ca interfejs IUnitOperation

/*! G³ówna klasa implementuja IUnitOpeartion. zawiera podstawowe funkcje od których zaczyna dzia³aæ program
 */

class ATL_NO_VTABLE CUnitOperation :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnitOperation, &CLSID_UnitOperation>,
	public IDispatchImpl<IUnitOperation, &IID_IUnitOperation, &LIBID_Cape2FluentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ICapeUnit, &__uuidof(ICapeUnit), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUnitReport, &__uuidof(ICapeUnitReport), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUtilities, &__uuidof(ICapeUtilities), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<IATCapeXDiagnostic, &__uuidof(IATCapeXDiagnostic), &LIBID_AspenCapeOpenExtensions, /* wMajor = */ 23>
{
public:
	CUnitOperation();

	DECLARE_REGISTRY_RESOURCEID(IDR_UNITOPERATION)


	BEGIN_COM_MAP(CUnitOperation)
		COM_INTERFACE_ENTRY(IUnitOperation)
		COM_INTERFACE_ENTRY2(IDispatch, ICapeUnit)
		COM_INTERFACE_ENTRY(ICapeUnit)
		COM_INTERFACE_ENTRY(ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeUnknown)
		COM_INTERFACE_ENTRY(ECapeUser)
		COM_INTERFACE_ENTRY(ICapeIdentification)
		COM_INTERFACE_ENTRY(ICapeUnitReport)
		COM_INTERFACE_ENTRY(ICapeUtilities)
		COM_INTERFACE_ENTRY_NOINTERFACE(IATCapeXDiagnostic)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(InvalidateUnit)(void);

	// ECapeRoot Methods
public:
	STDMETHOD(get_name)(BSTR * name)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_name)(BSTR * name)\n");
#endif
		*name = errDesc.Copy();
		return S_OK;
	}


	// ECapeUnknown Methods
public:

	// ECapeUser Methods
public:
	STDMETHOD(get_code)(long * code)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_code)(long * code)\n");
#endif
		*code = 0;
		return S_OK;
	}
	STDMETHOD(get_description)(BSTR * description)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_description)(BSTR * description)\n");
#endif
		*description = errDesc.Copy();
		return S_OK;
	}
	STDMETHOD(get_scope)(BSTR * scope)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_scope)(BSTR * scope)\n");
#endif
		*scope = errScope.Copy();
		return S_OK;
	}
	STDMETHOD(get_interfaceName)(BSTR * interfaceName)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_interfaceName)(BSTR * interfaceName)\n");
#endif
		*interfaceName = errInterface.Copy();
		return S_OK;
	}
	STDMETHOD(get_operation)(BSTR * operation)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_operation)(BSTR * operation)\n");
#endif
		CComBSTR myErr(L"Operation not available");
		*operation = myErr.Copy();
		myErr.Empty();
		return S_OK;
	}
	STDMETHOD(get_moreInfo)(BSTR * moreInfo)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_moreInfo)(BSTR * moreInfo)\n");
#endif
		CComBSTR myErr(L"No more info");
		*moreInfo = myErr.Copy();
		myErr.Empty();
		return S_OK;
	}

	// ICapeIdentification Methods
public:
	STDMETHOD(get_ComponentName)(BSTR * name)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_ComponentName)(BSTR * name)\n");
		fprintf(mystream,"	- %p\n",this);
		fprintf(mystream,"	- mNameptr %p\n",&myName);
#endif
		*name = myName.Copy();
		return S_OK;
	}
	STDMETHOD(put_ComponentName)(BSTR name)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(put_ComponentName)(BSTR name)\n");
		fprintf(mystream,"	- %p\n",this);
		fprintf(mystream,"	- mNameptr %p\n",&myName);
#endif
		myName.Empty();
		myName = name;
		return S_OK;
	}
	STDMETHOD(get_ComponentDescription)(BSTR * desc)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_ComponentDescription)(BSTR * desc)\n");
#endif
		*desc = myDesc.Copy();
		return S_OK;
	}
	STDMETHOD(put_ComponentDescription)(BSTR desc)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(put_ComponentDescription)(BSTR desc)\n");
#endif
		myDesc.Empty();
		myDesc = desc;
		return S_OK;
	}

	// ICapeUnit Methods
public:
	STDMETHOD(get_ports)(LPDISPATCH * ports)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_ports)(LPDISPATCH * ports)\n");
#endif	
		IPortCollection* tmp;
		myports->QueryInterface(IID_IPortCollection,(void**)&tmp);
		*ports = (LPDISPATCH)tmp; // przy get zwalnia chyba ten co wywo³uje funkcje - pobiera parametr, ja robie addref
		return S_OK;
	}
	STDMETHOD(get_ValStatus)(CapeValidationStatus * ValStatus)
	{

#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_ValStatus)(CapeValidationStatus * ValStatus)\n");
#endif
		*ValStatus = myvalStatus;
		return S_OK;
	}
	//! G³ówna funkcja obliczaj¹ca, wywo³ywana przez ASPENA
	/*!
	 Funkcja wywo³uje Fluenta, oraz wykonuje ca³y proces obliczeñ - konwertuje dane z ASPENA, wywo³uje wyj¹tki w nim, kontroluje Fluenta
	*/
	STDMETHOD(Calculate)();

	STDMETHOD(Validate)(BSTR * message, VARIANT_BOOL * isValid)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(Validate)(BSTR * message, VARIANT_BOOL * isValid)\n");
#endif
		long count;
		unsigned int a;
		ICapeCollection *ptr;
		ICapeUnitPort *ptrICapeUnitPort;
		IPort *port;
		VARIANT id;
		LPDISPATCH disp;
		LPDISPATCH ptrConnectedObject;
		CComBSTR myErr(L"Port nie podlaczony");
		CComBSTR tmp;
		HRESULT herr;
		IATCapeXDiagnostic* ASPEN_diag;

		VariantInit(&id);
		id.vt = VT_I4;
		// tu if ze sprawdzaniem external error!!
		if(err->Get_Num_of_Nodes()>1)	{		// tu sprawdzenie b³êdów od skryptu (metoda stara)
			unsigned int nr = err->Get_Num_of_Nodes();
			CComBSTR extErr = err->GetNthNodeData(nr);	// ostatni komunikat tutaj
			*message = extErr.Copy();
			*isValid = VARIANT_FALSE;
			myvalStatus = CAPE_INVALID;
			err->PrintAll();
			CComBSTR errorin(L"Error in Validate - check LOG for reason");
			SetError(errorin,L"ICapeUnit",L"Validate");
			if(czyASPEN)	{
				herr = simulationContext->QueryInterface(IID_IATCapeXDiagnostic,(void**)&ASPEN_diag);
				if(herr==S_OK && czyValidate == FALSE) {
					czyValidate = TRUE;
					CComBSTR raisederror(L"C2F ERROR");
					ASPEN_diag->SendMsgToHistory(errorin);
					for(a=0;a<err->Get_Num_of_Nodes();a++)	{
						tmp = err->GetNthNodeData(a);
						ASPEN_diag->SendMsgToHistory(tmp);
						tmp.Empty();
					}				
					ASPEN_diag->RaiseError(ErrorSeverityError,L"ICapeUnit",raisederror);	ASPEN_diag->Release();
				}
			}

			return S_OK;
		}

		// tu sprawdzenie b³êdów od wykonania fluenta

		herr = myports->QueryInterface(IID_ICapeCollection,(void**)&ptr);
		ptr->Count(&count);

		for(int i=1;i<=count;i++)	// tu od samej kontrolki
		{
			id.lVal = i;
			ptr->Item(id,&disp);
			port = (IPort*)disp;
			port->QueryInterface(IID_ICapeUnitPort,(void**)&ptrICapeUnitPort); port->Release();
			ptrICapeUnitPort->get_connectedObject(&ptrConnectedObject);
			if(ptrConnectedObject==NULL)
			{
				*message = myErr.Copy();
				*isValid = VARIANT_FALSE;
				myvalStatus = CAPE_INVALID;
				ptrICapeUnitPort->Release();
				ptr->Release();
				myErr.Empty();
				//				err->AddError("Validate::ptrConnectedObject==NULL"); // nie moze byc bo ten blad nie oznacza nic z³ego
				return S_OK;
			}
			ptrConnectedObject->Release();
			ptrICapeUnitPort->Release();
		}
		myvalStatus = CAPE_VALID;
		*isValid = VARIANT_TRUE;
		*message = myErr.Copy();
		myErr.Empty();
		ptr->Release();
		return S_OK;
	}

	// ICapeUnitReport Methods
public:
	STDMETHOD(get_reports)(VARIANT * reports)
	{
		VariantClear(&v_rep);
		VariantInit(&v_rep);
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_reports)(VARIANT * reports)\n");
		fprintf(mystream,"	- v_rep %p\n",v_rep);
		fprintf(mystream,"	- rep1 %p\n",rep1);
		fprintf(mystream,"	- %p\n",this);
#endif

		LONG rgIndices=1;
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = 2;
		rep1 = SafeArrayCreate(VT_BSTR, 1, rgsabound);	// rep1 jest niszczone na zewn¹trz!! doczytaæ o stringach!!

		SafeArrayPutElement(rep1,&rgIndices,rep[0].Copy());
		rgIndices=0;
		SafeArrayPutElement(rep1,&rgIndices,rep[1].Copy());

		v_rep.vt = VT_BSTR|VT_ARRAY;
		v_rep.parray = rep1;
		*reports = v_rep;
		return S_OK;
	}

	STDMETHOD(get_selectedReport)(BSTR * report)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_selectedReport)(BSTR * report)\n");
#endif
		wchar_t buffer[50];
		swprintf_s(buffer,50,L"Raport %d",reportIndex);
		CComBSTR mess(buffer);
		*report = mess.Copy();;
		mess.Empty();
		return S_OK;
	}
	STDMETHOD(put_selectedReport)(BSTR report)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(put_selectedReport)(BSTR report)\n");
#endif
		BSTR xtmp1 = SysAllocString(L"Report 1");
		BSTR xtmp2 = SysAllocString(L"Report 2");
		if (_tcscmp(OLE2T(report), OLE2T(xtmp1)) == 0)
			reportIndex = 1;
		if (_tcscmp(OLE2T(report), OLE2T(xtmp2)) == 0)
			reportIndex = 2;

		SysFreeString(xtmp1);
		SysFreeString(xtmp2);
		return S_OK;
	}
	STDMETHOD(ProduceReport)(BSTR * message)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(ProduceReport)(BSTR * message)\n");
#endif
		wchar_t buffer[50];
		swprintf_s(buffer,50,L"Produce Raport %d",reportIndex);
		CComBSTR mess(buffer);
		*message = mess.Copy();;
		mess.Empty();
		return S_OK;
	}

	// ICapeUtilities Methods
public:
	STDMETHOD(get_parameters)(LPDISPATCH * parameters)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_parameters)(LPDISPATCH * parameters)\n");
#endif

		IParameterCollection* tmp;
		myports->QueryInterface(IID_IParameterCollection,(void**)&tmp);
		*parameters = (LPDISPATCH)tmp;
		return S_OK;

	}

	STDMETHOD(put_simulationContext)(LPDISPATCH rhs)
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(put_simulationContext)(LPDISPATCH rhs)\n");
#endif
		IATCapeXDiagnostic* tmp;
		HRESULT herr;
		//  Set simulationContext = RHS - to jest chyba odrazu QueryInterface aby uzyskaæ wskaŸnik 
		simulationContext = rhs;
		simulationContext->AddRef();

		// sprawdzenie czy pod aspenem jest uruchomione
		herr = simulationContext->QueryInterface(IID_IATCapeXDiagnostic,(void**)&tmp);
		if(herr==E_NOINTERFACE)
			czyASPEN = FALSE;
		else	{
			czyASPEN = TRUE;
			tmp->Release();
		}
		return S_OK;
	}
	STDMETHOD(Initialize)()
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(Initialize)()\n");
#endif
		return S_OK;
	}
	STDMETHOD(Terminate)()
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(Terminate)()\n");
#endif
		simulationContext->Release();	// wywala siê wtedy jesli zamknie siê Aspena odrazu g³ównym exit. Jesli najpierw zamkniemy flowsheet bêdzie ok
		return S_OK;
	}
	STDMETHOD(Edit)()
	{
#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(Edit)()\n");
#endif
		int res;
		res = MessageBox(NULL,L"Read script file again?",L"Warning",MB_OKCANCEL);
		if(res==IDOK)	{
			if(my_params->Creadfile(dirp)==FAIL)	{	// wszystkie b³êdy skrytpu s¹ zwracane tutaj
				MessageBox(NULL,L"UnitOperation::Creadfile problem",L"ERROR",MB_OK);
				err->AddError("CUnitOperation::Creadfile problem");
				err->PrintAll();
				return S_OK;
			} else	{
				my_params->sERR = 0;	// czyœcimy jakieœ stare b³êdy jeœli by³y
				err->Clear_All();
			}
		}
//		mydialog = new C_myDialogParam;
//		mydialog->Create(L"OPENGL",WS_THICKFRAME|WS_CAPTION|WS_VISIBLE|WS_SYSMENU|WS_CLIPCHILDREN|WS_CLIPSIBLINGS|CS_OWNDC,NULL);		
		return S_OK;
	}

private:
	CComBSTR errDesc;
	CComBSTR errInterface;
	CComBSTR errScope;
	CComBSTR myName;
	CComBSTR myDesc;
	CComBSTR externalError;		// tu wszystkie b³êdy podczas inicjalizacji i odpalania Fluenta	
	CComBSTR rep[2]; SAFEARRAY *rep1; SAFEARRAYBOUND rgsabound[1];
	VARIANT v_rep;
	CapeValidationStatus myvalStatus;
	int reportIndex;
	LPDISPATCH simulationContext;

	IPortCollectionPtr myports;
	//	IPortPtr p;
	//	IPortPtr pout;
	IPort *p;
	IPort *p1;
	IPort *pout;
	IParameterCollectionPtr myparams;
	VARIANT dopliku;
	VARIANT varerr;
	void SetError(BSTR desc, BSTR interf, BSTR scope);

	char *filename;
	char dirp[MAX_STRING];		// katalog z programem
	BOOL czyASPEN; // prawda jeœli odpalone pod ASPENEM
	BOOL czyValidate; // jesli prawda to b³êdy z validate choc raz zosta³y wydrukowane

	C_myRunProcess *runfluent;
	C_Error *err;
	C_Params *my_params;
	C_myDialogParam *mydialog;

	long ileportow;	// tu jest przechowywana ilosc portów w kontrolce - zecywista

public:
	~CUnitOperation(void);

	// IATCapeXDiagnostic Methods
public:
	STDMETHOD(SendMsgToHistory)(BSTR message)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(SendMsgToTerminal)(BSTR message)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(RaiseError)(ErrorSeverity severity, BSTR context, BSTR message)
	{
		return E_NOTIMPL;
	}
};

OBJECT_ENTRY_AUTO(__uuidof(UnitOperation), CUnitOperation)
