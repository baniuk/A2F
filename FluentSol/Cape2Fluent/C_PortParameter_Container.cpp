#include "StdAfx.h"
#include "C_PortParameter_Container.h"

C_PortParameter_Container::C_PortParameter_Container(void)
{
	unsigned int a;
	for (a=0;a<MAX_INPUTS;a++)
	{
		inputs[a] = NULL;
	}
}

C_PortParameter_Container::~C_PortParameter_Container(void)
{
	unsigned int a;
	for (a=0;a<MAX_INPUTS;a++)
	{
		SAFE_DELETE(inputs[a]);
	}
}

BOOL C_PortParameter_Container::RegisterComponentP(char* compName, int inputID)
/// \retval FAIL Je�li b��d - dodajemy kolejny komponent a nie ma ju� miejsca (MAX_EXPORTS) lub chcemy doda� wi�cej wejs� ni� dozwolone
/// \retval OK Je�li sukces
{
	if (inputID>MAX_INPUTS)
		return FAIL;

	if (inputID>=ile)	{
		inputs[inputID] = new C_Parameter_Container;
		ile++;
	}
	
	return inputs[inputID]->RegisterComponent(compName);
}

unsigned int C_PortParameter_Container::GetNumOfComponentsP(int inputID)
/// \retval 0 Je�li odnosimy si� do wej�cia wi�kszego ni� ilo�� dozwolonych
/// \retval UINT Ilo�� przechowywanych komponent�w dla danego wej�cia
{
	if (inputID>MAX_INPUTS)
		return 0;

	return inputs[inputID]->GetNumOfComponents();

}

char* C_PortParameter_Container::GetComponentNameP(unsigned int CompID, int inputID)
/// \retval NULL Je�li b��d - CompID wi�kszy ni� ilo�� przechowywanych komponent�w lub odnosimy si� do wej�cia wi�kszego ni� ilo�� dozwolonych
/// \retval ptr Je�li sukces
{
	if (inputID>MAX_INPUTS)
		return NULL;

	return inputs[inputID]->GetComponentName(CompID);
}

BOOL C_PortParameter_Container::AssignParamToCompP(unsigned int CompID, nazwy_parametrow paramID, double paramVal, int inputID)
/// \retval FAIL Je�li b��d - nie znaleziono nazwy komponentu lub paramID nie prawid�owy lub odnosimy si� do wej�cia wi�kszego ni� ilo�� dozwolonych
/// \retval OK Je�li sukces
{
	if (inputID>MAX_INPUTS)
		return FAIL;

	return inputs[inputID]->AssignParamToComp(CompID,paramID,paramVal);

}

BOOL C_PortParameter_Container::AssignParamToCompP(char* compName, nazwy_parametrow paramID, double paramVal, int inputID)
/// \retval FAIL Je�li b��d - nie znaleziono nazwy komponentu lub paramID nie prawid�owy lub odnosimy si� do wej�cia wi�kszego ni� ilo�� dozwolonych
/// \retval OK Je�li sukces
{
	if (inputID>MAX_INPUTS)
		return FAIL;

	return inputs[inputID]->AssignParamToComp(compName,paramID,paramVal);
}

int C_PortParameter_Container::GetCompIDP(char* compName, int inputID)
/// \retval -1 Je�li b��d - nie znaleziono nazwy komponentu lub odnosimy si� do wej�cia wi�kszego ni� ilo�� dozwolonych
/// \retval liczba Je�li sukces
{
	if (inputID>MAX_INPUTS)
		return -1;
	
	return inputs[inputID]->GetCompID(compName);
}

BOOL C_PortParameter_Container::GetParameterP( char* compName,nazwy_parametrow paramID, double& paramVal, int inputID )
/// \retval FAIL Je�li b��d - nie znaleziono odpowiednika paramID lub CompID jest > ni� ilo�� przechowywanych komponent�w lub nie znaleziono nazwy komponentu lub odnosimy si� do wej�cia wi�kszego ni� ilo�� dozwolonych
/// \retval OK Je�li sukces
{
	if (inputID>MAX_INPUTS)
		return FAIL;

	return inputs[inputID]->GetParameter(compName,paramID,paramVal);

}

BOOL C_PortParameter_Container::GetParameterP( unsigned int CompID, nazwy_parametrow paramID, double& paramVal, int inputID )
/// \retval FAIL Je�li b��d - nie znaleziono odpowiednika paramID lub CompID jest > ni� ilo�� przechowywanych komponent�w lub nie znaleziono nazwy komponentu lub odnosimy si� do wej�cia wi�kszego ni� ilo�� dozwolonych
/// \retval OK Je�li sukces
{
	if (inputID>MAX_INPUTS)
		return FAIL;

	return inputs[inputID]->GetParameter(CompID,paramID,paramVal);

}

BOOL C_PortParameter_Container::ClearAllP(void)
/// \retval zawsze OK
{
	for(int a=0;a<ile;a++)
		inputs[a]->ClearAll();
	return OK;
}

//unsigned int C_PortParameter_Container::GetNumInputs(void);

/*! 
Drukuje zawarto�� tablicy inputs, kt�ra zawiera obiekty C_Parameter_Container
*/
void C_PortParameter_Container::PrintParams(FILE* fid)
{
	unsigned int a;
	
	for(a=0;a<ile;a++)
	{
		fprintf(fid,"\t\tINPUT NO: %d:\n",a+1);
		inputs[a]->PrintParams(fid);
	}
}