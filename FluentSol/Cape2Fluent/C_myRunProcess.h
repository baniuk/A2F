#pragma once
#include "C_PortParameter_Container.h"

//! Klasa s�u��ca do obs�ugi fluenta. Trzyma dane zwi�zane z strumieniami, obrabia wyniki, generuje pliki fluenta
/*! Klasa s�u��ca do obs�ugi fluenta. Trzyma dane zwi�zane z strumieniami (ich parametry fizyczne oraz generuje pliki
	dla fluenta, uruchamia go oraz odzyskuje wyniki
*/
class C_myRunProcess
{
public:
	/// Konstruktor - pobiera klas� do obs�ugi b��d�w oraz odniesienie do klasy przechowuj�cej parametry ze skryptu
	C_myRunProcess(C_Error* perr,C_Params* params);
	~C_myRunProcess(void);
	CComBSTR procname;
	CComBSTR parname;	//LPWSTR
	TCHAR *subprocname;
	BOOL StartFluent(void);
private:
	CComBSTR FLUENT_PATH;
	CComBSTR COMMAND_LINE;
	/// nazwa pliku wyj�ciowego
	CComBSTR fulloutname;	
	BOOL WaitForStart(TCHAR* nazwa, unsigned int obrot, unsigned int czas);
	BOOL WaitForProcess(TCHAR* nazwa);
	BOOL PrintProcessNameAndID(DWORD processID, TCHAR* nazwa);
	C_PortParameter_Container Parameters;
	/// \todo usun�� parametry po zaimplementowaniu nowych GetParam
	double pressure;
	double totalflow;
	double fraction[MAX_EXPORTS];
	double temperature;
	// --------------------------
	/// tu przechowuj� zaimportowane parametry,- srednia z zaimportowanych dla wszystkich komponent�w
	C_PortParameter_Container SR;		
	/// tu przechowuj� zaimportowane parametry, - suma z zaimportowanych dla wszystkich komponent�w
	C_PortParameter_Container SUM;	
	/// tymczasowa zmienna do przechowywania przeliczonych parametr�w wyj�ciowych (takich jakie s� przekazywane do Aspena) tylko po to aby mo�na by�o je nagra� na dysk
	C_PortParameter_Container outParameters;
	/// ile jest element�w w prof
	unsigned int ile_danych;	
	/// funkcja usuwa podw�jnego slaska do �ciezek, modyfikuje ci�g wej�ciowy
	void RemoveDoubleSlash(char* in); 
	/// kopia klasy zawieraj�cej parametry ze skryptu (nie modyfiowa� tu)
	C_Params* copyparams;
	/// Klasa obs�ugi b��d�w
	C_Error *err;
public:
	/// Tworzy �rodowisko do uruchomienia fluenta - generuje scm oraz journalC_Params
	BOOL CreateEnv(void);
	/// Wczytuje dane z Fluenta.
	/*! Wczytuje dane z Fluenta. Wczytuje wszystkie wielkosci ze struktury C_Params->bEXPORTS i z nazwy pliku fulloutname
		Wyniki l�duj� w tablicach SR oraz SUM, Te tablice s� klasami C_Parameter_Container, ale nie koniecznie musza przechowywa� wszystkie warto�ci - tylko te importowane.
		Je�li co� nie jest importowane to klasa ta zwraca FAIL przy pr�bie odczytu danego parametru
	*/
	BOOL ImportData(void);

	/// jesli 1 to parametry aktualne
	BOOL paramsval;	
	/// pobiera parametry z klasy na zewn�trz - wersja starsza
	/*!
	 Funkcja wpisuje parametry strumienia do do klasy C_Parameter_Container. Wersja starsza - obs�uga tylko jednego wejscia
	 @param[out] temp	temepratura 
	 @param[out] fract	tablica z udzialami	
	 @param[out] flow	przep�yw
	 @param[out] pres	cisnienie
	*/
	/// \warning Obsolete Function
	void GetParams(double& temp, double *fract, double& flow, double& pres);
	
	/// pobiera parametry z klasy na zewn�trz - wersja nowsza
	/*!
	 Funkcja pobiera parametry strumienia z klasy C_Parameter_Container. Wersja nowsza - obs�uga wielu wejs� w modelu. 
	 Dane odczytane z fluenta s� trzymane w odzielnych obiektach SR i SUM i st�d s� odrazu przepisywane do SAFEARRAY.
	 Ta funkcja nie korzysta ze skojarzonych z ca�� klas� parametr�w wej�ciowych C_myRunProcess::Parameters
	 @param[out] temperature	temepratura 
	 @param[out] fraction		udzia�	
	 @param[out] flow			przep�yw
	 @param[out] pressure		cisnienie
	 @param[in] compNames		nazwa zwi�zku - pobrana z ASPENA
	*/
	BOOL GetParams(SAFEARRAY *temperature, SAFEARRAY *fraction, SAFEARRAY *flow, SAFEARRAY *pressure, SAFEARRAY *compNames);
	
	/// wpisuje parametry do klasy, wersja starsza
	/*!
	 Funkcja wpisuje parametry strumienia do do klasy C_Parameter_Container. Wersja starsza - obs�uga tylko jednego wejscia
	 @param[in] temp	temepratura 
	 @param[in] fract	tablica z udzialami	
	 @param[in] flow	przep�yw
	 @param[in] pres	cisnienie
	*/
	/// \warning Obsolete Function
	BOOL PutParams(double temp, double *fract, double flow, double pres);

	/// wpisuje parametry do klasy, wersja nowsza
	/*!
	 Funkcja wpisuje parametry do klasy i tak�e dokonuje rejestracji komponent�w w klasie C_Parameter_Container. Dokonuje integracji tak�e z parametrami ze skryptu
	 Wersja nowsza - obs�uga wielu wejs� w modelu
	 @param[in] temperature	temepratura 
	 @param[in] fraction		udzia�	
	 @param[in] flow			przep�yw
	 @param[in] pressure		cisnienie
	 @param[in] compNames		nazwa zwi�zku - pobrana z ASPENA
	 @param[in] inputID			numer wej�cia
	*/
	BOOL PutParams(SAFEARRAY *temperature, SAFEARRAY *fraction, SAFEARRAY *flow, SAFEARRAY *pressure, SAFEARRAY *compNames,unsigned int inputID);

	//! Drukuje zawarto�� port�w do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie C_PortParameter_Container dla wszystkich wejs� do pliku. Parametry kt�re s� przekazane poprzez PutParams i zamienione na jednostki wewn�trzne
		Trzymane w zmiennej C_PortParameter_Container::Parameters
	@param[in] nazwa		nazwa pliku wraz ze �ciezk�. Sizezka powinna zawiera� podw�jne // 
	*/
	BOOL PrintPutParameters(char* nazwa);

	//! Drukuje zawarto�� port�w do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie C_PortParameter_Container dla wszystkich wejs� do pliku. Parametry kt�re s� przekazane poprzez GetParams i zamienione na jednostki zewn�trzne
		Trzymane w zmiennej C_PortParameter_Container::outParameters
	@param[in] nazwa		nazwa pliku wraz ze �ciezk�. Sizezka powinna zawiera� podw�jne // 
	*/
	BOOL PrintGetParameters(char* nazwa);
};
