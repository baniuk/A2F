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
}

CUnitPort::~CUnitPort()
{

}

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
*			\li Set names of component and descriptions
* \interface ICapeUnitPort			
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

/**
* \details  Release all interfaces
* \return   none
* \todo add ref countig to log for CComPtr vars
*/
void CUnitPort::FinalRelease()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	connectedObject.Release();
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
* \interface ICapeIdentification
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
* \interface ICapeIdentification
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
* \interface ICapeIdentification
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
* \interface ICapeIdentification
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
* \interface ICapeUnitPort				
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
* \interface ICapeUnitPort				
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
* \interface ICapeUnitPort				
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

/**
* \details  Returns the material, energy, or information object connected to the port using the Connect method.
* \interface ICapeUnitPort
* \param[out]	connectedObject	object from PMC to PME
* \return   CapeError
* \interface ICapeUnitPort	
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::get_connectedObject( LPDISPATCH * connectedObject )
{
	// object to return 
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	CComPtr<ICapeThermoMaterialObject> tmpconnextedObject(this->connectedObject);
	*connectedObject = tmpconnextedObject.Detach();
	PANTHEIOS_TRACE_DEBUG(	PSTR("IPortCollection pointer passed to PME: "), 
							pantheios::pointer(*connectedObject,pantheios::fmt::fullHex));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Connect connects a stream to a port. The port validates the type of the object being passed. Aspen Plus creates a material object
* when it connects a stream to a port that belongs to a CAPE-OPEN unit. It then calls the port’s Connect method passing in the material object's
* IDispatch interface. Aspen Plus gives the new material object the same name as stream that was connected to the port. Material objects are 
* described in CAPE-OPEN COM Thermodynamic Interfaces, Chapter 27.
* This method invalidate unit
* \interface ICapeUnitPort
* \param[in]	objectToConnect	object from PME to connect to	
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::Connect( LPDISPATCH objectToConnect )
{
	HRESULT err_code;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// assign PME object to local var
	CComPtr<IDispatch> tmpconnectedObject(objectToConnect);
	try
	{
		// quering to demanded interface (with addref)
		err_code = tmpconnectedObject->QueryInterface(IID_PPV_ARGS(&connectedObject));
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("IID_ICapeThermoMaterialObject QueryInterface exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("IID_ICapeThermoMaterialObject QueryInterface error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IID_ICapeThermoMaterialObject->QueryInterface exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IID_ICapeThermoMaterialObject not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}		
	PANTHEIOS_TRACE_DEBUG(	PSTR("IID_ICapeThermoMaterialObject addres "),
							pantheios::pointer(connectedObject.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	
	// invalidating unit after change of the port
	exValidationStatus = CAPE_NOT_VALIDATED;
	PANTHEIOS_TRACE_DEBUG(	PSTR("Unit status: "),
							pantheios::integer(exValidationStatus));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Disconnect disconnects the port from the connected stream. Aspen Plus calls Disconnect when a stream is disconnected from a port that
* belongs to a CAPE-OPEN unit.
* \interface ICapeUnitPort
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitPort::Disconnect()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// disconect object
	connectedObject = NULL;
	exValidationStatus = CAPE_NOT_VALIDATED;
	PANTHEIOS_TRACE_DEBUG(	PSTR("Unit status: "),
							pantheios::integer(exValidationStatus));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

