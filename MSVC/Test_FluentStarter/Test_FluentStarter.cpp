/**
 * \file Test_FluentStarter.cpp
 * \brief Main file that starts all tests
 * \details Tests Fluent starter
 * \pre Nedd fluent installed
 * \author PB
 * \date 2014/02/05
 * \warning All test should be run on virtual machine A2F.
 */


#include "stdafx.h"

#include "..\Common_utilities\Pantheios_header.h"
#include "..\Common_utilities\PantheiosLogHelper.h"
#include "..\FluentStart\C_Properties.h"

/// Log file name and initialization of Pantheios API
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("Test_FluentStarter");
#ifndef PANTHEIOS_LOG_FILE_NAME
	#define PANTHEIOS_LOG_FILE_NAME	"c:\\Test_FluentStarter.pantlog"
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
    { toFile,  PANTHEIOS_SEV_DEBUG    },
	{ toConsole,  PANTHEIOS_SEV_ERROR },
    PANTHEIOS_FE_N_TERMINATOR_ENTRY(PANTHEIOS_SEV_CRITICAL)
};

/**
 * \brief Struktura ³¹cz¹ca poziom b³edu z konkretnym wyjœciem
 *
 * LOGI::File i LOGI::Console ³¹cz¹ siê z pozycjami w PAN_FE_N_SEVERITY_CEILINGS
 */
pan_be_N_t PAN_BE_N_BACKEND_LIST[] = {
    PANTHEIOS_BE_N_STDFORM_ENTRY(toFile, pantheios_be_file, 0),
	PANTHEIOS_BE_N_STDFORM_ENTRY(toConsole, pantheios_be_fprintf, 0),
    PANTHEIOS_BE_N_TERMINATOR_ENTRY
};

using namespace std;

// set global context for script
string application_scope = "FLUENT";

int _tmain(int argc, _TCHAR* argv[])
{
	int ret = 0;
	if (pantheios::pantheios_init() < 0)
	{
		std::cerr << "Failed to initialise the Pantheios logging libraries!\n" << std::endl;
		return FALSE;
	}
	else
	{
		pantheios_be_file_setFilePath(PSTR(PANTHEIOS_LOG_FILE_NAME), PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BEID_ALL);
		pantheios::log_INFORMATIONAL("Logger enabled!");
	}
	::testing::InitGoogleTest(&argc, argv);
	ret = RUN_ALL_TESTS();

	pantheios::log_INFORMATIONAL("Logger disabled!");
	pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);
	pantheios::pantheios_uninit();
	return ret;
}

/** 
 * \test FluentStarter:_StartFluent
 * Try start Fluent. Most parameters set separately in C_Properties
 * \see C_Properties
 */
TEST(FluentStarter,DISABLED__StartFluent)
{
	HRESULT err = E_FAIL;
	ASSERT_NO_THROW(err = C_FluentStarter::StartFluent());
	ASSERT_HRESULT_SUCCEEDED(err);
}

/** 
 * \test FluentStarter:_CreateSCM
 * Creates journal file and SCM in %TMP% directory
 */
TEST(FluentStarter,_CreateJournal)
{
	try
	{
		C_FluentStarter::CreateJournal();
	}
	catch(std::exception& ex)
	{
		std::cerr << "Caught exception: " << ex.what() << endl;
		ASSERT_TRUE(false);
	}
	std::cerr << "Need to check journal file manually" << std::endl;
}
