#include "StdAfx.h"
#include "C_myRunProcess.h"

#define M_PI 3.14159265358979323846264338327950288419716939937510

C_myRunProcess::C_myRunProcess(C_Error* perr,C_Params* params)
{
	err = perr;
	copyparams = params;
//	procname = TEXT("e:\\FluentInc\\ntbin\\ntx86\\fluent.exe");
	parname = TEXT(" 3ddp");
//	subprocname = TEXT("fl6326s.exe");
	paramsval = FALSE;

}

C_myRunProcess::~C_myRunProcess(void)
{

}

BOOL C_myRunProcess::StartFluent(void)
/// \retval FAIL Jeœli Fluent nie wystartowa³
/// \retval OK Jeœli sukces
{
	BOOL ret;
	BOOL ret1;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	si.lpDesktop = NULL;
	
		CComBSTR ff = " 3ddp";
//	CComBSTR gg = "g:\\ANSYS Inc\\v120\\fluent\\ntbin\\ntx86\\fluent.exe";

	ret1 = CreateProcess(procname,
					parname,
					NULL,
					NULL,
					FALSE,
					0,
					NULL,
					NULL,
					&si,
					&pi);

	if(ret1!=0)	{
		size_t origsize = strlen(copyparams->bSUBPROCNAME) + 1;
		const size_t newsize = MAX_STRING;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, copyparams->bSUBPROCNAME, _TRUNCATE);
		ret = WaitForStart(wcstring,3, 6);
	} else	{
		err->AddError("StartFluent::Function failed");
		ret = FAIL;
	}

	return ret;
}

BOOL C_myRunProcess::WaitForStart(TCHAR* nazwa, unsigned int obrot, unsigned int czas)
/// \retval FAIL Jeœli nie doczeka³ siê na w³asciwy proces
/// \retval OK Jeœli sukces
{
		// czeka czas sekund na start i pozniej zwraca b³¹d. Proboje "obrot" razy
	unsigned int licz = 0;
	BOOL ret;

	while(licz<obrot)
	{
		ret = WaitForProcess(nazwa);
		if(ret==FAIL)
			Sleep(czas*1000);
		else
			return OK;
		licz++;
	}
	err->AddError("WaitForStart::Function failed");
	return FAIL;	// nie uruchomi³o siê
}

BOOL C_myRunProcess::WaitForProcess(TCHAR* nazwa)
/// \retval FAIL Jeœli proces nie wystartowa³
/// \retval OK Jeœli sukces
{
	BOOL ret = FAIL;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
	{
		err->AddError("WaitForProcess::Function failed");
        return FAIL;
	}

	cProcesses = cbNeeded / sizeof(DWORD);

	for ( i = 0; i < cProcesses; i++ )	{
		if( aProcesses[i] != 0)	{
			ret = PrintProcessNameAndID( aProcesses[i], nazwa);
			if(ret==OK)	{
				break;
			}
		}
	}
	return ret;
}

BOOL C_myRunProcess::PrintProcessNameAndID(DWORD processID, TCHAR* nazwa)
/// \retval FAIL Jeœli nie znaleziono procesu o danej nazwie
/// \retval OK Jeœli sukces
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	DWORD d;

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ|SYNCHRONIZE,
                                   TRUE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }
 

	if(wcscmp(szProcessName,nazwa)==0)	{
		d = WaitForSingleObject( hProcess, INFINITE );
		CloseHandle( hProcess );
		return OK;
	}
	else	{
		CloseHandle( hProcess );
		return FAIL;
	}
}

void C_myRunProcess::RemoveDoubleSlash(char* in)
{
	char ttmp[MAX_STRING];

	unsigned int a;
	unsigned int licznik = 0;
	for(a=0;a<strlen(in)-1;a++)	{
		if(in[a]=='\\' && in[a+1]=='\\')
			continue;
		else
			ttmp[licznik++] = in[a];
	}
	ttmp[licznik++] = in[a];	// ostatni znak
	ttmp[licznik] = 0;						// koniec ci¹gu

	// kopiowanie do wejœciowego
	for(a=0;a<=licznik;a++)
		in[a] = ttmp[a];
}

// Tworzy œrodowisko do uruchomienia fluenta - generuje scm oraz journalC_Params
BOOL C_myRunProcess::CreateEnv(void)
/// \retval FAIL Jeœli b³¹d - wiele mo¿liwych Ÿróde³ b³êdu
/// \retval OK Jeœli sukces
{
	double paramVal2;
	char* tmpin;
	char* tmpsurf;
	char* tmpmat;
	FILE *fid;
	CComBSTR jname = "journal";
	CComBSTR ptmp;
	CComBSTR fulljname;
	CComBSTR etmp;
	unsigned int a;
	double paramVal1;
	BOOL ret;

	if(copyparams->ValidateParams(BASIC))	{// flag is set, dla bezpieczenstwa, zakladam ze obsluga b³êów na zewn¹trz
		FLUENT_PATH = copyparams->bFLUENT_PATH;
		procname = FLUENT_PATH;
		fulljname = copyparams->bDATA_PATH;
		fulljname.Append(jname);
	} else {
		err->AddError("CreateEnv::BASIC validation error - check if the script is complete");
		return FAIL;
	}

	if(copyparams->ValidateParams(PARAMS))	{
		COMMAND_LINE = copyparams->bCOMMAND_LINE;
		parname = COMMAND_LINE; // s¹ jakieœ parametry, jesli nie to domyœlny z konstruktora
	} else {
		COMMAND_LINE = " 3ddp -g -i ";
		COMMAND_LINE.Append(fulljname);	// dodawanie pliku journal do uruchomienia
		parname = COMMAND_LINE;
	}
	// tu walidacja plików case i wynkow, jeœli ich nie ma to nic nie robimy
// usuwanie podwjnych // tylko do wpisu w pliku scm i journal
	RemoveDoubleSlash(copyparams->bDATA_PATH);

	CW2A pszA(fulljname);
	if(fopen_s(&fid,pszA,"w+"))	{
		err->AddError("CreateEnv::Cant open journal file");
		return FAIL;
	}
	fprintf(fid,"(load \"%s%s\")",copyparams->bDATA_PATH,"_starter.scm");	// starter.scm - domyslna nazwa pliku scm uruchamianego przez journal
	fclose(fid);
/* tworzenie scm dla:
						velocity_inlet
						bez energii
						dwa sk³adniki (udzia³ 0 do 1)
						podane na jedno wejscie
						jedno wyjœcie
						*/
	/// \warning W tym przypadku dopuszczalne s¹ wpisy w assign nie dubluj¹ce siê (czyli na wejœciu zawsze kilka komponentów ale o udziale 0-1)
	/// \todo Dodaæ funkcê w której moznaby zdefinowaæ tak¿e modele
/*	if (copyparams->ValidateParams(PROBLEM0)==OK) // reaktor-artykul-lam-zmiana-URANS-kwas-faza-ciagla_0_133s.cas
	{
		if (strcmp(copyparams->bSUBPROCNAME,"fl12016s.exe")!=0)
		{
			err->AddError("CreateEnv::No valid version of Fluent found");
			return FAIL;
		} else {
			ptmp = copyparams->bDATA_PATH;
			ptmp.Append(L"_starter.scm");
			CW2A pszB(ptmp);
			if(fopen_s(&fid,pszB,"w+"))	{
				err->AddError("CreateEnv::Cant open scm file");
				return FAIL;
			}
			fulloutname = copyparams->bDATA_PATH;
			fulloutname.Append(L"_out.prof");
			fprintf(fid,"(ti-menu-load-string \"!del %S\")\n",fulloutname);	// kasowanie starego pliku
			ptmp = copyparams->bDATA_PATH;
			ptmp.Append(copyparams->bCASE_NAME);
			// fluent_scie¿ki-postepowania.txt
			if (copyparams->ValidateParams(ENERGY)!=OK)
			{
				fprintf(fid,"(ti-menu-load-string \"file/read-case-data %S\")\n",ptmp);
				// odczytujê nazwê powierzchni skojarzonego z danym materia³em rozproszonym
				tmpmat = copyparams->bCOMPONENTS.GetSubString(1,COMPONENTS_NAZWA);	// nazwa materia³u rozproszonego
				int line = copyparams->bASSIGNS.GetLineIndex(tmpmat,ASSIGN_COMPONENTS_NAZWA); //numer lini w assigns zawieraj¹cy nazwê materia³u - zak³¹dam ¿e nie ma niejednosznacznoœci - jeden materia³ do jednego wejscia przypisany
				if(line<0) {err->AddError("CreateEnv::Problem in ASSIGNS");	return FAIL;}
				tmpsurf = copyparams->bASSIGNS.GetSubString(line,ASSIGN_SURF_NAME);	// nazwa powierzchni skojarzona z materia³em
				tmpin = copyparams->bASSIGNS.GetSubString(line,ASSIGN_INPUTID);		// index wejscia w ASPENIE do którego pod³¹czony jest dany materia³ (numeracja od 1!!)
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s\")\n",tmpsurf,"mixture");

				// dla rozproszonej wej1
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal1,atoi(tmpin)-1);
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFRACTION,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					paramVal1,
					"no",
					paramVal2);

				tmpmat = copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_NAZWA);	// nazwa materia³u nierozproszonego
				
				// dla nie rozproszonej wej1 
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					paramVal2);

				// odczytujê nazwê powierzchni skojarzonego z danym materia³em nierozproszonym
				tmpmat = copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_NAZWA);	// nazwa materia³u nierozproszonego
				line = copyparams->bASSIGNS.GetLineIndex(tmpmat,ASSIGN_COMPONENTS_NAZWA); //numer lini w assigns zawieraj¹cy nazwê materia³u - zak³¹dam ¿e nie ma niejednosznacznoœci - jeden materia³ do jednego wejscia przypisany
				if(line<0) {err->AddError("CreateEnv::Problem in ASSIGNS");	return FAIL;}
				tmpsurf = copyparams->bASSIGNS.GetSubString(line,ASSIGN_SURF_NAME);	// nazwa powierzchni skojarzona z materia³em
				tmpin = copyparams->bASSIGNS.GetSubString(line,ASSIGN_INPUTID);		// index wejscia w ASPENIE do którego pod³¹czony jest dany materia³ (numeracja od 1!!)
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s\")\n",tmpsurf,"mixture");

				// dla rozproszonej wej2
				tmpmat = copyparams->bCOMPONENTS.GetSubString(1,COMPONENTS_NAZWA);	// nazwa materia³u rozproszonego
//				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal1,atoi(tmpin)-1);
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFRACTION,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					0.0,
					"no",
					paramVal2);

				// dla nie rozproszonej wej2 
				tmpmat = copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_NAZWA);	// nazwa materia³u nierozproszonego
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					paramVal2);

				fprintf(fid,"(ti-menu-load-string \"solve/iterate %d\")\n",copyparams->bNUMOFITER);
				etmp = copyparams->bEXPORTS.GetSubString(0,EXPORT_NAME);
				for(a=1;a<copyparams->bEXPORTS.GetIle();a++)	{
					etmp.Append(L" ");
					etmp.Append(copyparams->bEXPORTS.GetSubString(a,EXPORT_NAME));
				}
				fprintf(fid,"(ti-menu-load-string \"file/write-profile %S %s , %S\")\n",fulloutname,copyparams->bOUTPUT_SURFACE.DATA_CONTAINER[0],etmp);
				fprintf(fid,"(ti-menu-load-string \"/\")\n");
				fprintf(fid,"(ti-menu-load-string \"exit yes\")");
			} 
			else {	// nie ma energii zaimplmentnowanej dla tego przypadku
				err->AddError("CreateEnv::Energy case not implemented yet");
				return FAIL;
			}
		} // if da w³aœciwej wersji fluenta
		fclose(fid);
		return OK;
	} // if problem0
*/
	/* tworzenie scm dla:
						velocity_inlet
						bez energii
						dwa sk³adniki (udzia³ 0 do 1)
						podane na jedno wejscie
						jedno wyjœcie
						model eulera!!!
						*/
	/// \warning W tym przypadku dopuszczalne s¹ wpisy w assign nie dubluj¹ce siê (czyli na wejœciu zawsze kilka komponentów ale o udziale 0-1)
	if (copyparams->ValidateParams(PROBLEM0)==OK) // reaktor-k-eps-URANS-amoniak-F_ciagla-new-22-00530.cas - model eulera
	{
		if (strcmp(copyparams->bSUBPROCNAME,"fl12016s.exe")!=0 && strcmp(copyparams->bSUBPROCNAME,"fl1214s.exe")!=0)
		{
			err->AddError("CreateEnv::No valid version of Fluent found");
			return FAIL;
		} else {
			ptmp = copyparams->bDATA_PATH;
			ptmp.Append(L"_starter.scm");
			CW2A pszB(ptmp);
			if(fopen_s(&fid,pszB,"w+"))	{
				err->AddError("CreateEnv::Cant open scm file");
				return FAIL;
			}
			fulloutname = copyparams->bDATA_PATH;
			fulloutname.Append(L"_out.prof");
			fprintf(fid,"(ti-menu-load-string \"!del %S\")\n",fulloutname);	// kasowanie starego pliku
			ptmp = copyparams->bDATA_PATH;
			ptmp.Append(copyparams->bCASE_NAME);
			// fluent_scie¿ki-postepowania2.txt
			if (copyparams->ValidateParams(ENERGY)!=OK)
			{
				fprintf(fid,"(ti-menu-load-string \"file/read-case-data %S\")\n",ptmp);
				// odczytujê nazwê powierzchni skojarzonego z danym materia³em rozproszonym
				tmpmat = copyparams->bCOMPONENTS.GetSubString(1,COMPONENTS_NAZWA);	// nazwa materia³u rozproszonego
				int line = copyparams->bASSIGNS.GetLineIndex(tmpmat,ASSIGN_COMPONENTS_NAZWA); //numer lini w assigns zawieraj¹cy nazwê materia³u - zak³¹dam ¿e nie ma niejednosznacznoœci - jeden materia³ do jednego wejscia przypisany
				if(line<0) {err->AddError("CreateEnv::Problem in ASSIGNS");	return FAIL;}
				tmpsurf = copyparams->bASSIGNS.GetSubString(line,ASSIGN_SURF_NAME);	// nazwa powierzchni skojarzona z materia³em
				tmpin = copyparams->bASSIGNS.GetSubString(line,ASSIGN_INPUTID);		// index wejscia w ASPENIE do którego pod³¹czony jest dany materia³ (numeracja od 1!!)
//				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s\")\n",tmpsurf,"mixture");

				// dla rozproszonej wej1
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal1,atoi(tmpin)-1);
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFRACTION,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f %s %s %20.15f %s %20.15f %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					paramVal1,
					"yes",
					"no",
					0.01,
					"no",
					0.01,
					"no",
					paramVal2);

				tmpmat = copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_NAZWA);	// nazwa materia³u nierozproszonego
				
				// dla nie rozproszonej wej1 
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f %s %s %20.15f %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					paramVal2,
					"yes",
					"no",
					0.0,
					"no",
					0.0);

				// odczytujê nazwê powierzchni skojarzonego z danym materia³em ci¹g³ym
				tmpmat = copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_NAZWA);	// nazwa materia³u nierozproszonego
				line = copyparams->bASSIGNS.GetLineIndex(tmpmat,ASSIGN_COMPONENTS_NAZWA); //numer lini w assigns zawieraj¹cy nazwê materia³u - zak³¹dam ¿e nie ma niejednosznacznoœci - jeden materia³ do jednego wejscia przypisany
				if(line<0) {err->AddError("CreateEnv::Problem in ASSIGNS");	return FAIL;}
				tmpsurf = copyparams->bASSIGNS.GetSubString(line,ASSIGN_SURF_NAME);	// nazwa powierzchni skojarzona z materia³em
				tmpin = copyparams->bASSIGNS.GetSubString(line,ASSIGN_INPUTID);		// index wejscia w ASPENIE do którego pod³¹czony jest dany materia³ (numeracja od 1!!)
//				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s\")\n",tmpsurf,"mixture");

				// dla rozproszonej wej2
				tmpmat = copyparams->bCOMPONENTS.GetSubString(1,COMPONENTS_NAZWA);	// nazwa materia³u rozproszonego
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal1,atoi(tmpin)-1);
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFRACTION,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f %s %s %20.15f %s %20.15f %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					paramVal1,
					"yes",
					"no",
					0.0,
					"no",
					0.0,
					"no",
					paramVal2);
				

				// dla nie rozproszonej wej2 
				tmpmat = copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_NAZWA);	// nazwa materia³u nierozproszonego
				ret = Parameters.GetParameterP(tmpmat,PARAM_MOLEFLOW,paramVal2,atoi(tmpin)-1);
				if(ret==FAIL) {err->AddError("CreateEnv::Problem with material name");	return FAIL;}
				fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s %s %s %s %s %s %s %20.15f %s %s %20.15f %s %20.15f\")\n",
					tmpsurf,
					tmpmat,
					"no",
					"no",
					"yes",
					"yes",
					"no",
					paramVal2,
					"yes",
					"no",
					0.01,
					"no",
					0.01);

				if(copyparams->sNUMOFTIMESTEPS==FALSE)	// czyli user nie poda³ iloœci kroków - inicjalozacja tylko porzez solve/iterate
					fprintf(fid,"(ti-menu-load-string \"solve/iterate %d\")\n",copyparams->bNUMOFITER);
				else
					fprintf(fid,"(ti-menu-load-string \"solve/dual-time-iterate %d %d\")\n",copyparams->bNUMOFTIMESTEPS,copyparams->bNUMOFITER);
				etmp = copyparams->bEXPORTS.GetSubString(0,EXPORT_NAME);
				for(a=1;a<copyparams->bEXPORTS.GetIle();a++)	{
					etmp.Append(L" ");
					etmp.Append(copyparams->bEXPORTS.GetSubString(a,EXPORT_NAME));
				}
				fprintf(fid,"(ti-menu-load-string \"file/write-profile %S %s , %S\")\n",fulloutname,copyparams->bOUTPUT_SURFACE.DATA_CONTAINER[0],etmp);
				fprintf(fid,"(ti-menu-load-string \"/\")\n");
				fprintf(fid,"(ti-menu-load-string \"exit yes\")");
			} 
			else {	// nie ma energii zaimplmentnowanej dla tego przypadku
				err->AddError("CreateEnv::Energy case not implemented yet");
				return FAIL;
			}
		} // if da w³aœciwej wersji fluenta
		fclose(fid);
		return OK;
	} // if problem0


/*	tworzenie scm dla:	mass_flow_inlet
						wybór energii
						jedno wejœcie
						bez mieszaniny
						fluent: fl12016s.exe
						*/
	if(	strcmp(copyparams->bBOUND_COND,"mass-flow-inlet")==0 &&
		copyparams->bINPUT_SURFACE.GetIle()==1 &&
		copyparams->bCOMPONENTS.GetIle()==0 )
	{
		ptmp = copyparams->bDATA_PATH;
		ptmp.Append(L"_starter.scm");
		CW2A pszB(ptmp);
		if(fopen_s(&fid,pszB,"w+"))	{
			err->AddError("CreateEnv::Cant open scm file");
			return FAIL;
		}
		fulloutname = copyparams->bDATA_PATH;
		fulloutname.Append(L"_out.prof");
		fprintf(fid,"(ti-menu-load-string \"!del %S\")\n",fulloutname);	// kasowanie starego pliku
		ptmp = copyparams->bDATA_PATH;
		ptmp.Append(copyparams->bCASE_NAME);
		fprintf(fid,"(ti-menu-load-string \"file/read-case-data %S\")\n",ptmp);
		fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/zone-type %s %s\")\n",copyparams->bINPUT_SURFACE.DATA_CONTAINER[0],copyparams->bBOUND_COND);
		if(strcmp(copyparams->bENERGY_EQ,"yes")==0)	// w zale¿noœci czy energia jest czy nie w³¹zona s¹ ró¿ne drogi przejœcia przez parametry wejœciowe
			fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/mass-flow-inlet %s yes yes no %20.15f no %f no 0 yes yes no 0 no 0 no 1\")\n",copyparams->bINPUT_SURFACE.DATA_CONTAINER[0],totalflow,temperature);
		else
			fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/mass-flow-inlet %s yes no %f no 0 yes yes no 0 no 0 no 1\")\n",copyparams->bINPUT_SURFACE.DATA_CONTAINER[0],totalflow);

		if(copyparams->sNUMOFTIMESTEPS==FALSE)	// czyli user nie poda³ iloœci kroków - inicjalozacja tylko porzez solve/iterate
			fprintf(fid,"(ti-menu-load-string \"solve/iterate %d\")\n",copyparams->bNUMOFITER);
		else
			fprintf(fid,"(ti-menu-load-string \"solve/dual-time-iterate %d %d\")\n",copyparams->bNUMOFTIMESTEPS,copyparams->bNUMOFITER);
		etmp = copyparams->bEXPORTS.DATA_CONTAINER[0];
		for(a=1;a<copyparams->bEXPORTS.GetIle();a++)	{
			etmp.Append(L" ");
			etmp.Append(copyparams->bEXPORTS.DATA_CONTAINER[a]);
		}
		fprintf(fid,"(ti-menu-load-string \"file/write-profile %S %s , %S\")\n",fulloutname,copyparams->bOUTPUT_SURFACE.DATA_CONTAINER[0],etmp);
		fprintf(fid,"(ti-menu-load-string \"/\")\n");
		fprintf(fid,"(ti-menu-load-string \"exit yes\")");
		fclose(fid);
		return OK;
	} 

/*	tworzenie scm dla:	velocity_inlet
						wybór energii
						jedno wejœcie
						musi byc zdefiniowany choc jeden skladnik (gestosc)
						fluent: fl12016s.exe
						*/
	if(	strcmp(copyparams->bBOUND_COND,"velocity-inlet")==0 &&
		copyparams->bINPUT_SURFACE.GetIle()==1 &&
		copyparams->bCOMPONENTS.GetIle()==1 )
	{
		ptmp = copyparams->bDATA_PATH;
		ptmp.Append(L"_starter.scm");
		CW2A pszB(ptmp);
		if(fopen_s(&fid,pszB,"w+"))	{
			err->AddError("CreateEnv::Cant open scm file");
			return FAIL;
		}
		fulloutname = copyparams->bDATA_PATH;
		fulloutname.Append(L"_out.prof");
		fprintf(fid,"(ti-menu-load-string \"!del %S\")\n",fulloutname);	// kasowanie starego pliku
		ptmp = copyparams->bDATA_PATH;
		ptmp.Append(copyparams->bCASE_NAME);
		fprintf(fid,"(ti-menu-load-string \"file/read-case-data %S\")\n",ptmp);
		fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/zone-type %s %s\")\n",copyparams->bINPUT_SURFACE.DATA_CONTAINER[0],copyparams->bBOUND_COND);
		if(strcmp(copyparams->bENERGY_EQ,"yes")==0)	// w zale¿noœci czy energia jest czy nie w³¹zona s¹ ró¿ne drogi przejœcia przez parametry wejœciowe
			fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s yes yes no %20.15f yes no 0 no 0 no 1 no %f\")\n",copyparams->bINPUT_SURFACE.DATA_CONTAINER[0],totalflow,temperature);
		else
			fprintf(fid,"(ti-menu-load-string \"define/boundary-conditions/velocity-inlet %s yes yes no %20.15f yes no 0 no 0 no 1\")\n",copyparams->bINPUT_SURFACE.DATA_CONTAINER[0],totalflow);

		if(copyparams->sNUMOFTIMESTEPS==FALSE)	// czyli user nie poda³ iloœci kroków - inicjalozacja tylko porzez solve/iterate
			fprintf(fid,"(ti-menu-load-string \"solve/iterate %d\")\n",copyparams->bNUMOFITER);
		else
			fprintf(fid,"(ti-menu-load-string \"solve/dual-time-iterate %d %d\")\n",copyparams->bNUMOFTIMESTEPS,copyparams->bNUMOFITER);
		etmp = copyparams->bEXPORTS.DATA_CONTAINER[0];
		for(a=1;a<copyparams->bEXPORTS.GetIle();a++)	{
			etmp.Append(L" ");
			etmp.Append(copyparams->bEXPORTS.DATA_CONTAINER[a]);
		}
		fprintf(fid,"(ti-menu-load-string \"file/write-profile %S %s , %S\")\n",fulloutname,copyparams->bOUTPUT_SURFACE.DATA_CONTAINER[0],etmp);
		fprintf(fid,"(ti-menu-load-string \"/\")\n");
		fprintf(fid,"(ti-menu-load-string \"exit yes\")");
		fclose(fid);
		return OK;
	}
	err->AddError("CreateEnv::No valid boundary found in script or not alloved combination of phases and boundary conditions"); // tu musi byc lepszy opis bo to moze byc czesty blad
	return FAIL;
}

BOOL C_myRunProcess::ImportData(void)
/// \retval FAIL Jeœli b³¹d - nie mo¿na otworzyæ pliku lub zaimportowaæ wymaganych danych lub u¿ytkownik poda³ w exports z³e s³owo kluczowe okreœlaj¹ce typ parametru
/// \retval OK Jeœli sukces
{
	FILE *fid;
	unsigned int a;
	char ch;
	char* cont;
	char buff[MAX_STRING];
	fpos_t *poz=NULL;
	BOOL znalezione;
	double tmp,suma;
	unsigned int ile;
	double SRtmp, SUMtmp;
	char *tmpname, *tmppar; // nazwa komponentu oraz nazwa parametru dla danej linii
	nazwy_parametrow par;
	
//fulloutname = "j:\\ASPEN_PROJECT\\FluentSol\\fluentdata\\ruratest";
/// \bug poni¿szy fragment moze nie dzialac gdy zmieni siê ilosc parametrów odczytywanych - przydatne tylko gdy zmienia sie ich konfiguracja	
/// \code	
	SUM.ClearAll();
	SR.ClearAll();
/// \endcode
	CW2A pszA(fulloutname);
	if(fopen_s(&fid,pszA,"r+"))	{
		err->AddError("ImportData::Cant open result dat file");
		return FAIL;
	}
	poz = new fpos_t[copyparams->bEXPORTS.GetIle()];
	for(a=0;a<copyparams->bEXPORTS.GetIle();a++)	{	// po wszystkich parametrach
		cont = copyparams->bEXPORTS.GetSubString(a,EXPORT_NAME);
		znalezione = FALSE;
		while(!feof(fid))	{				// po ca³ym pliku
			ch = (char)fgetc(fid);			// jeden znak
			if(ch==cont[0])	{				// jeœli jest taki sam jak pierwszy znak to sprawdzamy ca³oœæ
				fseek(fid,-1,SEEK_CUR);		// cofamy o jeden zeby zniwelowac fgetc
				fgets(buff, strlen(cont)+1, fid);
				if(strcmp(buff,cont)==0) {	// to samo
					fgetpos(fid,&poz[a]);	// zapamiêtujemy pozycjê
					znalezione = TRUE;
					break;
				}
			}
		}
		if(znalezione==FALSE)	{	// problem, nie znalezliœmy a powinno byc
			fclose(fid);
			SAFE_DELETE_ARRAY(poz);
			err->AddError("ImportData::Nothing imported");
			return FAIL;
		}  
	}

// tu mamy w tablicy pozycje elemntów zaraz po tekscie oznaczaj¹cym typ
// rejestruje wszystkie zwi¹zki w zmiennych /sum i SR
	for (a=0;a<copyparams->bCOMPONENTS.GetIle();a++)	// po wszystkich komponentach
	{
		tmpname = copyparams->bCOMPONENTS.GetSubString(a,COMPONENTS_NAZWA);	// pobieram nazwe komponentu
		SUM.RegisterComponent(tmpname);	// i go rejestruje
		SR.RegisterComponent(tmpname);	// 
	}
	for(a=0;a<copyparams->bEXPORTS.GetIle();a++)	{	// po wszystkich parametrach (liniach w polu exports)
		suma = 0;
		ile = 0;
		fsetpos(fid,&poz[a]);				// na pierwsze dane
		while(fscanf_s(fid,"%lf",&tmp)!=0)	{
			suma+=tmp;
			ile++;
		}
		SRtmp = suma/ile;
		SUMtmp = suma;
/// \bug nie koniecznie to musi dzia³aæ dla kilku wyjœæ ze wzgledu na ró¿n¹ iloœæ elementów powierzchni
/// \code
		ile_danych = ile;	// ta wartosc bedzie taka sama dla wszystkich wielkosci, potrzzeban bo niektóre s¹ œredni¹ a niektóre sum¹
/// \endcode
		tmpname = copyparams->bEXPORTS.GetSubString(a,EXPORT_COMPONENTS_NAZWA);	// pobieram nazwê zwi¹zku z kolejnej lini wpisu w exports
		tmppar = copyparams->bEXPORTS.GetSubString(a,EXPORT_PROP);	// pobieram co jest zczytywane w danej lini (temperatura, itp)
		// konwersja z wpisów u¿ytkownika na w³aœciwy format akeptowalny przez klasê C_Parameters_Container
		if (strcmp(tmppar,"TEMPERATURE")==0 || strcmp(tmppar,"temperature")==0)
			par = PARAM_TEMPERATURE;
		else
			if (strcmp(tmppar,"PRESSURE")==0 || strcmp(tmppar,"pressure")==0)
				par = PARAM_PRESSURE;
			else
				if (strcmp(tmppar,"TOTALFLOW")==0 || strcmp(tmppar,"totalflow")==0)
					par = PARAM_MOLEFLOW;
				else
					if (strcmp(tmppar,"FRACTION")==0 || strcmp(tmppar,"fraction")==0)
						par = PARAM_MOLEFRACTION;
					else
						return FAIL;
	
		if (strcmp(tmpname,"ALL")==0 || strcmp(tmpname,"all")==0)	// czyli wpisujemy do wszystkich komponentów
			for (int b=0;b<SUM.GetNumOfComponents();b++)
			{
/// domyœlnie u¿ywam metod z klasy podrzêdnej C_Parameter_Container bo tylko jedno wyjœcie 
/// \code
				SUM.AssignParamToComp(b,par,SUMtmp);
				SR.AssignParamToComp(b,par,SRtmp);
/// \endcode
			}			
		else	// wpisujemy tylko do wybranego
		{
			SUM.AssignParamToComp(tmpname,par,SUMtmp);
			SR.AssignParamToComp(tmpname,par,SRtmp);
		}

	}

	fclose(fid);

	SAFE_DELETE_ARRAY(poz);
	return OK;
}

// pobiera parametry z klasy

void C_myRunProcess::GetParams(double& temp, double *fract, double& flow, double& pres)
{
/*	unsigned int a;

	double tfratio;
	tfratio = atof(copyparams->bMOLEPERKG.DATA_CONTAINER[0]);

	// wszystko przepisuje i dopiero w razie czego to zamieniam na to z fluenta
	temp = temperature;
	memcpy_s(fract,MAX_EXPORTS*sizeof(double),fraction,MAX_EXPORTS*sizeof(double));
	/// \bug Tu jest chyba b³¹d bo jeœli w skrypcie nie bêdzie odczytu Flow to tu mog¹ pojawiæ siê z³e jednostki
	flow = totalflow;
	pres = pressure;
	for(a=0;a<copyparams->bEXPORTS.GetIle();a++)	{
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,EXPORT_PROP),"temperature")==0)	{		// to znaczy ¿e mamy z fluenta ten parametr
			temp = SR[a]; continue; }
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,EXPORT_PROP),"totalflow")==0)			// to znaczy ¿e mamy z fluenta ten parametr
		{
			if(strcmp(copyparams->bBOUND_COND,"mass-flow-inlet")==0)
			{
				flow = SUM[a]*tfratio;	// wyjscie w kg/sec, przeliczone ma mol/sec
				continue;
			}
			if(copyparams->ValidateParams(VELOCITY_INLET))
			{
				double area = atof(copyparams->bINPUT_SURFACE.GetSubString(0,SURF_AREA));
				double density = atof(copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_GESTOSC));
				flow = SR[a]*density*area*tfratio;	// wyjscie w m/sec przeliczone na mol/sec
				continue;
			}
		}
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,EXPORT_PROP),"pressure")==0)	{		// to znaczy ¿e mamy z fluenta ten parametr
			pres = SR[a]; continue; }
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,EXPORT_PROP),"fraction")==0)	{		// to znaczy ¿e mamy z fluenta ten parametr
			fract[a] = SR[a]; continue; }
	}
*/
}

/*
BOOL C_myRunProcess::GetParams(SAFEARRAY *temperature, SAFEARRAY *fraction, SAFEARRAY *flow, SAFEARRAY *pressure, SAFEARRAY *compNames)
/// \retval FAIL Jeœli Jakaœ funkcja podrzêdna zwóci FAIL (parametr nie znaleziony - raczej wszystko mo¿liwe na etapie dewelopingu ni¿ dzia³ania programu) lub te¿ nie znaleziono kombinacji w³aœciwej w ValidateParams. W tym ostanim przypadku niektóre parametry mog¹ mieæ nieokreslone wartoœci
/// \retval OK Jeœli sukces
{
	LONG u,l,x;	// ile componentów
	UINT dim;
	LONG a;
	CComBSTR tmp;
	double val,tfratio,valsum;
	LONG index = 0;
	BOOL ret;
	BOOL done = FAIL;	// ok jeœli zostanie wykoana jakaœ konwersja, czyli gdy wartoœæ przep³ywu jest poprawna	
	dim = SafeArrayGetDim(compNames);
	SafeArrayGetUBound(compNames,1,&u);
	SafeArrayGetLBound(compNames,1,&l);
	// pierwszy etap - przepisanie wszystkiego ze struktury C_Parameter_Container do SAFEARRAY, w drugim etapie dopiero zastêpujemy tymi z fluenta
	for(a=l;a<=u;a++)	// po komponentach
	{
		SafeArrayGetElement(compNames, &a, &tmp);
		CW2A pszB(tmp);	// nazwa komponentu

// temepratura
		SafeArrayGetUBound(temperature,1,&x);
		ret = SR.GetParameter(pszB,PARAM_TEMPERATURE,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy. Przepisujemy domyœlnie z wejscia 0
			ret = Parameters.GetParameterP(pszB,PARAM_TEMPERATURE,val,0);
			if(ret==FAIL) return FAIL;
		} else
			SR.GetParameter(pszB,PARAM_TEMPERATURE,val);	// z fluenta
		if(a>x) // to jest aby zachowaæ rozmiary tablic takie jak podaje aspen - np dla kilku komponentow ta sama wartosc jest trzymana w jednej komórce
			SafeArrayPutElement(temperature,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayPutElement(temperature,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
// cisnienie
		SafeArrayGetUBound(pressure,1,&x);
		ret = SR.GetParameter(pszB,PARAM_PRESSURE,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy
			ret = Parameters.GetParameterP(pszB,PARAM_PRESSURE,val,0);
			if(ret==FAIL) return FAIL;
		} else
			SR.GetParameter(pszB,PARAM_PRESSURE,val);	// z fluenta
		if(a>x)
			SafeArrayPutElement(pressure,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayPutElement(pressure,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
// fraction
		SafeArrayGetUBound(fraction,1,&x);
		ret = SR.GetParameter(pszB,PARAM_MOLEFRACTION,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy
			ret = Parameters.GetParameterP(pszB,PARAM_MOLEFRACTION,val,0);
			if(ret==FAIL) return FAIL;
		} else
			SR.GetParameter(pszB,PARAM_MOLEFRACTION,val);	// z fluenta
		if(ret==FAIL) return FAIL;
		if(a>x)
			SafeArrayPutElement(fraction,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayPutElement(fraction,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
// flow
		SafeArrayGetUBound(flow,1,&x);
		ret = Parameters.GetParameterP(pszB,PARAM_MOLEPERKG,tfratio,0);
		ret = SR.GetParameter(pszB,PARAM_MOLEFLOW,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy
			ret = Parameters.GetParameter(pszB,PARAM_MOLEFLOW,val);
			valsum = val;
			if(ret==FAIL) return FAIL;
		} else	{
			SR.GetParameter(pszB,PARAM_MOLEFLOW,val);	// s¹ potrzebne 2
			SUM.GetParameter(pszB,PARAM_MOLEFLOW,valsum);
		}

		// -----------------------------------------------------------------
		if(copyparams->ValidateParams(MASS_FLOW_INLET))	{
			val = valsum*tfratio;	
			done = OK;
		}
		// -----------------------------------------------------------------
		if(copyparams->ValidateParams(VELOCITY_INLET))	{
			/// \bug Problem dla wiêkszej iloœci wyjœæ 
			double area = atof(copyparams->bOUTPUT_SURFACE.GetSubString(0,SURF_AREA));	// pow
			double density;
			Parameters.GetParameterP(pszB,PARAM_DENSITY,density,0);
			val =  val*tfratio*density*area;	
			done = OK;
		}
		if(a>x)
			SafeArrayPutElement(flow,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayPutElement(flow,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
		if(ret==FAIL || done==FAIL) return FAIL;
	}	// koniec przepisywania, pêtla po materia³ach
	return OK;

}

*/

/*!
	 Lekko zmieniona wersja - dzia³a przy za³o¿eniu ¿e dla kilku komponentów wszystkie struktury wyjœciowe bêd¹ mia³y rozmiar iloœci komponentów i parametry strumieni odpowiednio wpisane. 
	 Na przyk³ad pomimo ze jest jedna temperatura do T bedzie mia³o rozmiar [2] i dwa razy wpisan¹ t¹ sam¹ temperaturê zgodnie z kolejnoœci¹ faz w compNames.
	 
*/
BOOL C_myRunProcess::GetParams(SAFEARRAY *temperature, SAFEARRAY *fraction, SAFEARRAY *flow, SAFEARRAY *pressure, SAFEARRAY *compNames)
/// \retval FAIL Jeœli Jakaœ funkcja podrzêdna zwóci FAIL (parametr nie znaleziony - raczej wszystko mo¿liwe na etapie dewelopingu ni¿ dzia³ania programu) lub te¿ nie znaleziono kombinacji w³aœciwej w ValidateParams. W tym ostanim przypadku niektóre parametry mog¹ mieæ nieokreslone wartoœci
/// \retval OK Jeœli sukces
{
	LONG u,l;	// ile componentów
	UINT dim;
	LONG a;
	CComBSTR tmp;
	double val,tfratio,valsum;
	LONG index = 0;
	BOOL ret;
	BOOL done = FAIL;	// ok jeœli zostanie wykoana jakaœ konwersja, czyli gdy wartoœæ przep³ywu jest poprawna	
	dim = SafeArrayGetDim(compNames);
	SafeArrayGetUBound(compNames,1,&u);
	SafeArrayGetLBound(compNames,1,&l);
	// pierwszy etap - przepisanie wszystkiego ze struktury C_Parameter_Container do SAFEARRAY, w drugim etapie dopiero zastêpujemy tymi z fluenta
	outParameters.ClearAllP();
	for(a=l;a<=u;a++)	// po komponentach
	{
		SafeArrayGetElement(compNames, &a, &tmp);
		CW2A pszB(tmp);	// nazwa komponentu
		ret=outParameters.RegisterComponentP(pszB,0);	// rejestracja komponentu w tymczasowej zmiennej uzywanej tylko do zrzucania danych wyjsciowych na dysk

// temepratura
		ret = SR.GetParameter(pszB,PARAM_TEMPERATURE,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy. Przepisujemy domyœlnie z wejscia 0
			ret = Parameters.GetParameterP(pszB,PARAM_TEMPERATURE,val,0);
			if(ret==FAIL) return FAIL;
		} else
			SR.GetParameter(pszB,PARAM_TEMPERATURE,val);	// z fluenta
		ret=outParameters.AssignParamToCompP(pszB,PARAM_TEMPERATURE,val,0);
		SafeArrayPutElement(temperature,&index,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
// cisnienie
		ret = SR.GetParameter(pszB,PARAM_PRESSURE,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy
			ret = Parameters.GetParameterP(pszB,PARAM_PRESSURE,val,0);
			if(ret==FAIL) return FAIL;
		} else
			SR.GetParameter(pszB,PARAM_PRESSURE,val);	// z fluenta
		ret=outParameters.AssignParamToCompP(pszB,PARAM_PRESSURE,val,0);
		SafeArrayPutElement(pressure,&index,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
// fraction
		ret = SR.GetParameter(pszB,PARAM_MOLEFRACTION,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy
			ret = Parameters.GetParameterP(pszB,PARAM_MOLEFRACTION,val,0);
			if(ret==FAIL) return FAIL;
		} else
			SR.GetParameter(pszB,PARAM_MOLEFRACTION,val);	// z fluenta
		if(ret==FAIL) return FAIL;
		ret=outParameters.AssignParamToCompP(pszB,PARAM_MOLEFRACTION,val,0);
		SafeArrayPutElement(fraction,&index,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
// flow
		ret = Parameters.GetParameterP(pszB,PARAM_MOLEPERKG,tfratio,0);
		ret = SR.GetParameter(pszB,PARAM_MOLEFLOW,val);
		if(ret==FAIL)	{	// czyli najprawdopodbniej nie zostalo zainicjalizowane albo inny b³¹d - bierzemy z wejœcia i przepisujemy
			ret = Parameters.GetParameter(pszB,PARAM_MOLEFLOW,val);
			valsum = val;
			if(ret==FAIL) return FAIL;
		} else	{
			SR.GetParameter(pszB,PARAM_MOLEFLOW,val);	// s¹ potrzebne 2
			SUM.GetParameter(pszB,PARAM_MOLEFLOW,valsum);
		}

		// -----------------------------------------------------------------
		if(copyparams->ValidateParams(MASS_FLOW_INLET))	{
			val = valsum*tfratio;	
			done = OK;
		}
		// -----------------------------------------------------------------
		if(copyparams->ValidateParams(VELOCITY_INLET))	{
			/// \bug Problem dla wiêkszej iloœci wyjœæ 
			double area = atof(copyparams->bOUTPUT_SURFACE.GetSubString(0,SURF_AREA));	// pow
			double density;
			Parameters.GetParameterP(pszB,PARAM_DENSITY,density,0);
			val =  val*tfratio*density*area;	
			done = OK;
		}
		ret=outParameters.AssignParamToCompP(pszB,PARAM_MOLEFLOW,val,0);
		SafeArrayPutElement(flow,&index,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
		if(ret==FAIL || done==FAIL) return FAIL;

		index++;	// tablice wejœciowe mog¹ byæ ró¿nie numerowane(indexy) ale te wyjsciowe s¹ zawsze od 0
	}	// koniec przepisywania, pêtla po materia³ach
	return OK;

}

// wpisuje parametry do klasy
BOOL C_myRunProcess::PutParams(double temp, double *fract, double flow, double pres)
/// \retval OK Zawsze
{
	double tfratio;
	tfratio = atof(copyparams->bMOLEPERKG.DATA_CONTAINER[0]);	// zmienic!!!

	temperature = temp;
	memcpy_s(fraction,MAX_EXPORTS*sizeof(double),fract,MAX_EXPORTS*sizeof(double));
	totalflow = flow;	// jakby zaden if nie wyszedl
	if(strcmp(copyparams->bBOUND_COND,"MASS-FLOW-INLET")==0)
		totalflow = flow/tfratio;	// z aspena wychodza mole/sec, tu przeliczenie na kg/sec
	if(copyparams->ValidateParams(VELOCITY_INLET))	{
		double area = atof(copyparams->bINPUT_SURFACE.GetSubString(0,SURF_AREA));
		double density = atof(copyparams->bCOMPONENTS.GetSubString(0,COMPONENTS_GESTOSC));
		totalflow =  (flow/tfratio)/(density*area);	// przeliczenie z moli/s na m/s
	}
	pressure = pres;
	paramsval = TRUE;
	return OK;
}

BOOL C_myRunProcess::PutParams(SAFEARRAY *temperature, SAFEARRAY *fraction, SAFEARRAY *flow, SAFEARRAY *pressure, SAFEARRAY *compNames,unsigned int inputID)
/// \retval FAIL Jeœli Jakaœ funkcja podrzêdna zwóci FAIL (rejestracja parmaetru albo parametr nie znaleziony - raczej wszystko mo¿liwe na etapie dewelopingu ni¿ dzia³ania programu), lub te¿ nie znaleziono kombinacji w³aœciwej w ValidateParams. W tym ostanim przypadku niektóre parametry mog¹ mieæ nieokreslone wartoœci
/// \retval OK Jeœli sukces
{
	LONG u,l,x;	// ile componentów
	UINT dim;
	LONG a;
	CComBSTR tmp;
	double val,tfratio;
	LONG index = 0;
	BOOL ret;
	unsigned int compid = 0;
	int line;
	char* tmpmat;
	BOOL done = FAIL;	// ok jeœli zostanie wykoana jakaœ konwersja, czyli gdy wartoœæ przep³ywu jest poprawna	
	dim = SafeArrayGetDim(compNames);
	SafeArrayGetUBound(compNames,1,&u);
	SafeArrayGetLBound(compNames,1,&l);
	for (a=l;a<=u;a++)
	{
		SafeArrayGetElement(compNames, &a, &tmp);
		CW2A pszB(tmp);
		ret = Parameters.RegisterComponentP(pszB,inputID);
		if(ret==FAIL) return FAIL;
// gêstosc (z skryptu)
		if(copyparams->ValidateParams(VELOCITY_INLET))
		{
			line = copyparams->bCOMPONENTS.GetLineIndex(pszB,COMPONENTS_NAZWA);
			if(line<0) return FAIL;
			ret = Parameters.AssignParamToCompP(pszB,PARAM_DENSITY,atof(copyparams->bCOMPONENTS.GetSubString(line,COMPONENTS_GESTOSC)),inputID);
			if(ret==FAIL) return FAIL;
		}
// moleperkilo (z skryptu)
		if(copyparams->ValidateParams(VELOCITY_INLET))
		{
			line = copyparams->bCOMPONENTS.GetLineIndex(pszB,COMPONENTS_NAZWA);
			if(line<0) return FAIL;
			ret = Parameters.AssignParamToCompP(pszB,PARAM_MOLEPERKG,atof(copyparams->bCOMPONENTS.GetSubString(line,COMPONENTS_MOLEPERKG)),inputID);
			if(ret==FAIL) return FAIL;
		}
// temepratura
		SafeArrayGetUBound(temperature,1,&x);
		if(a>x)
			SafeArrayGetElement(temperature,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayGetElement(temperature,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
		ret = Parameters.AssignParamToCompP(pszB,PARAM_TEMPERATURE,val,inputID);
		if(ret==FAIL) return FAIL;
// cisnienie
		SafeArrayGetUBound(pressure,1,&x);
		if(a>x)
			SafeArrayGetElement(pressure,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayGetElement(pressure,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
		ret = Parameters.AssignParamToCompP(pszB,PARAM_PRESSURE,val,inputID);
		if(ret==FAIL) return FAIL;
// fraction
		SafeArrayGetUBound(fraction,1,&x);
		if(a>x)
			SafeArrayGetElement(fraction,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayGetElement(fraction,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
		ret = Parameters.AssignParamToCompP(pszB,PARAM_MOLEFRACTION,val,inputID);
		if(ret==FAIL) return FAIL;
// flow
		SafeArrayGetUBound(flow,1,&x);
		if(a>x)
			SafeArrayGetElement(flow,&index,&val);	// to jeœli jeden parametr bêdzie dla wszystkich komponentów
		else
			SafeArrayGetElement(flow,&a,&val);	// to jeœli ka¿dy komponent ma inn¹ wartoœæ parametru
		ret = Parameters.AssignParamToCompP(pszB,PARAM_MOLEFLOW,val,inputID);	// jesli zaden z if ponizej nie wyjdzie
		ret = Parameters.GetParameterP(pszB,PARAM_MOLEPERKG,tfratio,inputID);
// -----------------------------------------------------------------
		if(copyparams->ValidateParams(MASS_FLOW_INLET))	{
			val = val/tfratio;	// z aspena wychodza mole/sec, tu przeliczenie na kg/sec
			ret = Parameters.AssignParamToCompP(pszB,PARAM_MOLEFLOW,val,inputID);
			done = OK;
		}
// -----------------------------------------------------------------

		if(copyparams->ValidateParams(VELOCITY_INLET))	{
			line = copyparams->bASSIGNS.GetLineIndex(pszB,ASSIGN_COMPONENTS_NAZWA);	if(line<0) return FAIL; // linia z nazw¹ materia³u
			tmpmat = copyparams->bASSIGNS.GetSubString(line,ASSIGN_SURF_NAME);	// nazwa wejscia skojarzona z materialem
			line = copyparams->bINPUT_SURFACE.GetLineIndex(tmpmat,SURF_NAME); if(line<0) return FAIL;	// nr lini z nazwa powierzchni wejsc
			double area = atof(copyparams->bINPUT_SURFACE.GetSubString(line,SURF_AREA));	// pow
			double density,molefr;
			Parameters.GetParameterP(pszB,PARAM_DENSITY,density,inputID);
			Parameters.GetParameterP(pszB,PARAM_MOLEFRACTION,molefr,inputID);
			val =  ((val/tfratio)/(density*area))*molefr;	// przeliczenie z moli/s na m/s, val - wartosc z aspena pocz¹tkowa, uwzglêdniony udzia³ molowy materia³u w strumieniu
			ret = Parameters.AssignParamToCompP(pszB,PARAM_MOLEFLOW,val,inputID);
			done = OK;
		}
		if(ret==FAIL || done==FAIL) return FAIL;
	}

	return OK;
}

BOOL C_myRunProcess::PrintPutParameters(char* nazwa)
/// \retval FAIL Jeœli b³¹d - nie mo¿na by³o otworzyæ pliku
/// \retval OK Jeœli sukces
{
	errno_t err;
	FILE* fid;
	if( (err  = fopen_s( &fid, nazwa, "w+" )) !=0 )
      return FAIL;

	char timeline[26];
	struct _timeb timebuffer;
	_ftime_s( &timebuffer );
	ctime_s( timeline, 26, & ( timebuffer.time ) );

	fprintf(fid,"\n-- %.19s.%hu %s\n", timeline, timebuffer.millitm, &timeline[18] );

	Parameters.PrintParams(fid);

	fclose(fid);
	return OK;

}

BOOL C_myRunProcess::PrintGetParameters(char* nazwa)
/// \retval FAIL Jeœli b³¹d - nie mo¿na by³o otworzyæ pliku
/// \retval OK Jeœli sukces
{
	errno_t err;
	FILE* fid;
	if( (err  = fopen_s( &fid, nazwa, "w+" )) !=0 )
      return FAIL;

	char timeline[26];
	struct _timeb timebuffer;
	_ftime_s( &timebuffer );
	ctime_s( timeline, 26, & ( timebuffer.time ) );

	fprintf(fid,"\n-- %.19s.%hu %s\n", timeline, timebuffer.millitm, &timeline[18] );

	outParameters.PrintParams(fid);

	fclose(fid);
	return OK;

}