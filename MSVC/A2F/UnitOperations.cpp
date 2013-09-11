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

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li HRESULT = Failure
*                     \li S_OK = Success
* \see
*			\li http://msdn.microsoft.com/en-us/library/afkt56xx(v=vs.110).aspx
*			\li http://www.murrayc.com/learning/windows/usecomfromatl.shtml
*/
HRESULT CUnitOperations::FinalConstruct()
{
	// Logging API initialization

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
*                     \li S_OK = Success
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

