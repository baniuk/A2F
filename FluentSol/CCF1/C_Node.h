#pragma once

/* Prosta klasa do obs³ugi list. W ka¿dym wêŸle jest tablica z danymi i adres do nastêpnego 
wêz³a. Dodawanie kolejnych wêz³ow poprzez obiekt g³ówny. Generalnie trzeba uwa¿aæ na to na który weze³ pokauje bierz¹cy odres. Zawsze powinien to byæ pierwszy obiekt
Przyk³¹d:
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
	C_Node* Get_Next(void);		// /zwraca adres kolejnego wêz³a w stosunku do aktualnego
	void Add_Next(char* pdata);	// dodaje kolejny wpis do listy. PRzetestowany dla obiektu g³ównego, powinien dzia³aæ dla ka¿dego wêz³a
	void Node_Init(void);	// u¿ycie tylko dla pierwszego wêz³a
	unsigned int Get_Num_of_Nodes(void);	// zwraca ilosc wêz³ów
	void Clear_All(void);	// kasuje wszyskie wez³y oprócz tego dla którego zosta³o wywo³ane (kasuje w dó³ do koñca)
	char* GetNthNodeData(unsigned int nr);	// zwraca ci¹g dla nth wêz³a
private:
	C_Node* next;		// adres nastêpnego albo NULL jesli nie ma
	unsigned int nodenr;	// numer wez³a liczony od 0
};
