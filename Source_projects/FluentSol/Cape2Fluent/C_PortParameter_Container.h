#pragma once
#include "c_parameter_container.h"

//! Klasa przechowuje kontainery z parametrami dla poszczególnych wejsc, parametry powi¹zane z danymi uzyskanymi z ASPENA oraz ze skryptu. Jedyna ró¿nica pomiêdzy klas¹ C_Parameter_Container.h jest taka, ¿e ta klasa przechowuje obiekty klasy C_Parameter_Container.h, dziêki czemu mo¿na przechowywaæ kilka wejœæ.
/*!
Klasa przechowuj¹ca parametry dla poszczególnych sk³adników strumienia dla poszczególnych wejœæ. Powi¹zana z ASPENEM, wype³niana g³ównie w klasie C_myRunProcess.h. Powi¹zana jest tak¿e z parametrami ze skryptu. 
Niektóre parametry w tej klasie s¹ brane ze skryptu te¿.
Jedyna ró¿nica pomiêdzy klas¹ C_Parameter_Container.h jest taka, ¿e ta klasa przechowuje obiekty klasy C_Parameter_Container.h, dziêki czemu mo¿na przechowywaæ kilka wejœæ.
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
	 Dodaje komponent o danej nazwie do listy przechowywanych. Komponenety s¹ numerowane od 0 w kolejnoœci dodawania
	 wejscia od zera i musz¹ byæ rejestrowane w kolejnoœci.
	 W klasie mozna przechowywac albo komponenty dla jedengo wejscia klasa bazowa jest inicjalizowana automatycznie) albo tablice klas bazowych!! Zalezy jak sieodwo³ujemy (przez jakie funkcje)
	 Uwaga na zmienn¹ ile która moze przechowywac albo ilosc komponentów albo ilosc wejsc
	 ile jest aktualnie przechowywanych wejœæ (uzywa do tego celu zmiennej ile z klasy bazowej (bo kazdy obiekt z tablicy inputs i tak ma swoj¹ w³asn¹ ile
*/
	BOOL RegisterComponentP(char* compName, int inputID);
public:
	//! Zwraca ilosc przechowywanych komponentów w klasie dla danego wejscia
	/*!
	 Funkcja zwraca ilosc przechowywanych komponentów (materia³ów) w klasie
	 @param[in] inputID		numer wejœcia w kolejnoœci rejestrowania 
	*/
	unsigned int GetNumOfComponentsP(int inputID);

	//! Zwraca nazwê komponentu po podaniu jego id, lub NULL gdy go nie ma
	/*!
	 Funkcja zwraca nazwê komponentu po podaniu jego id, czyli numeru w kolejnoœci dodania przez RegisterComponent. NAzwa najczêœciej bêdzie pochodzi³a z ASPENA
	 @param[in] CompID	numer komponentu 
	 @param[in] inputID		numer wejœcia w kolejnoœci rejestrowania 
	*/
	char* GetComponentNameP(unsigned int CompID, int inputID);

	//! Dodaje parametr do komponentu - rozpoznaje po id
	/*!
	 Funkcja dodaje parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		numer komponentu 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	wartoœæ parametru 
	 @param[in] inputID		numer wejœcia w kolejnoœci rejestrowania 
	*/
	BOOL AssignParamToCompP(unsigned int CompID, nazwy_parametrow paramID, double paramVal, int inputID);

	//! Dodaje parametr do komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja dodaje parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia³u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[in] paramVal	wartoœæ parametru 
	 @param[in] inputID		numer wejœcia w kolejnoœci rejestrowania 
	*/
	BOOL AssignParamToCompP(char* compName, nazwy_parametrow paramID, double paramVal, int inputID);

	//! Zwraca id komponentu na podstawie nazwy, lub -1 gdy nie ma go
	/*!
	 @param[in] compName	nazwa komponentu - materia³u 
	 @param[in] inputID		numer wejœcia w kolejnoœci rejestrowania 
	*/
	int GetCompIDP(char* compName, int inputID);

	//! Zwraca parametr komponentu - rozpoznaje po nazwie
	/*!
	 Funkcja zwraca parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] compName	nazwa komponentu - materia³u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	wartoœæ parametru 
	 @param[in] inputID		numer wejœcia w kolejnoœci rejestrowania 
	*/
	BOOL GetParameterP(char* compName,nazwy_parametrow paramID, double& paramVal, int inputID);

	//! Zwraca parametr komponentu - rozpoznaje po id
	/*!
	 Funkcja zwraca parametr do materia³u. Parametr to jedna z wlaœciwoœci fizycznych zdefinowana w klasie C_Parameters_Set.h
	 @param[in] CompID		id komponentu - materia³u 
	 @param[in] paramID		nazwa parametru do dodania zgodna z definicja w C_Parameters_Set.h 
	 @param[out] paramVal	wartoœæ parametru 
	 @param[in] inputID		numer wejœcia w kolejnoœci rejestrowania 
	*/
	BOOL GetParameterP(unsigned int CompID, nazwy_parametrow paramID, double& paramVal, int inputID);

	//! Kasuje zawartoœæ klasy - wszystkich danych wszystkich wejœæ
	/*! Kasuje zawartoœæ klasy - wszystkich danych  wszystkich wejœæ
	*/
	BOOL ClearAllP(void);

	//! Drukuje zawartoœæ portów do pliku
	/*! Zapisuje wszystkie parametry trzymane w klasie dla wszystkich wejsæ do pliku. Dziedziczenie jest Ÿle zrobione - mo¿na by lepiej
	@param[in] fid			identyfikator pliku gdzie ma byæ zapisane
	*/
	void PrintParams(FILE* fid);

};
