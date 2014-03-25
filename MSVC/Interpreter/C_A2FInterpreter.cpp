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
 * \excpetion ConfigurationException - on error in config4cpp
 * \pre external variable \c application_scope must be set
 * \see http://stackoverflow.com/questions/1012571/stdstring-to-float-or-double
*/
void C_A2FInterpreter::GetSurfaceParams( const std::string& portName, std::string& surf, float& area )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	const char** list;
	int	listSize;
	lookup4List(portName.c_str(),list,listSize);
	// assign list entries to output
	surf = list[static_cast<UINT>(SurfParams::SurfName)];
	std::stringstream numberAsString(list[static_cast<UINT>(SurfParams::SurfArea)]);				// number given as string = list[1];
	numberAsString >> area;
	if(numberAsString.fail())
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("String not converted to number"));	// should never hit here because of earlier syntax checking
		throw std::runtime_error("C_A2FInterpreter::GetSurfaceParams:String not converted to number");
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));

}
