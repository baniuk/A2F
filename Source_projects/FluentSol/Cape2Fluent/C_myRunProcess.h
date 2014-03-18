#pragma once
#include "C_PortParameter_Container.h"

//! Klasa s³u¿¹ca do obs³ugi fluenta. Trzyma dane zwi¹zane z strumieniami, obrabia wyniki, generuje pliki fluenta
/*! Klasa s³u¿¹ca do obs³ugi fluenta. Trzyma dane zwi¹zane z strumieniami (ich parametry fizyczne oraz generuje pliki
	dla fluenta, uruchamia go oraz odzyskuje wyniki
*/
class C_myRunProcess
{
public:
	/// Konstruktor - pobiera klasê do obs³ugi b³êdów oraz odniesienie do klasy przechowuj¹cej parametry ze skryptu
	C_myRunProcess(C_Error* perr,C_Params* params);
	~C_myRunProcess(void);
	CComBSTR procname;
	CComBSTR parname;	//LPWSTR
	TCHAR *subprocname;
	BOOL StartFluent(void);
private:
	CComBSTR FLUENT_PATH;
	CComBSTR COMMAND_LINE;
	/// nazwa pliku wyjœciowego
	CComBSTR fulloutname;	
	BOOL WaitForStart(TCHAR* nazwa, unsigned int obrot, unsigned int czas);
	BOOL WaitForProcess(TCHAR* nazwa);
	BOOL PrintProcessNameAndID(DWORD processID, TCHAR* nazwa);
	C_PortParameter_Container Parameters;
	/// \todo usun¹æ parametry po zaimplementowaniu nowych GetParam
	double pressure;
	double totalflow;
	double fraction[MAX_EXPORTS];
	double temperature;
	// --------------------------
	/// tu przechowujê zaimportowane parametry,- srednia z zaimportowanych dla wszystkich komponentów
	C_PortParameter_Container SR;		
	/// tu przechowujê zaimportowane parametry, - suma z zaimportowanych dla wszystkich komponentów
	C_PortParameter_Container SUM;	
	/// tymczasowa zmienna do przechowywania przeliczonych parametrów wyjœciowych (takich jakie s¹ przekazywane do Aspena) tylko po to aby mo¿na by³o je nagraæ na dysk
	C_PortParameter_Container outParameters;
	/// ile jest elementów w prof
	unsigned int ile_danych;	
	/// funkcja usuwa podwójnego slaska do œciezek, modyfikuje ci¹g wejœciowy
	void RemoveDoubleSlash(char* in); 
	/// kopia klasy zawieraj¹cej parametry ze skryptu (nie modyfiowaæ tu)
	C_Params* copyparams;
	/// Klasa obs³ugi b³êdów
	C_Error *err;
public:
	/// Tworzy œrodowisko do uruchomienia fluenta - generuje scm oraz journalC_Params
	BOOL CreateEnv(void);
	/// Wczytuje dane z Fluenta.
	/*! Wczytuje dane z Fluenta. Wczytuje wszystkie wielkosci ze struktury C_Params->bEXPORTS i z nazwy pliku fulloutname
		Wyniki l¹duj¹ w tablicach SR oraz SUM, Te tablice s¹ klasami C_Parameter_Container, ale nie koniecznie musza przechowywaæ wszystkie wartoœci - tylko te importowane.
		Jeœli coœ nie jest importowane to klasa ta zwraca FAIL przy próbie odczytu danego parametru
	*/
	BOOL ImportData(void);

	/// jesli 1 to parametry aktualne
	BOOL paramsval;	
	/// pobiera parametry z klasy na zewn¹trz - wersja starsza
	/*!
	 Funkcja wpisuje parametry strumienia do do klasy C_Parameter_Container. Wersja starsza - obs³uga tylko jednego wejscia
	 @param[out] temp	temepratura 
	 @param[out] fract	tablica z udzialami	
	 @param[out] flow	przep³yw
	 @param[out] pres	cisnienie
	*/
	/// \warning Obsolete Function
	void GetParams(double& temp, double *fract, double& flow, double& pres);
	
	/// pobiera parametry z klasy na zewn¹trz - wersja nowsza
	/*!
	 Funkcja pobiera parametry strumienia z klasy C_Parameter_Container. Wersja nowsza - obs³uga wielu wejsæ w modelu. 
	 Dane odczytane z fluenta s¹ trzymane w odzielnych obiektach SR i SUM i st¹d s¹ odrazu przepisywane do SAFEARRAY.
	 Ta funkcja nie korzysta ze skojarzonych z ca³¹ klas¹ parametrów wejœciowych C_myRunProcess::Parameters
	 @param[out] temperature	temepratura 
	 @param[out] fraction		udzia³	
	 @param[out] flow			przep³yw
	 @param[out] pressure		cisnienie
	 @param[in] compNames		nazwa zwi¹zku - pobrana z ASPENA
	*/
	BOOL GetParams(SAFEARRAY *temperature, SAFEARRAY *fraction, SAFEARRAY *flow, SAFEARRAY *pressure, SAFEARRAY *compNames);
	
	/// wpisuje parametry do klasy, wersja starsza
	/*!
	 Funkcja wpisuje parametry strumienia do do klasy C_Parameter_Container. Wersja starsza - obs³uga tylko jednego wejscia
	 @param[in] temp	temepratura 
	 @param[in] fract	tablica z udzialami	
	 @param[in] flow	przep³yw
	 @param[in] pres	cisnienie
	*/
	/// \warning Obsolete Function
	BOOL PutParams(double temp, double *fract, double flow, double pres);

	/// wpisuje parametry do klasy, wersja nowsza
	/*!
	 Funkcja wpisuje parametry do klasy i tak¿e dokonuje rejestracji komponentów w klasie C_Parameter_Container. Dokonuje integracji tak¿e z parametrami ze skryptu
	 Wersja nowsza - obs³uga wielu wejsæ w modelu
	 @param[in] temperature	temepratura 
	 @param[in] fraction		udzia³	
	 @param[in] flow			przep³yw
	 @param[in] pressure		cisnienie
	 @param[in] compNames		nazwa zwi¹zku - pobrana z ASPENA
	 @param[in] inputID			numer wejœcia
	*/
	BOOL PutParams(SAFEARRAY *temperature, SAFEARRAY *fraction, SAFEARRAY *flow, SAFEARRAY *pressure, SAFEARRAY *compNames,unsigned int inputID);

	//! Drukuje zawartoœæ portów do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie C_PortParameter_Container dla wszystkich wejsæ do pliku. Parametry które s¹ przekazane poprzez PutParams i zamienione na jednostki wewnêtrzne
		Trzymane w zmiennej C_PortParameter_Container::Parameters
	@param[in] nazwa		nazwa pliku wraz ze œciezk¹. Sizezka powinna zawieraæ podwójne // 
	*/
	BOOL PrintPutParameters(char* nazwa);

	//! Drukuje zawartoœæ portów do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie C_PortParameter_Container dla wszystkich wejsæ do pliku. Parametry które s¹ przekazane poprzez GetParams i zamienione na jednostki zewnêtrzne
		Trzymane w zmiennej C_PortParameter_Container::outParameters
	@param[in] nazwa		nazwa pliku wraz ze œciezk¹. Sizezka powinna zawieraæ podwójne // 
	*/
	BOOL PrintGetParameters(char* nazwa);
};
