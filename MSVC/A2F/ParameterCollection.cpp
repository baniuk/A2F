/**
 * \file    ParameterCollection.cpp
 * \brief   COClass for ICapeCollection interface
 * \details The aim of the Collection interface is to give a CAPE-OPEN component the possibility to expose a list of objects to any client
 * of the component.
 * \author  PB
 * \date    2013/09/19
 * \version 0.5
 */

#include "stdafx.h"
#include "ParameterCollection.h"

// CParameterCollection


CParameterCollection::CParameterCollection()
{
	parameterCount = 0;	// set to 0 aacording to Cape2Fluent code
}

CParameterCollection::~CParameterCollection()
{

}

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
*			\li Set names of interface and descriptions
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*           \li S_OK = Success
*/
HRESULT CParameterCollection::FinalConstruct()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// set name and description of the PMC
	componentName = L"A2FPortCollection";
	componentDescription = L"Collection of ports";
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

void CParameterCollection::FinalRelease()
{

}

/**
* \details  Allows to save description of the component given by PME. This name can be later passed to other PMES that use this control
* \param[in]	desc	description of the component passed from PME.
* \return   CapeError
* \retval   status   The program status.
*                     \li S_OK		Success
*/
STDMETHODIMP CParameterCollection::put_ComponentDescription( BSTR desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	componentDescription.Empty();	// clear string
	componentDescription = desc;	// copy string from PME
	PANTHEIOS_TRACE_DEBUG(PSTR("Component description: "), PW2M(componentDescription) );
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
STDMETHODIMP CParameterCollection::get_ComponentDescription( BSTR * desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*desc = componentDescription.Copy();
	PANTHEIOS_TRACE_DEBUG(PSTR("Component desc passed to PME: "), PW2M(componentDescription) );
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
STDMETHODIMP CParameterCollection::put_ComponentName( BSTR name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	componentName.Empty();	// clear string
	componentName = name;	// copy string from PME
	PANTHEIOS_TRACE_DEBUG(PSTR("Component name: "), PW2M(componentName) );
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
STDMETHODIMP CParameterCollection::get_ComponentName( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*name = componentName.Copy();
	PANTHEIOS_TRACE_DEBUG(PSTR("Component name passed to PME: "), PW2M(componentName) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Returns number of parameters
* \param[out]	itemsCount	number of parameters passed to PME
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success   
* \warning Number of parameters is set to 0 according to old code          
*/
STDMETHODIMP CParameterCollection::Count( long * itemsCount )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*itemsCount = parameterCount;
	PANTHEIOS_TRACE_DEBUG(PSTR("Number of parameters: "), pantheios::integer(*itemsCount) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
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
* \todo Finish          
*/
STDMETHODIMP CParameterCollection::Item( VARIANT id, LPDISPATCH * Item )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));

// 	CComPtr<IParameterCollection> ptmpIParameterCollection(pa);
// 	*Item = ptmpIUnitPort.Detach();
// 	PANTHEIOS_TRACE_DEBUG(	PSTR("IUnitPort pointer passed to PME: "), 
// 		pantheios::pointer(*Item,pantheios::fmt::fullHex));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CParameterCollection::get_moreInfo( BSTR * moreInfo )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CParameterCollection::get_operation( BSTR * operation )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CParameterCollection::get_interfaceName( BSTR * interfaceName )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CParameterCollection::get_scope( BSTR * scope )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CParameterCollection::get_description( BSTR * description )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CParameterCollection::get_code( long * code )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CParameterCollection::get_name( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}
