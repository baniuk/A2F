// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit


#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlsafe.h>
#import "c:\Program Files (x86)\Common Files\CAPE-OPEN\CAPE-OPENv1-0-0.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, auto_search

// user includes
#include "Pantheios_header.h"
// ads collections
#include <atlcoll.h>
/// \todo enable config4cpp headers
//#include <config4cpp/Configuration.h>
//#include <config4cpp/SchemaValidator.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include "Material.h"

// user definitions
#define YES TRUE
#define NO FALSE

#ifndef PORTS_NUMBER
	#define PORTS_NUMBER 2 //!< number of ports in PMC
#else
	#error Port number defined!!
#endif
/**
 * Status of the unit shared among interfaces
 * \details Thi vaiable is modified by:
 *	\li IUnitOperations
 *	\li IUnitPort
 * Calling the Validate method is expected to set the unit’s status to either CAPE_VALID or CAPE_INVALID, depending on whether the 
 * validation tests succeed or fail. Making a change to the unit operation, such as setting a parameter value, or connecting a stream to
 * a port is expected to set the unit’s status to CAPE_NOT_VALIDATED.
 * Contains starus of the PMC. Can have the following values:
 * \li CAPE_INVALID
 * \li CAPE_VALID
 * \li CAPE_NOT_VALIDATED
 * 
 * \see AspenPlusUserModelsV8_2-Ref.pdf pp. 274
 * */
extern CapeValidationStatus exValidationStatus; //!< validation status shred among classes
extern "C" const GUID ;