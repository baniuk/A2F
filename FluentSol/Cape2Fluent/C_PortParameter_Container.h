#pragma once
#include "c_parameter_container.h"

//! Klasa przechowuje kontainery z parametrami dla poszczeg�lnych wejsc, parametry powi�zane z danymi uzyskanymi z ASPENA oraz ze skryptu. Jedyna r�nica pomi�dzy klas� C_Parameter_Container.h jest taka, �e ta klasa przechowuje obiekty klasy C_Parameter_Container.h, dzi�ki czemu mo�na przechowywa� kilka wej��.
/*!
Klasa przechowuj�ca parametry dla poszczeg�lnych sk�adnik�w strumienia dla poszczeg�lnych wej��. Powi�zana z ASPENEM, wype�niana g��wnie w klasie C_myRunProcess.h. Powi�zana jest tak�e z parametrami ze skryptu. 
Niekt�re parametry w tej klasie s� brane ze skryptu te�.
Jedyna r�nica pomi�dzy klas� C_Parameter_Container.h jest taka, �e ta klasa przechowuje obiekty klasy C_Parameter_Container.h, dzi�ki czemu mo�na przechowywa� kilka wej��.
*/
class C_PortParameter_Container :
	public C_Parameter_Container
{
public:
	C_PortParameter_Container(void);
	~C_PortParameter_Container(void);
private:
	C_Parameter_Container *inputs[MAX_INPUTS];

public:
/*!
	 Dodaje komponent o danej nazwie do listy przechowywanych. Komponenety s� numerowane od 0 w kolejno�ci dodawania
	 wejscia od zera i musz� by� rejestrowane w kolejno�ci.
	 W klasie mozna przechowywac albo komponenty dla jedengo wejscia klasa bazowa jest inicjalizowana automatycznie) albo tablice klas bazowych!! Zalezy jak sieodwo�ujemy (przez jakie funkcje)
	 Uwaga na zmienn� ile kt�ra moze przechowywac albo ilosc komponent�w albo ilosc wejsc
	 ile jest aktualnie przechowywanych wej�� (uzywa do tego celu zmiennej ile z klasy bazowej (bo kazdy obiekt z tablicy inputs i tak ma swoj� w�asn� ile
*/
	BOOL RegisterComponentP(char* compName, int inputID);
public:
	//! Zwraca ilosc przechowywanych komponent�w w klasie dla danego wejscia
	/*!
	 Funkcja zwraca ilosc przechowywanych komponent�w (materia��w) w klasie
	 @param[in] inputID		numer wej�cia w kolejno�ci rejestrowania 
	*/
	unsigned int GetNumOfComponentsP(int inputID);

	//! Zwraca nazw� komponentu po podaniu jego id, lub NULL gdy go nie ma
	/*!
	 Funkcja zwraca nazw� komponentu po podaniu jego id, czyli numeru w kolejno�ci dodania przez RegisterComponent. NAzwa najcz�ciej b�dzie pochodzi�a z ASPENA
	 @param[in] CompID	numer komponentu 
	 @param[in] inputID		numer wej�cia w kolejno�ci rejestrowania 
	*/
	char* GetComponentNameP(unsigned int CompID, int inputID);

	//! Dodaje parametr do komponentu - rozpoznaje po id
	/*!
	 Funkcja dodaje parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		numer komponentu 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	warto�� parametru 
	 @param[in] inputID		numer wej�cia w kolejno�ci rejestrowania 
	*/
	BOOL AssignParamToCompP(unsigned int CompID, nazwy_parametrow paramID, double paramVal, int inputID);

	//! Dodaje parametr do komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja dodaje parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia�u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	warto�� parametru 
	 @param[in] inputID		numer wej�cia w kolejno�ci rejestrowania 
	*/
	BOOL AssignParamToCompP(char* compName, nazwy_parametrow paramID, double paramVal, int inputID);

	//! Zwraca id komponentu na podstawie nazwy, lub -1 gdy nie ma go
	/*!
	 @param[in] compName	nazwa komponentu - materia�u 
	 @param[in] inputID		numer wej�cia w kolejno�ci rejestrowania 
	*/
	int GetCompIDP(char* compName, int inputID);

	//! Zwraca parametr komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja zwraca parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia�u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	warto�� parametru 
	 @param[in] inputID		numer wej�cia w kolejno�ci rejestrowania 
	*/
	BOOL GetParameterP(char* compName,nazwy_parametrow paramID, double& paramVal, int inputID);

	//! Zwraca parametr komponentu - rozpoznaje po id
	/*!
	 Funkcja zwraca parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		id komponentu - materia�u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	warto�� parametru 
	 @param[in] inputID		numer wej�cia w kolejno�ci rejestrowania 
	*/
	BOOL GetParameterP(unsigned int CompID, nazwy_parametrow paramID, double& paramVal, int inputID);

	//! Kasuje zawarto�� klasy - wszystkich danych wszystkich wej��
	/*! Kasuje zawarto�� klasy - wszystkich danych  wszystkich wej��
	*/
	BOOL ClearAllP(void);

	//! Drukuje zawarto�� port�w do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie dla wszystkich wejs� do pliku. Dziedziczenie jest �le zrobione - mo�na by lepiej
	@param[in] fid			identyfikator pliku gdzie ma by� zapisane
	*/
	void PrintParams(FILE* fid);

};
