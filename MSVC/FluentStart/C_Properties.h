/**
 * \file C_Properties.h
 * \brief Contains declarations of all proerties
 * \details This properties will be later moved to external file
 * \author PB
 * \date 2014/02/06
 */

#ifndef C_Properties_h__
#define C_Properties_h__

#include <atlstr.h>

/**
 * \class C_Properties
 * \brief Keeps temporary definitions of parameters
 * \details In future this class will be replaced by config4*. All strings are static, cont or nonconst, it depends on the function where they are used
 * \author PB
 * \date 2014/02/07
 * \note Initialization of static string in main object *.cpp but in correct namespace. Must be C_Properties::
 * \see http://stackoverflow.com/questions/2605520/c-where-to-initialize-static-const
*/
class C_Properties
{
private:
	C_Properties(void) {};
	~C_Properties(void) {};
public:
	/// Path to script file
	static const ATL::CString PAR_SCRIPT_PATH;
	/// Path to Fluent exe
	static const ATL::CString PAR_PROCNAME;
	/// Parameter to pass to Fluent
	static ATL::CString PAR_PARNAME;
	/// Name of the subprocess
	static const ATL::CString PAR_SUBPROCNAME;
	/// PAth to the environment
	static const ATL::CString PAR_PATH;
};
#endif // C_Properties_h__

