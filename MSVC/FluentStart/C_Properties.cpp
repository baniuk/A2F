/**
 * \file C_Properties.cpp
 * \brief Contains definitions of all properties
 * \details This properties will be later moved to external file
 * \author PB
 * \date 2014/02/06
 */
#include "stdafx.h"
#include "C_Properties.h"

/// path to main starter exe. This starter spawns next processes
const ATL::CString C_Properties::PAR_PROCNAME = _T("ff");
/// run 3dpp version of fluent
ATL::CString C_Properties::PAR_PARNAME = _T(" 3ddp");
/// name of the subprocess: fl12016s.exe
const ATL::CString C_Properties::PAR_SUBPROCNAME = _T("fl12016s.exe");