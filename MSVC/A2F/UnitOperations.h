// UnitOperations.h : Declaration of the CUnitOperations

#pragma once
#include "resource.h"       // main symbols



#include "A2F_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CUnitOperations

class ATL_NO_VTABLE CUnitOperations :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnitOperations, &CLSID_UnitOperations>,
	public IDispatchImpl<IUnitOperations, &IID_IUnitOperations, &LIBID_A2FLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ICapeUnit, &__uuidof(ICapeUnit), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CUnitOperations()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_UNITOPERATIONS)


	BEGIN_COM_MAP(CUnitOperations)
		COM_INTERFACE_ENTRY(IUnitOperations)
		COM_INTERFACE_ENTRY2(IDispatch, ICapeUnit)
		COM_INTERFACE_ENTRY(ICapeUnit)
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
	STDMETHOD(get_ports)(LPDISPATCH * ports);
	STDMETHOD(get_ValStatus)(CapeValidationStatus * ValStatus);
	STDMETHOD(Calculate)();
	STDMETHOD(Validate)(BSTR * message, VARIANT_BOOL * isValid);
};

OBJECT_ENTRY_AUTO(__uuidof(UnitOperations), CUnitOperations)
