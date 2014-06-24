/**
 * \file C_Interpreter.cpp
 * \brief Warper class definition for config4cpp parser
 * \details Implements basic functionality of config4cpp
 * \author PB
 * \date 2014/03/19
 * \see simple-encapsulation example from config4cpp install dir
 */
#include "stdafx.h"
#include "C_Interpreter.h"
#include "..\Common_utilities\scheme.h"

using namespace config4cpp;
using namespace std;

extern string application_scope; //!< Name of the main application scope (FLUENT or COMSOL)

/**
 * \brief Main constructor
 * \details Constructs config4cpp object
 * \param wantDiagnostics - can be true or false 
 * If set true detailed diagnostic will be produced and printed to std during calls to parseSchema() and Validate()
 * \author PB
 * \date 2014/03/19
 * \see simple-encapsulation example from config4cpp install dir
*/
C_Interpreter::C_Interpreter(bool wantDiagnostics) : listSize(0)
{
	_ASSERT(!application_scope.empty());
	names = nullptr;
	m_wantDiagnostics = wantDiagnostics;
	m_cfg = Configuration::create();			// creation of config2cpp object.
	m_validator = new SchemaValidator();
}


/**
 * \brief Destroys the config4cpp object
 * \author PB
 * \date 2014/03/19
*/
C_Interpreter::~C_Interpreter(void)
{
	delete m_validator;
	((Configuration *)m_cfg)->destroy();
	if(listSize>0)
	{
		for(int i=0; i<listSize; ++i)
			delete[] names[i];
		delete[] names;
	}
}

/**
 * \brief Opens and validate configuration file
 * \details Opens and perform SchemeValidation on configuration file. Throw exception on any error.
 * \param[in] cfgInput file name with configuration to open
 * \return nothing
 * \retval void
 * \author PB
 * \date 2014/03/19
 * \exception ConfigurationException - on error in config4cpp
 * \exception std::exception - on other error. Uses predefined exceptions from std: http://stackoverflow.com/questions/688447/best-practices-for-defining-your-own-exception-classes
 * \see simple-encapsulation example from config4cpp install dir
 * \pre external variable \c application_scope must be set before use
*/
void C_Interpreter::OpenAndValidate( const char* cfgInput)
{
//	if(application_scope.empty())
//		throw CException
	Configuration* cfg = (Configuration*)m_cfg;
	SchemaValidator* validator = (SchemaValidator*)m_validator;
	if (strcmp(cfgInput, "") != 0) {
		cfg->parse(cfgInput);				// input config file
		validator->parseSchema(schema);	// schema file
		validator->validate(cfg,application_scope.c_str(),"");
	}
	else
		throw std::invalid_argument("Empty file provided");
	
}

/**
 * \brief Lookups for string parmaeter
 * \details Lookups for string parameter of given option. Need extern variable application_scope set to FLUENT of COMSOL dependign o apllication. This is only main scope
 * other should be given e.g - scope.option.
 * \param[in] name name of the parameter to get value of
 * \return value of named parameter
 * \retval pointer to const char
 * \author PB
 * \date 2014/03/23
 * \exception ConfigurationException - on error in config4cpp
 * \see encapsulate-lookuo-api example from config4cpp install dir
 * \pre external variable \c application_scope must be set before use
*/
const char* C_Interpreter::lookup4String(const char* name)
{
	Configuration* cfg = (Configuration*)m_cfg;
	return cfg->lookupString(application_scope.c_str(), name);
}

/**
 * \brief Lookups for int parmaeter
 * \details Lookups for int parameter of given option. Need extern variable application_scope set to FLUENT of COMSOL dependign o apllication. This is only main scope
 * other should be given e.g - scope.option.
 * \param[in] name name of the parameter to get value of
 * \return value of named parameter
 * \retval integer value
 * \author PB
 * \date 2014/03/23
 * \exception ConfigurationException - on error in config4cpp
 * \see encapsulate-lookuo-api example from config4cpp install dir
 * \pre external variable \c application_scope must be set
*/
int C_Interpreter::lookup4Int(const char* name)
{
	Configuration* cfg = (Configuration*)m_cfg;
	return cfg->lookupInt(application_scope.c_str(), name);
}

/**
 * \brief Lookups for float parmaeter
 * \details Lookups for float parameter of given option. Need extern variable application_scope set to FLUENT of COMSOL dependign o apllication. This is only main scope
 * other should be given e.g - scope.option.
 * \param[in] name name of the parameter to get value of
 * \return value of named parameter
 * \retval floating point value
 * \author PB
 * \date 2014/03/23
 * \exception ConfigurationException - on error in config4cpp
 * \see encapsulate-lookuo-api example from config4cpp install dir
 * \pre external variable \c application_scope must be set before use
*/
float C_Interpreter::lookup4Float(const char* name)
{
	Configuration* cfg = (Configuration*)m_cfg;
	return cfg->lookupFloat(application_scope.c_str(), name);
}

/**
 * \brief Lookups for list of parameters
 * \details Lookups for list of parameters of given name. Need extern variable application_scope set to FLUENT of COMSOL dependign o apllication.
 * This is only main scope other should be given e.g - scope.option.
 * \param[in] name - name of the list (parameter)
 * \param[out] list - list of parameters
 * \param[out] listSize - size of the array of strings returned (number of parmaeters in list)
 * \return array of strings that contains parameters in list
 * \retval \c void
 * \author PB
 * \date 2014/03/24
 * \exception ConfigurationException - on error in config4cpp
 * \exception std::exception in other error
 * \see encapsulate-lookuo-api example from config4cpp install dir
 * \pre external variable \c application_scope must be set before use
*/
void C_Interpreter::lookup4List(const char* name, const char **& list, int& listSize)
{
	Configuration* cfg = (Configuration*)m_cfg;
	cfg->lookupList(application_scope.c_str(), name, list, listSize);
}


/**
 * \brief Looksup for uuid parameters in given scope
 * \details Returns table with uuid list of parameters in given scope. List conatains only names of the parameters and they must be later 
 * decoded by the function (these are list in this case so void C_Interpreter::lookup4List(const char* name, const char **& list, int& listSize)
 * should be used. Examplary output can look as follows:
 * \code
 2>  uid-000000000-EXPORTED_VALUE
 2>  uid-000000001-EXPORTED_VALUE
 \endcode
 * \param[in] name - name of the scope where uid-params are (sub-scope, not main FLUENT)
 * \param[out] list - list of parameters in \c name
 * \param[out] listSize - size of the array of strings returned (number of parmaeters in list)
 * \return array of strings that contains parameters in \c list scope. If listSize is zero list is undefined
 * \retval \c void
 * \author PB
 * \date 2014/03/26
 * \exception ConfigurationException - on error in config4cpp
 * \exception std::exception in other error
 * \pre external variable \c application_scope must be set before use
 * \note This method fills private fields C_Interpreter::listSize and C_Interpreter::names because it converts config4cpp::StringVector to const char**
 * StringVector is local but must exist after end of method.
*/
void C_Interpreter::lookup4uidNames( const char* name, const char **& list, int& listSize )
{
	Configuration* cfg = (Configuration*)m_cfg;
	config4cpp::StringVector uidNames;	
	cfg->listLocallyScopedNames(application_scope.c_str(), name, Configuration::CFG_LIST, false, uidNames);
	this->listSize = listSize = uidNames.length();
	if(listSize>0)
	{
		names = new const char*[uidNames.length()];
		for(int i=0; i<uidNames.length(); ++i)
		{
			names[i] = new char[ strlen(uidNames[i]) + sizeof(char) ];		// extra char for trailing 0 of c-string
			strcpy_s(const_cast<char*>(names[i]), strlen(uidNames[i]) + sizeof(char), uidNames[i]);
		}
		list = names;
	}
}
