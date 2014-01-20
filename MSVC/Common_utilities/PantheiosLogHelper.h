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

#include <comutil.h>
#include <atlsafe.h>

/// Dumps VARIANT data to log file
void dumpVariant( const VARIANT* data, const TCHAR* desc);

#endif // PantheiosLogHelper_h__