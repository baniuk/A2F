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

}


CPortCollection::~CPortCollection()
{

}

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
*			\li create instances of IUnitPort that is extended version of IUnitPort interface. Extended version provides some additional methods 
*			that are required on PMC side. The PME will call IUnitPort interface drom the same object (coclass instance) and will not see these
*			aditional methods.
*			\li sets first element in CPortCollection::ports array
*			\li Initializes all ports
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li S_OK = Success
* \warning Number of initialized ports in this function mus equal to PORTS_NUMBER in stdafx.h     
* \todo Check Release on AddPort fail
*/
HRESULT CPortCollection::FinalConstruct()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;	// cede returned by COM functions used below
	// set name and description of the PMC
	componentName = L"A2FPortCollection";
	componentDescription = L"Collection of ports";
	CComPtr<IUnitPort> tmpIUnitPort;	// temporary IUnitPort interface

	PANTHEIOS_TRACE_DEBUG(PSTR("Creating "), pantheios::integer(PORTS_NUMBER),PSTR(" ports"));
	// create instance of CoClass for IUnitPort (IUnitPortEx)	
	// create instances of all ports
	for (int nport=0;nport<PORTS_NUMBER;++nport)
	{
		err_code = tmpIUnitPort.CoCreateInstance(__uuidof(UnitPort));
		if(FAILED(err_code)) //error
		{
			PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IUnitPort not created because: "), 
									pantheios::integer(err_code,pantheios::fmt::fullHex),
									PSTR(" Error: "), winstl::error_desc_a(err_code));
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}
		// add port to vector
		ports.push_back(tmpIUnitPort.Detach());	// clears also tmpIUnitPort Releases ownership of a pointer, sets the CComPtrBase::p data member
		// variable to NULL, and returns a copy of the pointer.
		PANTHEIOS_TRACE_DEBUG(PSTR("Added port no: "),pantheios::integer(nport),PSTR(" "),winstl::error_desc_a(err_code));
	}
	// sets first free port in array
	currentPort = ports.begin();
	/************************************************************************/
	/* Add first port: INLET                                                */
	/************************************************************************/
	err_code = AddPort(L"IN_1",L"Inlet port 1", CAPE_INLET);
	if(FAILED(err_code))
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Port Initialize failed because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	/************************************************************************/
	/* Add second port: OUTLET                                              */
	/************************************************************************/
	err_code = AddPort(L"OUT_1",L"Output port 1", CAPE_OUTLET);
	if(FAILED(err_code))
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Port Initialize failed because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}

	for(CComPtr<IUnitPort> n_port : ports)
		PANTHEIOS_TRACE_DEBUG(	PSTR("IUnitPort address: "), 
								pantheios::pointer(n_port.p,pantheios::fmt::fullHex));

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
* \warning Ports are numbered from 1        
*/
STDMETHODIMP CPortCollection::Item( VARIANT id, LPDISPATCH * Item )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_DEBUG(PSTR("Input id: "),id);
	CComPtr<IUnitPort> ptmpIUnitPort; // port to be returned to PME
	CComPtr<ICapeIdentification> ptmpICapeIdentification;	// to get to name of the port
	CComBSTR componentName;
	HRESULT err_code;

	try
	{
		switch(id.vt)
		{
		case VT_I4:
			ptmpIUnitPort = ports.at(id.lVal-1);	// add reference to IUnitPort
			*Item = ptmpIUnitPort.Detach();
			break;
		case VT_BSTR:
			for(CComPtr<IUnitPort> item : ports)	// go through all ports in array
			{
				err_code = item->QueryInterface(IID_PPV_ARGS(&ptmpICapeIdentification));	// query for ICapeIdentification::get_ComponentName
				if(FAILED(err_code)) 
				{
					// we ar ehere in case if portCollection is ok but requested interface is not supported
					PANTHEIOS_TRACE_ERROR(	PSTR("Instance of ICapeIdentification not created because: "), 
											pantheios::integer(err_code,pantheios::fmt::fullHex),
											PSTR(" Error: "), winstl::error_desc_a(err_code),
											PSTR("Port addres: "), pantheios::pointer(item.p,pantheios::fmt::fullHex));
					PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
					return err_code;
				}		
				err_code = ptmpICapeIdentification->get_ComponentName(&componentName); // get name of the component
				if(FAILED(err_code)) 
				{
					// we ar ehere in case if portCollection is ok but requested interface is not supported
					PANTHEIOS_TRACE_ERROR(	PSTR("get_ComponentName failed: "), 
											pantheios::integer(err_code,pantheios::fmt::fullHex),
											PSTR(" Error: "), winstl::error_desc_a(err_code),
											PSTR("Port addres: "), pantheios::pointer(item.p,pantheios::fmt::fullHex));
					PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
					return err_code;
				}		
				if(componentName==id.bstrVal)
				{
					ptmpIUnitPort = item;	// add reference to IUnitPort
					*Item = ptmpIUnitPort.Detach();
				}
			}
			break;
		default:
			PANTHEIOS_TRACE_CRITICAL(PSTR("Should not be here never"));
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return E_FAIL;
		}
	}
	catch (const std::out_of_range& oor) {
		PANTHEIOS_TRACE_ERROR(	PSTR("Out of Range error: "), oor.what());
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// return HRESULT
	}
	PANTHEIOS_TRACE_DEBUG(	PSTR("IUnitPort pointer passed to PME: "), 
							pantheios::pointer(*Item,pantheios::fmt::fullHex));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
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
	*itemsCount = ports.size();
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
* \details  Adds ports to collection. Uses CPortCollection::currentPort iterator as actual position to set (set in CPortCollection::FinalConstruct())
* \return   HRESULT value
* \param[in] portName Name of the created port
* \param[in] portDescription description of the port
* \param[in] portDirection direction of the port
*			\li CAPE_INLET
*			\li CAPE_OUTLET
* \retval   status   The program status.
*           \li S_OK		Success
*           \li HRESULT otherwise
* \todo Port number to add should be passed to function for code clearity          
*/
HRESULT CPortCollection::AddPort(const WCHAR* portName, const WCHAR* portDescription, CapePortDirection portDirection)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	CComPtr<ICapeIdentification> pUnitPortIdentification;	// temporary pointer to IUnitPort->ICapeIdentification interface to set name of port and description
	CComPtr<IUnitPortEx> pUnitPortEx;		// temporary variable for holding unitport interface
	HRESULT err_code;
	
	// stop if we call AddPort more times than defined PORTS_NUMBER
	PANTHEIOS_MESSAGE_ASSERT(currentPort!=ports.end(),PSTR("More AddPort calls than defined PORTS_NUMBER"));
	// query ICapeIdentification interface to set name and description
	try
	{
		// get IUnitPortInterface to pass it to PortCollection
		err_code = (*currentPort)->QueryInterface(IID_PPV_ARGS(&pUnitPortIdentification));
	}
	catch (const std::out_of_range& oor) {
		PANTHEIOS_TRACE_ERROR(	PSTR("Out of Range error: "), oor.what());
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// return HRESULT
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
	// calling put_ComponentName method from IUnitPort through IDispatch interface
	CComBSTR name(portName);	
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
	CComBSTR desc(portDescription);
	err_code = pUnitPortIdentification->put_ComponentDescription(desc);
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
		err_code = (*currentPort)->QueryInterface(IID_PPV_ARGS(&pUnitPortEx));
	}
	catch (const std::out_of_range& oor) {
		PANTHEIOS_TRACE_ERROR(	PSTR("Out of Range error: "), oor.what());
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// return HRESULT
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
	pUnitPortEx->put_direction(static_cast<int>(portDirection));
	PANTHEIOS_TRACE_DEBUG(PSTR("Port created: "),PW2M(name),PSTR(" "), PW2M(desc),PSTR(" "),pantheios::integer(portDirection));
	// increasing iterator 
	currentPort++;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;	// return S_OK
}
