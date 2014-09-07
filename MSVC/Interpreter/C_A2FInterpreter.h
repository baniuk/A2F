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
	ExpSurface,		///< Name of the exported surface
	ExpVariable,	///< Name of the Fluent variable to export
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
* Assumes that we know format of the list and know which parameter is where. Throws only std exceptions and convert config4cpp exceptions to std
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
	void A2FGetSurfaceParams(const std::string& portName, std::string& surf, float& area);
	/// Overload member of A2FGetSurfaceParams
	void A2FGetSurfaceParams( std::vector<std::string>& SurfName, std::vector<float>& SurfArea);
	/// Gets EXPORTS from params
	void A2FGetExportsParams(std::vector<std::string>& surface, std::vector<std::string>& variable, std::vector<std::string>& compName);
	/// Gets ASSIGNS form params
	void A2FGetAssignsParams(std::vector<std::string>& compName, std::vector<std::string>& PMC_stream_name, std::vector<std::string>& surfName);
	/// Warper of C_Interpreter::OpenAndValidate
	void A2FOpenAndValidate(const char* cfgInput);
	/// Warper of C_Interpreter::lookup4String
	const char* A2Flookup4String(const char* name);
	/// Warper of C_Interpreter::lookup4Int
	int A2Flookup4Int(const char* name);
	/// Warper of C_Interpreter::lookup4Float
	float A2Flookup4Float(const char* name);
	/// Warper of C_Interpreter::lookup4List
	void A2Flookup4List(const char* name, const char **& list, int& listSize);
	/// Warper of C_Interpreter::lookup4uidNames
	void A2Flookup4uidNames(const char* name, const char **& list, int& listSize);
	/// Conversion between strings and wstrings
	static std::wstring s2ws(const std::string& s);
private:
	/// converts string to number
	template <typename T>
	T str2int(const char* str);
};
#endif // C_A2FInterpreter_h__
