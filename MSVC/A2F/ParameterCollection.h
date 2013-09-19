/**
 * \file    ParameterCollection.h
 * \brief   COClass header for PortCollection interface
 * \details The aim of the Collection interface is to give a CAPE-OPEN component the possibility to expose a list of objects to any client
 * of the component. The client will not be able to modify the collection, i.e. removing, replacing or adding elements. However, since the client
 * will have access to any CAPE-OPEN interface exposed by the items of the collection, it will be able to modify the state of any element.
 * \author  PB
 * \date    2013/09/19
 * \version 0.5
 */

#pragma once
#include "resource.h"       // main symbols



#include "A2F_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CParameterCollection

class ATL_NO_VTABLE CParameterCollection :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CParameterCollection, &CLSID_ParameterCollection>,
	public IDispatchImpl<IParameterCollection, &IID_IParameterCollection, &LIBID_A2FLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeCollection, &__uuidof(ICapeCollection), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CParameterCollection();
	~CParameterCollection();

	DECLARE_REGISTRY_RESOURCEID(IDR_PARAMETERCOLLECTION)


	BEGIN_COM_MAP(CParameterCollection)
		COM_INTERFACE_ENTRY(IParameterCollection)
		COM_INTERFACE_ENTRY2(IDispatch, ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeUnknown)
		COM_INTERFACE_ENTRY(ECapeUser)
		COM_INTERFACE_ENTRY(ICapeCollection)
		COM_INTERFACE_ENTRY(ICapeIdentification)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	/// Initializing method called after constructor 
	HRESULT FinalConstruct();

	/// Cleaning-up before destructor
	void FinalRelease();

public:

public:
	/// ECapeRoot Methods
	STDMETHOD(get_name)(BSTR * name);

	// ECapeUnknown Methods
public:

public:
	/// ECapeUser Methods
	STDMETHOD(get_code)(long * code);
	/// ECapeUser Methods
	STDMETHOD(get_description)(BSTR * description);
	/// ECapeUser Methods
	STDMETHOD(get_scope)(BSTR * scope);
	/// ECapeUser Methods
	STDMETHOD(get_interfaceName)(BSTR * interfaceName);
	/// ECapeUser Methods
	STDMETHOD(get_operation)(BSTR * operation);
	/// ECapeUser Methods
	STDMETHOD(get_moreInfo)(BSTR * moreInfo);

public:
	/// ICapeCollection Methods
	STDMETHOD(Item)(VARIANT id, LPDISPATCH * Item);
	/// ICapeCollection Methods
	STDMETHOD(Count)(long * itemsCount);

public:
	/// ICapeIdentification Methods
	STDMETHOD(get_ComponentName)(BSTR * name);
	/// ICapeIdentification Methods
	STDMETHOD(put_ComponentName)(BSTR name);
	/// ICapeIdentification Methods
	STDMETHOD(get_ComponentDescription)(BSTR * desc);
	/// ICapeIdentification Methods
	STDMETHOD(put_ComponentDescription)(BSTR desc);

private:
	// name of te component passed by PME
	CComBSTR componentName;
	// description passed from PME
	CComBSTR componentDescription;

};

OBJECT_ENTRY_AUTO(__uuidof(ParameterCollection), CParameterCollection)
