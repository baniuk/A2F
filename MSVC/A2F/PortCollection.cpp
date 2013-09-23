/**
 * \file    PortCollection.cpp
 * \brief   COClass for ICapeCollection interface
 * \details The aim of the Collection interface is to give a CAPE-OPEN component the possibility to expose a list of objects to any client
 * of the component.
 * \author  PB
 * \date    2013/09/17
 * \version 0.5
 */

#include "stdafx.h"
#include "PortCollection.h"


// CPortCollection


CPortCollection::CPortCollection()
{
	pvalidationStatus = NULL;
}


CPortCollection::~CPortCollection()
{

}

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
*			\li Set names of interface and descriptions
*			\li create instance of IUnitPortEx that is extended version of IUnitPort interface. Extended version provides some additional methods 
*			that are required on PMC side. The PME will call IUnitPort interface drom the same object (coclass instance) and will not see these
*			aditional methods.
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li S_OK = Success
*/
HRESULT CPortCollection::FinalConstruct()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;	// cede returned by COM functions used below
	// set name and description of the PMC
	componentName = L"A2FPortCollection";
	componentDescription = L"Collection of ports";

	// create instance of CoClass for IUnitPort (IUnitPortEx)	
	try
	{
		err_code = inputPort.CoCreateInstance(__uuidof(UnitPort));
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("IUnitPortEx->CoCreateInstance exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("IUnitPortEx->CoCreateInstance error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IUnitPortEx->CoCreateInstance exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	if(FAILED(err_code)) //error
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IUnitPortEx not created because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	PANTHEIOS_TRACE_DEBUG(	PSTR("Instance of IUnitPortEx created"),
							PSTR(" Error: "), winstl::error_desc_a(err_code));

	err_code = Initialize();
	if(FAILED(err_code))
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Port Initialize failed because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	PANTHEIOS_TRACE_DEBUG(	PSTR("Port created"),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Release all interfaces
* \return   none
*/
void CPortCollection::FinalRelease()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	inputPort.Release();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

STDMETHODIMP CPortCollection::get_name( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CPortCollection::get_code( long * code )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CPortCollection::get_description( BSTR * description )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CPortCollection::get_scope( BSTR * scope )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CPortCollection::get_interfaceName( BSTR * interfaceName )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CPortCollection::get_operation( BSTR * operation )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CPortCollection::get_moreInfo( BSTR * moreInfo )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

/**
* \details Return an element from the collection. The requested element can be identified by its actual name (e.g. type CapeString) or by its 
* position in the collection (e.g. type CapeLong). The name of an element is the value returned by the ComponentName() method of its
* ICapeIdentification interface. The advantage of retrieving an item by name rather than by position is that it is much more efficient. 
* This is because it is faster to check all names from the server part than checking then from the client, 
* where a lot of COM/CORBA calls would be required.
* \param[in]	id		Identifier for the requested item:
*				\li name of item (the variant contains a string)
*				\li position in collection (it contains a long)
* \param[out]	Item	returned port
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CPortCollection::Item( VARIANT id, LPDISPATCH * Item )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	CComPtr<IUnitPort> ptmpIUnitPort(inputPort);
	*Item = ptmpIUnitPort.Detach();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

/**
* \details  Returns number of ports
* \param[out]	itemsCount	number of ports passed to PME
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CPortCollection::Count( long * itemsCount )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*itemsCount = 1;ports.size();
	PANTHEIOS_TRACE_DEBUG(PSTR("Returned number of ports: "), pantheios::integer(*itemsCount) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Returns component name from PMC. Default name is set in CPortCollection::FinalConstruct()
* \param[out]	name	name of the component returned to PME	
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CPortCollection::get_ComponentName( BSTR * name )
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
STDMETHODIMP CPortCollection::put_ComponentName( BSTR name )
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
STDMETHODIMP CPortCollection::get_ComponentDescription( BSTR * desc )
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
STDMETHODIMP CPortCollection::put_ComponentDescription( BSTR desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	componentDescription.Empty();	// clear string
	componentDescription = desc;	// copy string from PME
	PANTHEIOS_TRACE_DEBUG(PSTR("Component description: "), PW2M(componentDescription) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Adds ports to collection. All definitions, names and directions are here
* \return   HRESULT value
* \retval   status   The program status.
*           \li S_OK		Success
*           \li HRESULT otherwise
*/
HRESULT CPortCollection::Initialize()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));

	CComPtr<ICapeIdentification> pUnitPortIdentification;	// temporary pointer to IUnitPort->ICapeIdentification interface to set name of port and description
	CComPtr<IUnitPortEx> pUnitPortEx;		// temporary variable for holding unitport interface
	HRESULT err_code;

	// obtain interface to IUnitPort of the same object to call ICapeUnitPort methods
	try
	{
		err_code = inputPort->QueryInterface(IID_PPV_ARGS(&pUnitPortIdentification)); // getting interface pointer (creating referenco of CoClass)
		// IID_PPV_ARGS - keepsa correct type (gets IID using CComPtr definition)
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("ICapeIdentification QueryInterface exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("ICapeIdentification QueryInterface error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IUnitPort->QueryInterface exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of ICapeIdentification not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}		

	PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeIdentification addres "),
		pantheios::pointer(pUnitPortIdentification.p,pantheios::fmt::fullHex),
		PSTR(" Error: "), winstl::error_desc_a(err_code));

	/************************************************************************/
	/* Configuration of port no 1                                           */
	/************************************************************************/
	// calling put_ComponentName method from IUnitPort through IDispatch interface
	/// name of the first port
	CComBSTR name(OLESTR("IN_1"));	
	err_code = pUnitPortIdentification->put_ComponentName(name);
	if(FAILED(err_code)) // error checking
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("put_ComponentName failed because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	// calling put_ComponentDescription method from IUnitPort through IDispatch interface
	/// description of the first port
	name = OLESTR("Inlet port 1");
	err_code = pUnitPortIdentification->put_ComponentDescription(name);
	if(FAILED(err_code)) // error checking
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("put_ComponentDescription failed because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	// calls IUnitPortEx interface method to assign direction of the port
	try
	{
		// get IUnitPortInterface to pass it to PortCollection
		err_code = inputPort->QueryInterface(IID_PPV_ARGS(&pUnitPortEx));
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("IUnitPortEx->QueryInterface exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("IUnitPortEx->QueryInterface error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IUnitPortEx->QueryInterface exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IUnitPortEx not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}		
	PANTHEIOS_TRACE_DEBUG(	PSTR("IUnitPortEx addres "),
							pantheios::pointer(pUnitPortEx.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	// set port direction
	pUnitPortEx->put_direction(static_cast<int>(CAPE_INLET));

	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;	// return S_OK
}

/**
* \details  Allows to pass pointer to CUnitOperations::validationStatus to IPortCollection Interface. This interface must modify this status in 
* every change of port or material.
* \interface IPortCollectionEx
* \param[in]	unitValStatus	pointer to CUnitOperations::validationStatus 
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CPortCollection::put_unitValStatus( BYTE * unitValStatus )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	CComPtr<IUnitPortEx> pUnitPortEx;		// temporary variable for holding unitport interface
	HRESULT err_code;

	if(NULL == unitValStatus)
		return E_POINTER;
	pvalidationStatus = reinterpret_cast<CapeValidationStatus*>(unitValStatus);

	// calls IUnitPortEx interface method to assign direction of the port
	try
	{
		// get IUnitPortInterface to pass it to PortCollection
		err_code = inputPort->QueryInterface(IID_PPV_ARGS(&pUnitPortEx));
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("IUnitPortEx->QueryInterface exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("IUnitPortEx->QueryInterface error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IUnitPortEx->QueryInterface exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IUnitPortEx not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}		
	PANTHEIOS_TRACE_DEBUG(	PSTR("IUnitPortEx addres "),
							pantheios::pointer(pUnitPortEx.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	// pass valStatus pointer from IUnitOperations
	err_code = pUnitPortEx->put_unitValStatus(unitValStatus);
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("put_unitValStatus failed because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}		

	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}
