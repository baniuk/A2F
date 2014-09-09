/**
 * \file    UnitOperations.h
 * \brief   COClass header for unit operations
 * \details Implements basic interfaces required by CAPE-OPEN
 * \author  PB
 * \date    2013/09/10
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
 * \class StreamNumber
 * \brief Defines correct order of streams in Materials vector
 * \details Streams are kept in Materials vector. Order of enmu defines order of materials in vector
 * \author PB
 * \date 2014/06/19
 * \see UnitOperations::Calculate()
 * \see http://82.145.77.86:8080/trac/A2F/wiki/Schematy
 * \see http://82.145.77.86:8080/trac/A2F/wiki/A2F_Fit_1
*/
enum class StreamNumber : std::size_t
{
	inputPort_REFOR=0,	///< input port REFOR from ASPEN
	inputPort_P1,	///< input port P1 from ASPEN
	outputPort_ANODOFF,	///< output port ANODOFF from ASPEN
	outputPort_EXHAUST ///< output port EXHAUST from ASPEN
};

/**
 * \class CUnitOperations
 *
 * \brief CoClass for basic interfaces implementing Unit Operations
 *
 * Class implements basic interfaces for Unit Operations according to documentation. Implemented interfaces:
 * \li ICapeUnit
 * \li ECapeRoot
 * \li ECapeUser
 * \li ICapeIdentification
 * \li ICapeUtilities
 * \li ECapeUnknown
 * \li ICapeUnitReport
 * \li ICapeDiagnostic - no implementation on PMC side. Only to use on PME side.
 *
 * \note Represents basic object initiated at the beginning
 *
 * \author PB
 *
 * \date 2013/09/10
 *
 * \see 
 * \li AspenPlusUserModelsV8_2-Ref.pdf
 * \li CO_Unit_Operations_v6.25.pdf
 * \li Methods&Tools_Integrated_Guidelines.pdf
 *
 * \todo Finish documentation - add methods descriptions
 * 
 * \warning ICapeDiagnostic - likely not neccessary to implement. Should be found correct tlb in registry? The same situation in case of
 * ICapeParameter interface witch is not implemented here but called by IID
 */
class ATL_NO_VTABLE CUnitOperations :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CUnitOperations, &CLSID_UnitOperations>,
	public IDispatchImpl<IUnitOperations, &IID_IUnitOperations, &LIBID_A2FLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ICapeUnit, &__uuidof(ICapeUnit), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUtilities, &__uuidof(ICapeUtilities), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeUnitReport, &__uuidof(ICapeUnitReport), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeDiagnostic, &__uuidof(ICapeDiagnostic), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CUnitOperations();
	~CUnitOperations();

	DECLARE_REGISTRY_RESOURCEID(IDR_UNITOPERATIONS)


	BEGIN_COM_MAP(CUnitOperations)
		COM_INTERFACE_ENTRY(IUnitOperations)
		COM_INTERFACE_ENTRY2(IDispatch, ICapeUnit)
		COM_INTERFACE_ENTRY(ICapeUnit)
		COM_INTERFACE_ENTRY(ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeUser)
		COM_INTERFACE_ENTRY(ICapeIdentification)
		COM_INTERFACE_ENTRY(ICapeUtilities)
		COM_INTERFACE_ENTRY(ECapeUnknown)
		COM_INTERFACE_ENTRY(ICapeUnitReport)
		COM_INTERFACE_ENTRY(ICapeDiagnostic)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	/// Initializing method called after constructor 
	HRESULT FinalConstruct();

	/// Cleaning-up before destructor
	void FinalRelease();

public:
	/// ICapeUnit Method
	STDMETHOD(get_ports)(LPDISPATCH * ports);
	/// ICapeUnit Method
	STDMETHOD(get_ValStatus)(CapeValidationStatus * ValStatus);
	/// ICapeUnit Method
	STDMETHOD(Calculate)();
	/// ICapeUnit Method
	STDMETHOD(Validate)(BSTR * message, VARIANT_BOOL * isValid);

public:
	/// ECapeRoot Method
	STDMETHOD(get_name)(BSTR * name);

public:
	/// ECapeUser Method
	STDMETHOD(get_code)(long * code);
	/// ECapeUser Method
	STDMETHOD(get_description)(BSTR * description);
	/// ECapeUser Method
	STDMETHOD(get_scope)(BSTR * scope);
	/// ECapeUser Method
	STDMETHOD(get_interfaceName)(BSTR * interfaceName);
	/// ECapeUser Method
	STDMETHOD(get_operation)(BSTR * operation);
	/// ECapeUser Method
	STDMETHOD(get_moreInfo)(BSTR * moreInfo);

public:
	/// ICapeIdentification Method
	STDMETHOD(get_ComponentName)(BSTR * name);
	/// ICapeIdentification Method
	STDMETHOD(put_ComponentName)(BSTR name);
	/// ICapeIdentification Method
	STDMETHOD(get_ComponentDescription)(BSTR * desc);
	/// ICapeIdentification Method
	STDMETHOD(put_ComponentDescription)(BSTR desc);

public:
	/// ICapeUtilities Method
	STDMETHOD(get_parameters)(LPDISPATCH * parameters);
	/// ICapeUtilities Method
	STDMETHOD(put_simulationContext)(LPDISPATCH rhs);
	/// ICapeUtilities Method
	STDMETHOD(Initialize)();
	/// ICapeUtilities Method
	STDMETHOD(Terminate)();
	/// ICapeUtilities Method
	STDMETHOD(Edit)();

	// ECapeUnknown Methods
public:

public:
	/// ICapeUnitReport Method
	STDMETHOD(get_reports)(VARIANT * reports);
	/// ICapeUnitReport Method
	STDMETHOD(get_selectedReport)(BSTR * report);
	/// ICapeUnitReport Method
	STDMETHOD(put_selectedReport)(BSTR report);
	/// ICapeUnitReport Method
	STDMETHOD(ProduceReport)(BSTR * message);

public:
	/// ICapeDiagnostic Methods
	STDMETHOD(PopUpMessage)(BSTR message);
	/// ICapeDiagnostic Methods
	STDMETHOD(LogMessage)(BSTR message);

private:
	/// collection of ports exposed by PMC to PME
	CComPtr<IPortCollection> portCollection;
	/// collection of parameters
	CComPtr<IParameterCollection> parameterCollection;
	/// name of te component passed by PME
	CComBSTR componentName;
	/// description passed from PME
	CComBSTR componentDescription;
	/// simulation context used for calling aspen interfaces
	CComPtr<IDispatch> simulationContext;
	/// Error passed by ECapeUser
	CComBSTR errDesc;
	// name of the interface calling error
	CComBSTR errInterface;
	/// scope of the error
	CComBSTR errScope;
	/// Set error description
	void SetError(const WCHAR* desc, const WCHAR* itface, const WCHAR* scope, HRESULT err_code);
	/// Set error description
	void SetError( const WCHAR* desc, const WCHAR* itface, const WCHAR* scope);
	/// Creates smf file for Fluent
	HRESULT CreateScm(void);
	/// collection of materials provided by ports in PMC
	std::vector<Material*> Materials;
	/// path and name of config file
	std::string configDir;

};

OBJECT_ENTRY_AUTO(__uuidof(UnitOperations), CUnitOperations)
