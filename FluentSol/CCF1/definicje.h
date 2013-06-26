#define MAX_LINE 128	// mxymalna dlugosc lini skryptu
#define FAIL FALSE
#define OK TRUE
#define MAX_STRING 512	// maxymalny rozmiar ciagu W C_Params tez jest ta definicja bo niewiedzieæ czemu nie widzi jej
#define MAX_EXPORTS 5	// maxymalna iosc exportowancych parametrów
#define MAX_SPACES 10	// maxymalan ilosc spacji w linii parametru (MAX_SPACES+1 skladowych)
#define MAX_CALLERS 1024 // do cerror
#define MAX_ERROR 1024

// obs³ugiwane makra:
//#define NO_CONFIG //nie wczytuje konfigu z pliku params.txt
#ifndef _DEBUG
#define NO_REGISTRY
#endif
//#define NO_REGISTRY // nie u¿ywa rejestru do znalezienia pliku params.txt
//#define PRINTOUT // drukuje do loga
#define NO_MATLAB // kompiluje bez matlaba

enum tryby_pracy {
	BASIC,				// scie¿ki
	PARAMS,				// sciezki oraz parametry wywo³ania fluenta
	CASE,				// dodatkowo plik case istnieje
	EXPORTS,			// istniej¹ dyrektywy do exportu
	PHASES,				// miesznina wielofazowa
	MULTIIN,				// wiele powierzchni wejsciowych w ramach jednego wejscia
	VELOCITY_INLET		// czy sa wszystkie rzeczy do velocity? (gestosc i powierzchnia)
};

#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }