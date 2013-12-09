// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define FAIL FALSE
#define OK TRUE
#define MAX_STRING 512	// maxymalny rozmiar ciagu W C_Params tez jest ta definicja bo niewiedzieæ czemu nie widzi jej
#define MAX_LINE 128	// mxymalna dlugosc lini skryptu

// obs³ugiwane makra:
// NO_CONFIG - nie wczytuje konfigu z pliku params.txt
// NO_REGISTRY - nie u¿ywa rejestru do znalezienia pliku params.txt
// PRINTOUT - drukuje do loga

enum tryby_pracy {
	BASIC,				// scie¿ki
	PARAMS,				// sciezki oraz parametry wywo³ania fluenta
	CASE,				// dodatkowo plik case istnieje
	DATA				// istniej¹ dyrektywy do exportu
};

#include <crtdbg.h>

#include "C_Params.h"
#include "Data_To_Read.h"

// TODO: reference additional headers your program requires here
