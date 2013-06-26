#pragma once
#include "c_node.h"

//! Klasa do obs³ugi b³êdów.
/*! Klasa umo¿liwia przechowanie dowolnej iloœci komunikatów o b³êdach a nastêpnie nagranie ich na dysk. Maksymalna d³ugoœæ komunikatu jest limitowana definicj¹ MAX_ERROR w definicje.h
*/

class C_Error :
	public C_Node
{
public:
	C_Error(void);
	C_Error(char* edata);
	virtual ~C_Error(void);

	//! Dodaje komunikat o b³êdzie do listy
	/*!
	Dodaje komunikat o b³êdzie do listy oraz ustawia zmienn¹ C_Error::changes na FALSE
	 @param[in] error ci¹g tekstowy z b³êdem
	*/
	void AddError(char* error);	// dodaje error do listy

	//! Zgrywa wszystkie b³edy na dysk
	/*!
	Zgrywa wszystkie b³edy na dysk do domyœlemgo pliku C:errorlog.txt. Komunikaty nie s¹ czyszczone oraz ustawia zmienn¹ C_Error::changes na FALSE
	*/
	void PrintAll(void);		// zgrywa wszystko na dysk, ale nie czyœci

	//! Czyœci wszystkie komunikaty
	/*!
	Czyœci wszystkie komunikaty - zeruje ca³¹ listê oraz ustawia zmienn¹ C_Error::changes na FALSE
	*/
	void ClearErrorStatus(void);	// czyœci liste b³êdów
private:
	//! Ta zmienna jest ustawiana na TRUE jeœli od ostatniego czyszczenia lub nagrania na dysk coœ siê zmieni³o
	BOOL changes;	// tru jesli s¹ zmiany od ostatniego nagrania b³êdów
};
