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
CapeValidationStatus exValidationStatus = CAPE_NOT_VALIDATED;

CUnitOperations::CUnitOperations()
{

}

CUnitOperations::~CUnitOperations()
{
	
}

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
*			\li Set names of component and descriptions
*			\li create instance of IPortCollection
*			\li create instance of IParameterCollection
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The CreateInstance status  - http://msdn.microsoft.com/en-us/library/windows/desktop/ms686615(v=vs.85).aspx
*                     \li S_OK		Success
* \see
*			\li http://msdn.microsoft.com/en-us/library/afkt56xx(v=vs.110).aspx
*			\li http://www.murrayc.com/learning/windows/usecomfromatl.shtml
*			\li A2f.idl file for additional interfaces definitions made from skratch
* \warning It seems that after adding model to workspace destructor is also called. Object is created, ask about ports and deleted.	
*/
HRESULT CUnitOperations::FinalConstruct()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;	// cede returned by COM functions used below
	// set name and description of the PMC
	componentName = L"A2F";
	componentDescription = L"FLUENT CAPE-OPEN unit operation implemented in CPP";

	// create instance of CoClass for ICapePortCollection
	try
	{
		err_code = portCollection.CoCreateInstance(__uuidof(PortCollection));
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("IPortCollection->CoCreateInstance exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("IPortCollection->CoCreateInstance error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IPortCollection->CoCreateInstance exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	if(FAILED(err_code))	// error
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of PortCollection not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	PANTHEIOS_TRACE_DEBUG(	PSTR("Instance of PortCollection created"),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	PANTHEIOS_TRACE_DEBUG(	PSTR("IPortCollection addres: "), 
							pantheios::pointer(portCollection.p,pantheios::fmt::fullHex));
	
	// create instance of CoClass for ICapeParameterCollection
	try
	{
		err_code = parameterCollection.CoCreateInstance(__uuidof(ParameterCollection));
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("IParameterCollection->CoCreateInstance exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("IParameterCollection->CoCreateInstance error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected IParameterCollection->CoCreateInstance exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	if(FAILED(err_code))	// error
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IParameterCollection not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	PANTHEIOS_TRACE_DEBUG(	PSTR("Instance of IParameterCollection created"),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	PANTHEIOS_TRACE_DEBUG(	PSTR("IParameterCollection addres: "), 
							pantheios::pointer(parameterCollection.p,pantheios::fmt::fullHex));
	
	PANTHEIOS_TRACE_DEBUG(	PSTR("Unit status: "),
							pantheios::integer(exValidationStatus));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Release all interfaces
* \return   none
* \todo add ref countig to log for CComPtr vars
*/
void CUnitOperations::FinalRelease()
{
	// releases Aspen interfaces
	ULONG count = simulationContext->Release(); // returns currnet object reference count
	PANTHEIOS_TRACE_DEBUG(	PSTR("Release IDispatch pointer: "), 
							pantheios::pointer(simulationContext,pantheios::fmt::fullHex),
							PSTR(" count= "),
							pantheios::integer(count));
	portCollection.Release(); // release pointer - make sure that all instances will be closed
	parameterCollection.Release();
}

/**
* \details  Ports returns an ICapeCollection interface that provides access to the unit�s list of ports. Each element accessed through
* the returned interface must support the ICapeUnitPort interface. It is called by PME just after initialization.
* Query interface returns error code if requested interface is not supported. In case more general errors, exception _com_error is thrown.
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
	CComPtr<IPortCollection> ptmpIPortCollection(portCollection);	// add reference to portCollection
	*ports = ptmpIPortCollection.Detach();
	PANTHEIOS_TRACE_DEBUG(	PSTR("IPortCollection pointer passed to PME: "), 
							pantheios::pointer(*ports,pantheios::fmt::fullHex));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;	// return S_OK or other HRESULT
}

/**
* \details  Returns to PME status of PMC.
* \return   Return S_OK on success.
* \param[out]   ValStatus   The PMC status.
*				\li CAPE_VALID
*				\li CAPE_INVALID
*				\li CAPE_NOT_VALIDATED
*
* \see
*			\li AspenPlusUserModelsV8_2-Ref.pdf pp. 274	
*/
STDMETHODIMP CUnitOperations::get_ValStatus( CapeValidationStatus * ValStatus )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
//	*ValStatus = validationStatus;
	*ValStatus = exValidationStatus;
	PANTHEIOS_TRACE_DEBUG(PSTR("Status passed to PME: "),pantheios::integer(*ValStatus));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

STDMETHODIMP CUnitOperations::Calculate()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

/**
* \details  Called by PME - returns status of PMC after checking PMC condition. Calling the Validate method is expected to set the unit�s
* status to either CAPE_VALID or CAPE_INVALID, depending on whether the validation tests succeed or fail. Making a change to the unit operation,
* such as setting a parameter value, or connecting a stream to a port is expected to set the unit�s status to CAPE_NOT_VALIDATED.
* \return   Return Vbool status of the unit
* \param[out]	message	Message passed to PME
* \param[out]   isValid   The PMC status.
*				\li CAPE_VALID
*				\li CAPE_INVALID
*				\li CAPE_NOT_VALIDATED
*
* \see
*			\li AspenPlusUserModelsV8_2-Ref.pdf pp. 274
* \todo
*		Finish
*/
STDMETHODIMP CUnitOperations::Validate( BSTR * message, VARIANT_BOOL * isValid )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));

	long count;		// number of ports
	VARIANT id;	// to hold port number
	HRESULT err_code;
	CComPtr<ICapeCollection> ptmpIPortCollection;	// local portcollection interface (addref)
	CComPtr<IDispatch> lpdisp;
	CComPtr<ICapeUnitPort> ptmpICapeUnitPort;				// local IUnitPort interface
	CComBSTR outMessage;	// output message
	// getting number of ports
	try
	{
		err_code = portCollection->QueryInterface(IID_PPV_ARGS(&ptmpIPortCollection));
		PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeCollection addres "),
								pantheios::pointer(ptmpIPortCollection.p,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		if(FAILED(err_code)) 
		{
			// we ar ehere in case if portCollection is ok but requested interface is not supported
			PANTHEIOS_TRACE_ERROR(	PSTR("Instance of ICapeCollection not created because: "), 
									pantheios::integer(err_code,pantheios::fmt::fullHex),
									PSTR(" Error: "), winstl::error_desc_a(err_code));
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}		
		ptmpIPortCollection->Count(&count);	// get number of ports
		// check if all ports connected by calling IUnitPortMethod
		VariantInit(&id); // initializa variant var for ICapePortCollection::Item
		id.vt = VT_I4; // set type to int4
		for(long p=1; p<=count; ++p)	// ports ar enumbered from 1
		{
			id.lVal = p;	// port number
			err_code = ptmpIPortCollection->Item(id,&lpdisp);	// get IDisp interface
			if(FAILED(err_code)) 
			{
				// we ar ehere in case if portCollection is ok but requested interface is not supported
				PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->Item failed because: "), 
										pantheios::integer(err_code,pantheios::fmt::fullHex),
										PSTR(" Error: "), winstl::error_desc_a(err_code));
				PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
				return err_code;
			}		
			err_code = lpdisp->QueryInterface(IID_PPV_ARGS(&ptmpICapeUnitPort));	// get IUnitPort
			PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeUnitPort addres "),
									pantheios::pointer(ptmpICapeUnitPort.p,pantheios::fmt::fullHex),
									PSTR(" Error: "), winstl::error_desc_a(err_code));
			if(FAILED(err_code)) 
			{
				// we ar ehere in case if portCollection is ok but requested interface is not supported
				PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IUnitPort not created because: "), 
										pantheios::integer(err_code,pantheios::fmt::fullHex),
										PSTR(" Error: "), winstl::error_desc_a(err_code));
				PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
				return err_code;
			}	
			lpdisp = NULL;	// clean for next use
			PANTHEIOS_TRACE_DEBUG(	PSTR("Testing port: "),
									pantheios::integer(p),PSTR(" at addres: "),	
									pantheios::pointer(ptmpICapeUnitPort.p,pantheios::fmt::fullHex));
			err_code = ptmpICapeUnitPort->get_connectedObject(&lpdisp);
			if(FAILED(err_code)) 
			{
				// we ar ehere in case if portCollection is ok but requested interface is not supported
				PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->get_connectedObject failed because: "), 
										pantheios::integer(err_code,pantheios::fmt::fullHex),
										PSTR(" Error: "), winstl::error_desc_a(err_code));
				PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
				return err_code;
			}	
			if(NULL==lpdisp)
			{
				exValidationStatus = CAPE_INVALID;
				*isValid = VARIANT_FALSE;	// is not ok
				outMessage = L"Unit is not valid and not ready";
				break;	// one port is not connected, breaking execution
			}
			else
			{
				exValidationStatus = CAPE_VALID;
				*isValid = VARIANT_TRUE;	// is ok
				outMessage = L"Unit is valid and ready";
			}
			lpdisp = NULL; // clean for next use
			
		}
	}
	catch(_com_error e)	// catching com errors encapsulated in _ccom_error class
	{
		// we are here in case of general errors with portCollection pointer and query interface
		PANTHEIOS_TRACE_ERROR(PSTR("QueryInterface exception: "),e.ErrorMessage());
		PANTHEIOS_TRACE_ERROR(PSTR("QueryInterface error code: "),pantheios::integer(e.Error(),pantheios::fmt::fullHex));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return e.Error();	// return HRESULT
	}
	catch(...)	// unsuported exceptions
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected QueryInterface exception"));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return E_FAIL;	// unexpected exception
	}
	*message = outMessage.Copy();	// return message to PME
	PANTHEIOS_TRACE_DEBUG(	PSTR("Unit status: "),
							pantheios::integer(exValidationStatus));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
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

/**
* \details  Returns component name from PMC. Default name is set in CUnitOperations::FinalConstruct()
* \param[out]	name	name of the component returned to PME	
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitOperations::get_ComponentName( BSTR * name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*name = componentName.Copy();
	PANTHEIOS_TRACE_DEBUG(PSTR("Component name passed to PME: "), PW2M(componentName) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Allows to save name of the component given by PME. This name can be later passed to other PMES that use this control. Method is called
* on name change
* \param[in]	name	name of the component passed from PME.
* \return   CapeError
* \retval   status   The program status.
*                     \li S_OK		Success
*/
STDMETHODIMP CUnitOperations::put_ComponentName( BSTR name )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	componentName.Empty();	// clear string
	componentName = name;	// copy string from PME
	PANTHEIOS_TRACE_DEBUG(PSTR("Component name: "), PW2M(componentName) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Returns component desc from PMC. Default desc is set in CUnitOperations::FinalConstruct()
* \param[out]	desc	desc of the component returned to PME	
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*/
STDMETHODIMP CUnitOperations::get_ComponentDescription( BSTR * desc )
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
STDMETHODIMP CUnitOperations::put_ComponentDescription( BSTR desc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	componentDescription.Empty();	// clear string
	componentDescription = desc;	// copy string from PME
	PANTHEIOS_TRACE_DEBUG(PSTR("Component description: "), PW2M(componentDescription) );
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Parameters returns an ICapeCollection interface that provides access to the unit�s list of parameters. Each element accessed 
* through the returned interface must support the ICapeParameter interface.
* Query interface returns error code if requested interface is not supported. In case more general errors, exception _com_error is thrown.
* \param[out]	parameters	pointer to IParameterCollection
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li HRESULT	if exception _com_error caught or QueryInterface not returned S_OK 
*                     \li E_FAIL	if unsuported exception caught
*                     \li S_OK		Success
* \see
*			\li AspenPlusUserModelsV8_2-Ref.pdf pp. 277, 271
*/
STDMETHODIMP CUnitOperations::get_parameters( LPDISPATCH * parameters )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	CComPtr<IParameterCollection> ptmpIarameterCollection(parameterCollection);
	*parameters = ptmpIarameterCollection.Detach();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Initialize allows the unit to initialize itself. It is called once when the unit operation model is instantiated in a particular flowsheet.
*			The Initialize method must not change the current working directory: if it does Aspen Plus will not be able to access its own files and will fail.
*			If the Initialize method needs to display a dialog to allow a user to open a file, it must ensure that the current working directory is restored
*			after a file is selected.
*			This method passes unit validation status to other onterfaces
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
*           \li HRESULT		fail
* \see      AspenPlusUserModelsV8_2-Ref.pdf pp. 286
* \note		Any initialization that could fail must be placed here instead of the constructor.
*/
STDMETHODIMP CUnitOperations::Initialize()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;	// return S_OK
}

/**
* \details  Allows to save simulation context given by PME. Simulation context can be used for calling ASPEN interfaces
* \param[in]	rhs		pointer to Dispatch interface
* \return   CapeError
* \retval   status   The program status.
*           \li S_OK		Success
* \warning Original definitions does not include rhs parameter??  
* \todo use CComPtr here as in CUnitPort::Connect()
*/
STDMETHODIMP CUnitOperations::put_simulationContext( LPDISPATCH rhs)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// remembering pointer to Dispatch interface
	simulationContext = rhs;
	// increasing counter of references
	ULONG count = simulationContext->AddRef();
	PANTHEIOS_TRACE_DEBUG(	PSTR("AddRef IDispatch pointer: "), 
							pantheios::pointer(simulationContext,pantheios::fmt::fullHex),
							PSTR(" count= "),
							pantheios::integer(count));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

STDMETHODIMP CUnitOperations::Edit()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	MessageBox(NULL,"Read script file again?","Warning",MB_OKCANCEL);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
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

/**
* \details  Generally - interface allows a CAPE-OPEN component to generate output messages. Aspen Plus displays these messages in the Control Panel
* or the history file.
* \warning Not implemented here. Only to use on server side. Server provides implementation         
*/
STDMETHODIMP CUnitOperations::PopUpMessage( BSTR message )
{
	return E_NOTIMPL;
}

/**
* \details  Generally - interface allows a CAPE-OPEN component to generate output messages. Aspen Plus displays these messages in the Control Panel
* or the history file.
* \warning Not implemented here. Only to use on server side. Server provides implementation         
*/
STDMETHODIMP CUnitOperations::LogMessage( BSTR message )
{
	return E_NOTIMPL;
}

