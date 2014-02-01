/**
 * \file    Test_Material_Class.cpp
 * \brief   Main file that starts all tests
 * \details This testcase supports ATL and COM classes in order to test Material class propoerties based on ICapeThermoMaterialObject.
 * There is also PantheiosLogHelper tested here
 * \author  PB
 * \date    2014/01/02
 * \version 0.5
 * \see CapeMaterialObject.h
 * \see PantheiosLogHelper.h
 */


#include "stdafx.h"
#include "resource.h"
#include "Test_Material_Class_i.h"

#include "..\Common_utilities\Pantheios_header.h"
#include "..\Common_utilities\PantheiosLogHelper.h"

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
	HRESULT hr;
	pantheios_be_file_setFilePath(PSTR(PANTHEIOS_LOG_FILE_NAME), PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BEID_ALL);
	pantheios::log_INFORMATIONAL("Logger enabled!");
	hr = _AtlModule.InitializeCom();
	if(FAILED(hr))
		PANTHEIOS_TRACE_ERROR(PSTR("InitializeCom: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
	hr = _AtlModule.RegisterClassObjects(CLSCTX_INPROC_SERVER,REGCLS_MULTIPLEUSE); // sam to odkry³em
	if(FAILED(hr))
		PANTHEIOS_TRACE_ERROR(PSTR("RegisterClassObjects: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));

	int argc = 0;
	char** argv = NULL;
	::testing::InitGoogleTest(&argc, argv);
	int err = RUN_ALL_TESTS();

	pantheios::log_INFORMATIONAL("Logger disabled!");
	pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);
	pantheios::pantheios_uninit();

	_AtlModule.UninitializeCom();
	return err;
}

/** 
 * \test PantheiosLogHelper:_LogTest_VT_EMPTY Check VT_EMPTY
 */
TEST(PantheiosLogHelper,_LogTest_VT_EMPTY)
{
	VARIANT test;
	VariantInit(&test);
	PantheiosHelper::dumpVariant(&test,"_LogTest_VT_EMPTY");
	EXPECT_EQ(1,1);
}

/** 
 * \test PantheiosLogHelper:_LogTest_VT_ARRAY_DOUBLE Check array of doubles
 * This test will fail without detaching VARIANT in PantheiosHelper::dumpVariant
 */
TEST(PantheiosLogHelper,_LogTest_VT_ARRAY_DOUBLE)
{
	VARIANT out;
	VariantInit(&out);	// output variant

	CComSafeArray<double> tab(3); tab[0] = 20; tab[1] = 30; tab[2] = 40;
	CComVariant test(tab);	// assign table to CComVariant

	test.Detach(&out);	// copy test tab to out VARIANT
	PantheiosHelper::dumpVariant(&out,"_LogTest_VT_ARRAY_DOUBLE");
	// check if out is still valid after dumpVariant
	LONG index = 0;
	double tabval;
	SafeArrayGetElement(out.parray, &index, &tabval);
	EXPECT_EQ(20,tabval);

	index = 1;
	SafeArrayGetElement(out.parray, &index, &tabval);
	EXPECT_EQ(30,tabval);

	index = 2;
	SafeArrayGetElement(out.parray, &index, &tabval);
	EXPECT_EQ(40,tabval);
}

/** 
 * \test PantheiosLogHelper:_LogTest_VT_ARRAY_BSTR Check array of bstr
 */
TEST(PantheiosLogHelper,LogTest_VT_ARRAY_BSTR)
{
	VARIANT out;
	VariantInit(&out);	// output variant

	CComSafeArray<BSTR> tab(3); tab[0] = L"raz"; tab[1] = L"dwa"; tab[2] = L"trzy";
	CComVariant test(tab);	// assign table to CComVariant

	test.Detach(&out);	// copy test tab to out VARIANT
	PantheiosHelper::dumpVariant(&out,"LogTest_VT_ARRAY_BSTR");
	EXPECT_EQ(1,1);
}

/**
 * \class MaterialTest
 * \brief Fixture class for testing Material class
 * 
 * Creates environment for testing Material.cpp class. Creates one COM object of ICapeThermoMaterialObject
 * Choosen methods of ICapeThermoMaterialObject are implemented in CapeMaterialObject.h
 * Logging to file or console if error
 * \author PB
 * \date 2014/01/06
 *
 * \see 
 * \li Material.cpp
 * \li CapeMaterialObject.h
 */
class _MaterialTest : public ::testing::Test
{
protected:
	CComPtr<ICapeThermoMaterialObject> pCapeMaterialObject; // test object
	
	/// get access to private members of class Material
	const ATL::CComSafeArray<double>& get_private_Material_temperatures(const Material& obj) {
		return obj.temperatures;
	}
	const ATL::CComSafeArray<double>& get_private_Material_pressures(const Material& obj) {
		return obj.pressures;
	}
	HRESULT get_private_Material_get_Composition(Material& obj) {
		return obj.get_Composition();
	}
	LONG get_private_Material_numComp(const Material& obj) {
		return obj.numComp;
	}
	const ATL::CComSafeArray<BSTR>& get_private_Material_phases(const Material& obj) {
		return obj.phases;
	}
	const ATL::CComSafeArray<BSTR>& get_private_Material_compIds(const Material& obj) {
		return obj.compIds;
	}
	/// creates COM reference of ICapeThermoMaterialObject
	virtual void SetUp()
	{
		HRESULT hr;
 		hr = pCapeMaterialObject.CoCreateInstance(CLSID_CapeMaterialObject); // create instance of ICapeThermoMaterialObject
		if(FAILED(hr))
			PANTHEIOS_TRACE_ERROR(PSTR("CoCreateInstance: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
	}

	/// cleans up
	virtual void TearDown()
	{
		pCapeMaterialObject.Release();
	}
};
/** 
 * \test _MaterialTest:_COM_method_call Test of COM object calling
 * Calls GetNumComponents method and expects one component.
 */
TEST_F(_MaterialTest, _COM_method_call) {
	LONG n;
	HRESULT hr;
	hr = pCapeMaterialObject->GetNumComponents(&n);
	if(FAILED(hr))
		PANTHEIOS_TRACE_ERROR(PSTR("GetNumComponents: "), pantheios::integer(hr,pantheios::fmt::fullHex),PSTR(" Error: "), winstl::error_desc_a(hr));
	EXPECT_HRESULT_SUCCEEDED(hr);
	EXPECT_EQ(3, n);
}

/** 
 * \test _MaterialTest:_constructor_noInitialization Test of constructor
 */
TEST_F(_MaterialTest, _constructor_noInitialization) {
	
	/// \note no AddRef here \see http://369o.com/data/books/atl/0321159624/ch03lev1sec4.html The Type-Cast Operator
	Material testMaterial(pCapeMaterialObject);	// no AddRef here
}

/**
 * \test _MaterialTest:_FlashMaterialObject
 * Assumes that:
 * \li temperatures differ by 10
 * \li pressures differ by 100
 */
TEST_F(_MaterialTest, _FlashMaterialObject) {

	LONG index;				// lower and upper bounds of phisical properties array

	Material testMaterial(pCapeMaterialObject);	// no AddRef here
	testMaterial.FlashMaterialObject();
	// verification of temeratures
	double startT = 20;	// temperatury ró¿ni¹ siê o 10 i startuja z 20
 	for(index=get_private_Material_temperatures(testMaterial).GetLowerBound(); index<=get_private_Material_temperatures(testMaterial).GetUpperBound(); ++index)
 	{	
 		EXPECT_EQ(startT,get_private_Material_temperatures(testMaterial).GetAt(index));
 		startT+=10;
 	}

	// verification of pressures
	CComSafeArray<double> pressures(get_private_Material_pressures(testMaterial));
	double startP = 200;	// ciœnienia ró¿ni¹ siê o 100 i startuja z 200
	for(index=get_private_Material_pressures(testMaterial).GetLowerBound(); index<=get_private_Material_pressures(testMaterial).GetUpperBound(); ++index)
	{	
		EXPECT_EQ(startP,get_private_Material_pressures(testMaterial).GetAt(index));
		startP+=100;
	}
}

/**
 * \test _MaterialTest:_get_Composition
 * Assumes that:
 * \li first component "H20"
 * \li second component "O2"
 * \li third component "SiO"
 * \li one phase "Liquid"
 */
TEST_F(_MaterialTest, _get_Composition) {

	HRESULT hr;
	Material testMaterial(pCapeMaterialObject);	// no AddRef here
	hr = get_private_Material_get_Composition(testMaterial);
	EXPECT_HRESULT_SUCCEEDED(hr);
	EXPECT_EQ(3,get_private_Material_numComp(testMaterial));

	CComSafeArray<BSTR> phases(get_private_Material_phases(testMaterial));
	CComSafeArray<BSTR> compIds(get_private_Material_compIds(testMaterial));
	EXPECT_STREQ(L"Liquid",phases.GetAt(0));
	
	EXPECT_STREQ(L"H20",compIds.GetAt(0));
	EXPECT_STREQ(L"O2",compIds.GetAt(1));
	EXPECT_STREQ(L"SiO",compIds.GetAt(2));	
}