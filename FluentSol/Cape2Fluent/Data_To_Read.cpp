#include "StdAfx.h"
#include "Data_To_Read.h"

Data_To_Read::Data_To_Read(void)
{
	pojemnosc = MAX_EXPORTS;	// ile elementów miesci
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

// Dodaje pozycjê podci¹gu w ci¹gu g³ównym do tablicy pozycji. Zlicza tak¿e iloœæ tych podciagów co odpowiada iloœci spacji-1
BOOL Data_To_Read::AddSubStringPoz(unsigned int line,unsigned int poz)
/// \retval FAIL Jeœli odwo³anie do wiêkszej linii ni¿ jest przechowywanych albo jeœli dodajemy wiêcej podci¹gów ni¿ dozwolone 
/// \retval OK Jeœli sukces
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

// Zwraca ilosc podci¹gów
unsigned int Data_To_Read::GetNumOfSubStrings(unsigned int line)
/// \retval 0 Jeœli podamy liniê wiêksz¹ niz iloœæ przechowywanych
/// \retval ile Jeœli ok
{
	if(line>=pojemnosc)
		return 0;
	else
		return ile_poz[line]+1;
}

// Zwraca wskaŸnik do podci¹gu, numeracja od 0
char* Data_To_Read::GetSubString(unsigned int line, unsigned int nr)
/// \retval NULL Jeœli nie znajdzie podci¹gu o danym nr w danej linii
/// \retval ptr Jeœli znajdzie
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

// Zwraca numer linii zawieraj¹cej dany ci¹g tekstowy na danej pozycji podci¹gu. Jeœli nie znalezione to zwraca -1
int Data_To_Read::GetLineIndex(char* paramName, unsigned int nr)
/// \retval -1 Jeœli nie znajdzie parametru o danej nazwie
/// \retval index Jeœli znajdzie
{
	/// \warning Ta funkcja zwraca pierwszy znaleziony parametr!! Nie sprawdza czy s¹ nastêpne
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
/// \retval -1 w tablicy tab jeœli nie znajdzie parametru o danej nazwie (index tab=indexowi linii)
/// \retval index Jeœli znajdzie
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
