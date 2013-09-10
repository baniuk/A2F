/**
 * \file    UnitOperations.cpp
 * \brief   COClass for unit operations
 * \details Implements basic interfaces required by CAPE-OPEN
 * \author  PB
 * \date    2013/09/10
 * \version 0.5
 */

#include "stdafx.h"
#include "UnitOperations.h"


// CUnitOperations

CUnitOperations::CUnitOperations()
{

}

CUnitOperations::~CUnitOperations()
{

}

HRESULT CUnitOperations::FinalConstruct()
{
	return S_OK;
}

void CUnitOperations::FinalRelease()
{

}

STDMETHODIMP CUnitOperations::get_ports( LPDISPATCH * ports )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ValStatus( CapeValidationStatus * ValStatus )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Calculate()
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Validate( BSTR * message, VARIANT_BOOL * isValid )
{
	return E_NOTIMPL;
}


STDMETHODIMP CUnitOperations::get_name( BSTR * name )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_code( long * code )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_description( BSTR * description )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_scope( BSTR * scope )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_interfaceName( BSTR * interfaceName )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_operation( BSTR * operation )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_moreInfo( BSTR * moreInfo )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ComponentName( BSTR * name )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_ComponentName( BSTR name )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ComponentDescription( BSTR * desc )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_ComponentDescription( BSTR desc )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_parameters( LPDISPATCH * parameters )
{
	return E_NOTIMPL;
}

/**
* \details  Initialize allows the unit to initialize itself. It is called once when the unit operation model is instantiated in a particular flowsheet.
*			The Initialize method must not change the current working directory: if it does Aspen Plus will not be able to access its own files and will fail.
*			If the Initialize method needs to display a dialog to allow a user to open a file, it must ensure that the current working directory is restored
*			after a file is selected.
* \return   CapeError
* \retval   status   The program status.
*                     \li 0 = Failure
*                     \li = Success
* \see      AspenPlusUserModelsV8_2-Ref.pdf pp. 286
* \note		Any initialization that could fail must be placed here instead of the constructor.
*/
STDMETHODIMP CUnitOperations::Initialize()
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_simulationContext( LPDISPATCH )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Edit()
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Terminate()
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_reports( VARIANT * reports )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_selectedReport( BSTR * report )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_selectedReport( BSTR report )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::ProduceReport( BSTR * message )
{
	return E_NOTIMPL;
}

