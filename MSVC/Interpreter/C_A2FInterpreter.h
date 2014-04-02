/**
 * \file C_A2FInterpreter.h
 * \brief Holds A2F specific config functions
 * \author PB
 * \date 2014/03/25
 */
#ifndef C_A2FInterpreter_h__
#define C_A2FInterpreter_h__

#include "c_interpreter.h"
#include <string>
#include <sstream>

/// Enum class for Surfaces
enum class SurfParams
{
	SurfName,		///< Name of the surface
	SurfArea		///< Area of the surface
};

/// Enum for Exports
enum class ExportParams
{
	ExpFunction,	///< Name of the export function
	ExpAspenParam,	///< Name of the Aspen stram parameter
	ExpComponent	///< Name of the chemical component
};

/// Enum for Assigns
enum class AssignParams
{
	AssComponent,	///< Name of the chemical component
	AssPMCInput,	///< Input of the PMC
	AssSurfName		///< Name of the surface
	
};

/**
 * \class C_A2FInterpreter
 * \brief Hold specific methods for A2F
 * \details Allows to as for specific parameters in lists. Can interpret particular fileds inlists. 
 * This class is strictly connected with script format. Class holds methods for acces to lists of parameters.
 * Assumes that we know format of the list and know which parameter is where.
 * \author PB
 * \date 2014/03/25
 * \see Script definition for A2F
 * \pre external variable \c application_scope must be set before use
 * \pre Config script must be validated using OpenAndValidate(const char* cfgInput);
 * \todo add description of script params in \c Getxxx functions
*/
class C_A2FInterpreter :
	public C_Interpreter
{
public:
	C_A2FInterpreter(bool wantDiagnostics = false);
	~C_A2FInterpreter(void);
	/// Gets params connected with surface of given name
	void GetSurfaceParams(const std::string& portName, std::string& surf, float& area);
	/// Gets EXPORTS from params
	void GetExportsParams(std::vector<std::string>& fluentFcn, std::vector<std::string>& aspenProp, std::vector<std::string>& compName);
	/// Gets ASSIGNS form params
	void GetAssignsParams(std::vector<std::string>& compName, std::vector<int>& noInput, std::vector<std::string>& surfName);
private:
	/// converts string to number
	template <typename T>
	T str2int(const char* str);
};
#endif // C_A2FInterpreter_h__

