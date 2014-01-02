/**
 * \file    Test_Material_Class.cpp
 * \brief   Main file that starts all tests
 * \details This testcase supports ATL and COM classes in order to test Material class propoerties based on ICapeThermoMaterialObject
 * \author  PB
 * \date    2014/01/02
 * \version 0.5
 */


#include "stdafx.h"
#include "resource.h"
#include "Test_Material_Class_i.h"

#include "..\A2F\Pantheios_header.h"

/// Log file name and initialization of Pantheios API
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("Test_Material_Class");
#ifndef PANTHEIOS_LOG_FILE_NAME
	#define PANTHEIOS_LOG_FILE_NAME	"c:\\Test_Material_Class.pantlog"
#else
	#error PANTHEIOS_LOG_FILE_NAME already defined!!
#endif

/**
 * \brief Struktura okreœlaj¹ca minimalny poziom b³edu który trafia do danego logu
 *
 * DEBUG jest poziomem najni¿szym, co znaczy ¿e do pliku trafi wszystko. Ta struktura dzia³a
 * jedynie gdy linkuje siê do biblioteki be.N. Kolejnoœæ b³êdów:
 * -# DEBUG
 * -# INFORMATIONAL
 * -# NOTICE
 * -# WARNING
 * -# ERROR
 * -# CRITICAL
 * -# ALERT
 * -# EMERGENCY
 * \n
 * Do konsoli trafi wszystko powy¿ej DEBUG
 */
pan_fe_N_t PAN_FE_N_SEVERITY_CEILINGS[]  = {
    { toFile,  PANTHEIOS_SEV_DEBUG },
    PANTHEIOS_FE_N_TERMINATOR_ENTRY(PANTHEIOS_SEV_CRITICAL)
};

/**
 * \brief Struktura ³¹cz¹ca poziom b³edu z konkretnym wyjœciem
 *
 * LOGI::File i LOGI::Console ³¹cz¹ siê z pozycjami w PAN_FE_N_SEVERITY_CEILINGS
 */
pan_be_N_t PAN_BE_N_BACKEND_LIST[] = {
    PANTHEIOS_BE_N_STDFORM_ENTRY(toFile, pantheios_be_file, 0),
    PANTHEIOS_BE_N_TERMINATOR_ENTRY
};

using namespace ATL;


class CTest_Material_ClassModule : public ATL::CAtlExeModuleT< CTest_Material_ClassModule >
{
public :
	DECLARE_LIBID(LIBID_Test_Material_ClassLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TEST_MATERIAL_CLASS, "{AFC204D5-5779-4FF5-9778-FE0B4E967C8C}")
	};

CTest_Material_ClassModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	pantheios_be_file_setFilePath(PSTR(PANTHEIOS_LOG_FILE_NAME), PANTHEIOS_BEID_ALL);
	pantheios::log_INFORMATIONAL("Logger enabled!");

	int argc = 0;
	char** argv = NULL;
	::testing::InitGoogleTest(&argc, argv);
	int err = RUN_ALL_TESTS();

	pantheios::log_INFORMATIONAL("Logger disabled!");
	pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);
	pantheios::pantheios_uninit();
	return err;
	//_AtlModule.WinMain(nShowCmd);
}

/** 
 * \test Material: Test of constructor
 */
TEST(_Material, noInitialization) {
	
	//	Material dummy;
	EXPECT_EQ(0, 0);
}