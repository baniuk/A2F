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
*			\li Set names of interface and descriptions
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li S_OK = Success
*/
HRESULT CPortCollection::FinalConstruct()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// set name and description of the PMC
	componentName = L"A2FPortCollection";
	componentDescription = L"Collection of ports";
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

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

STDMETHODIMP CPortCollection::Item( VARIANT id, LPDISPATCH * Item )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CPortCollection::Count( long * itemsCount )
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
* \details  Allows to put reference to port. This method is used during port initialize and allows to put any direction form outside.
* \interface IPortCollectionEx
* \param[in]	port	reference to IUnitPort interface	
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CPortCollection::put_port( IUnitPort * port )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	ports.push_back(port);
	PANTHEIOS_TRACE_DEBUG(	PSTR("Add port with address: "),
							pantheios::pointer(port,pantheios::fmt::fullHex),
							PSTR( " number of elements: "),
							pantheios::integer(ports.size()));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

