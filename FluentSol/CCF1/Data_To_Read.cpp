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
{
	if(ile_poz[line]>=MAX_SPACES || line>=pojemnosc)
		return FAIL;

	pozycje[line][ile_poz[line]++] = poz;
	// sprawdzam czy nowy wpis
	if(ktore[line]==FALSE)
	{
		ktore[line] = TRUE;
		ile++;
	}
	return OK;
}

// Zwraca ilosc podci¹gów
unsigned int Data_To_Read::GetNumOfSubStrings(unsigned int line)
{
	if(line>=pojemnosc)
		return 0;
	else
		return ile_poz[line]+1;
}

// Zwraca wskaŸnik do podci¹gu, numeracja od 0
char* Data_To_Read::GetSubString(unsigned int line, unsigned int nr)
{
	char* tmp;
	if(line>=pojemnosc || nr>=GetNumOfSubStrings(line))
		return NULL;

	if(nr==0)
		return DATA_CONTAINER[line];
	else	{
		tmp = DATA_CONTAINER[line];
		return &tmp[pozycje[line][nr-1]+1]; 
	}
}
