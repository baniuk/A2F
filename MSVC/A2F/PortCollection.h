/**
 * \file    PortCollection.h
 * \brief   COClass header for PortCollection interface
 * \details The aim of the Collection interface is to give a CAPE-OPEN component the possibility to expose a list of objects to any client
 * of the component. The client will not be able to modify the collection, i.e. removing, replacing or adding elements. However, since the client
 * will have access to any CAPE-OPEN interface exposed by the items of the collection, it will be able to modify the state of any element.
 * \author  PB
 * \date    2013/09/17
 * \version 0.5
 */

#pragma once
#include "resource.h"       // main symbols



#include "A2F_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


/**
 * \class CPortCollection
 *
 * \brief CoClass implementing ICapeCollection interface
 *
 * Class implements basic interfaces for objects collection and some additional interfaces. Collection is provided to PME by
 * CUnitOperations::get_ports( LPDISPATCH * ports ) method. In this case collection contains ports that will be avaiable in PMC.
 * \li ICapeCollection
 * \li ECapeRoot
 * \li ECapeUser
 * \li ICapeIdentification
 * \li ECapeUnknown
 *
 * \author PB
 *
 * \date 2013/09/16
 *
 * \see 
 * \li AspenPlusUserModelsV8_2-Ref.pdf pp. 271
 * \li Identification Common Interface.pdf
 * \li Methods&Tools_Integrated_Guidelines.pdf
 *
 * \todo 
 *		\li Finish documentation - add methods descriptions
 *		\li move input port to array
 * 
 */
class ATL_NO_VTABLE CPortCollection :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPortCollection, &CLSID_PortCollection>,
	public IDispatchImpl<IPortCollection, &IID_IPortCollection, &LIBID_A2FLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeCollection, &__uuidof(ICapeCollection), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CPortCollection();
	~CPortCollection();

	DECLARE_REGISTRY_RESOURCEID(IDR_PORTCOLLECTION)


	BEGIN_COM_MAP(CPortCollection)
		COM_INTERFACE_ENTRY(IPortCollection)
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
	// list of ports
	std::vector<CComPtr<IUnitPort>> ports;
	// status of the PMC unit referenced from CUnitOperations::validationStatus 
	CapeValidationStatus* pvalidationStatus;
	// adds one port to collection
	HRESULT AddPort(const WCHAR* portName, const WCHAR* portDescription, CapePortDirection portDirection);
	// keeps first free location in ports
	std::vector<CComPtr<IUnitPort>>::iterator currentPort;


};

OBJECT_ENTRY_AUTO(__uuidof(PortCollection), CPortCollection)
