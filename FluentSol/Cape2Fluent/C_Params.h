#pragma once
#ifndef NO_MATLAB
#include <myparser.h>
#endif
#include "Data_To_Read.h"

enum enumparams {	// kolejnosc taka jak w m, ERR zawsze ostatni - tylko dla przypadku u�ycia interpretera z matlaba - nie aktualny teraz
	FLUENT_PATH,
	val_FLUENT_PATH,
	DATA_PATH,
	val_DATA_PATH,
	COMMAND_LINE,
	val_COMMAND_LINE,
	CASE_NAME,
	val_CASE_NAME,
	ERR,
	val_ERR
};

//! \warning kolejno�� nazw musi pokrywa� si� z kolejno�ci� tych parametr�w w danym rozkazie
enum pola_komponentow	{		// nazwy poszczeg�lnych p�l, wa�ne bo komponenty jest trzymane w Data_To_Read i jest u�ywanba funkcja GetSubString, kt�ra za parametr przyjmuje numer podci�gu do wyci�cia. Dzi�ki temu jestesmy niezaleni w kodzie w zalezno�ci cio chcemy wyci��.
	COMPONENTS_NAZWA,
	COMPONENTS_GESTOSC,
	COMPONENTS_MOLEPERKG
};

//! \warning kolejno�� nazw musi pokrywa� si� z kolejno�ci� tych parametr�w w danym rozkazie
enum pola_exports	{
	//! nazwa funkcji exportowalej z Fluenta
	EXPORT_NAME,	
	//! jako co to mamy traktowa�? - wpisy dozwolone opisane w dokumentacji skryptu
	EXPORT_PROP,			
	//! jakiego komponentu sie dotyczy
	EXPORT_COMPONENTS_NAZWA
};
enum pola_input	{
	SURF_NAME,
	SURF_AREA
};

//! \warning kolejno�� nazw musi pokrywa� si� z kolejno�ci� tych parametr�w w danym rozkazie
enum pola_assigns	{
	ASSIGN_COMPONENTS_NAZWA, /*!< nazwa materia�u - musi zgadza� si� z ASPENEM i COMPONENTS_NAZWA */
	ASSIGN_INPUTID,		/*!< indeks wej�cia - numeryczny, musi zgadza� siez ASPENEM */
	ASSIGN_SURF_NAME,	/*!< nazwa powierzchni przypisana do danego wejscia z ASPENA, musi zgadza� si� z SURF_NAME */
};

//! Klasa do obs�ugi jezyka skryptowego do przekazaywnia parametr�w z wykorzystaniem matlaba i bez
/*! Klasa do obs�ugi jezyka skryptowego do przekazaywnia parametr�w z wykorzystaniem matlaba. J�zyk skyptowy w formacie:
komentarz
rozkaz
dane rozkazu

Pomi�dzy # nie mo�e by� spacji. Ka�dy b��dny rozkaz zwraca b��d. Je�li poprawny to dane l�duj� w odpowiedniej tablicy tekstowej
Kolejno�� enum musi by� taka sama jak w pliku parseparams.m, err i valerr zawsze ostatnie. Jesli parametr istnieje to pole val*** ma warto�� 1
JE�eli rozkaz ma kilka prametr�w i kilka cz�ci parametru to dodatkowo jest struktura enym z nazwami tychg podparametr�w (obs�uga w klasie Data_To_read)
Parametry ka�dego rozkazu s� umieszczane w odpowiedniej tablicy. Je�li rozkaz ma parametry sk��daj�ce si� z kilku cz�ci to wtedy obs�ug� przejmuje klasa Data_ToRead.h, kt�ra 
umo�liwia �atwy dost�p do poszczeg�lnych parametr�w.
*/

class C_Params
{
public:
	C_Params(C_Error* perr);
	~C_Params(void);
	char bFLUENT_PATH[MAX_STRING];		BOOL sFLUENT_PATH;
	char bDATA_PATH[MAX_STRING];		BOOL sDATA_PATH;
	char bERR[MAX_STRING];				BOOL sERR;
	char bCOMMAND_LINE[MAX_STRING];		BOOL sCOMMAND_LINE;
	char bCASE_NAME[MAX_STRING];		BOOL sCASE_NAME;
	Data_To_Read bEXPORTS;				BOOL sEXPORTS;
	Data_To_Read bINPUT_SURFACE;		BOOL sINPUT_SURFACE;
	Data_To_Read bOUTPUT_SURFACE;		BOOL sOUTPUT_SURFACE;
	Data_To_Read bASSIGNS;				BOOL sASSIGNS;
	char bBOUND_COND[MAX_STRING];		BOOL sBOUND_COND;
	char bENERGY_EQ[MAX_STRING];		BOOL sENERGY_EQ;
	char bSUBPROCNAME[MAX_STRING];		BOOL sSUBPROCNAME;
	int bNUMOFITER;						BOOL sNUMOFITER;
	int bNUMOFTIMESTEPS;				BOOL sNUMOFTIMESTEPS;
	int bNUMOFPORTS;					BOOL sNUMOFPORTS;
	Data_To_Read bMOLEPERKG;			BOOL sMOLEPERKG;
	Data_To_Read bCOMPONENTS;			BOOL sCOMPONENTS;
	//! liczba wszystkich mo�liwych parametr�w
	int numofparams; 
	//! aby sprawdzi� czy czytanie pliku powiod�o si� nalezy sprawdzi� warto�� sERR i ewentualnie je�li true to opis b��du
	int readfile(char* filename); 
private:
	C_Error *err;
#ifndef NO_MATLAB
	void AddFiledData(char16_t *in,int ile,int p);
#endif
	//! Wczytuje jedn� lini� skryptu i dokonuje konwersji do du�ych liter
	/*!
	 Funkcja wczytuje jedn� lini� skryptu i dokonuje konwersji do du�ych liter
	 @param[in] pFile		wska�nik do pliku
	 @param[in] bufor		bufor na wczytan� lini�
	*/
	BOOL LoadOneLine(FILE *pFile, char* bufor);
public:
	//! Dokonuje sprawdzenia czy spe�nione s� okre�lone warunki
	/*!
	 Funkcja sprawdza czy spe�nione s� okre�lone warunki. Nazwy warunk�w w definicje.h w tryby_pracy
	 Umo�liwia t odefiniowanie zestaw�w warunk�w kt�re musz� by� spe�nione i nazywanie ich jedn� nazw�.
	 @param[in] mode		typ warunku do sprawdzenia
	*/
	BOOL ValidateParams(tryby_pracy mode);

	//! Wczytuje i analizuje plik konfiguracyjny
	/*!
	 Funkcja wczytuje plik konfiguracyjny i dokonuje jego interpretacji, wype�niaj�c klas� C_Params odczytanymi danymi
	 Umo�liwia t odefiniowanie zestaw�w warunk�w kt�re musz� by� spe�nione i nazywanie ich jedn� nazw�.
	 @param[in] filename	nazwa pliku z parametrami
	*/
	BOOL Creadfile(char* filename);
};
