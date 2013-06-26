#pragma once
#include "C_Parameters_Set.h"

//! Klasa jest kontainerem z parametrami opisuj�cymi poszczeg�lne materia�y, parametry powi�zane z danymi uzyskanymi z ASPENA oraz ze skryptu
/*!
Klasa przechowuj�ca parametry dla poszczeg�lnych sk�adnik�w strumienia. Powi�zana z ASPENEM, wype�niana g��wnie w klasie C_myRunProcess.h. Powi�zana jest tak�e z parametrami ze skryptu. 
Niekt�re parametry w tej klasie s� brane ze skryptu te�.
*/

class C_Parameter_Container
{
public:
	C_Parameter_Container(void);
	~C_Parameter_Container(void);
private:
	C_Parameters_Set *ParametersContainer[MAX_EXPORTS];
	char *compNames[MAX_EXPORTS];

public:
	//! Dodaje komponent (materia�) o danej nazwie do listy przechowywanych. Komponenety s� numerowane od 0 w kolejno�ci dodawania
	//! Przed u�yciem nalezy zarejestrowa� komponenty. Ponowna rejestracja nie jest w tej wersji mo�liwa!!
	//! Komponenty s� przechowywane w kolejnosci rejestrowania
	BOOL RegisterComponent(char* compName);
protected:
	//! ile jest aktualnie przechowywanych komponent�w
	unsigned int ile;
public:
	//! Zwraca ilosc przechowywanych komponent�w w klasie
	/*!
	 Funkcja zwraca ilosc przechowywanych komponent�w (materia��w) w klasie
	*/
	unsigned int GetNumOfComponents(void);

	//! Zwraca nazw� komponentu po podaniu jego id, lub NULL gdy go nie ma
	/*!
	 Funkcja zwraca nazw� komponentu po podaniu jego id, czyli numeru w kolejno�ci dodania przez RegisterComponent. NAzwa najcz�ciej b�dzie pochodzi�a z ASPENA
	 @param[in] CompID	numer komponentu 
	*/
	char* GetComponentName(unsigned int CompID);

	//! Dodaje parametr do komponentu - rozpoznaje po id
	/*!
	 Funkcja dodaje parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		numer komponentu 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	warto�� parametru 
	*/
	BOOL AssignParamToComp(unsigned int CompID, nazwy_parametrow paramID, double paramVal);

	//! Dodaje parametr do komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja dodaje parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia�u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	warto�� parametru 
	*/
	BOOL AssignParamToComp(char* compName, nazwy_parametrow paramID, double paramVal);

	//! Zwraca id komponentu na podstawie nazwy, lub -1 gdy nie ma go
	/*!
	 @param[in] compName	nazwa komponentu - materia�u 
	*/
	int GetCompID(char* compName);

	//! Zwraca parametr komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja zwraca parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia�u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	warto�� parametru 
	*/
	BOOL GetParameter(char* compName,nazwy_parametrow paramID, double& paramVal);

	//! Zwraca parametr komponentu - rozpoznaje po id
	/*!
	 Funkcja zwraca parametr do materia�u. Parametr to jedna z wla�ciwo�ci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		id komponentu - materia�u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	warto�� parametru 
	*/
	BOOL GetParameter(unsigned int CompID, nazwy_parametrow paramID, double& paramVal);

	//! Kasuje zawarto�� klasy - wszystkich danych
	/*! Kasuje zawarto�� klasy - wszystkich danych
	*/
	void ClearAll();

	//! Drukuje zawarto�� port�w do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie dla wszystkich wejs� do pliku
	@param[in] fid			identyfikator pliku gdzie ma by� zapisane
	*/
	void PrintParams(FILE* fid);
};

