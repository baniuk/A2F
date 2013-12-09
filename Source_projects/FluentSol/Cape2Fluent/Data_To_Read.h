#pragma once
#include "C_Error.h"
//! Klasa sluzy do przechowywania danych jesli jest ich kilka do jednego rozkazu

/*! Klasa slozy do przechowywania danych jesli jest ich kilka do jednego rozkazu, wszystko domyslnie jest konwertowane do du¿ych liter juz w momencie wczytywania
 Umo¿liwia ³atwy dostêp do poszczeglnych sk³adowych rozkazu
 */
class Data_To_Read
{
public:
	Data_To_Read(void);
	~Data_To_Read(void);
	unsigned int pojemnosc;
	char *DATA_CONTAINER[MAX_EXPORTS];
	
private:
	//! ile czesci parametru dla kazdej linii
	unsigned short ile_poz[MAX_EXPORTS];	
	//! tu s¹ przechowywane pozycje pocz¹tków ci¹gów jeœli w datacontainer wystêpuje kilka ci¹gów jako jeden (zamias spacji to 0) tak naprawdê s¹ tu pozycje zer w ci¹gu g³ównym!! numeracja od zera
	unsigned int *pozycje[MAX_EXPORTS];		
	//! ilosc przechowywanych linii
	unsigned int ile;	
	//! s³u¿y do rozpoznania czy na danej pozycji 'line' jest wpis czy go nie ma. Jeœli nowy wpis to zwiêkszam ile
	BOOL ktore[MAX_EXPORTS];	
public: 
	/// Dodaje pozycjê podci¹gu w ci¹gu g³ównym do tablicy pozycji.	Zlicza tak¿e iloœæ tych podciagów co odpowiada iloœci spacji-1
	/*!
	 Dodaje pozycjê podci¹gu w ci¹gu g³ównym do tablicy pozycji.
	 Zlicza tak¿e iloœæ tych podciagów co odpowiada iloœci spacji-1
	 @param[in] line Index linii w bloku skryptu (pomiêdzy INSTR a END)
	 @param[in] poz  Index pozycji na któr¹ dodajemy (index 0 w ci¹gu)
	*/
	BOOL AddSubStringPoz(unsigned int line,unsigned int poz);

	//! Zwraca ilosc podci¹gów
	/*!
	 Zwraca ilosc podci¹gów
	 @param[in] line Index linii w bloku skryptu (pomiêdzy INSTR a END)
	*/
	unsigned int GetNumOfSubStrings(unsigned int line);

	//! Zwraca wskaŸnik do podci¹gu
	/*!
	 Zwraca wskaŸnik do podci¹gu
	 @param[in] line Index linii w bloku skryptu (pomiêdzy INSTR a END)
	 @param[in] nr Index pozycji - numer podci¹gu (lub jego nazwa) zdefiniowana w C_Params::pola_komponentow
	*/
	char* GetSubString(unsigned int line, unsigned int nr);

	//! Zwraca ilosc wpisów - danych przechowywanych
	unsigned int GetIle(void)
	{
		return ile;
	}
	//! Zwraca numer linii zawieraj¹cej dany ci¹g tekstowy na danej pozycji podci¹gu. Jeœli nie znalezione to zwraca -1
	/*!
	 Zwraca numer linii zawieraj¹cej dany ci¹g tekstowy na danej pozycji podci¹gu. Jeœli nie znalezione to zwraca -1
	 @param[in] paramName Ciag tekstowy, którego szukamy w wszystkich liniach przechowywanych
	 @param[in] nr Nazwa pozycji podci¹gu na którym szukamy parName zdefiniowana w C_Params::pola_komponentow
	*/
	int GetLineIndex(char* paramName, unsigned int nr);

	//! Zwraca numery linii zawieraj¹cych dany ci¹g tekstowy na danej pozycji podci¹gu. Jeœli nie znalezione to zwraca -1
	/*!
	 Zwraca numery linii zawieraj¹cych dany ci¹g tekstowy na danej pozycji podci¹gu. Jeœli nie znalezione to zwraca -1
	 Ta funkcja jest przystosowana do sytuacji gdy kilka linii mo¿e zawieraæ taki samy ci¹g na danej pozycji. Tablica z
	 wynikami musi byæ zaalokowana na zewn¹trz i mieæ rozmiar najbezpieczniej iloœci linii w rozkazie
	 @param[in] paramName Ciag tekstowy, którego szukamy w wszystkich liniach przechowywanych
	 @param[in] nr Nazwa pozycji podci¹gu na którym szukamy parName zdefiniowana w C_Params::pola_komponentow
	 @param[out] tab Tablica z wynikami
	 */
	void GetLineIndex(char* paramName, unsigned int nr,int* tab);
};
