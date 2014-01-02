// Test_Material_Class.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "Test_Material_Class_i.h"


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
	int argc = 0;
	char** argv = NULL;
	::testing::InitGoogleTest(&argc, argv);
	int err = RUN_ALL_TESTS();

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