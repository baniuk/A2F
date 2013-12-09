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
	unsigned int *pozycje[MAX_EXPORTS]; // tu s¹ przechowywane pozycje pocz¹tków ci¹gów jeœli w datacontainer wystêpuje kilka ci¹gów jako jeden (zamias spacji to 0)
										// tak naprawdê s¹ tu pozycje zer w ci¹gu g³ównym!!
										// numeracja od zera
	unsigned int ile;
	BOOL ktore[MAX_EXPORTS];	// s³u¿y do rozpoznania czy na danej pozycji 'line' coœ by³o czy jest to nowy wpis. Jeœli nowy wpis to zwiêkszam ile
	/* Na przyk³ad w data container[0] - z_velocity
					 datamapping[0] - totalflow
	 W datamaping moga byc wpisy:
		temperature
		totalflow
		pressure
		fraction
	*/
	C_Error *err;
public:
	// Dodaje pozycjê podci¹gu w ci¹gu g³ównym do tablicy pozycji. Zlicza tak¿e iloœæ tych podciagów co odpowiada iloœci spacji-1
	BOOL AddSubStringPoz(unsigned int line,unsigned int poz);
	// Zwraca ilosc podci¹gów
	unsigned int GetNumOfSubStrings(unsigned int line);
	// Zwraca wskaŸnik do podci¹gu
	char* GetSubString(unsigned int line, unsigned int nr);

	// Zwraca ilosc wpisów - danych przechowywanych
	unsigned int GetIle(void)
	{
		return ile;
	}
};
