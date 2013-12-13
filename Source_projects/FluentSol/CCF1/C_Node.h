#pragma once

/* Prosta klasa do obs�ugi list. W ka�dym w�le jest tablica z danymi i adres do nast�pnego 
w�z�a. Dodawanie kolejnych w�z�ow poprzez obiekt g��wny. Generalnie trzeba uwa�a� na to na kt�ry weze� pokauje bierz�cy odres. Zawsze powinien to by� pierwszy obiekt
Przyk��d:
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
*/
class C_Node
{
public:
	C_Node(void);
	C_Node(char* pdata);
	~C_Node(void);
	char data[128];				// dane
	C_Node* Get_Next(void);		// /zwraca adres kolejnego w�z�a w stosunku do aktualnego
	void Add_Next(char* pdata);	// dodaje kolejny wpis do listy. PRzetestowany dla obiektu g��wnego, powinien dzia�a� dla ka�dego w�z�a
	void Node_Init(void);	// u�ycie tylko dla pierwszego w�z�a
	unsigned int Get_Num_of_Nodes(void);	// zwraca ilosc w�z��w
	void Clear_All(void);	// kasuje wszyskie wez�y opr�cz tego dla kt�rego zosta�o wywo�ane (kasuje w d� do ko�ca)
	char* GetNthNodeData(unsigned int nr);	// zwraca ci�g dla nth w�z�a
private:
	C_Node* next;		// adres nast�pnego albo NULL jesli nie ma
	unsigned int nodenr;	// numer wez�a liczony od 0
};
