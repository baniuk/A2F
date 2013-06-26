// Port.h : Declaration of the CPort

#pragma once
#include "resource.h"       // main symbols

#include "Cape2Fluent_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

extern "C" void SetOaNoCache(void); 

// CPort

class ATL_NO_VTABLE CPort :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPort, &CLSID_Port>,
	public IDispatchImpl<IPort, &IID_IPort, &LIBID_Cape2FluentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUnitPort, &__uuidof(ICapeUnitPort), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CPort();

	DECLARE_REGISTRY_RESOURCEID(IDR_PORT)


	BEGIN_COM_MAP(CPort)
		COM_INTERFACE_ENTRY(IPort)
		COM_INTERFACE_ENTRY2(IDispatch, ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeUnknown)
		COM_INTERFACE_ENTRY(ECapeUser)
		COM_INTERFACE_ENTRY(ICapeIdentification)
		COM_INTERFACE_ENTRY(ICapeUnitPort)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::FinalRelease\n");
	#endif
	}

public:

	STDMETHOD(AddError)(VARIANT* in);
	STDMETHOD(debugfile)(VARIANT* in);
	STDMETHOD(get_direction)(BYTE* pVal);
	STDMETHOD(put_direction)(BYTE newVal);
	STDMETHOD(get_myName)(BSTR* pVal);
	STDMETHOD(put_myName)(BSTR newVal);
	STDMETHOD(get_myDesc)(BSTR* pVal);
	STDMETHOD(put_myDesc)(BSTR newVal);
	STDMETHOD(put_unit)(BYTE* newVal);

	// ECapeRoot Methods
public:
	STDMETHOD(get_name)(BSTR * name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_name)(BSTR * name)\n");
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
		fprintf(mystream,"CPort::STDMETHOD(get_code)(long * code)\n");
	#endif
		*code = 0;
		return S_OK;
	}
	STDMETHOD(get_description)(BSTR * description)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_description)(BSTR * description)\n");
	#endif
		*description = errDesc.Copy();
		return S_OK;
	}
	STDMETHOD(get_scope)(BSTR * scope)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_scope)(BSTR * scope)\n");
	#endif
		*scope = errScope.Copy();
		return S_OK;
	}
	STDMETHOD(get_interfaceName)(BSTR * interfaceName)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_interfaceName)(BSTR * interfaceName)\n");
	#endif
		*interfaceName = errInterface.Copy();
		return S_OK;
	}
	STDMETHOD(get_operation)(BSTR * operation)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_operation)(BSTR * operation)\n");
	#endif
		CComBSTR tmp(L"Operation not avaiable");
		*operation = tmp.Copy();
		tmp.Empty();
		return S_OK;
	}

	STDMETHOD(get_moreInfo)(BSTR * moreInfo)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_moreInfo)(BSTR * moreInfo)\n");
	#endif
		CComBSTR tmp(L"No more info");
		*moreInfo = tmp.Copy();
		tmp.Empty();
		return S_OK;
	}

	// ICapeIdentification Methods
public:
	STDMETHOD(get_ComponentName)(BSTR * name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_ComponentName)(BSTR * name)\n");
		fprintf(mystream,"	- %S\n",myNamePort);
		fprintf(mystream,"	- %p\n",this);
		fprintf(mystream,"	- mNameptr %p\n",&myNamePort);
	#endif
//		*name = myNamePort.Detach();
		*name = myNamePort.Copy();
		return S_OK;
	}
	STDMETHOD(put_ComponentName)(BSTR name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(put_ComponentName)(BSTR name)\n");
	#endif
		myNamePort.Empty();
		myNamePort = name;
		return S_OK;
	}
	STDMETHOD(get_ComponentDescription)(BSTR * desc)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_ComponentDescription)(BSTR * desc)\n");
	#endif
		*desc = myDesc.Copy();
		return S_OK;
	}
	STDMETHOD(put_ComponentDescription)(BSTR desc)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(put_ComponentDescription)(BSTR desc)\n");
	#endif
		//SysReAllocString(&myDesc,desc);
		myDesc.Empty();
		myDesc = desc;
		return S_OK;
	}

	// ICapeUnitPort Methods
public:
	STDMETHOD(get_portType)(CapePortType * portType)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_portType)(CapePortType * portType)\n");
	#endif
		*portType = CAPE_MATERIAL;
		return S_OK;
	}
	STDMETHOD(get_direction)(CapePortDirection * portDirection)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_direction)(CapePortDirection * portDirection)\n");
	#endif
		*portDirection = mydirection;
		return S_OK;
	}

	STDMETHOD(get_connectedObject)(LPDISPATCH * connectedObject)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(get_connectedObject)(LPDISPATCH * connectedObject)\n");
		fprintf(mystream,"	- %S\n",myNamePort);
		fprintf(mystream,"	- %p\n",myconnectedObject);
	#endif
/*
IPortCollection* tmp;
myports->QueryInterface(IID_IPortCollection,(void**)&tmp);
*ports = (LPDISPATCH)tmp; // przy get zwalnia chyba ten co wywo³uje funkcje - pobiera parametr, ja robie addref
*/
		CComBSTR tt = myNamePort;
		*connectedObject = (LPDISPATCH)myconnectedObject; 
		if(myconnectedObject!=NULL)	{
			myconnectedObject->AddRef(); addrefcount++;
		}
/*		ICapeThermoMaterialObject* tmp;
		if(myconnectedObject!=NULL)
		{
			myconnectedObject->QueryInterface(IID_ICapeThermoMaterialObject,(void**)&tmp);
			*connectedObject = (LPDISPATCH)tmp;
			tmp->Release();
		} else
			*connectedObject = NULL;*/
		return S_OK;
	}

	STDMETHOD(Connect)(LPDISPATCH objectToConnect)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(Connect)(LPDISPATCH objectToConnect)\n");
		fprintf(mystream,"	- %S\n",myNamePort);
		fprintf(mystream,"	- %p\n",myconnectedObject);
	#endif
//		ICapeThermoMaterialObject* tmp;
//		objectToConnect->QueryInterface(IID_ICapeThermoMaterialObject,(void**)&tmp);
//		myconnectedObject = tmp;
		myconnectedObject = (ICapeThermoMaterialObject*)objectToConnect;
		myconnectedObject->AddRef();
		if(pmyValStatus)
			*pmyValStatus = CAPE_NOT_VALIDATED; //invalidateunit

// przy get, jeœli wystawiam na zewn¹trz to ja addref a odbiorca release
		return S_OK;
	}

	STDMETHOD(Disconnect)()
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPort::STDMETHOD(Disconnect)()\n");
	#endif
		if(myconnectedObject!=NULL)	{			// hmmm? nie dzia³a z tym
			myconnectedObject->Release();	// wiesza sie na tym ??
//			myconnectedObject->Release();
//			myconnectedObject->Release();
//			myconnectedObject->Release();
//			myconnectedObject->Release();
			myconnectedObject = NULL;		// musi byc zero do funkcji validate
		}
//		myconnectedObject->Release();
		*pmyValStatus = CAPE_NOT_VALIDATED; //invalidateunit
		return S_OK;
	}

private:
	CComBSTR errDesc;
	CComBSTR errInterface;
	CComBSTR errScope;
	ICapeThermoMaterialObject *myconnectedObject;
	CComBSTR myNamePort;
	CComBSTR myDesc;
	CapePortDirection mydirection;
	FILE *mystream;
	void SetError(BSTR desc, BSTR interf, BSTR scope);
	CapeValidationStatus* pmyValStatus;
	int addrefcount;
	C_Error *err;

public:
	~CPort(void);
};

OBJECT_ENTRY_AUTO(__uuidof(Port), CPort)
