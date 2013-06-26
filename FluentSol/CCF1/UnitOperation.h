// UnitOperation.h : Declaration of the CUnitOperation

#pragma once
#include "resource.h"       // main symbols

#include "CCF1_i.h"

#ifdef PRINTOUT
	FILE *mystream;
#endif

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

extern "C" void SetOaNoCache(void); 

_COM_SMARTPTR_TYPEDEF(IPort, __uuidof(IPort));
_COM_SMARTPTR_TYPEDEF(IPortCollection, __uuidof(IPortCollection));
_COM_SMARTPTR_TYPEDEF(IParameterCollection, __uuidof(IParameterCollection));
// CUnitOperation

class ATL_NO_VTABLE CUnitOperation :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CUnitOperation, &CLSID_UnitOperation>,
	public IDispatchImpl<IUnitOperation, &IID_IUnitOperation, &LIBID_CCF1Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ICapeUnit, &__uuidof(ICapeUnit), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUnitReport, &__uuidof(ICapeUnitReport), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUtilities, &__uuidof(ICapeUtilities), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
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


	// ICapeUnit Methods
public:
	STDMETHOD(get_ports)(LPDISPATCH * ports)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(get_ports)(LPDISPATCH * ports)\n");
	#endif	
		IPortCollection* tmp;
		myports->QueryInterface(IID_IPortCollection,(void**)&tmp);
		*ports = (LPDISPATCH)tmp; // przy get zwalnia chyba ten co wywo�uje funkcje - pobiera parametr, ja robie addref
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

	STDMETHOD(Calculate)()
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(Calculate)()\n");
	#endif
		ICapeThermoMaterialObject* inletMaterial;
		ICapeThermoMaterialObject* outletMaterial;
		ICapeUnitPort* inletPort;
		ICapeUnitPort* outletPort;
		IDispatch* disp; 
		IDispatch* disp2; 
		IDispatch* disp3; 
		IDispatch* disp4; 
		CComBSTR s;
		ICapeCollection* capecol;
		VARIANT id;
		VARIANT compIds;
		VARIANT avialprops;
		VARIANT T;
		VARIANT p;
		VARIANT X;
		VARIANT f;
		HRESULT herr;
		double temperature, pressure, fraction, flow;
		VariantInit(&id);
		VariantInit(&avialprops);

		myports->QueryInterface(IID_ICapeCollection,(void**)&capecol);
		id.vt = VT_I4; id.lVal = 1;
		capecol->Item(id,&disp); disp->QueryInterface(IID_ICapeUnitPort,(void**)&inletPort); disp->Release();
		id.vt = VT_I4; id.lVal = 2;
		capecol->Item(id,&disp2); disp2->QueryInterface(IID_ICapeUnitPort,(void**)&outletPort); disp2->Release();

		inletPort->get_connectedObject(&disp3);
		disp3->QueryInterface(IID_ICapeThermoMaterialObject,(void**)&inletMaterial); disp3->Release();
		outletPort->get_connectedObject(&disp4);
		disp4->QueryInterface(IID_ICapeThermoMaterialObject,(void**)&outletMaterial); disp4->Release();
 
		herr = inletMaterial->AvailableProps(&avialprops);

		CComBSTR myproperty(L"Temperature");
		CComBSTR myphase(L"overall");
		CComBSTR mole = "mole";
		VariantInit(&compIds);
		VariantInit(&T);
		herr = inletMaterial->GetPropW(myproperty,myphase,compIds,L"",L"",&T);
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			SetError(L"Blad",L"UnitOper",L"none");
			err->AddError("Calculate::inletMaterial->GetPropW Temperature");
			return ECapeUnknownHR;
		}

		myproperty = L"Pressure";
		VariantInit(&compIds);
		VariantInit(&p);
		herr = inletMaterial->GetPropW(myproperty,myphase,compIds,L"",L"",&p);
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			SetError(L"Blad",L"UnitOper",L"none");
			err->AddError("Calculate::inletMaterial->GetPropW Pressure");
			return ECapeUnknownHR;
		}

		myproperty = L"Fraction";
		VariantInit(&compIds);
		VariantInit(&X);
		herr = inletMaterial->GetPropW(myproperty,myphase,compIds,L"",mole,&X);
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			err->AddError("Calculate::inletMaterial->GetPropW Fraction");
			SetError(L"Blad",L"UnitOper",L"none");
			return ECapeUnknownHR;
		}

		myproperty = L"TotalFlow";
		VariantInit(&compIds);
		VariantInit(&f);
		herr = inletMaterial->GetPropW(myproperty,myphase,compIds,L"",mole,&f); // mol/sec
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			err->AddError("Calculate::inletMaterial->GetPropW TotalFlow");
			SetError(L"Blad",L"UnitOper",L"none");
			return ECapeUnknownHR;
		}

		if(T.vt==(VT_ARRAY|VT_R8) && p.vt==(VT_ARRAY|VT_R8) && X.vt==(VT_ARRAY|VT_R8) && f.vt==(VT_ARRAY|VT_R8))	{
			LONG index = 0;
			SafeArrayGetElement(T.parray, &index, &temperature);
			SafeArrayGetElement(p.parray, &index, &pressure);
			SafeArrayGetElement(X.parray, &index, &fraction);
			SafeArrayGetElement(f.parray, &index, &flow);

			runfluent->PutParams(temperature,fraction,flow,pressure);

			if(my_params->ValidateParams(BASIC) && my_params->ValidateParams(CASE) && my_params->ValidateParams(EXPORTS))	{
				BOOL ret;

				ret = runfluent->CreateEnv();
				if(ret==FAIL)	{
					my_params->sERR = 1;
					strcpy_s(my_params->bERR,MAX_STRING,"Calculate::CreateEnv problem");
					capecol->Release();
					inletPort->Release();
					outletPort->Release();
					inletMaterial->Release();
					outletMaterial->Release();
					err->AddError("Calculate::CreateEnv problem");
					return S_OK;
				}
	

				ret = runfluent->StartFluent();
				if(ret==FAIL)	{
					my_params->sERR = 1;
					strcpy_s(my_params->bERR,MAX_STRING,"Calculate::StartFluent problem");
					capecol->Release();
					inletPort->Release();
					outletPort->Release();
					inletMaterial->Release();
					outletMaterial->Release();
					err->AddError("Calculate::StartFluent problem");
					return S_OK;
				}
				ret = runfluent->ImportData();
				if(ret==FAIL)	{
					my_params->sERR = 1;
					strcpy_s(my_params->bERR,MAX_STRING,"Calculate::ImportData problem");
					capecol->Release();
					inletPort->Release();
					outletPort->Release();
					inletMaterial->Release();
					outletMaterial->Release();
					err->AddError("Calculate::ImportData problem");
					return S_OK;
				}
			} else	{
				my_params->sERR = 1;
				strcpy_s(my_params->bERR,MAX_STRING,"Script Parser: BASIC_CASE_DATA problem");
				capecol->Release();
				inletPort->Release();
				outletPort->Release();
				inletMaterial->Release();
				outletMaterial->Release();
				err->AddError("Calculate::BASIC_CASE_DATA problem - check if the script consists all required parameters");
				return S_OK;
			}

			runfluent->GetParams(temperature,fraction,flow,pressure);	// odzysk parametr�w (cz�� mo�e by� wej�ciowych cz�� z fluenta)
			SafeArrayPutElement(T.parray, &index, &temperature);
			SafeArrayPutElement(p.parray, &index, &pressure);
			SafeArrayPutElement(X.parray, &index, &fraction);
			SafeArrayPutElement(f.parray, &index, &flow);

		} else {
			myvalStatus = CAPE_INVALID;
			my_params->sERR=1;
			strcpy_s(my_params->bERR,MAX_STRING,"Calculate::Internal error");
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			err->AddError("Calculate::No valid data passed to function");
			return S_OK;
		}



		myproperty = L"Temperature";
		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",L"",T);
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			SetError(L"Blad",L"UnitOper",L"none");
			err->AddError("Calculate::outletMaterial->GetPropW Temperature");
			return ECapeUnknownHR;
		}

		myproperty = L"Pressure";
		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",L"",p);
		if(FAILED(herr))
			{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			SetError(L"Blad",L"UnitOper",L"none");
			err->AddError("Calculate::outletMaterial->GetPropW Pressure");
			return ECapeUnknownHR;
		}

		myproperty = L"Fraction";
		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",mole,X);
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			SetError(L"Blad",L"UnitOper",L"none");
			err->AddError("Calculate::outletMaterial->GetPropW Fraction");
			return ECapeUnknownHR;
		}
		
		

		myproperty = L"TotalFlow";
		VariantInit(&compIds);
		herr = outletMaterial->SetPropW(myproperty,myphase,compIds,L"",mole,f);
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			SetError(L"Blad",L"UnitOper",L"none");
			err->AddError("Calculate::outletMaterial->GetPropW TotalFlow");
			return ECapeUnknownHR;
		}

		// flash the outlet material (all outlet ports must be flashed by a CAPE-OPEN unit operation)
		VARIANT props;
		VariantInit(&props);

		CComBSTR tp = "TP";
		herr = outletMaterial->CalcEquilibrium(tp,props);
		if(FAILED(herr))
		{
			capecol->Release();
			inletPort->Release();
			outletPort->Release();
			inletMaterial->Release();
			outletMaterial->Release();
			SetError(L"Blad",L"UnitOper",L"none");
			err->AddError("Calculate::inletMaterial->CalcEquilibrium");
			return ECapeUnknownHR;
		}


		capecol->Release();
		inletPort->Release();
		outletPort->Release();
		inletMaterial->Release();
		outletMaterial->Release();

		return S_OK;
	}

	STDMETHOD(Validate)(BSTR * message, VARIANT_BOOL * isValid)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(Validate)(BSTR * message, VARIANT_BOOL * isValid)\n");
	#endif
		long count;
		ICapeCollection *ptr;
		ICapeUnitPort *ptrICapeUnitPort;
		IPort *port;
		VARIANT id;
		LPDISPATCH disp;
		LPDISPATCH ptrConnectedObject;
		CComBSTR myErr(L"Port nie podlaczony");
		HRESULT herr;

		VariantInit(&id);
		id.vt = VT_I4;
		// tu if ze sprawdzaniem external error!!
		if(err->Get_Num_of_Nodes()>1)	{		// tu sprawdzenie b��d�w od skryptu (metoda stara)
			unsigned int nr = err->Get_Num_of_Nodes();
			CComBSTR extErr = err->GetNthNodeData(nr);	// ostatni komunikat tutaj
			*message = extErr.Copy();
			*isValid = VARIANT_FALSE;
			myvalStatus = CAPE_INVALID;
			err->PrintAll();
			return S_OK;
		}

		// tu sprawdzenie b��d�w od wykonania fluenta

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
				//err->AddError("Validate::ptrConnectedObject==NULL");
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
	// get - zwraca z komponentu i wystawia do wska�nika, str 195
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
		rep1 = SafeArrayCreate(VT_BSTR, 1, rgsabound);	// rep1 jest niszczone na zewn�trz!! doczyta� o stringach!!
	
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
		//  Set simulationContext = RHS - to jest chyba odrazu QueryInterface aby uzyska� wska�nik 
		simulationContext = rhs;
		simulationContext->AddRef();
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
		simulationContext->Release();	// wywala si� wtedy jesli zamknie si� Aspena odrazu g��wnym exit. Jesli najpierw zamkniemy flowsheet b�dzie ok
		return S_OK;
	}
	STDMETHOD(Edit)()
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CUnitOperation::STDMETHOD(Edit)()\n");
	#endif
//		MessageBox(NULL,L"Text",L"Text1",MB_OK);
		return S_OK;
	}
private:
	CComBSTR errDesc;
	CComBSTR errInterface;
	CComBSTR errScope;
	CComBSTR myName;
	CComBSTR myDesc;
	CComBSTR externalError;		// tu wszystkie b��dy podczas inicjalizacji i odpalania Fluenta	
	CComBSTR rep[2]; SAFEARRAY *rep1; SAFEARRAYBOUND rgsabound[1];
	VARIANT v_rep;
	CapeValidationStatus myvalStatus;
	int reportIndex;
	LPDISPATCH simulationContext;
	
	IPortCollectionPtr myports;
//	IPortPtr p;
//	IPortPtr p1;
	IPort *p;
	IPort *p1;
	IParameterCollectionPtr myparams;
	VARIANT dopliku;
	VARIANT varerr;
	void SetError(BSTR desc, BSTR interf, BSTR scope);

	char *filename;
	char dirp[MAX_STRING];		// katalog z programem

	C_myRunProcess *runfluent;
	C_Error *err;
	C_Params *my_params;


	/*Private params As ParameterCollection
	  Private ports As PortCollection*/
public:

	~CUnitOperation(void);
	STDMETHOD(InvalidateUnit)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(UnitOperation), CUnitOperation)
