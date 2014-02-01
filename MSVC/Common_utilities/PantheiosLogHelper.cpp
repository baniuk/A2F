/**
 * \file    PantheiosLogHelper.cpp
 * \brief   Helps in logging
 * \author  PB
 * \date    2014/01/20
 * \version 0.5
 * \remarks Requires "Pantheios_header.h" and <comutil.h>
 */

#include "stdafx.h"
#include "PantheiosLogHelper.h"

/**
* \details  Dumps any VARIANT variable to logfile
* \param[in] data variable to be dumped      
* \param[in] desc Description to be added as prefix to log line
* \note See Detach() used on CComSafeArray. If not used destructor destroys also VARIANT passed from caller!!
*/
void PantheiosHelper::dumpVariant( const VARIANT* data, const TCHAR* desc)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	ATL::CComSafeArray<double> doubleHolder;	// keep relevant data for VT_ARRAY | VT_R8
	ATL::CComSafeArray<BSTR> bstrHolder;		// keep relevant data for VT_ARRAY | VT_BSTR
	LONG index;									// tables indexing
	PANTHEIOS_TRACE_DEBUG(PSTR("VARIANT name: "), desc);
	switch(data->vt)
	{
	case (VT_ARRAY | VT_R8):
		PANTHEIOS_TRACE_DEBUG(PSTR("VARIANT type: "), pantheios::integer(data->vt,pantheios::fmt::fullHex),PSTR(" "), PSTR("VT_ARRAY | VT_R8"));
		doubleHolder.Attach(data->parray);
		for(index = doubleHolder.GetLowerBound(); index <= doubleHolder.GetUpperBound(); ++index)
			PANTHEIOS_TRACE_DEBUG(	PSTR("	VARIANT data["),pantheios::integer(index),PSTR("]: "), pantheios::real(doubleHolder[index]));
		doubleHolder.Detach();
		break;
 	case VT_ARRAY | VT_BSTR:
 		PANTHEIOS_TRACE_DEBUG(PSTR("VARIANT type: "), pantheios::integer(data->vt,pantheios::fmt::fullHex),PSTR(" "), PSTR("VT_ARRAY | VT_BSTR"));
		bstrHolder.Attach(data->parray);
		for(index = bstrHolder.GetLowerBound(); index <= bstrHolder.GetUpperBound(); ++index)
			PANTHEIOS_TRACE_DEBUG(	PSTR("	VARIANT data["),pantheios::integer(index),PSTR("]: "), PW2M(bstrHolder[index]));
		bstrHolder.Detach();
 		break;
	case VT_EMPTY:
		PANTHEIOS_TRACE_DEBUG(PSTR("VARIANT type: "), pantheios::integer(data->vt,pantheios::fmt::fullHex),PSTR(" "), PSTR("VT_EMPTY"));
		break;
	default:
		PANTHEIOS_TRACE_DEBUG(PSTR("Unknown VARIANT type: "), pantheios::integer(data->vt,pantheios::fmt::fullHex),PSTR(" "));
	}
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}
