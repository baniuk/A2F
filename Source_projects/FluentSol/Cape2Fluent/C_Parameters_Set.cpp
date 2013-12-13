#include "StdAfx.h"
#include "C_Parameters_Set.h"

C_Parameters_Set::C_Parameters_Set(void)
: Temperature(0)
, MoleFlow(0)
, Pressure(0)
, MoleFraction(0)
, Density(0)
, moleperkg(0)
, bTemperature(FAIL)
, bMoleFlow(FAIL)
, bPressure(FAIL)
, bMoleFraction(FAIL)
, bDensity(FAIL)
, bmoleperkg(FAIL)
{
}

C_Parameters_Set::~C_Parameters_Set(void)
{
}

void C_Parameters_Set::ClearAll()
{
	Temperature = 0;
	Pressure = 0;
	MoleFlow = 0;
	MoleFraction = 0;
	Density = 0;
	moleperkg = 0;
	bTemperature = FAIL;
	bPressure = FAIL;
	bMoleFlow = FAIL;
	bMoleFraction = FAIL;
	bDensity = FAIL;
	bmoleperkg = FAIL;
}
