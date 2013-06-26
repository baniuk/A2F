#pragma once
#include "C_Parameters_Set.h"

//! Klasa jest kontainerem z parametrami opisuj¹cymi poszczególne materia³y, parametry powi¹zane z danymi uzyskanymi z ASPENA oraz ze skryptu
/*!
Klasa przechowuj¹ca parametry dla poszczególnych sk³adników strumienia. Powi¹zana z ASPENEM, wype³niana g³ównie w klasie C_myRunProcess.h. Powi¹zana jest tak¿e z parametrami ze skryptu. 
Niektóre parametry w tej klasie s¹ brane ze skryptu te¿.
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
	//! Dodaje komponent (materia³) o danej nazwie do listy przechowywanych. Komponenety s¹ numerowane od 0 w kolejnoœci dodawania
	//! Przed u¿yciem nalezy zarejestrowaæ komponenty. Ponowna rejestracja nie jest w tej wersji mo¿liwa!!
	//! Komponenty s¹ przechowywane w kolejnosci rejestrowania
	BOOL RegisterComponent(char* compName);
protected:
	//! ile jest aktualnie przechowywanych komponentów
	unsigned int ile;
public:
	//! Zwraca ilosc przechowywanych komponentów w klasie
	/*!
	 Funkcja zwraca ilosc przechowywanych komponentów (materia³ów) w klasie
	*/
	unsigned int GetNumOfComponents(void);

	//! Zwraca nazwê komponentu po podaniu jego id, lub NULL gdy go nie ma
	/*!
	 Funkcja zwraca nazwê komponentu po podaniu jego id, czyli numeru w kolejnoœci dodania przez RegisterComponent. NAzwa najczêœciej bêdzie pochodzi³a z ASPENA
	 @param[in] CompID	numer komponentu 
	*/
	char* GetComponentName(unsigned int CompID);

	//! Dodaje parametr do komponentu - rozpoznaje po id
	/*!
	 Funkcja dodaje parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		numer komponentu 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	wartoœæ parametru 
	*/
	BOOL AssignParamToComp(unsigned int CompID, nazwy_parametrow paramID, double paramVal);

	//! Dodaje parametr do komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja dodaje parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia³u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	wartoœæ parametru 
	*/
	BOOL AssignParamToComp(char* compName, nazwy_parametrow paramID, double paramVal);

	//! Zwraca id komponentu na podstawie nazwy, lub -1 gdy nie ma go
	/*!
	 @param[in] compName	nazwa komponentu - materia³u 
	*/
	int GetCompID(char* compName);

	//! Zwraca parametr komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja zwraca parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia³u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	wartoœæ parametru 
	*/
	BOOL GetParameter(char* compName,nazwy_parametrow paramID, double& paramVal);

	//! Zwraca parametr komponentu - rozpoznaje po id
	/*!
	 Funkcja zwraca parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		id komponentu - materia³u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	wartoœæ parametru 
	*/
	BOOL GetParameter(unsigned int CompID, nazwy_parametrow paramID, double& paramVal);

	//! Kasuje zawartoœæ klasy - wszystkich danych
	/*! Kasuje zawartoœæ klasy - wszystkich danych
	*/
	void ClearAll();

	//! Drukuje zawartoœæ portów do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie dla wszystkich wejsæ do pliku
	@param[in] fid			identyfikator pliku gdzie ma byæ zapisane
	*/
	void PrintParams(FILE* fid);
};

