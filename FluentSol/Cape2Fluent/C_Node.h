#pragma once

//! Prosta klasa do obs³ugi list jednokierunkowych
/*! Prosta klasa do obs³ugi list. W ka¿dym wêŸle jest tablica z danymi i adres do nastêpnego 
wêz³a. Dodawanie kolejnych wêz³ow poprzez obiekt g³ówny. Generalnie trzeba uwa¿aæ na to na który weze³ pokauje bierz¹cy odres. Zawsze powinien to byæ pierwszy obiekt
Przed u¿yciem trzeba zainicjalizowaæ pierwszy obiekt funkcj¹ C_Node::Node_Init

\code
	unsigned int ilenode,a;
	C_Node node("node 1");
	node.Node_Init();
	C_Node* tmp;

	node.Add_Next("node 2");
	node.Add_Next("node 3");

	ilenode = node.Get_Num_of_Nodes();

	tmp = &node;
	for(a=0;a<ilenode;a++)
	{
		printf("%s\n",tmp->data);
		tmp = tmp->Get_Next();
	}

	node.Clear_All();
	
	tmp = &node;
	ilenode = node.Get_Num_of_Nodes();
	for(a=0;a<ilenode;a++)
	{
		printf("%s\n",tmp->data);
		tmp = tmp->Get_Next();
	}
	
	node.Add_Next("node 2a");

	tmp = &node;
	ilenode = node.Get_Num_of_Nodes();
	for(a=0;a<ilenode;a++)
	{
		printf("%s\n",tmp->data);
		tmp = tmp->Get_Next();
	}

	_getch();
	return 0;
 \endcode
*/
class C_Node
{
public:
	C_Node(void);
	C_Node(char* pdata);
	~C_Node(void);
	char data[MAX_LENGTH_NODE];	/*!< dane tekstowe przechowywane w pojedyñczym wêŸle definicje.h - d³ugoœæ */

	//! Zwraca adres kolejnego wêz³a w stosunku do aktualnego
	/*!
	Zwraca adres kolejnego wêz³a w stosunku do aktualnego, lub NULL gdy jest to wêze³ ostatni
	*/
	C_Node* Get_Next(void);		

	//! Dodaje kolejny wpis do listy.
	/*!
	 Dodaje kolejny wpis do listy.
	 @param[in] pdata ci¹g tekstowy z wpisem o d³ugoœci MAX_LENGTH_NODE w definicje.h
	*/
	void Add_Next(char* pdata);	

	//! Inicjalizacja listy, powinno byæ u¿yte jako pierwsze
	/*!
	 Inicjalizacja listy, powinno byæ u¿yte jako pierwsze
	*/
	void Node_Init(void);	

	//! Zwraca ilosc wêz³ów
	/*!
	 Zwraca ilosc wêz³ów przechowywanych w liœcie
	*/
	unsigned int Get_Num_of_Nodes(void);	

	//! Kasuje wszyskie wez³y.
	/*!
	 Kasuje wszyskie wez³y od tego dla którego zosta³o wywo³ane (kasuje w dó³ do koñca). Czyœci listê
	*/
	void Clear_All(void);	

	//! Zwraca ci¹g dla nth wêz³a
	/*!
	 Zwraca ci¹g przechowywany w nth wêŸle (liczone od 0)
	 @param[in] nr numer wêz³a
	*/
	char* GetNthNodeData(unsigned int nr);	
private:
	C_Node* next;		/*!< adres nastêpnego albo NULL jesli nie ma*/
	unsigned int nodenr;	/*!< numer wez³a liczony od 0*/
};
