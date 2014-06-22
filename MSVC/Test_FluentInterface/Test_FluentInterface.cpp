/**
 * \file Test_FluentInterface.cpp
 * \brief Main file that starts all tests
 * \details Tests Fluent Interface static class
 * \author PB
 * \date 2014/06/22
 */

#include "stdafx.h"

#include "..\Common_utilities\Pantheios_header.h"

/// Log file name and initialization of Pantheios API
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("Test_FluentInterface");
#ifndef PANTHEIOS_LOG_FILE_NAME
	#define PANTHEIOS_LOG_FILE_NAME	"c:\\Test_FluentInterface.pantlog"
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
 * \test FluentInterface,_wrongFile
 * \brief Try to open nonexistent file.
 * \post Expect exception std::ios_base::failure
 * \author PB
 * \date 2014/06/22
*/
TEST(FluentInterface,_wrongFile)
{
	EXPECT_THROW(C_FluentInterface test("notfile.prof"),std::ios_base::failure);
}

/**
 * \test FluentInterface,_goodFile
 * \brief Try to open existent file.
 * \post Expect no exception 
 * \author PB
 * \date 2014/06/22
*/
TEST(FluentInterface,_goodFile)
{
	EXPECT_NO_THROW(C_FluentInterface test("example_profile.prof"));
}

class _FluentInterface : public ::testing::Test
{
	virtual void SetUp()
	{
	}
	virtual void TearDown()
	{
	}
};

/**
 * \test _FluentInterface,_getSurfaceOffset
 * \brief Finds offset of line in prof file where surface starts
 * \pre file must exist
 * \post offset 26547 - number of bytes from beginig of file with LFCR on every line
 * \author PB
 * \date 2014/06/22
*/
TEST_F(_FluentInterface,_getSurfaceOffset)
{
	bool exception_thrown = false;
	try
	{
		C_FluentInterface test("example_profile.prof");
		EXPECT_EQ(26547,test.getSurfaceOffset("cathode-outlet"));
	}
	catch( const exception& ex)
	{
		cerr << ex.what() << endl;
		exception_thrown = true;
	}
	EXPECT_FALSE(exception_thrown);	
}

/**
 * \test _FluentInterface,_getSurfaceOffsetWrong
 * \brief Try to find nonexistent surface
 * \pre file must exist
 * \post throw exception std::logic_error
 * \author PB
 * \date 2014/06/22
*/
TEST_F(_FluentInterface,_getSurfaceOffsetWrong)
{
	bool exception_thrown = false;
	try
	{
		C_FluentInterface test("example_profile.prof");
		test.getSurfaceOffset("cathode-outlety");
	}
	catch( const exception& ex)
	{
		cerr << ex.what() << endl;
		exception_thrown = true;
	}
	EXPECT_TRUE(exception_thrown);	
}

/**
 * \test _FluentInterface,_getSurfaceOffset
 * \brief Finds offset of line in prof file where function starts
 * \pre file must exist
 * \post offset 39226 - number of bytes from beginig of file with LFCR on every line
 * \author PB
 * \date 2014/06/22
*/
TEST_F(_FluentInterface,_getFunctionOffset)
{
	bool exception_thrown = false;
	try
	{
		C_FluentInterface test("example_profile.prof");
		EXPECT_EQ(39226,test.getFunctionOffset("velocity-magnitude",test.getSurfaceOffset("cathode-outlet")));
	}
	catch( const exception& ex)
	{
		cerr << ex.what() << endl;
		exception_thrown = true;
	}
	EXPECT_FALSE(exception_thrown);	
}

/**
 * \test _FluentInterface,_getSurfaceOffsetWrong
 * \brief Try to find nonexistent function
 * \pre file must exist
 * \post throw exception std::logic_error or can throw std::ios_base
 * \author PB
 * \date 
 */
TEST_F(_FluentInterface,_getFunctionOffsetWrong)
{
	bool exception_thrown = false;
	try
	{
		C_FluentInterface test("example_profile.prof");
		test.getFunctionOffset("velocity-magnitudey",test.getSurfaceOffset("cathode-outlet"));
	}
	catch( const exception& ex)
	{
		cerr << ex.what() << endl;
		exception_thrown = true;
	}
	EXPECT_TRUE(exception_thrown);	
}