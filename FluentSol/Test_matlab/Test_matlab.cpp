// Test_matlab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{

	HANDLE hLogFile;
	hLogFile = CreateFile(L"c:\\log.txt", GENERIC_WRITE, 
						  FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 
						  FILE_ATTRIBUTE_NORMAL, NULL);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, hLogFile);

	double liczba;
	if (!mclInitializeApplication(NULL,0)) 
    {
		std::cerr << "could not initialize the application properly" << std::endl;
		return -1;

    }
	if( !testlib2Initialize() )
    {
		std::cerr << "could not initialize the library properly" << std::endl;
		return -1;
    }
	try
	{
		mwArray a("testfile.txt");
		mwArray out;
		testfile(1,out,a);
		out.GetData(&liczba,1);
		_RPT0(_CRT_WARN,"Test");
	} catch(const mwException& e)
		{
			std::cerr << e.what() << std::endl;
			return -2;
        }
        catch (...)
        {
          std::cerr << "Unexpected error thrown" << std::endl;
          return -3;
        }     
        // Call the application and library termination routine
	testlib2Terminate();


	mclTerminateApplication();
	CloseHandle(hLogFile);
	return 0;
}

