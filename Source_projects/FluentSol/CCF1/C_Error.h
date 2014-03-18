#pragma once
#include "c_node.h"

class C_Error :
	public C_Node
{
public:
	C_Error(void);
	C_Error(char* edata);
	virtual ~C_Error(void);

	void AddError(char* error);	// dodaje error do listy
	void PrintAll(void);		// zgrywa wszystko na dysk, ale nie czyœci
	void ClearErrorStatus(void);	// czyœci liste b³êdów
private:
	BOOL changes;	// tru jesli s¹ zmiany od ostatniego nagrania b³êdów
};
