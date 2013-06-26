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
	void PrintAll(void);		// zgrywa wszystko na dysk, ale nie czy�ci
	void ClearErrorStatus(void);	// czy�ci liste b��d�w
private:
	BOOL changes;	// tru jesli s� zmiany od ostatniego nagrania b��d�w
};
