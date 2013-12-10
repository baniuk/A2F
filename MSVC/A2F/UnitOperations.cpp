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
* \remark According to https://groups.google.com/forum/#!topic/microsoft.public.win32.programmer.ole/d1Gg2_0F4pU the COM functions 
* do not throw exceptions 
*/
HRESULT CUnitOperations::FinalConstruct()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;	// cede returned by COM functions used below
	// set name and description of the PMC
	componentName = L"A2F";
	componentDescription = L"FLUENT CAPE-OPEN unit operation implemented in CPP";

	// create instance of CoClass for ICapePortCollection
	err_code = portCollection.CoCreateInstance(__uuidof(PortCollection));
	if(FAILED(err_code))	// error
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of PortCollection not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	PANTHEIOS_TRACE_DEBUG(	PSTR("Instance of PortCollection created on IPortCollection addres: "), 
							pantheios::pointer(portCollection.p,pantheios::fmt::fullHex));
	
	// create instance of CoClass for ICapeParameterCollection
	err_code = parameterCollection.CoCreateInstance(__uuidof(ParameterCollection));
	if(FAILED(err_code))	// error
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IParameterCollection not created because: "), 
			pantheios::integer(err_code,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	PANTHEIOS_TRACE_DEBUG(	PSTR("Instance of IParameterCollection created on IParameterCollection addres: "), 
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
	PANTHEIOS_TRACE_DEBUG(	PSTR("Release IDispatch (simulationContext) pointer: "), 
		pantheios::pointer(simulationContext,pantheios::fmt::fullHex));
	PANTHEIOS_TRACE_DEBUG(	PSTR("Release IpotCollection (portCollection) pointer: "), 
		pantheios::pointer(portCollection,pantheios::fmt::fullHex));
	PANTHEIOS_TRACE_DEBUG(	PSTR("Release IParameterCollection (parameterCollection) pointer: "), 
		pantheios::pointer(parameterCollection,pantheios::fmt::fullHex));

	simulationContext.Release(); // returns currnet object reference count, we AddRef makes assignment on put_simlationcontext
	portCollection.Release(); // release pointer - make sure that all instances will be closed
	parameterCollection.Release();
}

/**
* \details  Ports returns an ICapeCollection interface that provides access to the unit’s list of ports. Each element accessed through
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
	if(!ports) { PANTHEIOS_TRACE_CRITICAL(PSTR("Wrong pointer!")); return E_POINTER;}
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
	if(!ValStatus) { PANTHEIOS_TRACE_CRITICAL(PSTR("Wrong pointer!")); return E_POINTER;}
	*ValStatus = exValidationStatus;
	PANTHEIOS_TRACE_DEBUG(PSTR("Status passed to PME: "),pantheios::integer(*ValStatus));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \details Calculate the unit operation. This is the function that performs the actual model calculation.
 * \return   Return status of the unit
 * \li S_OK on Success
 * \sa Calculate()
 */
STDMETHODIMP CUnitOperations::Calculate()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;
	VARIANT id;	// to hold port number
	LPDISPATCH lpDisp;
	CComPtr<ICapeCollection> ptmpIPortCollection;	// local portcollection interface (addref)
	CComPtr<IDispatch> lpdisp;
	CComPtr<ICapeUnitPort> ptmpInputPort;				// local IUnitPort interface
	CComPtr<ICapeUnitPort> ptmpOutputPort;				// local IUnitPort interface
	CComPtr<ICapeThermoMaterialObject> ptmpInputPortMaterial;
	CComPtr<ICapeThermoMaterialObject> ptmpOutputPortMaterial;

	// ******************* Call ICapeCollection ******************************************************************************************************
	err_code = portCollection->QueryInterface(IID_PPV_ARGS(&ptmpIPortCollection));
	PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeCollection addres "),
							pantheios::pointer(ptmpIPortCollection.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of ICapeCollection not created because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}
	// **************** Get input port for collection ***********************************************************************************************
	lpdisp.Release();	// release teporary IDispatch pointer
	VariantInit(&id); // initialize variant var for ICapePortCollection::Item
	id.vt = VT_I4; // set type to int4
	id.lVal = 1;	// port number
	err_code = ptmpIPortCollection->Item(id,&lpDisp);	// get IDispatch interface for requesting ICapeUnitPort
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->Item failed because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	
	lpdisp.Attach(lpDisp);	// taking ownership over IUnitPort returned by CPortCollection::Item( VARIANT id, LPDISPATCH * Item )
	err_code = lpdisp->QueryInterface(IID_PPV_ARGS(&ptmpInputPort));	// get IUnitPort
	PANTHEIOS_TRACE_DEBUG(	PSTR("Input port addres "),
							pantheios::pointer(ptmpInputPort.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of Input Port not created because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	

	// **************** Get output port for collection ***********************************************************************************************
	lpdisp.Release();	// release teporary IDispatch pointer
	VariantInit(&id); // initialize variant var for ICapePortCollection::Item
	id.vt = VT_I4; // set type to int4
	id.lVal = 2;	// port number
	err_code = ptmpIPortCollection->Item(id,&lpDisp);	// get IDispatch interface for requesting ICapeUnitPort
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->Item failed because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	
	lpdisp.Attach(lpDisp);	// taking ownership over IUnitPort returned by CPortCollection::Item( VARIANT id, LPDISPATCH * Item )
	err_code = lpdisp->QueryInterface(IID_PPV_ARGS(&ptmpOutputPort));	// get IUnitPort
	PANTHEIOS_TRACE_DEBUG(	PSTR("Output port addres "),
							pantheios::pointer(ptmpOutputPort.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of Output Port not created because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	
	// ************** Get material from port 2 *******************************************************************************************************
	lpdisp.Release();	// release teporary IDispatch pointer
	err_code = ptmpOutputPort->get_connectedObject(&lpDisp);
	PANTHEIOS_TRACE_ERROR(	PSTR("Object connected to port: "), 
							pantheios::pointer(lpDisp,pantheios::fmt::fullHex));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("get_connectedObject returned: "),	PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	
	lpdisp.Attach(lpDisp);
	err_code = lpdisp->QueryInterface(IID_PPV_ARGS(&ptmpOutputPortMaterial));
	PANTHEIOS_TRACE_DEBUG(	PSTR("Output port material addres "),
							pantheios::pointer(ptmpOutputPortMaterial.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of output port material not created because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	
	// ************** Get material from port 1 *******************************************************************************************************
	lpdisp.Release();	// release teporary IDispatch pointer
	err_code = ptmpOutputPort->get_connectedObject(&lpDisp);
	PANTHEIOS_TRACE_ERROR(	PSTR("Object connected to port: "), 
							pantheios::pointer(lpDisp,pantheios::fmt::fullHex));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("get_connectedObject returned: "),	PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	
	lpdisp.Attach(lpDisp);
	err_code = lpdisp->QueryInterface(IID_PPV_ARGS(&ptmpOutputPortMaterial));
	PANTHEIOS_TRACE_DEBUG(	PSTR("Output port material addres "),
							pantheios::pointer(ptmpOutputPortMaterial.p,pantheios::fmt::fullHex),
							PSTR(" Error: "), winstl::error_desc_a(err_code));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		PANTHEIOS_TRACE_ERROR(	PSTR("Instance of output port material not created because: "), 
								pantheios::integer(err_code,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		lpdisp.Release();
		PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
		return err_code;
	}	


	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details  Called by PME - returns status of PMC after checking PMC condition. Calling the Validate method is expected to set the unit’s
* status to either CAPE_VALID or CAPE_INVALID, depending on whether the validation tests succeed or fail. Making a change to the unit operation,
* such as setting a parameter value, or connecting a stream to a port is expected to set the unit’s status to CAPE_NOT_VALIDATED.
* This function performs the following operations:
*	\li query ICapeCollection from IPortCollection represented by private var CUnitOperations::portCollection (addRef)
*	\li calls CPortCollection::Count method from ICapeCollection
*	\li calls CPortCollection::Item method from ICapeCollection (n-times returned by CPortCollection::Count)
*	\li for every Item query for ICapeUnitPort and then it calls CUnitPort::get_connectedObject
*	\li returned object is provided from PME. If it is NULL then port is not connected
* \return   Return Vbool status of the unit
* \param[out]	message	Message passed to PME
* \param[out]   isValid   The PMC status.
*				\li CAPE_VALID
*				\li CAPE_INVALID
*				\li CAPE_NOT_VALIDATED
*
* \see
*			\li AspenPlusUserModelsV8_2-Ref.pdf pp. 274
* \remarks According to https://groups.google.com/forum/#!topic/microsoft.public.win32.programmer.ole/d1Gg2_0F4pU the COM functions 
* do not throw exceptions 		
* \todo Compare with example code and add missing features
* \todo to signal to the simulation environment that the unit is ready or not ready to be calculated, with a textual message describing the problem 
* in case the unit is not ready
*/
STDMETHODIMP CUnitOperations::Validate( BSTR * message, VARIANT_BOOL * isValid )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));

	long count;		// number of ports
	VARIANT id;	// to hold port number
	HRESULT err_code;
	CComPtr<ICapeCollection> ptmpIPortCollection;	// local portcollection interface (addref)
	LPDISPATCH lpDisp;
	CComPtr<IDispatch> lpdisp;
	CComPtr<ICapeUnitPort> ptmpICapeUnitPort;				// local IUnitPort interface
	CComBSTR outMessage;	// output message

	if(!message) { PANTHEIOS_TRACE_CRITICAL(PSTR("Wrong pointer!")); return E_POINTER;}
	if(!isValid) { PANTHEIOS_TRACE_CRITICAL(PSTR("Wrong pointer!")); return E_POINTER;}

	outMessage = L"Unit is not valid and not ready"; // by default unit is invalidated
	// getting number of ports
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
		err_code = ptmpIPortCollection->Item(id,&lpDisp);	// get IDispatch interface for requesting ICapeUnitPort
		lpdisp.Attach(lpDisp);	// taking ownership over IUnitPort returned by CPortCollection::Item( VARIANT id, LPDISPATCH * Item )
		// (Item Added reference)
		if(FAILED(err_code)) 
		{
			// we ar ehere in case if portCollection is ok but requested interface is not supported
			PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->Item failed because: "), 
									pantheios::integer(err_code,pantheios::fmt::fullHex),
									PSTR(" Error: "), winstl::error_desc_a(err_code));
			lpdisp.Release();
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}		
		err_code = lpdisp->QueryInterface(IID_PPV_ARGS(&ptmpICapeUnitPort));	// get IUnitPort
		PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeUnitPort addres "),
								pantheios::pointer(ptmpICapeUnitPort.p,pantheios::fmt::fullHex),
								PSTR(" Error: "), winstl::error_desc_a(err_code));
		if(FAILED(err_code)) 
		{
			// we are here in case if portCollection is ok but requested interface is not supported
			PANTHEIOS_TRACE_ERROR(	PSTR("Instance of IUnitPort not created because: "), 
									pantheios::integer(err_code,pantheios::fmt::fullHex),
									PSTR(" Error: "), winstl::error_desc_a(err_code));
			lpdisp.Release();
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}	
		// release ICapeUnitPort
		lpdisp.Release();	// clean for next use - having ICapeUnitPort we ask for object connected to it
		PANTHEIOS_TRACE_DEBUG(	PSTR("Testing port: "),
								pantheios::integer(p),PSTR(" at addres: "),	
								pantheios::pointer(ptmpICapeUnitPort.p,pantheios::fmt::fullHex));
		
		err_code = ptmpICapeUnitPort->get_connectedObject(&lpDisp);
		if(FAILED(err_code)) 
		{
			// we ar ehere in case if portCollection is ok but requested interface is not supported
			PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->get_connectedObject failed because: "), 
									PSTR(" Error: "), winstl::error_desc_a(err_code));
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}	
		if(NULL==lpDisp)
		{
			PANTHEIOS_TRACE_WARNING(PSTR("Object conected to port is not present: "),
									pantheios::pointer(lpDisp,pantheios::fmt::fullHex));
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
		ptmpICapeUnitPort.Release();	// clean for nex use in loop
		
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
	if(!name) { PANTHEIOS_TRACE_CRITICAL(PSTR("Wrong pointer!")); return E_POINTER;}
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
	if(!desc) { PANTHEIOS_TRACE_CRITICAL(PSTR("Wrong pointer!")); return E_POINTER;}
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
* \details  Parameters returns an ICapeCollection interface that provides access to the unit’s list of parameters. Each element accessed 
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
	if(!parameters) { PANTHEIOS_TRACE_CRITICAL(PSTR("Wrong pointer!")); return E_POINTER;}
	CComPtr<IParameterCollection> ptmpIarameterCollection(parameterCollection);
	*parameters = ptmpIarameterCollection.Detach();
	PANTHEIOS_TRACE_DEBUG(	PSTR("IParameterCollection returned to PME addres: "), 
							pantheios::pointer(*parameters,pantheios::fmt::fullHex));
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
*/
STDMETHODIMP CUnitOperations::put_simulationContext( LPDISPATCH rhs)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	// remembering pointer to Dispatch interface
	/// \todo rather attach here (control kept on PME side??) PME counts references, we releases?? Probablu PME release ownership to PMC
	simulationContext.Release();	// release old simulation context
	simulationContext = rhs;
	PANTHEIOS_TRACE_DEBUG(	PSTR("AddRef IDispatch pointer: "), 
							pantheios::pointer(simulationContext.p,pantheios::fmt::fullHex));
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

