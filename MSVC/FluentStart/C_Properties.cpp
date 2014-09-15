/**
* \file C_Properties.cpp
* \brief Contains definitions of all properties
* \details This properties will be later moved to external file
* \author PB
* \date 2014/02/06
*/
#include "stdafx.h"
#include "C_Properties.h"

/**
* \details path to main starter exe. This starter spawns next processes
* \deprecated
*/
const ATL::CString C_Properties::PAR_PROCNAME = _T("f:\\Program Files\\ANSYS Inc\\v145\\fluent\\ntbin\\ntx86\\fluent.exe");
/** \details run 3dpp version of fluent. The followng parameters are provided:
* \li -g run without gui or graphics,
* \li -i journal read the specified journal file,
* \see http://cdlab2.fluid.tuwien.ac.at/LEHRE/TURB/Fluent.Inc/fluent6.2/help/pdf/ug/chp01.pdf
* \deprecated
*/
ATL::CString C_Properties::PAR_PARNAME = _T(" 3ddp -i "); // 3ddp -g -i ";

/**
* \details name of the subprocess: fl12016s.exe
* \deprecated
*/
const ATL::CString C_Properties::PAR_SUBPROCNAME = _T("fl1450s.exe");

/**
* \details path to the directory with operational files
* \deprecated
*/
const ATL::CString C_Properties::PAR_PATH = _T("c:\\TMP\\");

/// path to the script
const ATL::CString C_Properties::PAR_SCRIPT_PATH = _T("c:\\A2F.cfg");