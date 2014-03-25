// Test_Interpreter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Common_utilities\Pantheios_header.h"

using namespace config4cpp;
using namespace std;

/// Log file name and initialization of Pantheios API
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("Test_FluentStarter");
#ifndef PANTHEIOS_LOG_FILE_NAME
	#define PANTHEIOS_LOG_FILE_NAME	"c:\\Test_Interpreter.pantlog"
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

// set global scope 
string application_scope;

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
 * \test Interpreter:_wrongFile
 * \brief Try to open nonexistent file.
 * \details Try to open file with configuration that not exist physically.
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Expect exception thrown by config4cpp
 * \author PB
 * \date 2014/03/22
 * \see config4cpp documentation
*/
TEST(Interpreter,_wrongFile)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_THROW(cfg->OpenAndValidate("wrongFile"),config4cpp::ConfigurationException);
	delete cfg;
}

/**
 * \test Interpreter:_correctFile
 * \brief Try to open existent file.
 * \details Try to open existent file with configuration.
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Expect no exception
 * \author PB
 * \date 2014/03/22
 * \see config4cpp documentation
*/
TEST(Interpreter,_correctFile)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	delete cfg;
}

/**
 * \test Interpreter:_wrongscope
 * \brief Try to open existent file with wrong scope.
 * \details Try to open existent file with configuration but the main scope is wrong
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Expect exception
 * \author PB
 * \date 2014/03/22
 * \see config4cpp documentation
*/
TEST(Interpreter,_wrongscope)
{
	application_scope = "FLUENTA";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_THROW(cfg->OpenAndValidate("A2F.cfg"),config4cpp::ConfigurationException);
	delete cfg;
}

/**
 * \test Interpreter:_noscopeset
 * \brief Test when no external scope will be set
 * \details \c application_scope must be set with valid scope. If not set at all (empty string) std Exception is thrown
 * \pre external variable \c application_scope \b{must not be} set 
 * \post Expect exception
 * \author PB
 * \date 2014/03/22
 * \see config4cpp documentation
 * \note Disbled in nirmal because causes assertion
*/
TEST(Interpreter,DISABLED_noscopeset)
{
	application_scope = "";
	C_Interpreter* cfg = new C_Interpreter();
	cfg->OpenAndValidate("A2F.cfg");
	delete cfg;
}

/**
 * \test Interpreter:_emptyconfig
 * \brief Test when empty name of config file is provided
 * \pre external variable \c application_scope \b{must not be} set 
 * \post Expect Exception
 * \author PB
 * \date 2014/03/22
 * \see config4cpp documentation
 * \todo finish
*/
TEST(Interpreter,_emptyconfig)
{
	application_scope = "FLUENTA";
	bool exception_thrown = false;
	C_Interpreter* cfg = new C_Interpreter();
	try
	{
		cfg->OpenAndValidate("");
	}
	catch( const exception& ex)
	{
		cerr << ex.what() << endl;
		exception_thrown = true;
	}
	EXPECT_TRUE(exception_thrown);	
	delete cfg;
}

/**
 * \test Interpreter:_parseSchema
 * \brief Parses schema file
 * \details Example of parsing schema file using SchemaValidator class. Throw exception if there are errors in scheme or config
 * \pre external variable \c application_scope must be set to FLUENT
 * \post No exception should be thrown
 * \author PB
 * \date 2014/03/22
 * \see config4cpp documentation
*/
TEST(Interpreter,_parseSchema)
{
	SchemaValidator* sv = new SchemaValidator();
	EXPECT_NO_THROW(sv->parseSchema(schema));
	delete sv;
}

/**
 * \test Interpreter:_parseandvalidate
 * \brief Parses and perform scheme validation.
 * \details 
 * Parses and perform scheme validation. Test of the use. Throw if:
 * \li there is syntax mistake in A2F.cfg
 * \li there is syntax mistake in schema
 * \li A2F does not fulfill schema (mispelling, wrong parameter etc)
 * \pre external variable \c application_scope must be set to FLUENT
 * \post No exception should be thrown
 * \author PB
 * \date 2014/03/22
 * \see config4cpp documentation
*/
TEST(Interpreter,_parseandvalidate)
{
	Configuration* cfg = Configuration::create();
	SchemaValidator* sv = new SchemaValidator();
	// parse script
	EXPECT_NO_THROW(cfg->parse("A2F.cfg"));
	// parse schema
	EXPECT_NO_THROW(sv->parseSchema(schema));
	// validate
	EXPECT_NO_THROW(sv->validate(cfg,"FLUENT",""));
	delete sv;
	cfg->destroy();
}

/**
 * \test Interpreter:_lookup4String_equal
 * \brief Gets one string parameter from configuration
 * \pre external variable \c application_scope must be set to FLUENT
 * \post No exception should be thrown, returned value equals \ctest.case
 * \author PB
 * \date 2014/03/23
 * \see config4cpp documentation
*/
TEST(Interpreter,_lookup4String_equal)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	string result;
	EXPECT_NO_THROW(result = cfg->lookup4String("CASE_NAME"));
	EXPECT_EQ(result.compare("test.case"),0);
	delete cfg;
}

/**
 * \test Interpreter:_lookup4String_nequal
 * \brief Gets one string parameter from configuration
 * \pre external variable \c application_scope must be set to FLUENT
 * \post No exception should be thrown, returned value not equals \ctest.case
 * \author PB
 * \date 2014/03/23
 * \see config4cpp documentation
*/
TEST(Interpreter,_lookup4String_nequal)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	string result;
	EXPECT_NO_THROW(result = cfg->lookup4String("COMMAND_LINE"));
	EXPECT_NE(result.compare("test.case"),0);
	delete cfg;
}

/**
 * \test Interpreter:_lookup4String_wrongask
 * \brief Gets one string parameter from configuration but we ask for nonexistent param
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Should throw exception, returned value not equals \ctest.case
 * \author PB
 * \date 2014/03/23
 * \see config4cpp documentation
*/
TEST(Interpreter,_lookup4String_wrongask)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	string result;
	EXPECT_THROW(result = cfg->lookup4String("COMMAND_LINEEE"),config4cpp::ConfigurationException);
	EXPECT_NE(result.compare("test.case"),0);
	delete cfg;
}

/**
 * \test Interpreter:_lookup4String_wrongformat
 * \brief Gets one string parameter from configuration but we ask for param defined as int. 
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Should not throw exception, returned value not equals \ctest.case
 * \author PB
 * \date 2014/03/23
 * \see config4cpp documentation
 * \see TEST(Interpreter,_lookup4Int_wrongformat)
 * \remarks In this case method returns regular string that contain number
*/
TEST(Interpreter,_lookup4String_wrongformat)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	string result;
	EXPECT_NO_THROW(result = cfg->lookup4String("NUMOFITER"));
	cerr << result << endl;
	EXPECT_NE(result.compare("test.case"),0);
	delete cfg;
}

/**
 * \test Interpreter:_lookup4Int_wrongformat
 * \brief Gets one int parameter from configuration but we ask for param defined as string. 
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Should throw exception, returned value not initialized
 * \author PB
 * \date 2014/03/23
 * \see config4cpp documentation
 * \see TEST(Interpreter,_lookup4String_wrongformat)
 * \remarks In this case method returns regular string that contain number
*/
TEST(Interpreter,_lookup4Int_wrongformat)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	int result;
	EXPECT_THROW(result = cfg->lookup4Int("COMMAND_LINE"),config4cpp::ConfigurationException);
	delete cfg;

}
/**
 * \test Interpreter:_lookup4Int_equal
 * \brief Gets one int parameter from configuration
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Should not throw exception, returned value equal 3 
 * \author PB
 * \date 2014/03/23
 * \see config4cpp documentation
 */
TEST(Interpreter,_lookup4Int_equal)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	int result;
	EXPECT_NO_THROW(result = cfg->lookup4Int("NUMOFITER"));
	EXPECT_EQ(result, 3);
	delete cfg;
}

/**
 * \test Interpreter:_lookup4Float_equal
 * \brief Gets one float parameter from configuration
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Should not throw exception, returned value equal 3 
 * \author PB
 * \date 2014/03/23
 * \see config4cpp documentation
 * \remarks In this case int vales can be read as well
 */
TEST(Interpreter,_lookup4Float_equal)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	float result;
	EXPECT_NO_THROW(result = static_cast<float>(cfg->lookup4Int("NUMOFITER")));
	EXPECT_EQ(result, 3);
	delete cfg;
}

/**
 * \test Interpreter:_lookup4List_equal
 * \brief Gets one list of parameter from configuration
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Should not throw exception, returned values equal "wylotpulpy", "0.0113" 
 * \author PB
 * \date 2014/03/24
 * \see config4cpp documentation
 * \note Numbers in lists are accesible as string but there will be always possible to convert them to number because there was scheme checking before.
 * Schemes check also list entries types.
 */
TEST(Interpreter,_lookup4List_equal)
{
	application_scope = "FLUENT";
	C_Interpreter* cfg = new C_Interpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));
	const char** list;
	int	listSize;
	try
	{
		cfg->lookup4List("SURFACES.OUTPUT1",list,listSize);
	}
	catch(...)
	{
		ASSERT_TRUE(true);
		delete cfg;
	}
	EXPECT_STREQ(list[0],"wylotpulpy");
	EXPECT_STREQ(list[1],"0.0113");

/*	EXPECT_EQ(result, 3);*/
	delete cfg;
}

/**
 * \test _GetSurfaceParams_equal
 * \brief Test acces to surface list
 * \pre external variable \c application_scope must be set to FLUENT
 * \post Expect surface name and its area as float number
 * \author PB
 * \date 2014/03/25
*/
TEST(A2FInterpreter,_GetSurfaceParams_equal)
{
	application_scope = "FLUENT";
	C_A2FInterpreter* cfg = new C_A2FInterpreter();
	EXPECT_NO_THROW(cfg->OpenAndValidate("A2F.cfg"));

	string surfaceName;
	float area;
	EXPECT_NO_THROW(cfg->GetSurfaceParams("SURFACES.OUTPUT1", surfaceName, area));
	EXPECT_STREQ(surfaceName.c_str(),"wylotpulpy");
	EXPECT_EQ(area,0.0113f);
	delete cfg;
}
