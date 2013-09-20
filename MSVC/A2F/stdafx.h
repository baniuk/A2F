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
#import "c:\Program Files (x86)\Common Files\CAPE-OPEN\CAPE-OPENv1-0-0.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, auto_search

// user includes
#include "Pantheios_header.h"
// adds decoding HRESULT errors (winstl::error_desc_a(err_code))
#include <winstl/error/error_desc.hpp>
#include <iostream>

// user definitions
#define YES TRUE
#define NO FALSE
extern "C" const GUID ;