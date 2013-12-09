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

//!Przechowuje zbiór podstawowych parametrów. Enum musi siê zgadzaæ z przechowywanymi parametrami
/*! Wartoœci nazw_parametrów musi siê zgadzaæ z przechowywanymi danymi. Parametry zdefiniowane w C_Parameters_Set.h
Dodatkowo przechowuje informacjê czy w danym polu jest dana aktualna czy nie.
*/

class C_Parameters_Set
{
public:
	C_Parameters_Set(void);
	~C_Parameters_Set(void);
	//! Temperatura pojedyñczego zwi¹zku
	double Temperature;
	//! Przep³yw pojedyñczego zwi¹zku
	double MoleFlow;
	//! Ciœnienie pojedyñczego zwi¹zku
	double Pressure;
	//! Udzia³ molowy pojedyñczego zwi¹zku
	double MoleFraction;
	//! Gêstoœæ zwi¹zku
	double Density;
	//! ilosc moli na kilogram substancji
	double moleperkg;
	//! czy cos jest w odpowiednich polach, OK jeœli tak,FAIL nie
	BOOL bTemperature;
	BOOL bMoleFlow;
	BOOL bPressure;
	BOOL bMoleFraction;
	BOOL bDensity;
	BOOL bmoleperkg;

	/// Kasuje zawartoœæ struktury
	/*! Kasuje zawartoœæ struktury - ustawia zera a resztê na FALSE
	*/
	void ClearAll();
};

//! Define a postfix increment operator for Suit.
inline nazwy_parametrow operator++( nazwy_parametrow &rs, int ) {
	return rs = (nazwy_parametrow)(rs + 1);
}
