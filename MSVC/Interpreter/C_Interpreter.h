/**
 * \file C_Interpreter.h
 * \brief Warper class definition for config4cpp parser
 * \author PB
 * \date 2014/03/19
 */
#ifndef C_Interpreter_h__
#define C_Interpreter_h__

/**
 * \class C_Interpreter
 * \brief Warper class definition for config4cpp parser
 * \details Implements basic functionality of config4cpp warper such as:
 * \li opening config
 * \li validating
 * \li parsing
 * \author PB
 * \date 2014/03/19
 * \see simple-encapsulation example from config4cpp install dir
 * \exception ConfigurationException on any error during parsing
*/
class C_Interpreter
{
public:
	/// Main constructor
	C_Interpreter(bool wantDiagnostics = false);
	~C_Interpreter(void);
	/// Opens config file and validates it
	void OpenAndValidate(const char* cfgInput, const char* cfgScope);
private:
	bool	m_wantDiagnostics;
	void*	m_cfg;						// opaque pointer to Config4Cpp config object
};
#endif // C_Interpreter_h__

