/**
 * \file    UnitOperations.cpp
 * \brief   COClass for unit operations
 * \details Implements basic interfaces required by CAPE-OPEN. Contains also initialization of Pantheios API.
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
*			Initializes also logging API and sets output log file.
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li E_FAIL = on Pantheios initialization fail (file and api)
*                     \li S_OK = Success
* \see
*			\li http://msdn.microsoft.com/en-us/library/afkt56xx(v=vs.110).aspx
*			\li http://www.murrayc.com/learning/windows/usecomfromatl.shtml
* \warning It seems that after adding model to workspace destructor is also called. Object is created, ask about ports and deleted.	
*/
HRESULT CUnitOperations::FinalConstruct()
{
// Logging API initialization
//	if(pantheios::init()<0)
//		return E_FAIL;
	// set file name and path
//	pantheios_be_file_setFilePath(PSTR(PANTHEIOS_LOG_FILE_NAME), PANTHEIOS_BEID_ALL);
//	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("LOG API Initialized")); 
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	portCollection.CreateInstance(__uuidof(PortCollection),NULL,CLSCTX_INPROC_SERVER);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Close log file and un-initialize Pantheios API
* \return   none
*/
void CUnitOperations::FinalRelease()
{
	// closing log file
//	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("LOG API Closing"));
//	pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);
//	pantheios::uninit();
}

/**
* \details  Ports returns an ICapeCollection interface that provides access to the unit’s list of ports. Each element accessed through
* the returned interface must support the ICapeUnitPort interface. It is called by PME just after initialization.
* \param[out]	ports	pointer to IPortCollection
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li HRESULT	if exception _com_error caught or QueryInterface not returned S_OK 
*                     \li E_FAIL	if unsuported exception caught
*                     \li S_OK		Success
* \see
*			\li AspenPlusUserModelsV8_2-Ref.pdf pp. 271, 273
*/
STDMETHODIMP CUnitOperations::get_ports( LPDISPATCH * ports )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	IPortCollection *tmp;	// temporary var for holding IportCollection pointer (CportCollection coclass)
	HRESULT err;	// error code for QueryInterface
	try
	{
		err = portCollection->QueryInterface(__uuidof(IPortCollection),(void**)&tmp); // getting interface pointer (creating referenco of CoClass)
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		PANTHEIOS_TRACE_ERROR(PSTR("IPortCollection->QueryInterface exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("IPortCollection->QueryInterface error code: "),pantheios::integer(e.Error()));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IPortCollection->QueryInterface exception"));
		return E_FAIL;	// unexpected exception
	}
	if(S_OK == err) 
	{
		PANTHEIOS_TRACE_DEBUG(PSTR("IportCollection addres "), pantheios::pointer(tmp,pantheios::fmt::fullHex));
		*ports = (LPDISPATCH)tmp;	// pointer to port collection exposed to PME 
	}
	else
	{
		PANTHEIOS_TRACE_ERROR(PSTR("IPortCollection->QueryInterface error code: "),pantheios::integer(err));
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return err;	// return S_OK or other HRESULT
}

STDMETHODIMP CUnitOperations::get_ValStatus( CapeValidationStatus * ValStatus )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Calculate()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Validate( BSTR * message, VARIANT_BOOL * isValid )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}


STDMETHODIMP CUnitOperations::get_name( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_code( long * code )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_description( BSTR * description )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_scope( BSTR * scope )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_interfaceName( BSTR * interfaceName )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_operation( BSTR * operation )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_moreInfo( BSTR * moreInfo )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ComponentName( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_ComponentName( BSTR name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ComponentDescription( BSTR * desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_ComponentDescription( BSTR desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_parameters( LPDISPATCH * parameters )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
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
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_simulationContext( LPDISPATCH )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Edit()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Terminate()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_reports( VARIANT * reports )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_selectedReport( BSTR * report )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_selectedReport( BSTR report )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::ProduceReport( BSTR * message )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

