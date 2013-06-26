#include "StdAfx.h"
#include "C_Node.h"

C_Node::C_Node(void)
{
	next=NULL;
}

C_Node::C_Node(char* pdata)
{
	next=NULL;
	strcpy_s(data,MAX_LENGTH_NODE,pdata);
}

C_Node::~C_Node(void)
{
	if(next!=NULL)	{
		delete next;
		next = NULL;
	}
}

C_Node* C_Node::Get_Next(void)
/// \retval C_Node *ptr Adres kolejnego wêz³a
/// \retval NULL Jeœli nie ma nastêpnego ju¿
{
	return next;
}

void C_Node::Add_Next(char* pdata)
{
	unsigned int nr = Get_Num_of_Nodes();
	unsigned int a;
	C_Node* tmp=this;
	for(a=nodenr;a<nr-1;a++)
	{
		tmp = tmp->Get_Next();
	}
	tmp->next = new C_Node;
	strcpy_s(tmp->next->data,MAX_LENGTH_NODE,pdata);
	tmp->next->nodenr = nodenr+1;

}

void C_Node::Node_Init(void)
{
	nodenr = 0;
}

unsigned int C_Node::Get_Num_of_Nodes(void)
/// \retval num Iloœæ wêz³ów
{
	C_Node* tmp = this;
	unsigned int licz = tmp->nodenr;
	while(tmp->next!=NULL)
	{
		tmp = tmp->Get_Next();
		licz++;
	}
	return ++licz;	// liczone razem z 0

}

void C_Node::Clear_All(void)
{
	if(next!=NULL)	{
		delete next;
		next = NULL;
	}

}

char* C_Node::GetNthNodeData(unsigned int nr)
/// \retval *ptr WskaŸnik do danych przechowywanych w nr wêŸle
/// \retval NULL Jeœli odwo³ujemy siê do nieistniej¹cego wêz³a
{
	unsigned int nri = Get_Num_of_Nodes();
	unsigned int a;
	if(nr>nri)
		return NULL;

	C_Node* tmp = this;
	if(nr==0)
		return this->data;
	for(a=nodenr;a<nr-1;a++)
	{
		tmp = tmp->Get_Next();
	}
	return tmp->data;
}