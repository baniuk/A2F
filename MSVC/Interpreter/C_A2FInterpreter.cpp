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
 * \exception std::exception in case of othe error
 * \excpetion ConfigurationException - on error in config4cpp
 * \pre external variable \c application_scope must be set
*/
void C_A2FInterpreter::GetSurfaceParams( const std::string& portName, std::string& surf, float& area )
{

}
