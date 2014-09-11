/**
 * \file    Material.cpp
 * \brief   Body of Material class
 * \details Provides tools for handling Cape-Open materials
 * \author  PB
 * \date    2013/12/30
 * \version 0.5
 */
#include "stdafx.h"
#include "Material.h"
#include "..\Common_utilities\PantheiosLogHelper.h"


/**
 * \brief Contructor
 * \details Construct material object basing on ICapeThermoMaterialObject interface. In other case use Material::Create method
 * \param[in] mat pointer to interface
 * \author PB
 * \date 2014/04/18
 * \see Material::Create
*/
Material::Material(ICapeThermoMaterialObject *mat)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	isValidated = INVALIDATED;
	this->mat = mat;
	mat->AddRef();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
 * \brief Helper method
 * \details Should not be used, only for tests.
 * \retval 
 * \author PB
 * \date 2014/02/01
*/
Material::Material( void )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_WARNING(PSTR("Illegal constructor used - only for tests"));
	isValidated = INVALIDATED;
	this->mat = NULL;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
 * \brief Copy constructor
 * \details Makes copy of object together with mat reference. Used in case of passing to methods. Oposite to copyFrom copies also mat reference.
 * \param[in] src - source material
 * \author PB
 * \date 2014/02/01
 * \see Material::copyFrom
*/
Material::Material(const Material& src)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	this->copyFrom(src);	// copy all arrays
	this->mat = src.mat;
	this->mat->AddRef();
	this->isValidated = src.isValidated;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
 * \brief Assigment operator
 * \details Copies rhs object to lhs obiect. Both are the same and references the same mat
 * \param[in] rhs - right side assigment
 * \author PB
 * \date 2014/02/01
 * \note
 * \warning
 * \see Material::copyFrom
 * \see Material::Material(const Material& src)
*/
Material& Material::operator= (const Material& rhs)
{
	if(mat) mat->Release();	// release lhs
	this->copyFrom(rhs);
	if(rhs.mat)
	{
		this->mat = rhs.mat;
		this->mat->AddRef();
	}
	return *this;
}

Material::~Material(void)
{
	if(mat)	mat->Release();
}

/**
* \details Flashes internal structures of Material object by copying properties of 
* Material:mat to relevant CCom classes
* \returns Status of the operation
* \warning Can be used only on input port material
*/
HRESULT Material::inFlashMaterialObject()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
	// get number of components, etc
	hr = get_Composition();
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("inFlashMaterialObject:get_Composition "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}

	hr = get_PhysicalProp();
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("inFlashMaterialObject:get_PhysicalProp "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}

	isValidated = VALIDATED;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
* \details Extract information on stream structure from material:
* \li number of components
* \li names of components
* \li ids of components (stored as UPPER CASE)
* \li phases avaiable in stream
* Fills relevant data in class
* \returns Status of the operation
* \warning Allows wrong phasesId returned from PME
*/
HRESULT Material::get_Composition()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
	// number of components in stream --> copy to numComp
	hr = mat->GetNumComponents(&numComp);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_Composition:GetNumComponents "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	PANTHEIOS_TRACE_DEBUG(PSTR("Number of components in input stram: "), pantheios::integer(numComp));

	// phases --> copy to phases
	VARIANT tmpPhases;
	VariantInit(&tmpPhases);
	hr = mat->get_PhaseIds(&tmpPhases);
	if(FAILED(hr))
	{	
//		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_WARNING(PSTR("get_Composition:get_PhaseIds "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
//		return hr;
	}
	else
	{
		PantheiosHelper::dumpVariant(&tmpPhases, "get_PhaseIds");
		phases.CopyFrom(tmpPhases.parray);
	}
		
	// id of componnets --> copy to compIds
	VARIANT tmpCompIds;
	VariantInit(&tmpCompIds);
	hr = mat->get_ComponentIds(&tmpCompIds);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_Composition:get_ComponentIds "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	PantheiosHelper::dumpVariant(&tmpCompIds, "get_ComponentIds");
	compIds.CopyFrom(tmpCompIds.parray);
	// change all components to uppercase
	CComBSTR tmp;
	for(LONG i = compIds.GetLowerBound(); i<=compIds.GetUpperBound(); ++i)
	{
		tmp = compIds[i];		// convrsion to CComBSTR http://msdn.microsoft.com/en-us/library/xc68523x.aspx
		tmp.ToUpper();			// to upper case
		compIds[i] = tmp.Copy();	// changed case back to the table
		tmp.Empty();
	}
	PantheiosHelper::dumpCComSafeArray(compIds, "get_ComponentIds_upper");
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}
/**
* \details Extract information on stream physical properties:
* \li temeprature
* \li pressure
* \li fraction
* \li Flow
* Fills relevant data in class. It is assumed that every array with data has the size of compIds
* \remarks Assumes extraction for all components of the stream even if there is the same parameter for all
* components. It will be duplicated in array.
* \warning compIds is not initialized - according to doc pp.16
* \returns Status of the operation
* \todo Check sizes of arrays if there are more components. Now there is no duplicating
*/
HRESULT Material::get_PhysicalProp()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
//	CComBSTR myphase;				// assumes overall
//	CComBSTR Mixture;				// assumes mixture
//	CComBSTR myproperty;			// physiscal property to get
	VARIANT outputProperty;			// to hold all variant returns from GetProp
	VARIANT empty;	empty.vt=VT_EMPTY;	// empty variant
	// ask for temperature
	VariantInit(&outputProperty);				// initialization of VARIANT
// 	myproperty = L"Temperature";	// physiscal property to get
// 	myphase = L"overall";			// assumes overall
// 	Mixture = L"Mixture";			// assumes mixture
	hr = mat->GetPropA(CComBSTR(L"temperature"),CComBSTR(L"overall"),empty,NULL,NULL,&outputProperty);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_PhysicalProp:GetTemperature "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	temperatures.CopyFrom(outputProperty.parray);
	// resize temperatures
	double dtmp = temperatures[0];
	temperatures.Resize(numComp,temperatures.GetLowerBound()); 
	for(UINT16 i=0;i<numComp;++i)
		temperatures[i] = dtmp;
	PantheiosHelper::dumpCComSafeArray(temperatures, "Temperatures");

	// ask for pressure
	VariantInit(&outputProperty);	// initialization of VARIANT
	hr = mat->GetPropA(CComBSTR(L"pressure"),CComBSTR(L"overall"),empty,NULL,NULL,&outputProperty);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_PhysicalProp:GetPressure "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	pressures.CopyFrom(outputProperty.parray);
	// resize pressures
	dtmp = pressures[0];
	pressures.Resize(numComp,pressures.GetLowerBound()); 
	for(UINT16 i=0;i<numComp;++i)
		pressures[i] = dtmp;
	PantheiosHelper::dumpCComSafeArray(pressures, "pressures");

	// ask for flow
	VariantInit(&outputProperty);	// initialization of VARIANT
	hr = mat->GetPropA(CComBSTR(L"flow"),CComBSTR(L"overall"),CComVariant(compIds),NULL,CComBSTR(L"mole"),&outputProperty);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_PhysicalProp:GetFlow "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	flows.CopyFrom(outputProperty.parray);
	PantheiosHelper::dumpCComSafeArray(flows, "flows");

	// ask for mole
	VariantInit(&outputProperty);	// initialization of VARIANT
	hr = mat->GetPropA(CComBSTR(L"fraction"),CComBSTR(L"overall"),CComVariant(compIds),NULL,CComBSTR(L"mole"),&outputProperty);
	if(FAILED(hr))
	{	
		isValidated = INVALIDATED;
		PANTHEIOS_TRACE_ERROR(PSTR("get_PhysicalProp:GetFlow "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	fractions.CopyFrom(outputProperty.parray);
	PantheiosHelper::dumpCComSafeArray(fractions, "fractions");

	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Gets catalogue properties of component.
 * \details Return property of selected pure component.
 * \param[in] prop - name of property
 * \param[in] compName - name of the component. It must be in material
 * \param[in] mat - pointer to material
 * \param[out] C - numerical value of property
 * \return HRESULT value
 * \retval S_OK on success
 * \retval E_FAIL on error
 * \author PB
 * \date 2014/02/01
 * \see CO_Thermo.pdf pp. 68
 * \note Can be used before flashing. This is const method.
*/
HRESULT Material::getConstant(ICapeThermoMaterialObject *mat, BSTR prop, BSTR compName, double* C )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	if(NULL==C)
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("NULL pointer"));
		return E_FAIL;
	}
	HRESULT hr;
	VARIANT _outputConstant;
	// tworzenie array
	CComSafeArray<BSTR> proplist(1);
	CComSafeArray<BSTR> compIds(1);
	proplist[0] = prop;
	compIds[0] = compName;
	// pakowanie w variant
	CComVariant _proplist(proplist);
	CComVariant _compIds(compIds);

	VariantInit(&_outputConstant);
	hr = mat->GetComponentConstant(_proplist, _compIds,&_outputConstant);
	if(FAILED(hr))
	{	
		PANTHEIOS_TRACE_ERROR(PSTR("getConstant "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	CComSafeArray<VARIANT> outputConstant(_outputConstant.parray); // doc - zwraca array of variants
	*C = outputConstant.GetAt(0).dblVal;
	PANTHEIOS_TRACE_DEBUG(PSTR("Returned Constant "),pantheios::real(*C),PSTR(" Prop: "), PW2M(CComBSTR(prop)), PSTR(" Comp: "), PW2M(CComBSTR(compName)));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Flashes material object hold by class
 * \details This method copies all properties kept in internal structure of the obiect into mat object that is passed from outside. Used to write data to port
 * \return Result of the operation
 * \retval HRESULT
 * \retval S_OK, E_FAIL
 * \author PB
 * \date 2014/02/01
 * \see inFlashMAterialObject()
 * \warning Can be used only on output port material
*/
HRESULT Material::outFlashMaterialObject()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
	VARIANT empty;	empty.vt=VT_EMPTY;	// empty variant
	CComSafeArray<double> scalar(1);	// output for scalars
	if(isValidated==INVALIDATED)
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Cant copy parameters to material if invalidated"));
		return E_FAIL;
	}
	// temperatures
	scalar.SetAt(0,temperatures.GetAt(0));
	hr = mat->SetPropA(CComBSTR(L"temperature"),CComBSTR(L"overall"),empty,NULL,NULL,CComVariant(scalar));
	if(FAILED(hr))
	{	
		PANTHEIOS_TRACE_ERROR(PSTR("outFlashMaterialObject:SetTemperature "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	// pressures
	scalar.SetAt(0,pressures.GetAt(0));
	hr = mat->SetPropA(CComBSTR(L"pressure"),CComBSTR(L"overall"),empty,NULL,NULL,CComVariant(scalar));
	if(FAILED(hr))
	{	
		PANTHEIOS_TRACE_ERROR(PSTR("outFlashMaterialObject:SetPressure "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	// flow
	hr = mat->SetPropA(CComBSTR(L"flow"),CComBSTR(L"overall"),CComVariant(compIds),NULL,CComBSTR(L"mole"),CComVariant(flows));
	if(FAILED(hr))
	{	
		PANTHEIOS_TRACE_ERROR(PSTR("outFlashMaterialObject:SetFlows "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	// fraction
	hr = mat->SetPropA(CComBSTR(L"fraction"),CComBSTR(L"overall"),CComVariant(compIds),NULL,CComBSTR(L"mole"),CComVariant(fractions));
	if(FAILED(hr))
	{	
		PANTHEIOS_TRACE_ERROR(PSTR("outFlashMaterialObject:SetFractions "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Copy physical properties and structure of material from other material
 * \details Copy physical properties and structure of material from other material. Can be used for duplicating properties to output material.
 * \param[in] src - Source material
 * \return Result of the operation
 * \retval HRESULT
 * \li S_OK
 * \li E_FAIL
 * \author PB
 * \date 2014/02/01
 * \warning Assumes that source material is valid
 * \warning Temporary phases are off
*/
HRESULT Material::copyFrom( const Material& src )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	if(src.isValidated==INVALIDATED)
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Source is not validated"));
		return E_FAIL;
	}
//	phases = src.phases;
	PANTHEIOS_TRACE_WARNING(PSTR("Phases are teporary off"));
	compIds = src.compIds;
	temperatures = src.temperatures;
	pressures = src.pressures;
	flows = src.flows;
	fractions = src.fractions;
	numComp = src.numComp;
	isValidated = VALIDATED;
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));

	return S_OK;
}

/**
 * \brief Creates material object
 * \details Creates material object basing on raw ICapeCollection Interface. It makes all steps required to get final material object. It creates obejct of 
 * Material class
 * \param[in] _portName name of the port to create material from. Must exist in ASPEN and be the same as defined in CPortCollection::FinalConstruct()
 * \param[in] portCollection pointer to ICapeCollection interface
 * \param[out] ob pointer to Material class object
 * \return returns pointer to object of Material class
 * \retval \c HRESULT
 * \author PB
 * \date 2014/04/18
 * \example
 * \code{.cpp}
 err_code = portCollection->QueryInterface(IID_PPV_ARGS(&ptmpICapePortCollection));
 PANTHEIOS_TRACE_DEBUG(	PSTR("ICapeCollection addres "),
 pantheios::pointer(ptmpICapePortCollection.p,pantheios::fmt::fullHex),
 PSTR(" Error: "), winstl::error_desc_a(err_code));
 if(FAILED(err_code)) 
 {
 // we are here in case if portCollection is ok but requested interface is not supported
 SetError(L"Instance of ICapeCollection not created", L"IUnitOperation", L"Calculate", err_code);
 return ECapeUnknownHR;
 }

 // **************** Get input port for collection ***********************************************************************************************
 err_code = Material::Create(CComBSTR(L"REFOR"),ptmpICapePortCollection, inputPort);
 if(FAILED(err_code)) 
 {
 // we are here in case if portCollection is ok but requested interface is not supported
 SetError(L"Material::Create failed", L"IUnitOperation", L"Calculate", err_code);
 return ECapeUnknownHR;
 }
 \endcode
*/
HRESULT Material::Create( BSTR _portName, CComPtr<ICapeCollection> portCollection, Material* &ob )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT err_code;
	VARIANT id;	// to hold port number
	LPDISPATCH rawlpDisp;
	CComPtr<ICapeUnitPort> ptmpInputPort;				// local IUnitPort interface
	CComPtr<ICapeThermoMaterialObject> ptmpInputPortMaterial;

	// **************** Get input port for collection ***********************************************************************************************
	VariantInit(&id); // initialize variant var for ICapePortCollection::Item
	CComBSTR portName(_portName);
	id.vt = VT_BSTR; // set type to BSTR
	id.bstrVal = portName;	// port name
	err_code = portCollection->Item(id,&rawlpDisp);	// get IDispatch interface for requesting ICapeUnitPort
	if(FAILED(err_code)) 
	{
		// we ar ehere in case if portCollection is ok but requested interface is not supported
		rawlpDisp->Release();
		return ECapeUnknownHR;
	}	
	err_code = rawlpDisp->QueryInterface(IID_PPV_ARGS(&ptmpInputPort));	// get IUnitPort
	PANTHEIOS_TRACE_DEBUG(	PSTR("Input port addres "),
		pantheios::pointer(ptmpInputPort.p,pantheios::fmt::fullHex),
		PSTR(" Error: "), winstl::error_desc_a(err_code));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		rawlpDisp->Release();
		return ECapeUnknownHR;
	}	
	rawlpDisp->Release();	// release teporary IDispatch pointer
	
	// ************** Get material from input port ***************************************************************************************************
	err_code = ptmpInputPort->get_connectedObject(&rawlpDisp);
	PANTHEIOS_TRACE_DEBUG(	PSTR("Object connected to port: "), 
		pantheios::pointer(rawlpDisp,pantheios::fmt::fullHex));
	if(FAILED(err_code)) 
	{
		rawlpDisp->Release();
		return ECapeUnknownHR;
	}	
	err_code = rawlpDisp->QueryInterface(IID_PPV_ARGS(&ptmpInputPortMaterial));
	PANTHEIOS_TRACE_DEBUG(	PSTR("Input port material addres "),
		pantheios::pointer(ptmpInputPortMaterial.p,pantheios::fmt::fullHex),
		PSTR(" Error: "), winstl::error_desc_a(err_code));
	if(FAILED(err_code)) 
	{
		// we are here in case if portCollection is ok but requested interface is not supported
		rawlpDisp->Release();
		return ECapeUnknownHR;
	}	
	rawlpDisp->Release();	// release teporary IDispatch pointer
	// setting input material
	ob = new Material(ptmpInputPortMaterial);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Returns pointer to material object (ICapeThermoMaterialObject)
 * \details Returns pointer of material warped by this class. Can be used to call other methods from ICapeThermoMaterialObject interface.
 * Use if Material created by MAterial::Create method.
 * \return pointer kept in object
 * \retval \c ICapeThermoMaterialObject*
 * \author PB
 * \note This methods makes AddRef. Caller must Release
 * \date 2014/04/18
 * \see Material::Create
*/
ICapeThermoMaterialObject* Material::get_MaterialRef( void )
{
	mat->AddRef();
	return mat;
}


/**
 * \brief Returns molar weight of whole material
 * \details Sums all molar wieghts of all components in material. Takes into account only components with nonzero fraction. By default \c compIds contains all components defined
 * in stream
 * \param[out] m molar weight
 * \return Error code
 * \retval \c HRESULT
 * \author PB
 * \date 2014/07/20
 * \warning Matrial must be flased
*/
HRESULT Material::getMolarWeight( double &m )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	double C;
	m = 0.0;
	HRESULT hr;
	for(LONG i = compIds.GetLowerBound(); i <= compIds.GetUpperBound(); ++i) // po wszystkich komponentach
	{
		hr = Material::getConstant(this->mat, L"molecularWeight", compIds[i], &C);
		if(FAILED(hr))
		{
			PANTHEIOS_TRACE_ERROR(PSTR("getMolarWeight "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
			return hr;
		}
		if(fractions[i]!=0)
			m += C;
	}
	PANTHEIOS_TRACE_DEBUG(PSTR("Molar weight: "),pantheios::real(m));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Sets \c propertyName of value \c val to component name \c compName
 * \details In facts it modifies internal tables of material properties \c temperatures, \c pressures, \c flows, \c fractions 
 * \param[in] compName name of the component the same as in Aspen
 * \param[in] propertyName name of the property to change 
 * \param[in] val value to set
 * \return Error code in case of problem (if compName does not exists)
 * \retval \c HRESULT
 * \author PB
 * \note \c compName is not case sensitive
 * \date 2014/09/09
 * \see Common_definitions.hpp
*/
HRESULT Material::setProp( std::string compName, PropertyName propertyName, double val )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	LONG i, indexOfComp = -1;
	CComBSTR bcompName(compName.c_str());	// create BSTR from string
	bcompName.ToUpper();					// change to upper case
	// find index of component
	for(i = compIds.GetLowerBound(); i <= compIds.GetUpperBound(); ++i)
		if(compIds[i] == bcompName)	// compIds is in UPPER (HRESULT Material::get_Composition())
			indexOfComp = i;
	if(indexOfComp<0)	// not found
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Component of name: "),compName,PSTR(" not found"));
		return E_FAIL;
	}
	// indexOfComp keeps index of given component in data tables \c temperatures, \c pressures, \c flows, \c fractions

	// modify selected property
	switch(propertyName)
	{
	case PropertyName::Temperature:
		PANTHEIOS_TRACE_DEBUG(PSTR("Setting temperature of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") to "),
			pantheios::real(val));
		temperatures[indexOfComp] = val;
		break;
	case PropertyName::Pressure:
		PANTHEIOS_TRACE_DEBUG(PSTR("Setting pressure of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") to "),
			pantheios::real(val));
		pressures[indexOfComp] = val;
		break;
	case PropertyName::Fraction:
		PANTHEIOS_TRACE_DEBUG(PSTR("Setting fraction of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") to "),
			pantheios::real(val));
		fractions[indexOfComp] = val;
		break;
	case PropertyName::Flow:
		PANTHEIOS_TRACE_DEBUG(PSTR("Setting flow of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") to "),
			pantheios::real(val));
		flows[indexOfComp] = val;
		break;
	default:
		PANTHEIOS_TRACE_ERROR(PSTR("Wrong property name"));
		return E_FAIL;
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Gets \c propertyName of value \c val to component name \c compName
 * \details In facts it reads internal tables of material properties \c temperatures, \c pressures, \c flows, \c fractions 
 * \param[in] compName name of the component the same as in Aspen
 * \param[in] propertyName name of the property to change 
 * \param[out] val value to read
 * \return Error code in case of problem (if compName does not exists)
 * \retval \c HRESULT
 * \author PB
 * \note \c compName is not case sensitive
 * \date 2014/09/09
 * \see Common_definitions.hpp
*/
HRESULT Material::getProp( std::string compName, PropertyName propertyName, double& val )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	LONG i, indexOfComp = -1;
	CComBSTR bcompName(compName.c_str());	// create BSTR from string
	bcompName.ToUpper();					// change to upper case
	// find index of component
	for(i = compIds.GetLowerBound(); i <= compIds.GetUpperBound(); ++i)
		if(compIds[i] == bcompName) // compIds is in UPPER (HRESULT Material::get_Composition())
			indexOfComp = i;
	if(indexOfComp<0)	// not found
	{
		PANTHEIOS_TRACE_ERROR(PSTR("Component of name: "),compName,PSTR(" not found"));
		return E_FAIL;
	}
	// indexOfComp keeps index of given component in data tables \c temperatures, \c pressures, \c flows, \c fractions

	// modify selected property
	switch(propertyName)
	{
	case PropertyName::Temperature:
		val = temperatures[indexOfComp];
		PANTHEIOS_TRACE_DEBUG(PSTR("Reading temperature of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") as "),
			pantheios::real(val));
		break;
	case PropertyName::Pressure:
		val = pressures[indexOfComp];
		PANTHEIOS_TRACE_DEBUG(PSTR("Reading pressure of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") as "),
			pantheios::real(val));
		break;
	case PropertyName::Fraction:
		val = fractions[indexOfComp];
		PANTHEIOS_TRACE_DEBUG(PSTR("Reading fraction of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") as "),
			pantheios::real(val));
		break;
	case PropertyName::Flow:
		val = flows[indexOfComp];
		PANTHEIOS_TRACE_DEBUG(PSTR("Reading flow of component no "),pantheios::integer(indexOfComp),PSTR(" ("),compName,PSTR(") as "),
			pantheios::real(val));
		break;
	default:
		PANTHEIOS_TRACE_ERROR(PSTR("Wrong property name"));
		return E_FAIL;
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Gets list of components associated with material object
 * \details Wraper giving access to internal table \c compIds. Returns always in uppercase
 * \param[out] compList table with names of components
 * \return error code \c S_OK or \c E_FAIL
 * \retval \c HRESULT
 * \author PB
 * \date 2014/09/09
 * \warning Returns all components in stream also those with 0 flow
*/
HRESULT Material::getCompList( std::vector<std::string>& compList )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	LONG i;	// index of elements in internal compIds 
	std::wstring tmp;	// for conversion BSTR->string purposes
	compList.clear();	// remove all elements from vector
	PANTHEIOS_TRACE_DEBUG("Bounds of compIds: [", pantheios::integer(compIds.GetLowerBound()),PSTR(" "), pantheios::integer(compIds.GetUpperBound()),PSTR("]"));
	for(i = compIds.GetLowerBound(); i <= compIds.GetUpperBound(); ++i)
	{
		tmp.clear();
		tmp = compIds[i];	// conversion for wstring
		compList.push_back(ws2s(tmp));
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Converst between wstring and strin
 * \param[in] wstr \c wstring to convert
 * \return Converted string
 * \retval \c std::string
 * \author PB
 * \date 2014/09/09
 * \todo Move those method to common tools
 * 
 * \see http://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
*/
std::string Material::ws2s(const std::wstring& wstr)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	typedef std::codecvt_utf8<wchar_t> convert_typeX;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return converterX.to_bytes(wstr);
}

/**
 * \brief Gets mass flow of selected component [g/s]
 * \details Calculates mass flow of given component of stream \c compName using its molar flow provided by Aspen and its molar weight [g/s]
 * \param[in] compName Aspen name of the component of stream 
 * \param[out] flow Mass flow of component in [g/s]
 * \return error code \c S_OK, \c E_FAIL
 * \retval \c HRESULT
 * \author PB
 * \date 2014/09/10
*/
HRESULT Material::getMassFlow( std::string compName, double& flow)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	double flux, C;
	HRESULT hr;
	hr = getProp(compName,PropertyName::Flow,flux);	// gets flow of component [mol/s]
	if(FAILED(hr))
	{
		PANTHEIOS_TRACE_ERROR(PSTR("getMassFlow: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	hr = Material::getConstant(this->mat, L"molecularWeight", CComBSTR(compName.c_str()), &C);	// molar weight of component
	if(FAILED(hr))
	{
		PANTHEIOS_TRACE_ERROR(PSTR("getMassFlow: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	flow = flux * C;
	PANTHEIOS_TRACE_DEBUG(PSTR("Mass flow of "), compName, PSTR(" is "), pantheios::real(flow));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}

/**
 * \brief Gets total mass flow of all components [g/s]
 * \details Calculates mass flow of all components of stream \c compName using its molar flow provided by Aspen and its molar weight [g/s]
 * \param[out] totalFlux Mass flow of component in [g/s]
 * \return error code \c S_OK, \c E_FAIL
 * \retval \c HRESULT
 * \author PB
 * \date 2014/09/10
*/
HRESULT Material::getTotalMassFlow( double& totalFlux )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HRESULT hr;
	std::vector<std::string> components;
	double tmp;
	totalFlux = 0;
	hr = getCompList(components);	// get list of all components in string format
	if(FAILED(hr))
	{
		PANTHEIOS_TRACE_ERROR(PSTR("getTotalMassFlow: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
		return hr;
	}
	for(const auto &c : components)
	{
		if(FAILED(hr = getMassFlow(c, tmp)))
		{
			PANTHEIOS_TRACE_ERROR(PSTR("getTotalMassFlow: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
			return hr;
		}
		totalFlux+=tmp;
	}
	PANTHEIOS_TRACE_DEBUG(PSTR("Total mass flow is "), pantheios::real(totalFlux));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return S_OK;
}
