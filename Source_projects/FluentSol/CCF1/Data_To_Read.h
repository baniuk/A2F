#pragma once
#include "C_Error.h"
// slozy do przechowywania danych jesli jest ich kilka do jednego rozkazu
class Data_To_Read
{
public:
	Data_To_Read(void);
	~Data_To_Read(void);
	unsigned int pojemnosc;
	char *DATA_CONTAINER[MAX_EXPORTS];
	
private:
	unsigned short ile_poz[MAX_EXPORTS];	// ile czesci parametru dla kazdej linii
	unsigned int *pozycje[MAX_EXPORTS]; // tu s� przechowywane pozycje pocz�tk�w ci�g�w je�li w datacontainer wyst�puje kilka ci�g�w jako jeden (zamias spacji to 0)
										// tak naprawd� s� tu pozycje zer w ci�gu g��wnym!!
										// numeracja od zera
	unsigned int ile;
	BOOL ktore[MAX_EXPORTS];	// s�u�y do rozpoznania czy na danej pozycji 'line' co� by�o czy jest to nowy wpis. Je�li nowy wpis to zwi�kszam ile
	/* Na przyk�ad w data container[0] - z_velocity
					 datamapping[0] - totalflow
	 W datamaping moga byc wpisy:
		temperature
		totalflow
		pressure
		fraction
	*/
	C_Error *err;
public:
	// Dodaje pozycj� podci�gu w ci�gu g��wnym do tablicy pozycji. Zlicza tak�e ilo�� tych podciag�w co odpowiada ilo�ci spacji-1
	BOOL AddSubStringPoz(unsigned int line,unsigned int poz);
	// Zwraca ilosc podci�g�w
	unsigned int GetNumOfSubStrings(unsigned int line);
	// Zwraca wska�nik do podci�gu
	char* GetSubString(unsigned int line, unsigned int nr);

	// Zwraca ilosc wpis�w - danych przechowywanych
	unsigned int GetIle(void)
	{
		return ile;
	}
};
