/**
* \file    CapeMaterialObject.h
* \brief   Holds dummy definitions of all methods from ICapeThermoMaterialObject
* \details Holds dummy definitions of all methods from ICapeThermoMaterialObject used for testing purposes
* \author  PB
* \date    2014/01/01
* \version 0.5
*/

#pragma once
#include "resource.h"       // main symbols

#include "Test_Material_Class_i.h"

#define numofComp 3	/**< Number of components in stream */

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

/**
* \class CCapeMaterialObject
*
* \brief CoClass for ICapeThermoMaterialObject
*
* Class implements interface of ICapeThermoMaterialObject for testing purposes
*
* \note Represents basic object for test of Material.cpp class
*
* \author PB
*
* \date 2014/01/02
*/
class ATL_NO_VTABLE CCapeMaterialObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCapeMaterialObject, &CLSID_CapeMaterialObject>,
	public IDispatchImpl<ICapeMaterialObject, &IID_ICapeMaterialObject, &LIBID_Test_Material_ClassLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ICapeThermoMaterialObject, &__uuidof(ICapeThermoMaterialObject), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CCapeMaterialObject()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CAPEMATERIALOBJECT)

	BEGIN_COM_MAP(CCapeMaterialObject)
		COM_INTERFACE_ENTRY(ICapeMaterialObject)
		COM_INTERFACE_ENTRY2(IDispatch, ICapeThermoMaterialObject)
		COM_INTERFACE_ENTRY(ICapeThermoMaterialObject)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

private:

	// ICapeThermoMaterialObject Methods
public:
	STDMETHOD(get_ComponentIds)(VARIANT * compIds);
	STDMETHOD(get_PhaseIds)(VARIANT * PhaseIds);
	STDMETHOD(GetUniversalConstant)(VARIANT props, VARIANT * propVals)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetComponentConstant)(VARIANT props, VARIANT compIds, VARIANT * propVals)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(CalcProp)(VARIANT props, VARIANT phases, BSTR calcType)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(GetProp)(BSTR property, BSTR phase, VARIANT compIds, BSTR calcType, BSTR basis, VARIANT * results);
	STDMETHOD(SetProp)(BSTR property, BSTR phase, VARIANT compIds, BSTR calcType, BSTR basis, VARIANT values)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(CalcEquilibrium)(BSTR flashType, VARIANT props)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(SetIndependentVar)(VARIANT indVars, VARIANT values)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetIndependentVar)(VARIANT indVars, VARIANT * values)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(PropCheck)(VARIANT props, VARIANT * valid)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(AvailableProps)(VARIANT * props)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(RemoveResults)(VARIANT props)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(CreateMaterialObject)(LPDISPATCH * materialObject)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(Duplicate)(LPDISPATCH * clone)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(ValidityCheck)(VARIANT props, VARIANT * relList)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetPropList)(VARIANT * props)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetNumComponents)(long * numComp);
};

OBJECT_ENTRY_AUTO(__uuidof(CapeMaterialObject), CCapeMaterialObject)
