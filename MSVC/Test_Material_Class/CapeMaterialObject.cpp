// CapeMaterialObject.cpp : Implementation of CCapeMaterialObject

#include "stdafx.h"
#include "CapeMaterialObject.h"


// CCapeMaterialObject

/**
* \brief Implemented for test purposes
* \details Used in test _MaterialTest:_GetMaterialProps 
* Assumes three components in material:
* \li T = 20, P = 1000, F = 1, TF = 10
* \li
* \li
* \param[in] property
*	\li \a Temperature
*	\li \a Pressure
*	\li \a Fraction
*	\li \a TotalFlow
* \param[in] phase:
*	\li \a overall
* \param[in] compIds - obtained from ICapeThermoMaterialObject::get_ComponentIds	
* \param[in] calcType
*	\li \a Liquid
*	\li \a Mixture
*	\li \a Vapor
*	\li ""
* \param[in] basis 
*	\li \a mole
*	\li ""
* \param[out] results - parameter defined by myproperty	
* \see Test_Material_Class.cpp numofComp
*/
STDMETHODIMP CCapeMaterialObject::GetProp( BSTR property, BSTR phase, VARIANT compIds, BSTR calcType, BSTR basis, VARIANT * results )
{
	CComBSTR _property = property;
	CComBSTR _phase = phase;
	CComBSTR _calcType = calcType;
	CComBSTR _basis = basis;

	// initialize parameters
	CComSafeArray<double> T(numofComp); T[0] = 20; T[1] = 30; T[2] = 40;
	CComVariant _results(T);
	
 	if(_property == L"Temperature")
 	{
		_results.Detach(results);
 	}

	return S_OK;
}
/**
* \brief Implemented for test purposes
* \details Used in test _MaterialTest:_COM_method_call 
* \see Test_Material_Class.cpp
*/
STDMETHODIMP CCapeMaterialObject::GetNumComponents( long * numComp )
{
	*numComp = 1;
	return S_OK;
}

