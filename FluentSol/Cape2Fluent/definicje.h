#define MAX_LINE 128	/*!< mxymalna dlugosc lini skryptu */
#define FAIL FALSE
#define OK TRUE
#define MAX_STRING 512	/*!< maxymalny rozmiar ciagu W C_Params tez jest ta definicja bo niewiedzieæ czemu nie widzi jej */
#define MAX_EXPORTS 10	/*!< maxymalna iosc exportowancych parametrów*/
#define MAX_SPACES 10	/*!< maxymalan ilosc spacji w linii parametru (MAX_SPACES+1 skladowych)*/
#define MAX_CALLERS 1024 /*!< do cerror*/
#define MAX_ERROR 1024
#define MAX_COMPONENT_NAME 128
#define MAX_INPUT_PORTS 9	/*!< maxymalna ilosc wejsc obslugiwanych przez kod - dotyczy wejsc fizycznych*/
#define MAX_INPUTS MAX_INPUT_PORTS	/*!< maxymalna ilosc wejsc obslugiwanych przez kod - dotyczy klas przechowuj¹cyc parametry*/
#define MAX_LENGTH_NODE MAX_ERROR	/*!< maksymalna pojemnoœæ danych wêŸle*/
#define NUM_OF_INPUTS 2				/*!< ilosc wejsc w systemie cape open - program raczej nie jest automatyczny i prawdopodobnie wymaga przejzenia przed zmian¹ iloœc wejœæ (powinno byc kompatybilne w dó³, np dla 1 i 2 portów) - ta zmienna jest u¿ywana do okreœlenia rozmiaru tablicy ports[]*/
#define NUM_OF_OUTPUTS 1			/*!< ilosc wyjsc w systemie cape open - program raczej nie jest automatyczny i prawdopodobnie wymaga przejzenia przed zmian¹ iloœc wyjsc */
// obs³ugiwane makra:
//#define NO_CONFIG //nie wczytuje konfigu z pliku params.txt
#ifndef _DEBUG
#define NO_REGISTRY
#endif
//#define NO_REGISTRY // nie u¿ywa rejestru do znalezienia pliku params.txt
//#define PRINTOUT // drukuje do loga
#define NO_MATLAB // kompiluje bez matlaba

//! S³u¿y do walidacji ró¿nych kombinacji danych wejœciowych
enum tryby_pracy {
	/// scie¿ki
	BASIC,		
	/// sciezki oraz parametry wywo³ania fluenta
	PARAMS,		
	/// dodatkowo plik case istnieje
	CASE,		
	/// istniej¹ dyrektywy do exportu
	EXPORTS,	
	/// miesznina wielofazowa
	PHASES,			
	/// wiele powierzchni wejsciowych w ramach jednego wejscia
	MULTIIN,		
	/// czy sa wszystkie rzeczy do velocity? (gestosc i powierzchnia)
	VELOCITY_INLET,	
	/// do mass flow inlet
	MASS_FLOW_INLET,		
	/// równania energii w³¹czeone
	ENERGY,
	/// Problem 0 - jeden wlot (dwie powierzchnie), wylot, dwa komponenty w strumieniu
	PROBLEM0
};



#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p);   (p)=NULL; } }

#define CL '{687728BA-9FC0-4F97-A143-EBEE0735C18F}'