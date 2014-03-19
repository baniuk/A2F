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

using namespace config4cpp;

/**
 * \brief Main constructor
 * \details Constructs config4cpp object
 * \param wantDiagnostics - can be true or false 
 * If set true detailed diagnostic will be produced and printed to std during calls to parseSchema() and Validate()
 * \author PB
 * \date 2014/03/19
 * \see simple-encapsulation example from config4cpp install dir
*/
C_Interpreter::C_Interpreter(bool wantDiagnostics)
{
	m_wantDiagnostics = wantDiagnostics;
	m_cfg = Configuration::create();			// creation of config2cpp object.
}


/**
 * \brief Destroyes the config4cpp object
 * \author PB
 * \date 2014/03/19
*/
C_Interpreter::~C_Interpreter(void)
{
	((Configuration *)m_cfg)->destroy();
}

/**
 * \brief Opens and validate configuration file
 * \details Opens and perform SchemeValidation on configuration file. Throw exception on any error.
 * \param cfgInput file name wit configuration to open
 * \param cfgScope
 * \return nothing
 * \retval void
 * \author PB
 * \date 2014/03/19
 * \exception ConfigurationException
 * \see simple-encapsulation example from config4cpp install dir
*/
void C_Interpreter::OpenAndValidate( const char* cfgInput, const char* cfgScope )
{
	Configuration* cfg = (Configuration*)m_cfg;
	if (strcmp(cfgInput, "") != 0) {
		cfg->parse(cfgInput);
	}
	
}
