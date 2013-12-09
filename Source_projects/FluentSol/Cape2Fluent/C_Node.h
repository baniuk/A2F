#pragma once

//! Prosta klasa do obs�ugi list jednokierunkowych
/*! Prosta klasa do obs�ugi list. W ka�dym w�le jest tablica z danymi i adres do nast�pnego 
w�z�a. Dodawanie kolejnych w�z�ow poprzez obiekt g��wny. Generalnie trzeba uwa�a� na to na kt�ry weze� pokauje bierz�cy odres. Zawsze powinien to by� pierwszy obiekt
Przed u�yciem trzeba zainicjalizowa� pierwszy obiekt funkcj� C_Node::Node_Init

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
	char data[MAX_LENGTH_NODE];	/*!< dane tekstowe przechowywane w pojedy�czym w�le definicje.h - d�ugo�� */

	//! Zwraca adres kolejnego w�z�a w stosunku do aktualnego
	/*!
	Zwraca adres kolejnego w�z�a w stosunku do aktualnego, lub NULL gdy jest to w�ze� ostatni
	*/
	C_Node* Get_Next(void);		

	//! Dodaje kolejny wpis do listy.
	/*!
	 Dodaje kolejny wpis do listy.
	 @param[in] pdata ci�g tekstowy z wpisem o d�ugo�ci MAX_LENGTH_NODE w definicje.h
	*/
	void Add_Next(char* pdata);	

	//! Inicjalizacja listy, powinno by� u�yte jako pierwsze
	/*!
	 Inicjalizacja listy, powinno by� u�yte jako pierwsze
	*/
	void Node_Init(void);	

	//! Zwraca ilosc w�z��w
	/*!
	 Zwraca ilosc w�z��w przechowywanych w li�cie
	*/
	unsigned int Get_Num_of_Nodes(void);	

	//! Kasuje wszyskie wez�y.
	/*!
	 Kasuje wszyskie wez�y od tego dla kt�rego zosta�o wywo�ane (kasuje w d� do ko�ca). Czy�ci list�
	*/
	void Clear_All(void);	

	//! Zwraca ci�g dla nth w�z�a
	/*!
	 Zwraca ci�g przechowywany w nth w�le (liczone od 0)
	 @param[in] nr numer w�z�a
	*/
	char* GetNthNodeData(unsigned int nr);	
private:
	C_Node* next;		/*!< adres nast�pnego albo NULL jesli nie ma*/
	unsigned int nodenr;	/*!< numer wez�a liczony od 0*/
};
