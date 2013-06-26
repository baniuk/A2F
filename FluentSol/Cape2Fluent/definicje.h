#define MAX_LINE 128	/*!< mxymalna dlugosc lini skryptu */
#define FAIL FALSE
#define OK TRUE
#define MAX_STRING 512	/*!< maxymalny rozmiar ciagu W C_Params tez jest ta definicja bo niewiedzie� czemu nie widzi jej */
#define MAX_EXPORTS 10	/*!< maxymalna iosc exportowancych parametr�w*/
#define MAX_SPACES 10	/*!< maxymalan ilosc spacji w linii parametru (MAX_SPACES+1 skladowych)*/
#define MAX_CALLERS 1024 /*!< do cerror*/
#define MAX_ERROR 1024
#define MAX_COMPONENT_NAME 128
#define MAX_INPUT_PORTS 9	/*!< maxymalna ilosc wejsc obslugiwanych przez kod - dotyczy wejsc fizycznych*/
#define MAX_INPUTS MAX_INPUT_PORTS	/*!< maxymalna ilosc wejsc obslugiwanych przez kod - dotyczy klas przechowuj�cyc parametry*/
#define MAX_LENGTH_NODE MAX_ERROR	/*!< maksymalna pojemno�� danych w�le*/
#define NUM_OF_INPUTS 2				/*!< ilosc wejsc w systemie cape open - program raczej nie jest automatyczny i prawdopodobnie wymaga przejzenia przed zmian� ilo�c wej�� (powinno byc kompatybilne w d�, np dla 1 i 2 port�w) - ta zmienna jest u�ywana do okre�lenia rozmiaru tablicy ports[]*/
#define NUM_OF_OUTPUTS 1			/*!< ilosc wyjsc w systemie cape open - program raczej nie jest automatyczny i prawdopodobnie wymaga przejzenia przed zmian� ilo�c wyjsc */
// obs�ugiwane makra:
//#define NO_CONFIG //nie wczytuje konfigu z pliku params.txt
#ifndef _DEBUG
#define NO_REGISTRY
#endif
//#define NO_REGISTRY // nie u�ywa rejestru do znalezienia pliku params.txt
//#define PRINTOUT // drukuje do loga
#define NO_MATLAB // kompiluje bez matlaba

//! S�u�y do walidacji r�nych kombinacji danych wej�ciowych
enum tryby_pracy {
	/// scie�ki
	BASIC,		
	/// sciezki oraz parametry wywo�ania fluenta
	PARAMS,		
	/// dodatkowo plik case istnieje
	CASE,		
	/// istniej� dyrektywy do exportu
	EXPORTS,	
	/// miesznina wielofazowa
	PHASES,			
	/// wiele powierzchni wejsciowych w ramach jednego wejscia
	MULTIIN,		
	/// czy sa wszystkie rzeczy do velocity? (gestosc i powierzchnia)
	VELOCITY_INLET,	
	/// do mass flow inlet
	MASS_FLOW_INLET,		
	/// r�wnania energii w��czeone
	ENERGY,
	/// Problem 0 - jeden wlot (dwie powierzchnie), wylot, dwa komponenty w strumieniu
	PROBLEM0
};



#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p);   (p)=NULL; } }

#define CL '{687728BA-9FC0-4F97-A143-EBEE0735C18F}'