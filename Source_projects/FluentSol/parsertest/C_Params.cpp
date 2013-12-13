#include "StdAfx.h"
#include "C_Params.h"

C_Params::C_Params(void)
{
	numofparams = 10;	// w tej wersji, to siê musi zgadzaæ ze struktór¹ tworzon¹ w pliku m!!!
	sFLUENT_PATH = FALSE; // nic jeszcze nie ma
	sDATA_PATH = FALSE;
	sERR = FALSE;
	sCOMMAND_LINE = FALSE;
	sCASE_NAME = FALSE;
}

C_Params::~C_Params(void)
{
}

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

BOOL C_Params::ValidateParams(int mode)
{
/* mode - tryby walidacji w zaleznosci dla jakiej czynnosci */
	BOOL ret = FAIL;	// not validated

	switch(mode)
	{
	case BASIC:	// tylko scie¿ka do fluenta i scie¿ka do katalogu roboczego
		if(sFLUENT_PATH==1 && sDATA_PATH==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case PARAMS:	// tylko scie¿ka do fluenta i scie¿ka do katalogu roboczego, oraz inne parametry dla fluenta
		if(sCOMMAND_LINE==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	case CASE:	// tylko scie¿ka do fluenta i scie¿ka do katalogu roboczego, oraz istnieje plik case
		if(sCASE_NAME==1)
			ret = OK;						// valdacja, wszystko jest
	case DATA:	// tylko scie¿ka do fluenta i scie¿ka do katalogu roboczego, oraz istnieje plik case
		if(sDATA==1)
			ret = OK;						// valdacja, wszystko jest
		break;
	}	
	
	return ret;
}

BOOL C_Params::LoadOneLine(FILE *pFile, char* bufor)
{
	BOOL status=TRUE;
	BOOL ret = TRUE;
	int licznik = 0;
	char cc;
	size_t siz;
	do	{
		siz=fread((void*)&cc,sizeof(char),1,pFile);
		if(siz==0)	{
			ret = FALSE;
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


	return ret;



}

BOOL C_Params::Creadfile(char* filename)
{
	FILE* fid;
	char lin[MAX_LINE];
	BOOL ret;
	int line = 0;
	if(fopen_s(&fid,filename,"r+"))	{
		sprintf_s(bERR,MAX_STRING,"%s","File not opened");
		sERR = 1;
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
			ret = LoadOneLine(fid,lin);		// parametr
			if(ret==FALSE || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"%s","Error in script in line %d",line);	sERR = 1; fclose(fid); return FAIL;
			}
			strcpy_s(bFLUENT_PATH,MAX_STRING,lin);
			sFLUENT_PATH = 1;
		}

		if(strcmp(lin,"#DATA_PATH")==0)	{
			ret = LoadOneLine(fid,lin);		// parametr
			if(ret==FALSE || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"%s","Error in script in line %d",line);	sERR = 1; fclose(fid); return FAIL;
			}
			strcpy_s(bDATA_PATH,MAX_STRING,lin);
			sDATA_PATH = 1;
		}

		if(strcmp(lin,"#COMMAND_LINE")==0)	{
			ret = LoadOneLine(fid,lin);		// parametr
			if(ret==FALSE || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"%s","Error in script in line %d",line);	sERR = 1; fclose(fid); return FAIL;
			}
			strcpy_s(bCOMMAND_LINE,MAX_STRING,lin);
			sCOMMAND_LINE = 1;
		}

		if(strcmp(lin,"#CASE_NAME")==0)	{
			ret = LoadOneLine(fid,lin);		// parametr
			if(ret==FALSE || lin[0]=='#')	{
				sprintf_s(bERR,MAX_STRING,"%s","Error in script in line %d",line);	sERR = 1; fclose(fid); return FAIL;
			}
			strcpy_s(bCASE_NAME,MAX_STRING,lin);
			sCASE_NAME = 1;
		}

		if(strcmp(lin,"#DATA")==0)	{
			int licz = 0;
			do	{
				ret = LoadOneLine(fid,lin);		// parametr
				if(ret==FALSE || (lin[0]=='#' && licz==0) || licz>bDATA.pojemnosc)	{
					sprintf_s(bERR,MAX_STRING,"%s","Error in script in line %d",line);	sERR = 1; fclose(fid); return FAIL;
				}
				if(lin[0]<64) {	// koniec pliku i jakieœ spacje
					licz++; break;}	// ++ zeby na koñcy gra³o
				strcpy_s(bDATA.DATA_CONTAINER[licz],MAX_STRING,lin);
				sDATA = 1;
				licz++;
			} while(lin[0]!='#' || licz<bDATA.pojemnosc);	// albo nastepna linia albo wszystko przeczytane
			bDATA.ile = --licz;
		}

	} while(ret);

	return ret;

}
