/**
* \file C_A2FInterpreter.cpp
* \brief Implements class specific for A2F
* \details Class holds methods for acces to lists of parameters.
* \author PB
* \date 2014/03/25
*/
#include "stdafx.h"
#include "C_A2FInterpreter.h"

/**
* \brief Main constructor
* \details Constructs config4cpp object
* \param wantDiagnostics - can be true or false
* If set true detailed diagnostic will be produced and printed to std during calls to parseSchema() and Validate()
* \author PB
* \date 2014/03/19
* \see simple-encapsulation example from config4cpp install dir
*/
C_A2FInterpreter::C_A2FInterpreter(bool wantDiagnostics) : C_Interpreter(wantDiagnostics)
{
}

C_A2FInterpreter::~C_A2FInterpreter(void)
{
}

/**
* \brief Gets parameters connected with surface definition
* \details Return several params connected with surfaces. PArams are specified for A2F project.
* Encapsulates also const char* to string as general output.
* \param[in] portName - name of the port allowed by script, eg \c INPUT1, \c INPUT2, etc
* \param[out] surf - name of the surcae in Fluent connected with specified port
* \param[out] area - area of the surface inFluent
* \return Returns area and name of the surface in fluent read from the script.
* \retval \c void
* \author PB
* \date 2014/03/25
* \exception std::runtime_error in case of other error
* \exception std::invalid_argument - on error in config4cpp
* \pre external variable \c application_scope must be set
* \see http://stackoverflow.com/questions/1012571/stdstring-to-float-or-double
* \deprecated Assumes that surfaces are normal lists
*/
void C_A2FInterpreter::A2FGetSurfaceParams( const std::string& portName, std::string& surf, float& area )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	const char** list;
	int	listSize;
	try
	{
		lookup4List(portName.c_str(),list,listSize);
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FGetSurfaceParams caught exception"));
		throw std::invalid_argument(ex.c_str());
	}
	// assign list entries to output
	surf = list[static_cast<UINT>(SurfParams::SurfName)];
	area = str2int<float>(list[static_cast<UINT>(SurfParams::SurfArea)]); // number given as string = list[1];
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
* \brief Gets parameters connected with SURFACE field
* \details Return several params connected with surfaces. Params are specified for A2F project.
* Encapsulates also const char* to string as general output.
* \param[out] SurfName - name of the surcae in Fluent connected with specified port
* \param[out] SurfArea - area of the surface inFluent
* \return Returns area and name of the surface in fluent read from the script.
* \retval \c void
* \author PB
* \date 2014/03/25
* \exception std::runtime_error in case of other error
* \exception std::invalid_argument - on error in config4cpp
* \pre external variable \c application_scope must be set
* \see http://stackoverflow.com/questions/1012571/stdstring-to-float-or-double
*/
void C_A2FInterpreter::A2FGetSurfaceParams( std::vector<std::string>& SurfName, std::vector<float>& SurfArea)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	const char** list;	// list of EXPORTS names (uid)
	const char** paramList; // list of parameters in one uid
	int	listSize, unused;
	const std::string localScopeName = "SURFACES";	// local name of the scope where parmas are
	std::string listNamewithScope;		// name of the list but with local scope
	try
	{
		lookup4uidNames(localScopeName.c_str(), list, listSize);
		if(listSize==0)
		{
			PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FGetSurfaceParams got empty list from lookup4uidNames - no SURFACES?"));
			throw std::invalid_argument("C_A2FInterpreter::A2FGetSurfaceParams got empty list from lookup4uidNames - no SURFACES?");
		}
		// SURFACES fields are now listed in list. Iterate among them and copy data to output
		PANTHEIOS_TRACE_DEBUG(PSTR("List contains "), pantheios::integer(listSize), PSTR(" entries"));
		for (int i=0; i<listSize; ++i)
		{
			listNamewithScope = localScopeName + ".";	// add local scope to every list name
			listNamewithScope += list[i];
			PANTHEIOS_TRACE_DEBUG(PSTR("Looking for list: "), listNamewithScope);
			lookup4List(listNamewithScope.c_str(), paramList, unused);
			SurfName.push_back(paramList[static_cast<UINT>(SurfParams::SurfName)]); // add first param from list to output
			SurfArea.push_back(str2int<float>(paramList[static_cast<UINT>(SurfParams::SurfArea)]));
		}
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FGetSurfaceParams caught exception"));
		throw std::invalid_argument(ex.c_str());
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
* \brief Gets paramteres associated with EXPORT field
* \details Gets paramteres associated with EXPORT field. Those are:
* \li name of the Fluent function
* \li name of the physical property in Aspen
* \li name of the component defined in Aspen
* Method returns vectors of strings. Certain index must be applied to all of them, e.g. index 0 means all three properties given in one EXPORT.
* \param[out] surface - vector of names of Fluent surfaces to read variables from them for certain components
* \param[out] variable - vector of names of Fluent report variables
* \param[out] reportType - vector of report types (\see reports in Fluent)
* \return Properties of defined exports from Fluent. Connects name of the component with physical property of this component and Fluent
* \retval \c void
* \author PB
* \date 2014/04/02
* \see Schema.cfg
* \see A2F.cfg
* \exception std::invalid_argument - on error in config4cpp
* \exception std::runtime_error in case of other error
* \note Suitable only for EXPORT scope because of predefined variables inside. If structure of cfg changed, this function must change too.
*/
void C_A2FInterpreter::A2FGetExportsParams(std::vector<std::string>& reportType, std::vector<std::string>& surface, std::vector<std::string>& variable )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	const char** list;	// list of EXPORTS names (uid)
	const char** paramList; // list of parameters in one uid
	int	listSize, unused;
	const std::string localScopeName = "EXPORTS";	// local name of the scope where parmas are
	std::string listNamewithScope;		// name of the list but with local scope
	try
	{
		lookup4uidNames(localScopeName.c_str(), list, listSize);
		if(listSize==0)
		{
			PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FGetExportsParams got empty list from lookup4uidNames - no EXPORT?"));
			throw std::invalid_argument("C_A2FInterpreter::A2FGetExportsParams got empty list from lookup4uidNames - no EXPORT?");
		}
		// EXPORT fields are now listed in list. Iterate among them and copy data to output
		PANTHEIOS_TRACE_DEBUG(PSTR("List contains "), pantheios::integer(listSize), PSTR(" entries"));
		for (int i=0; i<listSize; ++i)
		{
			listNamewithScope = localScopeName + ".";	// add local scope to every list name
			listNamewithScope += list[i];
			PANTHEIOS_TRACE_DEBUG(PSTR("Looking for list: "), listNamewithScope);
			lookup4List(listNamewithScope.c_str(), paramList, unused);
			surface.push_back(paramList[static_cast<UINT>(ExportParams::ExpSurface)]); // add first param from list to output
			variable.push_back(paramList[static_cast<UINT>(ExportParams::ExpVariable)]);
			reportType.push_back(paramList[static_cast<UINT>(ExportParams::ExpReportType)]);
		}
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FGetExportsParams caught exception"));
		throw std::invalid_argument(ex.c_str());
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
* \brief Gets paramteres associated with ASSIGN field
* \details Gets lists of ASSIGNS and extract three parameters
* \param[out] compName - vector of names of Aspen Components
* \param[out] PMC_stream_name - numbers of inputs of PMC
* \param[out] surfName - names of the Fluent Surfaces
* \return Properties of defined assigns.
* \retval \c void
* \author PB
* \date 2014/04/02
* \see Schema.cfg
* \see A2F.cfg
* \exception std::invalid_argument - on error in config4cpp
* \exception std::runtime_error in case of other error
* \note Suitable only for EXPORT scope because of predefined variables inside. If structure of cfg changed, this function must change too.
*/
void C_A2FInterpreter::A2FGetAssignsParams( std::vector<std::string>& compName, std::vector<std::string>& PMC_stream_name, std::vector<std::string>& surfName )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	const char** list;	// list of ASSIGN names (uid)
	const char** paramList; // list of parameters in one uid
	int	listSize, unused;
	const std::string localScopeName = "ASSIGNS";	// local name of the scope where parmas are
	std::string listNamewithScope;		// name of the list but with local scope
	try
	{
		lookup4uidNames(localScopeName.c_str(), list, listSize);
		if(listSize==0)
		{
			PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FGetAssignsParams got empty list from lookup4uidNames - no ASSIGN scope?"));
			throw std::invalid_argument("C_A2FInterpreter::A2FGetAssignsParams got empty list from lookup4uidNames - no ASSIGN scope?");
		}
		// ASSIGN fields are now listed in list. Iterate among them and copy data to output
		PANTHEIOS_TRACE_DEBUG(PSTR("List contains "), pantheios::integer(listSize), PSTR(" entries"));
		for (int i=0; i<listSize; ++i)
		{
			listNamewithScope = localScopeName + ".";	// add local scope to every list name
			listNamewithScope += list[i];
			PANTHEIOS_TRACE_DEBUG(PSTR("Looking for list: "), listNamewithScope);
			lookup4List(listNamewithScope.c_str(), paramList, unused);
			compName.push_back(paramList[static_cast<UINT>(AssignParams::AssComponent)]); // add first param from list to output
			PMC_stream_name.push_back(paramList[static_cast<UINT>(AssignParams::AssPMCInput)]);
			surfName.push_back(paramList[static_cast<UINT>(AssignParams::AssSurfName)]);
		}
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FGetAssignsParams caught exception"));
		throw std::invalid_argument(ex.c_str());
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
* \brief Converts string to integer or float
* \details Converts string to integer. Can throw exceptions in case of fail
* \param[in] str - string to convert
* \return Converted integer value
* \retval \c int
* \author PB
* \date 2014/04/02
* \exception std::invalid_argument on conversion fail
*/
template <typename T>
T C_A2FInterpreter::str2int( const char* str )
{
	T converted;
	std::stringstream numberAsString(str);
	numberAsString >> converted;
	if(numberAsString.fail())
	{
		PANTHEIOS_TRACE_ERROR(PSTR("String not converted to number"));	// should never hit here because of earlier syntax checking
		throw std::runtime_error("C_A2FInterpreter::str2int:String not converted to number");
	}
	return converted;
}

/**
* \copydoc C_Interpreter::OpenAndValidate
* \note This method encapsulate original one and converts exceptions to std::exception. Adds also Pantheios logging
*/
void C_A2FInterpreter::A2FOpenAndValidate( const char* cfgInput )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	try
	{
		OpenAndValidate(cfgInput);
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2FOpenAndValidate caught exception "),ex.c_str());
		throw std::invalid_argument(ex.c_str());
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
* \copydoc C_Interpreter::lookup4String
* \note This method encapsulate original one and converts exceptions to std::exception. Adds also Pantheios logging
*/
const char* C_A2FInterpreter::A2Flookup4String( const char* name )
{
	try
	{
		return lookup4String(name);
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2Flookup4String caught exception " ),ex.c_str());
		throw std::invalid_argument(ex.c_str());
	}
}

/**
* \copydoc C_Interpreter::lookup4Int
* \note This method encapsulate original one and converts exceptions to std::exception. Adds also Pantheios logging
*/
int C_A2FInterpreter::A2Flookup4Int( const char* name )
{
	try
	{
		return lookup4Int(name);
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2Flookup4Int caught exception "),ex.c_str());
		throw std::invalid_argument(ex.c_str());
	}
}

/**
* \copydoc C_Interpreter::lookup4Float
* \note This method encapsulate original one and converts exceptions to std::exception. Adds also Pantheios logging
*/
float C_A2FInterpreter::A2Flookup4Float( const char* name )
{
	try
	{
		return lookup4Float(name);
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2Flookup4Float caught exception "),ex.c_str());
		throw std::invalid_argument(ex.c_str());
	}
}

/**
* \copydoc C_Interpreter::lookup4List
* \note This method encapsulate original one and converts exceptions to std::exception. Adds also Pantheios logging
*/
void C_A2FInterpreter::A2Flookup4List( const char* name, const char **& list, int& listSize )
{
	try
	{
		lookup4List(name, list, listSize);
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2Flookup4List caught exception "),ex.c_str());
		throw std::invalid_argument(ex.c_str());
	}
}

/**
* \copydoc C_Interpreter::lookup4uidNames
* \note This method encapsulate original one and converts exceptions to std::exception. Adds also Pantheios logging
*/
void C_A2FInterpreter::A2Flookup4uidNames( const char* name, const char **& list, int& listSize )
{
	try
	{
		lookup4uidNames(name, list, listSize);
	}
	catch(config4cpp::ConfigurationException& ex) // convert to std::exception
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_A2FInterpreter::A2Flookup4uidNames caught exception "),ex.c_str());
		throw std::invalid_argument(ex.c_str());
	}
}

/**
* \details Converst strings to wstrings. This is static method because most returns from this class is ASCII strings
* \param[in] s - string to convert
* \return Converted string
* \retval \c std::wstring
* \author PB
* \date 2014/04/08
* \todo Move thos method to common tools
*
* \see http://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
*/
std::wstring C_A2FInterpreter::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}