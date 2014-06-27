// Test_registrySupport.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Common_utilities\Pantheios_header.h"

using namespace std;

/// Log file name and initialization of Pantheios API
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("Test_registrySupport");
#ifndef PANTHEIOS_LOG_FILE_NAME
	#define PANTHEIOS_LOG_FILE_NAME	"c:\\Test_registrySupport.pantlog"
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
 * \test registrySupport:_wrongKey
 * \brief Try to open nonexistent key
 * \details Try to open nonexistent key
 * \pre Key must not exist
 * \post Expect return value other than ERROR_SUCCESS
 * \author PB
 * \date 2014/06/26
*/
TEST(registrySupport,_wrongKey)
{
	LONG ret;
	std::string out;
	ret = C_RegistrySupport::GetStringforKey(HKEY_CURRENT_USER,_T("Software\\Cape2Fluent"),_T("InstallDir"),out);
	EXPECT_NE(ERROR_SUCCESS,ret);
}

/**
 * \test registrySupport:_wrongvalue
 * \brief Try to open nonexistent value, key is ok
 * \details Try to open nonexistent value , key is ok
 * \pre value must not exist, key must exist
 * \post Expect return value other than ERROR_SUCCESS
 * \author PB
 * \date 2014/06/26
*/
TEST(registrySupport,_wrongvalue)
{
	LONG ret;
	std::string out;
	ret = C_RegistrySupport::GetStringforKey(HKEY_CURRENT_USER,_T("Software\\A2F"),_T("InstallDi"),out);
	EXPECT_NE(ERROR_SUCCESS,ret);
}

/**
 * \test registrySupport:_openKey
 * \brief Try to open value
 * \details Try to open string value, key is ok
 * \pre value must exist, must exist
 * \post Expect return value ERROR_SUCCESS
 * \author PB
 * \date 2014/06/26
*/
TEST(registrySupport,_openKey)
{
	LONG ret;
	std::string out;
	ret = C_RegistrySupport::GetStringforKey(HKEY_CURRENT_USER,_T("Software\\A2F"),_T("InstallDir"),out);
	cout << "Opened key: " << out << endl;
	EXPECT_EQ(ERROR_SUCCESS,ret);
}
