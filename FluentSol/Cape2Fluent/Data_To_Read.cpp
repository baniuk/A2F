#include "StdAfx.h"
#include "Data_To_Read.h"

Data_To_Read::Data_To_Read(void)
{
	pojemnosc = MAX_EXPORTS;	// ile element�w miesci
	ile = 0; // ile aktualnie przechowywanych
	for(unsigned int a=0;a<pojemnosc;a++)	{
		DATA_CONTAINER[a] = new char[MAX_STRING];
		pozycje[a] = new unsigned int[MAX_SPACES];
		ktore[a] = FALSE;	// nic nie ma
		for(unsigned int b=0;b<MAX_SPACES;b++) pozycje[a][b] = 0;
		ile_poz[a] = 0;
	}
//	err = new C_Error("Data_To_Read");
}

Data_To_Read::~Data_To_Read(void)
{
	for(unsigned int a=0;a<pojemnosc;a++)	{
		SAFE_DELETE_ARRAY(DATA_CONTAINER[a]);
		SAFE_DELETE_ARRAY(pozycje[a]);
	}
//	delete err;

}

// Dodaje pozycj� podci�gu w ci�gu g��wnym do tablicy pozycji. Zlicza tak�e ilo�� tych podciag�w co odpowiada ilo�ci spacji-1
BOOL Data_To_Read::AddSubStringPoz(unsigned int line,unsigned int poz)
/// \retval FAIL Je�li odwo�anie do wi�kszej linii ni� jest przechowywanych albo je�li dodajemy wi�cej podci�g�w ni� dozwolone 
/// \retval OK Je�li sukces
{
	if(ile_poz[line]>=MAX_SPACES || line>=pojemnosc)
		return FAIL;

	pozycje[line][ile_poz[line]++] = poz;
	// sprawdzam czy nowy wpis ?? (czy dana linia zostala juz policzona)
	if(ktore[line]==FALSE)
	{
		ktore[line] = TRUE;
		ile++;	// to jest licznik linii przechowywanych w klasie
	}
	return OK;
}

// Zwraca ilosc podci�g�w
unsigned int Data_To_Read::GetNumOfSubStrings(unsigned int line)
/// \retval 0 Je�li podamy lini� wi�ksz� niz ilo�� przechowywanych
/// \retval ile Je�li ok
{
	if(line>=pojemnosc)
		return 0;
	else
		return ile_poz[line]+1;
}

// Zwraca wska�nik do podci�gu, numeracja od 0
char* Data_To_Read::GetSubString(unsigned int line, unsigned int nr)
/// \retval NULL Je�li nie znajdzie podci�gu o danym nr w danej linii
/// \retval ptr Je�li znajdzie
{
	char* tmp;
	if(line>=pojemnosc || nr>=GetNumOfSubStrings(line) || line>=ile)
		return NULL;

	if(nr==0)
		return DATA_CONTAINER[line];
	else	{
		tmp = DATA_CONTAINER[line];
		return &tmp[pozycje[line][nr-1]+1]; 
	}
}

// Zwraca numer linii zawieraj�cej dany ci�g tekstowy na danej pozycji podci�gu. Je�li nie znalezione to zwraca -1
int Data_To_Read::GetLineIndex(char* paramName, unsigned int nr)
/// \retval -1 Je�li nie znajdzie parametru o danej nazwie
/// \retval index Je�li znajdzie
{
	/// \warning Ta funkcja zwraca pierwszy znaleziony parametr!! Nie sprawdza czy s� nast�pne
	unsigned int a;
	char local[MAX_COMPONENT_NAME];
	char parlocal[MAX_COMPONENT_NAME];
	for (a=0;a<ile;a++)
	{
		strcpy_s(parlocal,MAX_COMPONENT_NAME,paramName);
		_strupr_s(parlocal,MAX_COMPONENT_NAME);
		strcpy_s(local,MAX_COMPONENT_NAME,GetSubString(a,nr));
		_strupr_s(local,MAX_COMPONENT_NAME);
		if(strcmp(parlocal,local)==0)
			return a;
	}
	return -1;
}

void Data_To_Read::GetLineIndex( char* paramName, unsigned int nr,int* tab )
/// \retval -1 w tablicy tab je�li nie znajdzie parametru o danej nazwie (index tab=indexowi linii)
/// \retval index Je�li znajdzie
{
	unsigned int a;
	char local[MAX_COMPONENT_NAME];
	char parlocal[MAX_COMPONENT_NAME];
	for (a=0;a<ile;a++)
	{
		tab[a] = -1;
		strcpy_s(parlocal,MAX_COMPONENT_NAME,paramName);
		_strupr_s(parlocal,MAX_COMPONENT_NAME);
		strcpy_s(local,MAX_COMPONENT_NAME,GetSubString(a,nr));
		_strupr_s(local,MAX_COMPONENT_NAME);
		if(strcmp(parlocal,local)==0)
			tab[a] = a;
	}
}
