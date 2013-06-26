#include "StdAfx.h"
#include "C_Params.h"

C_Params::C_Params(C_Error* perr)
{
	err = perr;
	//! \warning Obsolete member
	//! \code
	numofparams = 28;	// w tej wersji, to siê musi zgadzaæ ze struktór¹ tworzon¹ w pliku m!!!
	//! \endcode
	sFLUENT_PATH = FALSE; // nic jeszcze nie ma
	sDATA_PATH = FALSE;
	sERR = FALSE;
	sCOMMAND_LINE = FALSE;
	sCASE_NAME = FALSE;
	sEXPORTS = FALSE;
	sOUTPUT_SURFACE = FALSE;
	sINPUT_SURFACE = FALSE;
	sNUMOFITER = FALSE;
	sBOUND_COND = FALSE;
	sENERGY_EQ = FALSE;
	sSUBPROCNAME = FALSE;
	sMOLEPERKG = FALSE;
	sCOMPONENTS = FALSE;
	sNUMOFPORTS = FALSE;
	sNUMOFTIMESTEPS = FALSE;

	bNUMOFITER = 100;	// wartsc domyslna
	strcpy_s(bMOLEPERKG.DATA_CONTAINER[0],MAX_STRING,"1"); bMOLEPERKG.AddSubStringPoz(0,0); // bez przelicznika
//	err = new C_Error("C_Params");
}

C_Params::~C_Params(void)
{

}

#ifndef NO_MATLAB
void C_Params::AddFiledData(char16_t *in,int ile, int p)
{
	if(ile>MAX_STRING)
		ile = MAX_STRING;
	char* base;
	int a;
	switch(p)
	{
	case FLUENT_PATH:
		base = bFLUENT_PATH;
		sFLUENT_PATH = TRUE;
		break;
	case DATA_PATH:
		base = bDATA_PATH;
		sDATA_PATH = TRUE;
		break;
	case COMMAND_LINE:
		base = bCOMMAND_LINE;
		sCOMMAND_LINE = TRUE;
		break;
	case CASE_NAME:
		base = bCASE_NAME;
		sCASE_NAME = TRUE;
		break;
	case ERR:
		base = bERR;
		sERR = TRUE;
		break;
	}
	for(a=0;a<ile;a++)
		base[a] = (char)in[a];
}
#endif

#ifndef NO_MATLAB
int C_Params::readfile(char* filename)
{
	int len = strlen(filename);
	int a;
	double returned_status;
	int p;

	if (!mclInitializeApplication(NULL,0)) 
    {
		std::cerr << "could not initialize the application properly" << std::endl;
		return -1;

    }
	if( !myparserInitialize() )
    {
		std::cerr << "could not initialize the library properly" << std::endl;
		return -1;
    }
	try
	{
		mxChar *mxfilename=NULL;
		mxChar *mxreturned=NULL;
		mwArray out_mwstatus;
		mwArray out_mwstr;
		mwString tempname;	// przechowuje tymczasowo nazwe pole struktury odczytna¹ z out_mwstr
		mwArray subfield;	// przechowuje macierz skojarzon¹ z danym polem (wartoœæ tego pola)
		int el;
		mxfilename = new mxChar[len+1];
		mwArray mwfilename(1,MAX_STRING,mxCHAR_CLASS);
		for(a=0;a<len;a++)	// konwersja do char 8bit, moze jakieœ makro jest do tego?
			mxfilename[a] = filename[a];
		mxfilename[a] = 0;
		mwfilename.SetCharData(mxfilename, len);
		parseparams(2,out_mwstr, out_mwstatus,mwfilename);
// sprawdzamy czy powiod³o siê wywo³anie funkcji
		out_mwstatus.GetData(&returned_status,1);
		if(returned_status==1)	{	// nie powiod³o siê, sprawdzamy w ERR czemu
			mxreturned = new mxChar[MAX_STRING];
			tempname = out_mwstr.GetFieldName(ERR);	const char* name = (const char*)tempname; // nazwa pola
			subfield = out_mwstr.Get(name, 1, 1); // dane skojarzone z tym polem
			el = subfield.NumberOfElements();				// d³ugoœæ ci¹gu w polu ERR
			subfield.GetCharData(mxreturned,el); mxreturned[el] = 0;	// komunikat o b³êdzie
			AddFiledData(mxreturned,el+1,ERR);	// fizyczne kopiowanie do mojej str w formacie c +1 zeby to zero wesz³o tez
		} else {
			mxreturned = new mxChar[MAX_STRING];
			for(p=val_FLUENT_PATH;p<val_ERR;p+=2)	// odzyskujemy wszystkie parametry, lecimy po validacjach czy warto odzyskiwaæ, err ju¿ nie wejdzie bo zawsze ostatni
			{				
				tempname = out_mwstr.GetFieldName(p);	const char* name = (const char*)tempname; // nazwa pola
				subfield = out_mwstr.Get(name, 1, 1); // dane skojarzone z tym polem
				subfield.GetData(&returned_status,1); // dane validacyjne dla pola
				if(returned_status==1)	{	// odzysk pola - za³o¿y³em ze pola textowe s¹!!!, 1 oznacza ¿e w polu coœ jest
					tempname = out_mwstr.GetFieldName(p-1);	const char* name = (const char*)tempname; // nazwa pola
					subfield = out_mwstr.Get(name, 1, 1); // dane skojarzone z tym polem
					el = subfield.NumberOfElements();				// d³ugoœæ ci¹gu w polu ERR
					subfield.GetCharData(mxreturned,el); mxreturned[el] = 0;	// w³aœciwe dane
					AddFiledData(mxreturned,el+1,p-1);	// fizyczne kopiowanie do mojej str w formacie c +1 zeby to zero wesz³o tez
				}
			}
		}
		
		SAFE_DELETE_ARRAY(mxreturned);
		SAFE_DELETE_ARRAY(mxfilename);

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
	myparserTerminate();
	mclTerminateApplication();
	return 0;
}

#endif
BOOL C_Params::ValidateParams(tryby_pracy mode)
/// \retval FAIL Jeœli dla danego zbioru nie ma walidacji
/// \retval OK Jeœli sukces
{
/* mode - tryby walidacji w zaleznosci dla jakiej czynnosci */
	BOOL ret = FAIL;	// not validated

	switch(mode)
	{
	case BASIC:	// tylko scie¿ka do fluenta i scie¿ka do katalogu roboczego
		if(sFLUENT_PATH==1 && sDATA_PATH==1 && sSUBPROCNAME==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case PARAMS:	// tylko scie¿ka do fluenta i scie¿ka do katalogu roboczego, oraz inne parametry dla fluenta
		if(sCOMMAND_LINE==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case CASE:	// tylko scie¿ka do fluenta i scie¿ka do katalogu roboczego, oraz istnieje plik case
		if(sCASE_NAME==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case EXPORTS:	// co wyci¹gaæ i z jakich powierzchni i co na wejsciu podawaæ
		if(sEXPORTS==1 && sINPUT_SURFACE==1 && sOUTPUT_SURFACE==1 && sBOUND_COND==1 && sENERGY_EQ==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case PHASES:
		if(sCOMPONENTS==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case MULTIIN:
		if(sCOMPONENTS==1 && bINPUT_SURFACE.GetIle()>1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case VELOCITY_INLET: // typ velocity, podana gestosc oraz powierzchnia dla wszytkich parametrów
		if(strcmp(bBOUND_COND,"VELOCITY-INLET")==0 || strcmp(bBOUND_COND,"velocity-inlet")==0)	{
			for (unsigned int a=0;a<bINPUT_SURFACE.GetIle();a++)	// czy wszystkie wejscia maja podanapowierzchniê?
				if(bINPUT_SURFACE.GetSubString(a,SURF_AREA)==NULL)	// nie ma tego pola
					return FAIL; 
			for (unsigned int a=0;a<bOUTPUT_SURFACE.GetIle();a++)	// czy wszystkie wyjscia maja podanapowierzchniê?
				if(bOUTPUT_SURFACE.GetSubString(a,SURF_AREA)==NULL)	// nie ma tego pola
					return FAIL;
			for (unsigned int a=0;a<bCOMPONENTS.GetIle();a++)	// czy jest gêstoœæ i mole podane w komponentach
				if( (bCOMPONENTS.GetSubString(a,COMPONENTS_GESTOSC)==NULL) ||
					(bCOMPONENTS.GetSubString(a,COMPONENTS_MOLEPERKG)==NULL) )	// nie ma tego pola
					 return FAIL;
			ret =  OK;
		}
		break;
	case MASS_FLOW_INLET: // typ velocity, podana gestosc oraz powierzchnia
		if(strcmp(bBOUND_COND,"MASS-FLOW-INLET")==0 || strcmp(bBOUND_COND,"mass-flow-inlet")==0)
			ret = OK;
		break;
	case ENERGY:	// w³¹czone równania energii
		if(strcmp(bENERGY_EQ,"YES")==0 || strcmp(bENERGY_EQ,"yes")==0)
			ret = OK;
		break;
	case PROBLEM0:
		if(ValidateParams(VELOCITY_INLET)==OK &&
			bCOMPONENTS.GetIle()==2 &&
			bINPUT_SURFACE.GetIle()==2)
			ret = OK;
		break;
	}	
	
	return ret;
}

// dokonuje konwersji do duzych liter
BOOL C_Params::LoadOneLine(FILE *pFile, char* bufor)
/// \retval FAIL Jeœli nie uda³o siê przeczytaæ linii, lub koniec pliku
/// \retval OK Jeœli sukces
{
	BOOL status=TRUE;
	BOOL ret = OK;
	int licznik = 0;
	char cc;
	size_t siz;
	do	{
		siz=fread((void*)&cc,sizeof(char),1,pFile);
		if(siz==0)	{
			ret = FAIL;
			break;
		}
		bufor[licznik++] = cc;
		_ASSERT(licznik-1<MAX_LINE);
		_ASSERT(licznik-1>-1);
		if(cc<31 && cc!=13)
			licznik--;
		if(cc==13 || cc==10)	{
			status = FALSE;
			bufor[licznik] = 0;
		}
	} while(status && licznik<MAX_LINE);
//	_strupr_s(bufor,MAX_LINE);
	return ret;
}

BOOL C_Params::Creadfile(char* filename)
/// \retval FAIL Jeœli b³¹d w danej linii skryptu
/// \retval OK Jeœli sukces
{
	BOOL czyok = OK;
	FILE* fid;
	char lin[MAX_LINE];
	BOOL ret;
	int line = 0;
	if(fopen_s(&fid,filename,"r+"))	{
		sprintf_s(bERR,MAX_STRING,"File not opened");
		sERR = 1;
		err->AddError("Creadfile::Configuration file not opened");
		return FAIL;
	}
	do	{
		ret = LoadOneLine(fid,lin); line++;
		if(strlen(lin)<2)
			continue;
		if(lin[0]=='#' && lin[1] == '#')
			continue;						// koment
	// ---------- instrukcje --------------------
		if(strcmp(lin,"#FLUENT_PATH")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid);
				err->AddError(bERR); return FAIL;
			}
			_strlwr_s(lin,MAX_LINE);
			strcpy_s(bFLUENT_PATH,MAX_STRING,lin);
			sFLUENT_PATH = 1;
		}

		if(strcmp(lin,"#SUBPROCNAME")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			_strlwr_s(lin,MAX_LINE);
			strcpy_s(bSUBPROCNAME,MAX_STRING,lin);
			sSUBPROCNAME = 1;
		}

		if(strcmp(lin,"#DATA_PATH")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			strcpy_s(bDATA_PATH,MAX_STRING,lin);
			sDATA_PATH = 1;
		}

		if(strcmp(lin,"#COMMAND_LINE")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			strcpy_s(bCOMMAND_LINE,MAX_STRING,lin);
			sCOMMAND_LINE = 1;
		}

		if(strcmp(lin,"#CASE_NAME")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			strcpy_s(bCASE_NAME,MAX_STRING,lin);
			sCASE_NAME = 1;
		}

		if(strcmp(lin,"#NUMOFITER")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			sscanf_s(lin,"%d",&bNUMOFITER);
			sNUMOFITER = 1;
		}

		if(strcmp(lin,"#NUMOFTIMESTEPS")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			sscanf_s(lin,"%d",&bNUMOFTIMESTEPS);
			sNUMOFTIMESTEPS = 1;
		}

		if(strcmp(lin,"#ACTIVEPORTS")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			sscanf_s(lin,"%d",&bNUMOFPORTS);
			sNUMOFPORTS = 1;
		}

		if(strcmp(lin,"#BOUND_COND")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			strcpy_s(bBOUND_COND,MAX_STRING,lin);
			sBOUND_COND = 1;
		}

		if(strcmp(lin,"#ENERGY_EQ")==0)	{
			ret = LoadOneLine(fid,lin); line++;		// parametr
			if(ret==FAIL || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
				err->AddError(bERR);return FAIL;
			}
			strcpy_s(bENERGY_EQ,MAX_STRING,lin);
			sENERGY_EQ = 1;
		}

/*		Tam gdzie s¹ kilka paramaetrów w lini troche inaczej od tego jak jest tylko jeden dla list
*/

		if(strcmp(lin,"#OUTPUT_SURFACE")==0)	{
			unsigned int licz = 0;
			unsigned int a;
			unsigned int ilespacjimabyc = 1;	// dwa parametry
			size_t stlen;
			do {
				ret = LoadOneLine(fid,lin); line++;		// parametr
				stlen = strlen(lin)+1;	// razem z zerem
				if(ret==FAIL || (lin[0]=='#' && licz==0) || licz>bOUTPUT_SURFACE.pojemnosc || stlen+1>MAX_STRING)	{
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				if(lin[0]<64) {	// koniec pliku i jakieœ spacje
					licz++; break;}	

				for(a=0;a<stlen;a++)	{		// szukamy spacji
					if(lin[a]==' '&& czyok==OK)	{
						lin[a] = 0;	// czyli koñczymy pierwszy ci¹g
						czyok = bOUTPUT_SURFACE.AddSubStringPoz(licz,a);
					}
				}
				if(bOUTPUT_SURFACE.GetNumOfSubStrings(licz)-1<ilespacjimabyc)	{	// brak spacji - b³¹d
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}

				memcpy(bOUTPUT_SURFACE.DATA_CONTAINER[licz],lin,sizeof(char)*stlen); 
				sOUTPUT_SURFACE = 1;
				licz++;
			} while(lin[0]!='#' || licz<bOUTPUT_SURFACE.pojemnosc);	// albo nastepna linia albo wszystko przeczytane
		}

		if(strcmp(lin,"#INPUT_SURFACE")==0)	{ // , nazwy poszczególnych pól w cparams.h (kolejnoœæ wa¿na!!)
			unsigned int licz = 0;
			unsigned int a;
			unsigned int ilespacjimabyc = 1;	// dwa parametry
			size_t stlen;
			do {
				ret = LoadOneLine(fid,lin); line++;		// parametr
				stlen = strlen(lin)+1;	// razem z zerem
				if(ret==FAIL || (lin[0]=='#' && licz==0) || licz>bINPUT_SURFACE.pojemnosc || stlen+1>MAX_STRING)	{
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				if(lin[0]<64) {	// koniec pliku i jakieœ spacje
					licz++; break;}	

				for(a=0;a<stlen;a++)	{		// szukamy spacji
					if(lin[a]==' '&& czyok==OK)	{
						lin[a] = 0;	// czyli koñczymy pierwszy ci¹g
						czyok = bINPUT_SURFACE.AddSubStringPoz(licz,a);
					}
				}
				if(bINPUT_SURFACE.GetNumOfSubStrings(licz)-1<ilespacjimabyc)	{	// brak spacji - b³¹d
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}

				memcpy(bINPUT_SURFACE.DATA_CONTAINER[licz],lin,sizeof(char)*stlen); 
				sINPUT_SURFACE = 1;
				licz++;
			} while(lin[0]!='#' || licz<bINPUT_SURFACE.pojemnosc);	// albo nastepna linia albo wszystko przeczytane
		}

		if(strcmp(lin,"#EXPORTS")==0)	{ // , nazwy poszczególnych pól w cparams.h (kolejnoœæ wa¿na!!)
			unsigned int licz = 0;
			unsigned int a;
			unsigned int ilespacjimabyc = 2;	// trzy parametry
			size_t stlen;
			do	{
				ret = LoadOneLine(fid,lin); line++;		// parametr
				stlen = strlen(lin)+1;	// razem z zerem
				if(ret==FAIL || (lin[0]=='#' && licz==0) || licz>bEXPORTS.pojemnosc || stlen+1>MAX_STRING)	{
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				if(lin[0]<64) {	// koniec pliku i jakieœ spacje
					licz++; break;}	// ++ zeby na koñcy gra³o

				for(a=0;a<stlen;a++)	{		// szukamy spacji
					if(lin[a]==' '&& czyok==OK)	{
						lin[a] = 0;	// czyli koñczymy pierwszy ci¹g
						czyok = bEXPORTS.AddSubStringPoz(licz,a);
					}
				}
				if(bEXPORTS.GetNumOfSubStrings(licz)-1<ilespacjimabyc)	{	// brak spacji - b³¹d
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				memcpy(bEXPORTS.DATA_CONTAINER[licz],lin,sizeof(char)*stlen); 
				sEXPORTS = 1;
				licz++;
			} while(lin[0]!='#' || licz<bEXPORTS.pojemnosc);	// albo nastepna linia albo wszystko przeczytane
		}

		if(strcmp(lin,"#MOLEPERKG")==0)	{
			unsigned int licz = 0;
			size_t stlen;
			do	{
				ret = LoadOneLine(fid,lin); line++;		// parametr
				stlen = strlen(lin)+1;	// razem z zerem
				if(ret==FAIL || (lin[0]=='#' && licz==0) || licz>bMOLEPERKG.pojemnosc || stlen+1>MAX_STRING)	{
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				if(lin[0]<48) {	// koniec pliku i jakieœ spacje
					licz++; break;}	// ++ zeby na koñcy gra³o
				strcpy_s(bMOLEPERKG.DATA_CONTAINER[licz],MAX_STRING,lin); // pierwszy fragment
				// tam gdzie zero w srodku ciagu musi byc memcpy
				czyok = bMOLEPERKG.AddSubStringPoz(licz,0);
				sMOLEPERKG = 1;
				licz++;
			} while(lin[0]!='#' || licz<bMOLEPERKG.pojemnosc);	// albo nastepna linia albo wszystko przeczytane
		}

		if(strcmp(lin,"#COMPONENTS")==0)	{// w tablicy przechowywane bêd¹ ca³e ci¹gi, tylko zamias spacji bêd¹ mia³y wstawione 0, nazwy poszczególnych pól w cparams.h (kolejnoœæ wa¿na!!)
			unsigned int licz = 0;
			unsigned int a;
			unsigned int ilespacjimabyc = 2;	// zalezy od tego co ma byæ - kontrola bledu na tym poziomie
			size_t stlen;
			do	{
				ret = LoadOneLine(fid,lin); line++;		// parametr
				stlen = strlen(lin)+1;	// razem z zerem
				if(ret==FAIL || (lin[0]=='#' && licz==0) || licz>bCOMPONENTS.pojemnosc || stlen+1>MAX_STRING)	{
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				if(lin[0]<64) {	// koniec pliku i jakieœ spacje
					licz++; break;}	// ++ zeby na koñcy gra³o
				for(a=0;a<stlen;a++)	{		// szukamy spacji
					if(lin[a]==' ' && czyok==OK)	{
						lin[a] = 0;	// czyli koñczymy pierwszy ci¹g
						czyok = bCOMPONENTS.AddSubStringPoz(licz,a);
					}
				}
				if(bCOMPONENTS.GetNumOfSubStrings(licz)-1<ilespacjimabyc)	{	// brak spacji - b³¹d
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				memcpy(bCOMPONENTS.DATA_CONTAINER[licz],lin,sizeof(char)*stlen);  
				sCOMPONENTS = 1;
				licz++;
			} while(lin[0]!='#' || licz<bCOMPONENTS.pojemnosc);	// albo nastepna linia albo wszystko przeczytane
		}
// Przypuszczalna sk³adnia ASSIGNS inputID nazwa_powierzchni_wej nazwa_materialu. Udzia³_molowy wziêty z ASPENA
		if(strcmp(lin,"#ASSIGNS")==0)	{// w tablicy przechowywane bêd¹ ca³e ci¹gi, tylko zamias spacji bêd¹ mia³y wstawione 0, nazwy poszczególnych pól w cparams.h (kolejnoœæ wa¿na!!)
			unsigned int licz = 0;
			unsigned int a;
			unsigned int ilespacjimabyc = 2;	// zalezy od tego co ma byæ - kontrola bledu na tym poziomie
			size_t stlen;
			do	{
				ret = LoadOneLine(fid,lin); line++;		// parametr
				stlen = strlen(lin)+1;	// razem z zerem
				if(ret==FAIL || (lin[0]=='#' && licz==0) || licz>bASSIGNS.pojemnosc || stlen+1>MAX_STRING)	{
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				if(lin[0]<64) {	// koniec pliku i jakieœ spacje
					licz++; break;}	// ++ zeby na koñcy gra³o
				for(a=0;a<stlen;a++)	{		// szukamy spacji
					if(lin[a]==' ' && czyok==OK)	{
						lin[a] = 0;	// czyli koñczymy pierwszy ci¹g
						czyok = bASSIGNS.AddSubStringPoz(licz,a);
					}
				}
				if(bASSIGNS.GetNumOfSubStrings(licz)-1<ilespacjimabyc)	{	// brak spacji - b³¹d
					sprintf_s(bERR,MAX_STRING,"Creadfile::Error in script in line %d",line);	sERR = 1; fclose(fid); 
					err->AddError(bERR);return FAIL;
				}
				memcpy(bASSIGNS.DATA_CONTAINER[licz],lin,sizeof(char)*stlen);  
				sASSIGNS = 1;
				licz++;
			} while(lin[0]!='#' || licz<bASSIGNS.pojemnosc);	// albo nastepna linia albo wszystko przeczytane
		}

	} while(ret);

	fclose(fid);
	return OK;

}
