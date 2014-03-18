#pragma once
#include "C_Error.h"
//! Klasa sluzy do przechowywania danych jesli jest ich kilka do jednego rozkazu

/*! Klasa slozy do przechowywania danych jesli jest ich kilka do jednego rozkazu, wszystko domyslnie jest konwertowane do du�ych liter juz w momencie wczytywania
 Umo�liwia �atwy dost�p do poszczeglnych sk�adowych rozkazu
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
	//! tu s� przechowywane pozycje pocz�tk�w ci�g�w je�li w datacontainer wyst�puje kilka ci�g�w jako jeden (zamias spacji to 0) tak naprawd� s� tu pozycje zer w ci�gu g��wnym!! numeracja od zera
	unsigned int *pozycje[MAX_EXPORTS];		
	//! ilosc przechowywanych linii
	unsigned int ile;	
	//! s�u�y do rozpoznania czy na danej pozycji 'line' jest wpis czy go nie ma. Je�li nowy wpis to zwi�kszam ile
	BOOL ktore[MAX_EXPORTS];	
public: 
	/// Dodaje pozycj� podci�gu w ci�gu g��wnym do tablicy pozycji.	Zlicza tak�e ilo�� tych podciag�w co odpowiada ilo�ci spacji-1
	/*!
	 Dodaje pozycj� podci�gu w ci�gu g��wnym do tablicy pozycji.
	 Zlicza tak�e ilo�� tych podciag�w co odpowiada ilo�ci spacji-1
	 @param[in] line Index linii w bloku skryptu (pomi�dzy INSTR a END)
	 @param[in] poz  Index pozycji na kt�r� dodajemy (index 0 w ci�gu)
	*/
	BOOL AddSubStringPoz(unsigned int line,unsigned int poz);

	//! Zwraca ilosc podci�g�w
	/*!
	 Zwraca ilosc podci�g�w
	 @param[in] line Index linii w bloku skryptu (pomi�dzy INSTR a END)
	*/
	unsigned int GetNumOfSubStrings(unsigned int line);

	//! Zwraca wska�nik do podci�gu
	/*!
	 Zwraca wska�nik do podci�gu
	 @param[in] line Index linii w bloku skryptu (pomi�dzy INSTR a END)
	 @param[in] nr Index pozycji - numer podci�gu (lub jego nazwa) zdefiniowana w C_Params::pola_komponentow
	*/
	char* GetSubString(unsigned int line, unsigned int nr);

	//! Zwraca ilosc wpis�w - danych przechowywanych
	unsigned int GetIle(void)
	{
		return ile;
	}
	//! Zwraca numer linii zawieraj�cej dany ci�g tekstowy na danej pozycji podci�gu. Je�li nie znalezione to zwraca -1
	/*!
	 Zwraca numer linii zawieraj�cej dany ci�g tekstowy na danej pozycji podci�gu. Je�li nie znalezione to zwraca -1
	 @param[in] paramName Ciag tekstowy, kt�rego szukamy w wszystkich liniach przechowywanych
	 @param[in] nr Nazwa pozycji podci�gu na kt�rym szukamy parName zdefiniowana w C_Params::pola_komponentow
	*/
	int GetLineIndex(char* paramName, unsigned int nr);

	//! Zwraca numery linii zawieraj�cych dany ci�g tekstowy na danej pozycji podci�gu. Je�li nie znalezione to zwraca -1
	/*!
	 Zwraca numery linii zawieraj�cych dany ci�g tekstowy na danej pozycji podci�gu. Je�li nie znalezione to zwraca -1
	 Ta funkcja jest przystosowana do sytuacji gdy kilka linii mo�e zawiera� taki samy ci�g na danej pozycji. Tablica z
	 wynikami musi by� zaalokowana na zewn�trz i mie� rozmiar najbezpieczniej ilo�ci linii w rozkazie
	 @param[in] paramName Ciag tekstowy, kt�rego szukamy w wszystkich liniach przechowywanych
	 @param[in] nr Nazwa pozycji podci�gu na kt�rym szukamy parName zdefiniowana w C_Params::pola_komponentow
	 @param[out] tab Tablica z wynikami
	 */
	void GetLineIndex(char* paramName, unsigned int nr,int* tab);
};
