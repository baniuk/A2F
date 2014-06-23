// CapeMaterialObject.cpp : Implementation of CCapeMaterialObject

#include "stdafx.h"
#include "CapeMaterialObject.h"


// CCapeMaterialObject

/**
* \brief Implemented for test purposes
* \details Used in test _MaterialTest:_GetMaterialProps 
* Assumes three components in material:
* \li T = 20, P = 1000, F = 1, TF = 10
* \li T = 30,
* \li T = 40,
* \param[in] property: \a Temperature,\a Pressure,\a Fraction,\a TotalFlow
* \param[in] phase: \a overall
* \param[in] compIds: obtained from ICapeThermoMaterialObject::get_ComponentIds	
* \param[in] calcType: \a Liquid, \a Mixture, \a Vapor, \a ""
* \param[in] basis: \a mole, \a ""
* \param[out] results: parameter defined by myproperty	
* \remarks Teperatures must differ by 10, pressures must differ by 100
* \see Test_Material_Class.cpp numofComp
*/
STDMETHODIMP CCapeMaterialObject::GetProp( BSTR property, BSTR phase, VARIANT compIds, BSTR calcType, BSTR basis, VARIANT * results )
{
	CComBSTR _property = property;
	CComBSTR _phase = phase;
	CComBSTR _calcType = calcType;
	CComBSTR _basis = basis;

	// initialize parameters
	CComSafeArray<double> T(1); T[0] = 20;
	CComSafeArray<double> P(1); P[0] = 200;
	CComSafeArray<double> F(numofComp); F[0] = 1; F[1] = 2; F[2] = 3;
	
	// output for temperature
 	if(_property == L"temperature")
 	{
		CComVariant _results(T);
		_results.Detach(results);
 	}
	// output for pressure
	if(_property == L"pressure")
	{
		CComVariant _results(P);
		_results.Detach(results);
	}
	// output for flow
	if(_property == L"flow")
	{
		CComVariant _results(F);
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
	*numComp = numofComp;
	return S_OK;
}

/**
* \brief Implemented for test purposes
* Assume that return CapeArrayString containing names of phases avaiable
* \li one phase "Liquid"
* \see Test_Material_Class.cpp
* \see CO Thermo Version 1.08.008.pdf
*/
STDMETHODIMP CCapeMaterialObject::get_PhaseIds( VARIANT * PhaseIds )
{
	CComSafeArray<BSTR> Phases(1);
	Phases[0] = L"Liquid";
	CComVariant _PhaseIds(Phases);
	_PhaseIds.Detach(PhaseIds);
	return S_OK;
}
/**
* \brief Implemented for test purposes
* Assume that return CapeArrayString containing names of components avaiable
* \li first component "H20"
* \li second component "O2"
* \li third component "SiO"
* \see Test_Material_Class.cpp
* \see CO Thermo Version 1.08.008.pdf
*/
STDMETHODIMP CCapeMaterialObject::get_ComponentIds( VARIANT * compIds )
{
	CComSafeArray<BSTR> Components(numofComp);
	Components[0] = L"H20";
	Components[1] = L"O2";
	Components[2] = L"SiO";
	CComVariant _compIds(Components);
	_compIds.Detach(compIds);
	return S_OK;
}

