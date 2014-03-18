#pragma once

#define POJEMNOSC 5

class Data_To_Read
{
public:
	Data_To_Read(void);
	~Data_To_Read(void);
	unsigned int ile;
	unsigned int pojemnosc;
	char *DATA_CONTAINER[POJEMNOSC];
};
