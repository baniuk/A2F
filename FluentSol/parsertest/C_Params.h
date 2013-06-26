#pragma once
#define MAX_STRING 512	// maxymalny rozmiar ciagu
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#include <myparser.h>
#include "Data_To_Read.h"

/* Klasa do obs�ugi jezyka skryptowego do przekazaywnia parametr�w z wykorzystaniem matlaba. J�zyk skyptowy w formacie:
##komentarz
#rozkaz
dane rozkazu

Pomi�dzy # nie mo�e by� spacji. Ka�dy b��dny rozkaz zwraca b��d. Je�li poprawny to dane l�duj� w odpowiedniej tablicy tekstowej
Kolejno�� enum musi by� taka sama jak w pliku parseparams.m, err i valerr zawsze ostatnie. Jesli parametr istnieje to pole val*** ma warto�� 1
*/

enum enumparams {	// kolejnosc taka jak w m, ERR zawsze ostatni
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
	C_Params(void);
	~C_Params(void);
	char bFLUENT_PATH[MAX_STRING];		BOOL sFLUENT_PATH;
	char bDATA_PATH[MAX_STRING];		BOOL sDATA_PATH;
	char bERR[MAX_STRING];				BOOL sERR;
	char bCOMMAND_LINE[MAX_STRING];	BOOL sCOMMAND_LINE;
	char bCASE_NAME[MAX_STRING];		BOOL sCASE_NAME;
	Data_To_Read bDATA;					BOOL sDATA;
	int numofparams; // liczba wszystkich mo�liwych parametr�w
	int readfile(char* filename); // aby sprawdzi� czy czytanie pliku powiod�o si� nalezy sprawdzi� warto�� sERR i ewentualnie je�li true to opis b��du
	// poprzez BOOL zwracane s� b��dy zwiazane z inicjalizacj� matlaba
private:
	void AddFiledData(char16_t *in,int ile,int p);
	BOOL LoadOneLine(FILE *pFile, char* bufor);
public:
	BOOL ValidateParams(int mode);
	BOOL Creadfile(char* filename);
};
