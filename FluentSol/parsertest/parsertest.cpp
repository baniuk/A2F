// parsertest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{

	char filename[] = "j:\\ASPEN_PROJECT\\FluentSol\\parsertest\\Matlab\\params.txt";	// podwójne //!!!
	C_Params my_params;

	my_params.Creadfile(filename);
	
	return 0;
}

