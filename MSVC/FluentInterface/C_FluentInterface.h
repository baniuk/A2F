/**
 * \file C_FluentInterface.h
 * \brief Header of C_FluentInterface class
 * \author PB
 * \date 2014/06/21
 */
#ifndef C_FluentInterface_h__
#define C_FluentInterface_h__

#include "..\Common_utilities\Pantheios_header.h"

/**
 * \class C_FluentInterface
 * \brief Supports input/output operations between Fluent and PMC
 * \details Allows compositions of scm files and reads out data files. Has full access to provate members of CUnitOperations class.
 * \author PB
 * \date 2014/06/21
 * \see CUnitOperations
 * \note It is a friend class to CUnitOperations
*/
class C_FluentInterface
{
public:
	C_FluentInterface(void);
	~C_FluentInterface(void);
	/// Creates smc file for Fluent
	void CreateScm(void);
};

#endif // C_FluentInterface_h__


