/**
 * \file    UnitPort.h
 * \brief   COClass header for ICapeUnitPort interface
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
 * \class CUnitPort
 *
 * \brief CoClass implementing ICapeUnitPort interface
 *
 * Class implements basic interfaces for ports and some additional interfaces. Ports are provided to PME as collection ICapeCollection
 * \li ICapeUnitPort
 * \li ECapeRoot
 * \li ECapeUser
 * \li ICapeIdentification
 * \li ECapeUnknown
 * \li IUnitPortEx - interface extending ICapeUnitPort capabilities
 *
 * \author PB
 *
 * \date 2013/09/17
 *
 * \see 
 *		\li AspenPlusUserModelsV8_2-Ref.pdf pp. 271, 270, 280
 *		\li Identification Common Interface.pdf
 *		\li Methods&Tools_Integrated_Guidelines.pdf
 *
 * \todo Finish documentation - add methods descriptions
 */
class ATL_NO_VTABLE CUnitPort :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnitPort, &CLSID_UnitPort>,
	public IDispatchImpl<IUnitPort, &IID_IUnitPort, &LIBID_A2FLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUnitPort, &__uuidof(ICapeUnitPort), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<IUnitPortEx, &__uuidof(IUnitPortEx)>
{
public:
	CUnitPort();
	~CUnitPort();

	DECLARE_REGISTRY_RESOURCEID(IDR_UNITPORT)


	BEGIN_COM_MAP(CUnitPort)
		COM_INTERFACE_ENTRY(IUnitPort)
		COM_INTERFACE_ENTRY2(IDispatch, ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeUnknown)
		COM_INTERFACE_ENTRY(ECapeUser)
		COM_INTERFACE_ENTRY(ICapeIdentification)
		COM_INTERFACE_ENTRY(ICapeUnitPort)
		COM_INTERFACE_ENTRY(IUnitPortEx)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	/// Initializing method called after constructor 
	HRESULT FinalConstruct();

	/// Cleaning-up before destructor
	void FinalRelease();

public:
	/// ECapeRoot Methods
	STDMETHOD(get_name)(BSTR * name);

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
	/// ICapeIdentification Methods
	STDMETHOD(get_ComponentName)(BSTR * name);
	/// ICapeIdentification Methods
	STDMETHOD(put_ComponentName)(BSTR name);
	/// ICapeIdentification Methods
	STDMETHOD(get_ComponentDescription)(BSTR * desc);
	/// ICapeIdentification Methods
	STDMETHOD(put_ComponentDescription)(BSTR desc);

public:
	/// ICapeUnitPort Methods
	STDMETHOD(get_portType)(CapePortType * portType);
	/// ICapeUnitPort Methods
	STDMETHOD(get_direction)(CapePortDirection * portDirection);
	/// ICapeUnitPort Methods
	STDMETHOD(get_connectedObject)(LPDISPATCH * connectedObject);
	/// ICapeUnitPort Methods
	STDMETHOD(Connect)(LPDISPATCH objectToConnect);
	/// ICapeUnitPort Methods
	STDMETHOD(Disconnect)();
	/// ICapeUnitPortEx Methods - own extension
	STDMETHOD(put_direction)(int portDirection);
	STDMETHOD(put_portType)(int portType);


private:
	/// name of te component passed by PME
	CComBSTR componentName;
	/// description passed from PME
	CComBSTR componentDescription;
	/// direction of the port
	/**
	* \details Define direction of the port. 
	* \li CAPE_INLET - default
	* \li CAPE_OUTLET
	* \li CAPE_INLET_OUTLET - should not be used
	* 
	* \see CO_Unit_Operations_v6.25.pdf pp. 280
	*/
	CapePortDirection portDirection;
	/// Type of the port
	/**
	* \details Allows to define port type: \c CapeMaterial, \c CapeEnergy, \c CapeInformation, or \c CapeAny. 
	* \see AspenPlus User models.pdf pp. 281
	*/ 
	CapePortType portType;
	/// Object connected to port (from outside)
	CComPtr<ICapeThermoMaterialObject> connectedObject; /**< the material object connected to this port, if version 1.0 */

public:
};

OBJECT_ENTRY_AUTO(__uuidof(UnitPort), CUnitPort)
