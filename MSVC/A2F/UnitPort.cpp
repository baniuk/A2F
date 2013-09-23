/**
 * \file    UnitPort.cpp
 * \brief   COClass for ICapeUnitPort interface
 * \author  PB
 * \date    2013/09/17
 * \version 0.5
 */

#include "stdafx.h"
#include "UnitPort.h"


// CUnitPort


CUnitPort::CUnitPort()
{
	// domyœlny kierunek
	portDirection = CAPE_INLET;
	pvalidationStatus = NULL;
}

CUnitPort::~CUnitPort()
{

}

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
*			\li Set names of component and descriptions
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   
*           \li S_OK		Success
*/
HRESULT CUnitPort::FinalConstruct()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// set name and description of the PMC
	componentName = L"A2F Port";
	componentDescription = L"FLUENT CAPE-OPEN unit operation implemented in CPP";

	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

void CUnitPort::FinalRelease()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

STDMETHODIMP CUnitPort::get_name( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::get_code( long * code )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::get_description( BSTR * description )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::get_scope( BSTR * scope )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::get_interfaceName( BSTR * interfaceName )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::get_operation( BSTR * operation )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::get_moreInfo( BSTR * moreInfo )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

/**
* \details  Returns component name from PMC. Default name is set in CPortCollection::FinalConstruct()
* \param[out]	name	name of the component returned to PME	
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::get_ComponentName( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*name = componentName.Copy();
	PANTHEIOS_TRACE_DEBUG(PSTR("Component name passed to PME: "), PW2M(componentName) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Allows to save name of the component given by PME. This name can be later passed to other PMES that use this control. 
* \param[in]	name	name of the component passed from PME.
* \return   CapeError
* \retval   status   The program status.
*                     \li S_OK		Success
*/
STDMETHODIMP CUnitPort::put_ComponentName( BSTR name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	componentName.Empty();	// clear string
	componentName = name;	// copy string from PME
	PANTHEIOS_TRACE_DEBUG(PSTR("Component name: "), PW2M(componentName) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Returns component desc from PMC. Default desc is set in CPortCollection::FinalConstruct()
* \param[out]	desc	desc of the component returned to PME	
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::get_ComponentDescription( BSTR * desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*desc = componentDescription.Copy();
	PANTHEIOS_TRACE_DEBUG(PSTR("Component desc passed to PME: "), PW2M(componentDescription) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Allows to save description of the component given by PME. This name can be later passed to other PMES that use this control
* \param[in]	desc	description of the component passed from PME.
* \return   CapeError
* \retval   status   The program status.
*                     \li S_OK		Success
*/
STDMETHODIMP CUnitPort::put_ComponentDescription( BSTR desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	componentDescription.Empty();	// clear string
	componentDescription = desc;	// copy string from PME
	PANTHEIOS_TRACE_DEBUG(PSTR("Component description: "), PW2M(componentDescription) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Returns type of the port to PME
* \param[out]	portType	type of the port	
* 			\li CAPE_MATERIAL
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::get_portType( CapePortType * portType )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*portType = CAPE_MATERIAL;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Returns direction of the port to PME
* \param[out]	portDirection	direction of the port	
* 			\li CAPE_INLET - default
*			\li CAPE_OUTLET
*			\li CAPE_INLET_OUTLET - should not be used
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::get_direction( CapePortDirection * portDirection )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*portDirection = this->portDirection;
	PANTHEIOS_TRACE_DEBUG(PSTR("Port direction passed to PME: "), pantheios::integer(this->portDirection) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Allows to put direction to port. This method is used during port initialize and allows to put any direction form outside.
* \interface IUnitPortEX
* \param[in]	portDirection	direction of the port	
* 			\li CAPE_INLET
*			\li CAPE_OUTLET
*			\li CAPE_INLET_OUTLET - should not be used
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::put_direction(int portDirection)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	this->portDirection = static_cast<CapePortDirection>(portDirection);
	PANTHEIOS_TRACE_DEBUG(PSTR("Port direction passed to PMC: "), pantheios::integer(this->portDirection) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

STDMETHODIMP CUnitPort::get_connectedObject( LPDISPATCH * connectedObject )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::Connect( LPDISPATCH objectToConnect )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitPort::Disconnect()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

/**
* \details  Allows to pass pointer to CUnitOperations::validationStatus to IUnitPort Interface. This interface must modify this status in 
* every change of port or material.
* \interface IUnitPortEX
* \param[in]	unitValStatus	pointer to CUnitOperations::validationStatus 
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::put_unitValStatus( BYTE * unitValStatus )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	if(NULL == unitValStatus)
		return E_POINTER;
	pvalidationStatus = reinterpret_cast<CapeValidationStatus*>(unitValStatus);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}
