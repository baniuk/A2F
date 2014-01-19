/**
 * \file    Material.cpp
 * \brief   Body of Material class
 * \details Provides tools for handling Cape-Open materials
 * \author  PB
 * \date    2013/12/30
 * \version 0.5
 */
#include "stdafx.h"
#include "Material.h"


Material::Material(ICapeThermoMaterialObject *mat)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	isValidated = INVALIDATED;
	this->mat = mat;
	mat->AddRef();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}


Material::~Material(void)
{
	mat->Release();
}

/**
* \details Flashes internal structures of Material object by copying properties of 
* Material:mat to relevant CCom classes
* \returns Status of the operation
*/
HRESULT Material::FlashMaterialObject()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
	// get number of components, etc
	hr = get_Composition();
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("FlashMaterialObject:get_Composition "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}

	hr = get_PhysicalProp();
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("FlashMaterialObject:get_PhysicalProp "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}

	isValidated = VALIDATED;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details Extract information on stream structure from material:
* \li number of components
* \li names of components
* \li ids of components
* \li phases avaiable in stream
* Fills relevant data in class
* \returns Status of the operation
*/
HRESULT Material::get_Composition()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
	// number of components in stream --> copy to numComp
	hr = mat->GetNumComponents(&numComp);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_Composition:GetNumComponents "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	
	// phases --> copy to phases
	VARIANT tmpPhases;
	VariantInit(&tmpPhases);
	hr = mat->get_PhaseIds(&tmpPhases);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_Composition:GetNumComponents "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	phases.CopyFrom(tmpPhases.parray);
	
	// id of componnets --> copy to compIds
	VARIANT tmpCompIds;
	VariantInit(&tmpCompIds);
	hr = mat->get_ComponentIds(&tmpCompIds);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_Composition:GetNumComponents "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	compIds.CopyFrom(tmpCompIds.parray);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}
/**
* \details Extract information on stream physical properties:
* \li temeprature
* \li pressure
* \li fraction
* \li Flow
* Fills relevant data in class
* \remarks Assumes extraction for all components of the stream even if there is the same parameter for all
* components. It will be duplicated in array.
* \returns Status of the operation
*/
HRESULT Material::get_PhysicalProp()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
	CComBSTR myphase;				// assumes overall
	CComBSTR Mixture;				// assumes mixture
	CComBSTR myproperty;			// physiscal property to get
	VARIANT outputProperty;						// to hold all variant returns from GetProp
	VARIANT compIds;
	// ask for temperature
	VariantInit(&outputProperty);				// initialization of VARIANT
	VariantInit(&compIds);
	myproperty = L"Temperature";	// physiscal property to get
	myphase = L"overall";			// assumes overall
	Mixture = L"Mixture";			// assumes mixture
	hr = mat->GetPropA(myproperty,myphase,compIds,Mixture,L"",&outputProperty);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_PhysicalProp:GetTemperature "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	temperatures.CopyFrom(outputProperty.parray);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

// HRESULT Material::GetTemperature(const VARIANT& compIds, VARIANT* T)
// {
// 	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
// 	HRESULT hr;
// //	CComSafeArray<double> tmpT;	// holds SAFEARRAY returned in VARIANT by CAPE-OPEN
// 	CComBSTR myphase(L"overall");			// assumes overall
// 	CComBSTR Mixture(L"Mixture");			// assumes mixture
// 	CComBSTR myproperty(L"Temperature");	// physiscal property to get
// // 	VARIANT vT;								// output data (SAFEARRAY)
// // 	VariantInit(&vT);						// initialization of VARIANT
// 	hr = mat->GetPropA(myproperty,myphase,compIds,Mixture,L"",T);
// 	if(FAILED(hr))
// 	{	
// 		PANTHEIOS_TRACE_ERROR(PSTR("GetTemperature: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
// 		return hr;
// 	}
// 	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
// }
