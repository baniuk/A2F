#pragma once
#include "c_node.h"

//! Klasa do obs�ugi b��d�w.
/*! Klasa umo�liwia przechowanie dowolnej ilo�ci komunikat�w o b��dach a nast�pnie nagranie ich na dysk. Maksymalna d�ugo�� komunikatu jest limitowana definicj� MAX_ERROR w definicje.h
*/

class C_Error :
	public C_Node
{
public:
	C_Error(void);
	C_Error(char* edata);
	virtual ~C_Error(void);

	//! Dodaje komunikat o b��dzie do listy
	/*!
	Dodaje komunikat o b��dzie do listy oraz ustawia zmienn� C_Error::changes na FALSE
	 @param[in] error ci�g tekstowy z b��dem
	*/
	void AddError(char* error);	// dodaje error do listy

	//! Zgrywa wszystkie b�edy na dysk
	/*!
	Zgrywa wszystkie b�edy na dysk do domy�lemgo pliku C:errorlog.txt. Komunikaty nie s� czyszczone oraz ustawia zmienn� C_Error::changes na FALSE
	*/
	void PrintAll(void);		// zgrywa wszystko na dysk, ale nie czy�ci

	//! Czy�ci wszystkie komunikaty
	/*!
	Czy�ci wszystkie komunikaty - zeruje ca�� list� oraz ustawia zmienn� C_Error::changes na FALSE
	*/
	void ClearErrorStatus(void);	// czy�ci liste b��d�w
private:
	//! Ta zmienna jest ustawiana na TRUE je�li od ostatniego czyszczenia lub nagrania na dysk co� si� zmieni�o
	BOOL changes;	// tru jesli s� zmiany od ostatniego nagrania b��d�w
};
