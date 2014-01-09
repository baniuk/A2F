// xx.h : Declaration of the Cxx

#pragma once
#include "resource.h"       // main symbols



#include "Test_Material_Class_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// Cxx

class ATL_NO_VTABLE Cxx :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<Cxx, &CLSID_xx>,
	public IDispatchImpl<Ixx, &IID_Ixx, &LIBID_Test_Material_ClassLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	Cxx()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_XX)


BEGIN_COM_MAP(Cxx)
	COM_INTERFACE_ENTRY(Ixx)
	COM_INTERFACE_ENTRY(IDispatch)
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



};

OBJECT_ENTRY_AUTO(__uuidof(xx), Cxx)
