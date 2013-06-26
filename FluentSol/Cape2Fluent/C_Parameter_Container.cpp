#include "StdAfx.h"
#include "C_Parameter_Container.h"

C_Parameter_Container::C_Parameter_Container(void)
: ile(0)
{
	for(int a=0;a<MAX_EXPORTS;a++)	{
		ParametersContainer[a] = NULL;
		compNames[a] = NULL;
	}
}

C_Parameter_Container::~C_Parameter_Container(void)
{
	for (int a=0;a<MAX_EXPORTS;a++)
	{
		SAFE_DELETE_ARRAY(compNames[a]);
		SAFE_DELETE(ParametersContainer[a]);
	}
}

// Dodaje komponent o danej nazwie do listy przechowywanych. Komponenety s� numerowane od 0 w kolejno�ci dodawania
BOOL C_Parameter_Container::RegisterComponent(char* compName)
/// \retval FAIL Je�li b��d - dodajemy kolejny komponent a nie ma ju� miejsca (MAX_EXPORTS)
/// \retval OK Je�li sukces
{
	if(ile>=MAX_EXPORTS)
		return FAIL;
	ParametersContainer[ile] = new C_Parameters_Set;
	compNames[ile] = new char[MAX_COMPONENT_NAME];
//	_strupr_s(compName,MAX_COMPONENT_NAME);
	strcpy_s(compNames[ile],MAX_COMPONENT_NAME,compName);

	ile++;
	return OK;
}

// Zwraca ilosc przechowywanych komponent�w w klasie
unsigned int C_Parameter_Container::GetNumOfComponents(void)
/// \retval UINT Ilo�� przechowywanych komponent�w
{
	return ile;
}

// Zwraca nazw� komponentu po podaniu jego id, lub NULL gdy go nie ma
char* C_Parameter_Container::GetComponentName(unsigned int CompID)
/// \retval NULL Je�li b��d - CompID wi�kszy ni� ilo�� przechowywanych komponent�w
/// \retval ptr Je�li sukces
{
	if (CompID<ile)
	{
		return compNames[CompID];
	} 
	else
	{
		return NULL;
	}
}

/*! 
	Dodaje parametr do komponentu - rozpoznaje po nazwie.  Ustawia tak�e pole bXX w klasie przechowuj�cej parametry C_Parameters_Set na OK co znaczy
	ze co� tam jest
*/
BOOL C_Parameter_Container::AssignParamToComp(unsigned int CompID, nazwy_parametrow paramID, double paramVal)
/// \retval FAIL Je�li b��d - CompID wi�kszy ni� ilo�� przechowywanych komponent�w lub paramVal nie prawid�owy
/// \retval OK Je�li sukces
{
	if(CompID>=ile)
		return FAIL;

	switch(paramID)
	{
	case PARAM_TEMPERATURE:
		ParametersContainer[CompID]->Temperature = paramVal;
		ParametersContainer[CompID]->bTemperature = OK;
		break;
	case PARAM_MOLEFLOW:
		ParametersContainer[CompID]->MoleFlow = paramVal;
		ParametersContainer[CompID]->bMoleFlow = OK;
		break;
	case PARAM_MOLEFRACTION:
		ParametersContainer[CompID]->MoleFraction = paramVal;
		ParametersContainer[CompID]->bMoleFraction = OK;
		break;
	case PARAM_PRESSURE:
		ParametersContainer[CompID]->Pressure = paramVal;
		ParametersContainer[CompID]->bPressure = OK;
		break;
	case PARAM_DENSITY:
		ParametersContainer[CompID]->Density = paramVal;
		ParametersContainer[CompID]->bDensity = OK;
		break;
	case PARAM_MOLEPERKG:
		ParametersContainer[CompID]->moleperkg = paramVal;
		ParametersContainer[CompID]->bmoleperkg = OK;
		break;
	default:
		return FAIL;
	}
	return OK;
}

BOOL C_Parameter_Container::AssignParamToComp(char* compName, nazwy_parametrow paramID, double paramVal)
/// \retval FAIL Je�li b��d - nie znaleziono nazwy komponentu lub paramID nie prawid�owy
/// \retval OK Je�li sukces
{
	int id;
	id = GetCompID(compName);
	if(id<0)
		return FAIL;
	return AssignParamToComp(id,paramID,paramVal);
}

// zwraca id komponentu na podstawie nazwy, lub -1 gdy nie ma go
int C_Parameter_Container::GetCompID(char* compName)
/// \retval -1 Je�li b��d - nie znaleziono nazwy komponentu
/// \retval liczba Je�li sukces
{
	char local1[MAX_COMPONENT_NAME];
	char local2[MAX_COMPONENT_NAME];
	strcpy_s(local1,MAX_COMPONENT_NAME,compName);
	_strupr_s(local1,MAX_COMPONENT_NAME);
	unsigned int a;
	for(a=0;a<ile;a++)	{
		
		strcpy_s(local2,MAX_COMPONENT_NAME,compNames[a]);
		
		_strupr_s(local2,MAX_COMPONENT_NAME);
		if(strcmp(local1,local2)==0)
			return a;
	}
	return -1;
}

BOOL C_Parameter_Container::GetParameter(char* compName,nazwy_parametrow paramID, double& paramVal)
/// \retval FAIL Je�li b��d - nie znaleziono odpowiednika paramID lub CompID jest > ni� ilo�� przechowywanych komponent�w lub nie znaleziono nazwy komponentu
/// \retval OK Je�li sukces
{
	int id;
	id = GetCompID(compName);
	if(id<0)
		return FAIL;
	return GetParameter(id,paramID,paramVal);
}

BOOL C_Parameter_Container::GetParameter(unsigned int CompID, nazwy_parametrow paramID, double& paramVal)
/// \retval FAIL Je�li b��d - nie znaleziono odpowiednika paramID lub CompID jest > ni� ilo�� przechowywanych komponent�w, lub zwracany komponent nie by� nigdy zainicjalizowany
/// \retval OK Je�li sukces
{
	BOOL ret;
	if(CompID>=ile)
		return FAIL;

	switch(paramID)
	{
	case PARAM_TEMPERATURE:
		ret = ParametersContainer[CompID]->bTemperature;
		paramVal = ParametersContainer[CompID]->Temperature;
		break;
	case PARAM_MOLEFLOW:
		ret = ParametersContainer[CompID]->bMoleFlow;
		paramVal = ParametersContainer[CompID]->MoleFlow;
		break;
	case PARAM_MOLEFRACTION:
		ret = ParametersContainer[CompID]->bMoleFraction;
		paramVal = ParametersContainer[CompID]->MoleFraction;
		break;
	case PARAM_PRESSURE:
		ret = ParametersContainer[CompID]->bPressure;
		paramVal = ParametersContainer[CompID]->Pressure;
		break;
	case PARAM_DENSITY:
		ret = ParametersContainer[CompID]->bDensity;
		paramVal = ParametersContainer[CompID]->Density;
		break;
	case PARAM_MOLEPERKG:
		ret = ParametersContainer[CompID]->bmoleperkg;
		paramVal = ParametersContainer[CompID]->moleperkg;
		break;
	default:
		return FAIL;
	}
	return ret;

}

void C_Parameter_Container::ClearAll()
{
	for (unsigned int a=0;a<GetNumOfComponents();a++)
		ParametersContainer[a]->ClearAll();
}

/*! 
	Drukuje zawarto�� tak naprawd� klasy C_Parameters_Set
*/
void C_Parameter_Container::PrintParams(FILE* fid)
{

	unsigned int a;
	double paramVal;
	BOOL ret;

	for(a=0;a<GetNumOfComponents();a++)
	{
		fprintf(fid,"Component name: %s:\n",GetComponentName(a));
		ret = GetParameter(a, PARAM_TEMPERATURE, paramVal);
		if(ret==OK)
			fprintf(fid,"\tTEMPERATURE:\t%f\n",paramVal);
		else
			fprintf(fid,"\tTEMPERATURE:\t%s\n","not set or used");
		ret = GetParameter(a, PARAM_MOLEFLOW, paramVal);
		if(ret==OK)
			fprintf(fid,"\tFLOW:\t\t%f\n",paramVal);
		else
			fprintf(fid,"\tFLOW:\t\t%s\n","not set or used");
		ret = GetParameter(a, PARAM_MOLEFRACTION, paramVal);
		if(ret==OK)
			fprintf(fid,"\tMOLEFRACTION:\t%f\n",paramVal);
		else
			fprintf(fid,"\tMOLEFRACTION:\t%s\n","not set or used");
		ret = GetParameter(a, PARAM_PRESSURE, paramVal);
		if(ret==OK)
			fprintf(fid,"\tPRESSURE:\t%f\n",paramVal);
		else
			fprintf(fid,"\tPRESSURE:\t%s\n","not set or used");
		ret = GetParameter(a, PARAM_DENSITY, paramVal);
		if(ret==OK)
			fprintf(fid,"\tDENSITY:\t%f\n",paramVal);
		else
			fprintf(fid,"\tDENSITY:\t%s\n","not set or used");
		ret = GetParameter(a, PARAM_MOLEPERKG, paramVal);
		if(ret==OK)
			fprintf(fid,"\tMOLEPERKG:\t%f\n",paramVal);
		else
			fprintf(fid,"\tMOLEPERKG:\t%s\n","not set or used");
		fprintf(fid,"\n");
	}


}