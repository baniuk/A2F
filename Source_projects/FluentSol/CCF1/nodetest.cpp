// nodetest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
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
}

