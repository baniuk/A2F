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
	CComBSTR myphase;				// assumes overall
	CComBSTR Mixture;				// assumes mixture
	CComBSTR myproperty;			// physiscal property to get
	VARIANT outputProperty;						// to hold all variant returns from GetProp
	VARIANT compIds;
	VariantInit(&outputProperty);				// initialization of VARIANT
	// ask for temperature
	VariantInit(&compIds);
	myproperty = L"Temperature";	// physiscal property to get
	myphase = L"overall";			// assumes overall
	Mixture = L"Mixture";			// assumes mixture
	hr = mat->GetPropA(myproperty,myphase,compIds,Mixture,L"",&outputProperty);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("FlashMaterialObject:GetTemperature "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	temperatures.CopyFrom(outputProperty.parray);
	isValidated = VALIDATED;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
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
