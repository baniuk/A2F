#include "StdAfx.h"
#include "Data_To_Read.h"

Data_To_Read::Data_To_Read(void)
{
	pojemnosc = POJEMNOSC;	// ile elementów miesci
	for(int a=0;a<pojemnosc;a++)
		DATA_CONTAINER[a] = new char[MAX_STRING];
}

Data_To_Read::~Data_To_Read(void)
{
	for(int a=0;a<pojemnosc;a++)
		SAFE_DELETE_ARRAY(DATA_CONTAINER[a]);

}
