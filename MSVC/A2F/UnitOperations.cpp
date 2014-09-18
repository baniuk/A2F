/**
* \file    UnitOperations.cpp
* \brief   COClass for unit operations
* \details Implements basic interfaces required by CAPE-OPEN. Contains also initialization of Pantheios API.
* \author  PB
* \date    2013/09/10
* \version 0.5
* \todo Implement error handling by ECapeUser
*/

#include "stdafx.h"
#include "UnitOperations.h"
#include "..\Common_utilities\PantheiosLogHelper.h"

// Definition of external variables
// CUnitOperations
CapeValidationStatus exValidationStatus = CAPE_NOT_VALIDATED;
/// set global context for script
std::string application_scope = "FLUENT";
/// set global and default name of script
std::string script_name = "A2F.cfg";

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
* \c installDir contains config script file. jou file and outputs from Fluent will be in directory given in script \b DATA_PATH
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

	// looking for working dir in registry
	if (ERROR_SUCCESS!=C_RegistrySupport::GetStringforKey(HKEY_CURRENT_USER,_T("Software\\A2F"),_T("InstallDir"),installDir))
	{
		// key not found, exiting
		PANTHEIOS_TRACE_ERROR(PSTR("Key not found, exiting"));
		MessageBox(NULL,"Registry key not found. Install A2F again","ERROR",MB_OK);
		SetError(L"Registry key not found. Install A2F again",L"ICapeUnitOperation",L"FinalConstruct");
		return ECapeUnknownHR;
	}
	// createjournal here with error checking and exception handling
	try
	{
		C_FluentStarter::CreateJournal( installDir+script_name );
	}
	catch (std::exception& ex)
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Cant create journal file, check if script is correct "), PSTR("Error returned: "), ex.what());
		std::string str(ex.what());	// convert char* to wchar required by SetError
		std::wstring wstr = C_A2FInterpreter::s2ws(str);
		SetError(wstr.c_str(), L"IUnitOperation", L"FinalConstruct", err_code);
		MessageBox(NULL,"Journal can not be created. Check script","ERROR",MB_OK);
		return ECapeUnknownHR;
	}

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

	if(simulationContext!=NULL)
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
* \details Calculate the unit operation. This is the function that performs the actual model calculation. It copies materials from ports to provate member of
* CUnitOperations::Materials. This member keeps objects of Material class that is initialized from materials from streams. This class is helper to materials.
* \return   Return status of the unit
* \li S_OK on Success
* \li ECapeUnknownHR
* \see AddError
* \warning It clears always CUnitOperations::Materials member on leave or on error.
*/
STDMETHODIMP CUnitOperations::Calculate()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;
	CComPtr<ICapeCollection> ptmpICapePortCollection;	// local portcollection interface (addref)
	Materials.resize(PORTS_NUMBER);
	try
	{
		// ******************* Call ICapeCollection ******************************************************************************************************
		err_code = portCollection->QueryInterface(IID_PPV_ARGS(&ptmpICapePortCollection));
		PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeCollection addres "),
			pantheios::pointer(ptmpICapePortCollection.p,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		if(FAILED(err_code))
			throw std::runtime_error("Instance of ICapeCollection not created");

		// **************** Get input port for collection ***********************************************************************************************
		err_code = Material::Create(CComBSTR(L"REFOR"),ptmpICapePortCollection, Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]);
		if(FAILED(err_code))
			throw std::runtime_error("Material::Create failed");

		// **************** Get output port for collection ***********************************************************************************************
		err_code = Material::Create(CComBSTR(L"ANODOFF"), ptmpICapePortCollection, Materials[static_cast< std::size_t >(StreamNumber::outputPort_ANODOFF)]);
		if(FAILED(err_code))
			throw std::runtime_error("Material::Create failed");

		// **************** Get input port for collection ***********************************************************************************************
		err_code = Material::Create(CComBSTR(L"P1"), ptmpICapePortCollection, Materials[static_cast< std::size_t >(StreamNumber::inputPort_P1)]);
		if(FAILED(err_code))
			throw std::runtime_error("Material::Create failed");

		// **************** Get output port for collection ***********************************************************************************************
		err_code = Material::Create(CComBSTR(L"EXHAUST"), ptmpICapePortCollection, Materials[static_cast< std::size_t >(StreamNumber::outputPort_EXHAUST)]);
		if(FAILED(err_code))
			throw std::runtime_error("Material::Create failed");

		// ************* Filling structures ********************************************************************************************************
		PANTHEIOS_TRACE_DEBUG(	PSTR("Flashing MAterial obiect for REFOR"));
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]->inFlashMaterialObject(); // fill internal structure of inputPort
		PANTHEIOS_TRACE_DEBUG(	PSTR("Flashing MAterial obiect for P1"));
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_P1)]->inFlashMaterialObject();
		if(FAILED(err_code))
			throw std::runtime_error("Error returned from inFlashMaterialObject");
		// ---- tests ---------------------------------------
		/** \test GetConstant live test
		* \code{.cpp}
		* double C;
		* Material::Create(CComBSTR(L"P1"), ptmpICapePortCollection, Materials[static_cast< std::size_t >(StreamNumber::inputPort_P1)]); // must be created
		* Material.inFlashMaterialObject(); // must be flashed
		* Material.getMolarWeight(C);
		* \endcode
		*/
		// testing purposes only
		double C;
		err_code = Materials[static_cast<std::size_t>(StreamNumber::inputPort_REFOR)]->getMolarWeight(C);
		// ---- end tests ---------------------------------------

		// other staff here, createScm and start Fluent and read results
		CreateScm();	// can throw exception on error which should be handled here

		err_code = Materials[static_cast< std::size_t >(StreamNumber::outputPort_ANODOFF)]->copyFrom(*Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]);	// copy physical propertios from input
		if(FAILED(err_code))
			throw std::runtime_error("Error returned from copyFrom input to output");
		err_code = Materials[static_cast< std::size_t >(StreamNumber::outputPort_EXHAUST)]->copyFrom(*Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]);	// copy physical propertios from input
		if(FAILED(err_code))
			throw std::runtime_error("Error returned from copyFrom input to output");

		err_code = Materials[static_cast< std::size_t >(StreamNumber::outputPort_ANODOFF)]->outFlashMaterialObject();	// fashing outputs
		if(FAILED(err_code))
			throw std::runtime_error("Error returned from outFlashMaterialObject");
		err_code = Materials[static_cast< std::size_t >(StreamNumber::outputPort_EXHAUST)]->outFlashMaterialObject();	// fashing outputs
		if(FAILED(err_code))
			throw std::runtime_error("Error returned from outFlashMaterialObject");

		// flash the outlet material (all outlet ports must be flashed by a CAPE-OPEN unit operation)
		VARIANT props;
		VariantInit(&props);

		CComBSTR tp = "TP";
		ICapeThermoMaterialObject* ptmpOutputPortMaterial;
		ptmpOutputPortMaterial = Materials[static_cast< std::size_t >(StreamNumber::outputPort_ANODOFF)]->get_MaterialRef(); // local copy of pointer kept by Material class
		err_code = ptmpOutputPortMaterial->CalcEquilibrium(tp,props);
		ptmpOutputPortMaterial->Release();	// must release here
		if(FAILED(err_code))
			throw std::runtime_error("Error returned from CalcEquilibrium");

		ptmpOutputPortMaterial = Materials[static_cast< std::size_t >(StreamNumber::outputPort_EXHAUST)]->get_MaterialRef(); // local copy of pointer kept by Material class
		err_code = ptmpOutputPortMaterial->CalcEquilibrium(tp,props);
		ptmpOutputPortMaterial->Release();	// must release here
		if(FAILED(err_code))
			throw std::runtime_error("Error returned from CalcEquilibrium");
	}
	catch(std::ios_base::failure& ex)	// on file opening error in createScm. No transfering exceptions
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Cant open scm file, check if DATA_PATH is correct in cfg file "), PSTR("Error returned: "), ex.what());
		std::string str(ex.what());	// convert char* to wchar required by SetError
		std::wstring wstr = C_A2FInterpreter::s2ws(str);
		SetError(wstr.c_str(), L"IUnitOperation", L"Calculate", err_code);
		for(Material *mat : Materials)
			SAFE_DELETE(mat);
		Materials.clear();
		return ECapeUnknownHR;
	}
	catch(std::exception& ex)
	{
		PANTHEIOS_TRACE_ERROR(	PSTR("Exception caught in Calculate: "), ex.what() );
		std::string str(ex.what());	// convert char* to wchar required by SetError
		std::wstring wstr = C_A2FInterpreter::s2ws(str);
		SetError(wstr.c_str(), L"IUnitOperation", L"Calculate", err_code);
		for(Material *mat : Materials)
			SAFE_DELETE(mat);
		Materials.clear();
		return ECapeUnknownHR;
	}
	// normal quit
	for(Material *mat : Materials)
		SAFE_DELETE(mat);
	Materials.clear();
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
	LPDISPATCH rawlpDisp;
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
		err_code = ptmpIPortCollection->Item(id,&rawlpDisp);	// get IDispatch interface for requesting ICapeUnitPort
		// (Item Added reference)
		if(FAILED(err_code))
		{
			// we ar ehere in case if portCollection is ok but requested interface is not supported
			PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->Item failed because: "),
				pantheios::integer(err_code,pantheios::fmt::fullHex),
				PSTR(" Error: "), winstl::error_desc_a(err_code));
			rawlpDisp->Release();
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}
		err_code = rawlpDisp->QueryInterface(IID_PPV_ARGS(&ptmpICapeUnitPort));	// get ICapeUnitPort
		PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeUnitPort addres "),
			pantheios::pointer(ptmpICapeUnitPort.p,pantheios::fmt::fullHex),
			PSTR(" Error: "), winstl::error_desc_a(err_code));
		if(FAILED(err_code))
		{
			// we are here in case if portCollection is ok but requested interface is not supported
			PANTHEIOS_TRACE_ERROR(	PSTR("Instance of ICapeUnitPort not created because: "),
				pantheios::integer(err_code,pantheios::fmt::fullHex),
				PSTR(" Error: "), winstl::error_desc_a(err_code));
			rawlpDisp->Release();
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}
		// release ICapeUnitPort
		rawlpDisp->Release();	// clean for next use - having ICapeUnitPort we ask for object connected to it
		PANTHEIOS_TRACE_DEBUG(	PSTR("Testing port: "),
			pantheios::integer(p),PSTR(" at addres: "),
			pantheios::pointer(ptmpICapeUnitPort.p,pantheios::fmt::fullHex));

		err_code = ptmpICapeUnitPort->get_connectedObject(&rawlpDisp);
		if(FAILED(err_code))
		{
			// we ar ehere in case if portCollection is ok but requested interface is not supported
			PANTHEIOS_TRACE_ERROR(	PSTR("ptmpIPortCollection->get_connectedObject failed because: "),
				PSTR(" Error: "), winstl::error_desc_a(err_code));
			rawlpDisp->Release();	// clean
			PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
			return err_code;
		}
		if(NULL==rawlpDisp)
		{
			PANTHEIOS_TRACE_WARNING(PSTR("Object conected to port: "),
				pantheios::integer(p), PSTR("is not present: "),
				pantheios::pointer(rawlpDisp,pantheios::fmt::fullHex));
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
		rawlpDisp->Release();	// Release because get_connectedObject makes addref
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
	*name = errDesc.Copy();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

STDMETHODIMP CUnitOperations::get_code( long * code )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*code = 0;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

STDMETHODIMP CUnitOperations::get_description( BSTR * description )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*description = errDesc.Copy();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

STDMETHODIMP CUnitOperations::get_scope( BSTR * scope )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*scope = errScope.Copy();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

STDMETHODIMP CUnitOperations::get_interfaceName( BSTR * interfaceName )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	*interfaceName = errInterface.Copy();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
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
	MessageBox(NULL,"Nothing to see here","Warning",MB_OKCANCEL);
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

/**
* \brief Sets error description
* \details Fills relevant data with description of the error. These data are used then when caller asks for ECapeRoot interface. Gets also HRESULT
* error code that can be returned by other function because there is logging here.
* \param[in] desc - description of the error
* \param[in] itface - name of the interface
* \param[in] scope - scope of the error
* \param[in] err_code - result of the function that returned error
* \return nothing
* \author PB
* \date 2014/02/11
* \remarks
* Use in the following way
* \code
err_code = inputPort.inFlashMaterialObject(); // fill internal structure of inputPort
if(FAILED(err_code))
{
SetError(L"Error returned from inFlashMaterialObject", L"IUnitOperation", L"Calculate", err_code);
return ECapeUnknownHR;
}
* \endcode
*/
void CUnitOperations::SetError( const WCHAR* desc, const WCHAR* itface, const WCHAR* scope, HRESULT err_code)
{
	PANTHEIOS_TRACE_ERROR(	PSTR("Error code returned by caller "), pantheios::integer(err_code,pantheios::fmt::fullHex),
		PSTR(" Error: "), winstl::error_desc_a(err_code));
	SetError(desc, itface, scope);
}

/**
* \brief Sets error description
* \details Fills relevant data with description of the error. These data are used then when caller asks for ECapeRoot interface
* \param[in] desc - description of the error
* \param[in] itface - name of the interface
* \param[in] scope - scope of the error
* \return nothing
* \author PB
* \date 2014/02/11
* \remarks
* Use in the following way
* \code
* SetError(L"The name of this object is read-only",L"ICapeIdentification",L"put_ComponentName");
* \endcode
*/
void CUnitOperations::SetError( const WCHAR* desc, const WCHAR* itface, const WCHAR* scope)
{
	PANTHEIOS_TRACE_ERROR(pantheios::w2m(desc),PSTR(" "),pantheios::w2m(itface),PSTR(" "), pantheios::w2m(scope));
	errDesc = desc;
	errInterface = itface;
	errScope = scope;
}

/**
* \brief Creates SCM file for Fluent.
* \details The SCM file contains all required calls of Fluent API.
* \param
* \return Nothing
* \retval void
* \li S_OK on success
* \li other HRESULT error on fail
* \author PB
* \date 2014/03/16
* \warning The last function must be exit.
* \exception Throw exception from C_A2FInterpreter class and std::ios_base::failure on file fail open or errors in Material class.
* \see http://82.145.77.86:8080/trac/A2F/wiki/Schematy#StartFluenta
* \see http://www.cplusplus.com/reference/ios/ios/exceptions/
* \see http://www.cplusplus.com/reference/ios/ios/setstate/
* \see http://msdn.microsoft.com/query/dev11.query?appId=Dev11IDEF1&l=EN-US&k=k(string%2Fstd%3A%3Agetline);k(std%3A%3Agetline);k(getline);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
* \see Examplary log of MAterial
* \code{.unparsed}
* [A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (101): Material::inFlashMaterialObject: Entering
* |	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (137): Material::get_Composition: Entering
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (147): Material::get_Composition: Number of components in input stram: 8
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (21): PantheiosHelper::dumpVariant: Entering
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (25): PantheiosHelper::dumpVariant: VARIANT name: get_PhaseIds
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (36): PantheiosHelper::dumpVariant: VARIANT type: 0x2008 VT_ARRAY | VT_BSTR
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[0]: Vapor
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[1]: Liquid
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (48): PantheiosHelper::dumpVariant: Leaving
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (21): PantheiosHelper::dumpVariant: Entering
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (25): PantheiosHelper::dumpVariant: VARIANT name: get_ComponentIds
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (36): PantheiosHelper::dumpVariant: VARIANT type: 0x2008 VT_ARRAY | VT_BSTR
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[0]: METHANE
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[1]: HYDROGEN
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[2]: WATER
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[3]: CO
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[4]: CO2
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[5]: O2
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[6]: PROPANE
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (39): PantheiosHelper::dumpVariant: 	VARIANT data[7]: N2
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (48): PantheiosHelper::dumpVariant: Leaving
* |	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (177): Material::get_Composition: Leaving
* |	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (195): Material::get_PhysicalProp: Entering
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (58): PantheiosHelper::dumpCComSafeArray: Entering
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[0]: 973.15
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[1]: 973.15
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[2]: 973.15
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[3]: 973.15
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[4]: 973.15
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[5]: 973.15
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[6]: 973.15
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[7]: 973.15
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (62): PantheiosHelper::dumpCComSafeArray: Leaving
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (58): PantheiosHelper::dumpCComSafeArray: Entering
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[0]: 101325
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[1]: 101325
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[2]: 101325
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[3]: 101325
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[4]: 101325
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[5]: 101325
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[6]: 101325
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[7]: 101325
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (62): PantheiosHelper::dumpCComSafeArray: Leaving
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (58): PantheiosHelper::dumpCComSafeArray: Entering
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[0]: 0
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[1]: 0.0023765
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[2]: 4.61319e-005
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[3]: 0.00177054
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[4]: 4.61319e-005
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[5]: 0
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[6]: 0
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[7]: 0.00359314
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (62): PantheiosHelper::dumpCComSafeArray: Leaving
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (58): PantheiosHelper::dumpCComSafeArray: Entering
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[0]: 0
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[1]: 0.303417
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[2]: 0.00588986
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[3]: 0.226052
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[4]: 0.00588986
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[5]: 0
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[6]: 0
* |	|	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Debug]: (61): PantheiosHelper::dumpCComSafeArray: 	CComSafeArray data[7]: 0.458751
* |	|	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (62): PantheiosHelper::dumpCComSafeArray: Leaving
* |	|	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (263): Material::get_PhysicalProp: Leaving
* |	[A2F.1142340, 7/21/2014 1:28:16.189 PM; Informational]: (121): Material::inFlashMaterialObject: Leaving
* \endcode
*/
void CUnitOperations::CreateScm( void )
{
	// use Materials
	// use working dir installDir
	//
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;
	std::unique_ptr<C_A2FInterpreter> cfg(new C_A2FInterpreter()); // smart pointer in case of exception
	std::string cfg_file = installDir + script_name;			// path to cfg file
	std::ofstream starter;	// scm file handle
	try
	{
		cfg->A2FOpenAndValidate( cfg_file.c_str() );	// validate config script in install dir

		std::string workingDir(cfg->A2Flookup4String("DATA_PATH")); // gets path for working dir from script
		std::string scm_file = workingDir + _T("starter.scm");		// define name of scm and path in working dir
		// initialize scm file
		PANTHEIOS_TRACE_DEBUG(PSTR("Creating scm: "), scm_file);
		starter.exceptions(starter.failbit|starter.badbit|starter.eofbit);	// will throw exceptions on all errors
		starter.open(scm_file.c_str(),std::ios::out| std::ios::trunc); // can throw exception here

		// define place to keep EXPORT params: surf_name, fluent_function)name, component name
		std::vector<string> surface;	// name of the surface for parameters to export from (Fluent)
		std::vector<string> variable;	// name of exported variable (Fluent)
		// temprary variables for properties
		double T, X, F;
		std::vector<std::string> compList;	// list of components in material
		// read EXPORT params
		cfg->A2FGetExportsParams(surface, variable);

		// creating scm file
		starter << ";; File generated automatically" << endl;
		starter << ";; Load main project file - full path must be provided" << endl;
		starter << ";; possible problem - file name must be without spaces and always with full patch, use / switch for directories" << endl;
		starter << ";; delete previous" << endl;
		// delete all output files (assiged to surfaces - we iterate along surfaces)
		for (const auto &surf : surface )
			starter << "(ti-menu-load-string \"!del " << cfg->lookup4String("DATA_PATH") << "_name_" << surf << ".prof \")" << endl;
		starter <<	";; load project" << endl;
		starter << "(ti-menu-load-string \"file/read-case-data " << cfg->lookup4String("DATA_PATH") << cfg->lookup4String("CASE_NAME") << "\")" << endl;
		starter << ";; Setting inputs" << endl;
		// ---------------------------------- REFOR ------------------------------------------------------
		// prepare for setting Fluent input REFOR - collecting required params from REFOR stream from ASPEN
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]->getCompList(compList);	// list of all components
		if(FAILED(err_code))
			throw std::runtime_error("CUnitOperations::CreateScm found error in Material::getCompList call");
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]->getProp(compList[0], PropertyName::Temperature, T); // temperature of first component (all shoud be the same)
		if(FAILED(err_code))
			throw std::runtime_error("CUnitOperations::CreateScm found error in Material::getProp call");
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]->getTotalMassFlow(F);	// get total mass flow
		if(FAILED(err_code))
			throw std::runtime_error("CUnitOperations::CreateScm found error in Material::getTotalMassFlow call");
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_REFOR)]->getProp("HYDROGEN", PropertyName::Fraction, X); // fraction of H2
		if(FAILED(err_code))
			throw std::runtime_error("CUnitOperations::CreateScm found error in Material::getProp call");
		// setting correct surface in FLuent
		starter << "(ti-menu-load-string \""			// opening quota "
			"define/boundary-conditions/ " <<			// command
			cfg->lookup4String("BOUND_COND") <<			// type of boundary
			" anode-inlet"								// surface
			" yes"
			" yes"
			" no " <<
			F <<										// total mass flux (5)
			" no " <<
			T <<										// temperature (7)
			" no"
			" 0"
			" no"
			" yes"
			" no"
			" no " <<
			0 <<										// mass fraction of h20 (14)
			" no " <<
			0 <<										// mass fraction of o2 (16)
			" no " <<
			X <<										// mass fraction of h2 (18)
			" yes"
			" no"
			" 0"
			"\")" << endl;
		// ---------------------------------- 1 ------------------------------------------------------
		// prepare for setting Fluent input REFOR - collecting required params from REFOR stream from ASPEN
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_P1)]->getProp(compList[0], PropertyName::Temperature, T); // temperature of first component (all shoud be the same)
		if(FAILED(err_code))
			throw std::runtime_error("CUnitOperations::CreateScm found error in Material::getProp call");
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_P1)]->getTotalMassFlow(F);	// get total mass flow
		if(FAILED(err_code))
			throw std::runtime_error("CUnitOperations::CreateScm found error in Material::getTotalMassFlow call");
		err_code = Materials[static_cast< std::size_t >(StreamNumber::inputPort_P1)]->getProp("O2", PropertyName::Fraction, X); // fraction of H2
		if(FAILED(err_code))
			throw std::runtime_error("CUnitOperations::CreateScm found error in Material::getProp call");
		// setting correct surface in FLuent
		starter << "(ti-menu-load-string \""			// opening quota "
			"define/boundary-conditions/ " <<			// command
			cfg->lookup4String("BOUND_COND") <<			// type of boundary
			" cathode-inlet"								// surface
			" yes"
			" yes"
			" no " <<
			F <<										// total mass flux (5)
			" no " <<
			T <<										// temperature (7)
			" no"
			" 0"
			" no"
			" yes"
			" no"
			" no " <<
			0 <<										// mass fraction of h20 (14)
			" no " <<
			X <<										// mass fraction of o2 (16)
			" no " <<
			0 <<										// mass fraction of h2 (18)
			" yes"
			" no"
			" 0"
			"\")" << endl;

		starter << ";; --------------------------------------------------------------" << endl;
		starter << "(ti-menu-load-string \"solve/iterate " << cfg->lookup4Int("NUMOFITER") << "\")" << endl;
		starter << ";; --------------------------------------------------------------" << endl;
		starter << ";; setting outputs" << endl;

		for( std::size_t i = 0; i < surface.size(); i++)
			starter << "(ti-menu-load-string \"file/write-profile " << cfg->lookup4String("DATA_PATH") << "_name_" << surface[i] << ".prof " << surface[i] << "," << variable[i] << "\")" << endl;

		starter << ";; --------------------------------------------------------------" << endl;
		starter << "(ti-menu-load-string \"/\")" << endl;
		starter << "(ti-menu-load-string \"exit yes\")" << endl;
	}
	catch(std::ios_base::failure& ex)	// on file opening error in createScm. No transfering exceptions
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Cant create scm file. "), PSTR("Error returned: "), ex.what());
		throw;	// rethrowing
	}
	catch(std::exception& ex)
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Cant create scm file. "), PSTR("Error returned: "), ex.what());
		starter.close();
		throw; // rethrowing
	}
	catch(...)
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("Unexpected exception"));
		starter.close();
		throw;
	}

	starter.close();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}