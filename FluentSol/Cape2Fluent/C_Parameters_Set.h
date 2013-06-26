#pragma once


enum nazwy_parametrow
{
	PARAM_TEMPERATURE,
	PARAM_MOLEFLOW,
	PARAM_PRESSURE,
	PARAM_MOLEFRACTION,
	PARAM_DENSITY,
	PARAM_MOLEPERKG
};

//!Przechowuje zbi�r podstawowych parametr�w. Enum musi si� zgadza� z przechowywanymi parametrami
/*! Warto�ci nazw_parametr�w musi si� zgadza� z przechowywanymi danymi. Parametry zdefiniowane w C_Parameters_Set.h
Dodatkowo przechowuje informacj� czy w danym polu jest dana aktualna czy nie.
*/

class C_Parameters_Set
{
public:
	C_Parameters_Set(void);
	~C_Parameters_Set(void);
	//! Temperatura pojedy�czego zwi�zku
	double Temperature;
	//! Przep�yw pojedy�czego zwi�zku
	double MoleFlow;
	//! Ci�nienie pojedy�czego zwi�zku
	double Pressure;
	//! Udzia� molowy pojedy�czego zwi�zku
	double MoleFraction;
	//! G�sto�� zwi�zku
	double Density;
	//! ilosc moli na kilogram substancji
	double moleperkg;
	//! czy cos jest w odpowiednich polach, OK je�li tak,FAIL nie
	BOOL bTemperature;
	BOOL bMoleFlow;
	BOOL bPressure;
	BOOL bMoleFraction;
	BOOL bDensity;
	BOOL bmoleperkg;

	/// Kasuje zawarto�� struktury
	/*! Kasuje zawarto�� struktury - ustawia zera a reszt� na FALSE
	*/
	void ClearAll();
};

//! Define a postfix increment operator for Suit.
inline nazwy_parametrow operator++( nazwy_parametrow &rs, int ) {
	return rs = (nazwy_parametrow)(rs + 1);
}
