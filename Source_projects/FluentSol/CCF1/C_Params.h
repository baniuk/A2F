#pragma once
#ifndef NO_MATLAB
#include <myparser.h>
#endif
#include "Data_To_Read.h"
/* Klasa do obs³ugi jezyka skryptowego do przekazaywnia parametrów z wykorzystaniem matlaba. Jêzyk skyptowy w formacie:
##komentarz
#rozkaz
dane rozkazu

Pomiêdzy # nie mo¿e byæ spacji. Ka¿dy b³êdny rozkaz zwraca b³¹d. Jeœli poprawny to dane l¹duj¹ w odpowiedniej tablicy tekstowej
Kolejnoœæ enum musi byæ taka sama jak w pliku parseparams.m, err i valerr zawsze ostatnie. Jesli parametr istnieje to pole val*** ma wartoœæ 1
*/

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
	char bBOUND_COND[MAX_STRING];		BOOL sBOUND_COND;
	char bENERGY_EQ[MAX_STRING];		BOOL sENERGY_EQ;
	char bSUBPROCNAME[MAX_STRING];		BOOL sSUBPROCNAME;
	int bNUMOFITER;						BOOL sNUMOFITER;
	Data_To_Read bMOLEPERKG;			BOOL sMOLEPERKG;
	Data_To_Read bPHASES;				BOOL sPHASES;
	int numofparams; // liczba wszystkich mo¿liwych parametrów
	int readfile(char* filename); // aby sprawdziæ czy czytanie pliku powiod³o siê nalezy sprawdziæ wartoœæ sERR i ewentualnie jeœli true to opis b³êdu
	// poprzez BOOL zwracane s¹ b³êdy zwiazane z inicjalizacj¹ matlaba
private:
	C_Error *err;
#ifndef NO_MATLAB
	void AddFiledData(char16_t *in,int ile,int p);
#endif
	BOOL LoadOneLine(FILE *pFile, char* bufor);
public:
	BOOL ValidateParams(int mode);
	BOOL Creadfile(char* filename);
};
