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

class C_Properties
{
public:
	C_Properties(void);
	~C_Properties(void);
	/// Path to Fluent exe
	static const ATL::CString PAR_PROCNAME;
};
#endif // C_Properties_h__

