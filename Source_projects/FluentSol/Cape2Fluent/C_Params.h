#pragma once
#ifndef NO_MATLAB
#include <myparser.h>
#endif
#include "Data_To_Read.h"

enum enumparams {	// kolejnosc taka jak w m, ERR zawsze ostatni - tylko dla przypadku u¿ycia interpretera z matlaba - nie aktualny teraz
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

//! \warning kolejnoœæ nazw musi pokrywaæ siê z kolejnoœci¹ tych parametrów w danym rozkazie
enum pola_komponentow	{		// nazwy poszczególnych pól, wa¿ne bo komponenty jest trzymane w Data_To_Read i jest u¿ywanba funkcja GetSubString, która za parametr przyjmuje numer podci¹gu do wyciêcia. Dziêki temu jestesmy niezaleni w kodzie w zaleznoœci cio chcemy wyci¹æ.
	COMPONENTS_NAZWA,
	COMPONENTS_GESTOSC,
	COMPONENTS_MOLEPERKG
};

//! \warning kolejnoœæ nazw musi pokrywaæ siê z kolejnoœci¹ tych parametrów w danym rozkazie
enum pola_exports	{
	//! nazwa funkcji exportowalej z Fluenta
	EXPORT_NAME,	
	//! jako co to mamy traktowaæ? - wpisy dozwolone opisane w dokumentacji skryptu
	EXPORT_PROP,			
	//! jakiego komponentu sie dotyczy
	EXPORT_COMPONENTS_NAZWA
};
enum pola_input	{
	SURF_NAME,
	SURF_AREA
};

//! \warning kolejnoœæ nazw musi pokrywaæ siê z kolejnoœci¹ tych parametrów w danym rozkazie
enum pola_assigns	{
	ASSIGN_COMPONENTS_NAZWA, /*!< nazwa materia³u - musi zgadzaæ siê z ASPENEM i COMPONENTS_NAZWA */
	ASSIGN_INPUTID,		/*!< indeks wejœcia - numeryczny, musi zgadzaæ siez ASPENEM */
	ASSIGN_SURF_NAME,	/*!< nazwa powierzchni przypisana do danego wejscia z ASPENA, musi zgadzaæ siê z SURF_NAME */
};

//! Klasa do obs³ugi jezyka skryptowego do przekazaywnia parametrów z wykorzystaniem matlaba i bez
/*! Klasa do obs³ugi jezyka skryptowego do przekazaywnia parametrów z wykorzystaniem matlaba. Jêzyk skyptowy w formacie:
komentarz
rozkaz
dane rozkazu

Pomiêdzy # nie mo¿e byæ spacji. Ka¿dy b³êdny rozkaz zwraca b³¹d. Jeœli poprawny to dane l¹duj¹ w odpowiedniej tablicy tekstowej
Kolejnoœæ enum musi byæ taka sama jak w pliku parseparams.m, err i valerr zawsze ostatnie. Jesli parametr istnieje to pole val*** ma wartoœæ 1
JE¿eli rozkaz ma kilka prametrów i kilka czêœci parametru to dodatkowo jest struktura enym z nazwami tychg podparametrów (obs³uga w klasie Data_To_read)
Parametry ka¿dego rozkazu s¹ umieszczane w odpowiedniej tablicy. Jeœli rozkaz ma parametry sk³¹daj¹ce siê z kilku czêœci to wtedy obs³ugê przejmuje klasa Data_ToRead.h, która 
umo¿liwia ³atwy dostêp do poszczególnych parametrów.
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
	//! liczba wszystkich mo¿liwych parametrów
	int numofparams; 
	//! aby sprawdziæ czy czytanie pliku powiod³o siê nalezy sprawdziæ wartoœæ sERR i ewentualnie jeœli true to opis b³êdu
	int readfile(char* filename); 
private:
	C_Error *err;
#ifndef NO_MATLAB
	void AddFiledData(char16_t *in,int ile,int p);
#endif
	//! Wczytuje jedn¹ liniê skryptu i dokonuje konwersji do du¿ych liter
	/*!
	 Funkcja wczytuje jedn¹ liniê skryptu i dokonuje konwersji do du¿ych liter
	 @param[in] pFile		wskaŸnik do pliku
	 @param[in] bufor		bufor na wczytan¹ liniê
	*/
	BOOL LoadOneLine(FILE *pFile, char* bufor);
public:
	//! Dokonuje sprawdzenia czy spe³nione s¹ okreœlone warunki
	/*!
	 Funkcja sprawdza czy spe³nione s¹ okreœlone warunki. Nazwy warunków w definicje.h w tryby_pracy
	 Umo¿liwia t odefiniowanie zestawów warunków które musz¹ byæ spe³nione i nazywanie ich jedn¹ nazw¹.
	 @param[in] mode		typ warunku do sprawdzenia
	*/
	BOOL ValidateParams(tryby_pracy mode);

	//! Wczytuje i analizuje plik konfiguracyjny
	/*!
	 Funkcja wczytuje plik konfiguracyjny i dokonuje jego interpretacji, wype³niaj¹c klasê C_Params odczytanymi danymi
	 Umo¿liwia t odefiniowanie zestawów warunków które musz¹ byæ spe³nione i nazywanie ich jedn¹ nazw¹.
	 @param[in] filename	nazwa pliku z parametrami
	*/
	BOOL Creadfile(char* filename);
};
