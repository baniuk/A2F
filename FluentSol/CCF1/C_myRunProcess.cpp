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
{
	BOOL ret;
	BOOL ret1;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	si.lpDesktop = NULL;
	
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
		ret = WaitForStart(wcstring,3, 2);
	} else	{
		err->AddError("StartFluent::Function failed");
		ret = FAIL;
	}

	return ret;
}

BOOL C_myRunProcess::WaitForStart(TCHAR* nazwa, unsigned int obrot, unsigned int czas)
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
{
	FILE *fid;
	CComBSTR jname = "journal";
	CComBSTR ptmp;
	CComBSTR fulljname;
	CComBSTR etmp;
	unsigned int a;

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

/*	tworzenie scm dla:	mass_flow_inlet
						wybór energii
						jedno wejœcie
						bez mieszaniny
						fluent: fl12016s.exe
						*/
	if(	strcmp(copyparams->bBOUND_COND,"mass-flow-inlet")==0 &&
		copyparams->bINPUT_SURFACE.GetIle()==1 &&
		copyparams->bPHASES.GetIle()==0 &&
		strcmp(copyparams->bSUBPROCNAME,"fl12016s.exe")==0)
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

		fprintf(fid,"(ti-menu-load-string \"solve/iterate %d\")\n",copyparams->bNUMOFITER);
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
		copyparams->bPHASES.GetIle()==1 &&
		strcmp(copyparams->bSUBPROCNAME,"fl12016s.exe")==0)
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

		fprintf(fid,"(ti-menu-load-string \"solve/iterate %d\")\n",copyparams->bNUMOFITER);
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
	err->AddError("CreateEnv::No valid boundary found in script");
	return FAIL;
}

BOOL C_myRunProcess::ImportData(void)
{
	/* Wczytuje dane z Fluenta. Wczytuje wszystkie wielkosci ze struktury C_Params->DATA i z nazwy pliku fulloutname
	   Wyniki l¹duj¹ w ret, przy czym zak³adam ¿e ret jest tworzone na zewn¹trz dynamicznie i ma rozmiar wskazywany przez pole 
	   C_Params->DATA->ile
	*/

	FILE *fid;
	unsigned int a;
	char ch;
	char* cont;
	char buff[MAX_STRING];
	fpos_t *poz=NULL;
	BOOL znalezione;
	double tmp,suma;
	unsigned int ile;
	
//fulloutname = "j:\\ASPEN_PROJECT\\FluentSol\\fluentdata\\ruratest";

	CW2A pszA(fulloutname);
	if(fopen_s(&fid,pszA,"r+"))	{
		err->AddError("ImportData::Cant open result dat file");
		return FAIL;
	}
	poz = new fpos_t[copyparams->bEXPORTS.GetIle()];
	for(a=0;a<copyparams->bEXPORTS.GetIle();a++)	{	// po wszystkich parametrach
		cont = copyparams->bEXPORTS.DATA_CONTAINER[a];
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
	for(a=0;a<copyparams->bEXPORTS.GetIle();a++)	{	// po wszystkich parametrach
		suma = 0;
		ile = 0;
		fsetpos(fid,&poz[a]);				// na pierwsze dane
		while(fscanf_s(fid,"%lf",&tmp)!=0)	{
			suma+=tmp;
			ile++;
		}
		SR[a] = suma/ile;
		SUM[a] = suma;
		ile_danych = ile;	// ta wartosc bedzie taka sama dla wszystkich wielkosci, potrzzeban bo niektóre s¹ œredni¹ a niektóre sum¹
	}

	fclose(fid);

	SAFE_DELETE_ARRAY(poz);
	return OK;
}

// pobiera parametry z klasy
void C_myRunProcess::GetParams(double& temp, double& fract, double& flow, double& pres)
{
	unsigned int a;

	double tfratio;
	tfratio = atof(copyparams->bMOLEPERKG.DATA_CONTAINER[0]);

	// wszystko przepisuje i dopiero w razie czego to zamieniam na to z fluenta
	temp = temperature;
	fract = fraction;
	flow = totalflow;
	pres = pressure;
	for(a=0;a<copyparams->bEXPORTS.GetIle();a++)	{
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,1),"temperature")==0)	{		// to znaczy ¿e mamy z fluenta ten parametr
			temp = SR[a]; continue; }
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,1),"totalflow")==0)			// to znaczy ¿e mamy z fluenta ten parametr
		{
			if(strcmp(copyparams->bBOUND_COND,"mass-flow-inlet")==0)
			{
				flow = SUM[a]*tfratio;	// wyjscie w kg/sec, przeliczone ma mol/sec
				continue;
			}
			if(copyparams->ValidateParams(VELOCITY_INLET))
			{
				double area = atof(copyparams->bINPUT_SURFACE.GetSubString(0,1));
				double density = atof(copyparams->bPHASES.GetSubString(0,1));
				flow = SR[a]*density*area*tfratio;	// wyjscie w m/sec przeliczone na mol/sec
				continue;
			}
		}
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,1),"pressure")==0)	{		// to znaczy ¿e mamy z fluenta ten parametr
			pres = SR[a]; continue; }
		if(strcmp(copyparams->bEXPORTS.GetSubString(a,1),"fraction")==0)	{		// to znaczy ¿e mamy z fluenta ten parametr
			fract = SR[a]; continue; }
	}
}

// wpisuje parametry do klasy
void C_myRunProcess::PutParams(double temp, double fract, double flow, double pres)
{
	double tfratio;
	tfratio = atof(copyparams->bMOLEPERKG.DATA_CONTAINER[0]);

	temperature = temp;
	fraction = fract;
	totalflow = flow;	// jakby zaden if nie wyszedl
	if(strcmp(copyparams->bBOUND_COND,"mass-flow-inlet")==0)
		totalflow = flow/tfratio;	// z aspena wychodza mole/sec, tu przeliczenie na kg/sec
	if(copyparams->ValidateParams(VELOCITY_INLET))	{
		double area = atof(copyparams->bINPUT_SURFACE.GetSubString(0,1));
		double density = atof(copyparams->bPHASES.GetSubString(0,1));
		totalflow =  (flow/tfratio)/(density*area);	// przeliczenie z moli/s na m/s
	}
	pressure = pres;
	paramsval = TRUE;
}
