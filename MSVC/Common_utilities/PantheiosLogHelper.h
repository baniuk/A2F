/**
 * \file    PantheiosLogHelper.h
 * \brief   Helps in logging
 * \author  PB
 * \date    2014/01/20
 * \version 0.5
 * \remarks Requires "Pantheios_header.h" and <comutil.h>
 */

#ifndef PantheiosLogHelper_h__
#define PantheiosLogHelper_h__

// user includes
#include "Pantheios_header.h"
#include <comutil.h>
#include <atlsafe.h>

/**
 * \class PantheiosHelper
 * \brief Class contains helper functions for laooging.
 * \details all functions are static. This is only conatainer for methods
 * \author PB
 * \date 2014/01/31
*/
class PantheiosHelper
{
public:
	/// Dumps VARIANT data to log file
	static void dumpVariant( const VARIANT* data, const TCHAR* desc);
	/// Dumps double array
	static void dumpCComSafeArray( const ATL::CComSafeArray<double>& data, const TCHAR* desc);
	/// Dumps BSTR array
	static void dumpCComSafeArray( const ATL::CComSafeArray<BSTR>& data, const TCHAR* desc);
};


#endif // PantheiosLogHelper_h__