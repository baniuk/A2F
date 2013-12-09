#include "StdAfx.h"
#include "C_Error.h"

C_Error::C_Error(void):C_Node()
{
	changes = FALSE;
}

C_Error::C_Error(char* edata):C_Node(edata)
{
	changes = FALSE;
}

C_Error::~C_Error(void)
{
}

void C_Error::AddError(char* error)
{
	Add_Next(error);
	changes = TRUE;
}

void C_Error::ClearErrorStatus(void)
{
	Clear_All();
	changes = FALSE;
}

void C_Error::PrintAll(void)
{
	unsigned int ilenode,a;
	C_Node* tmp;
	FILE* fid;
	char timeline[26];
	struct _timeb timebuffer;
	_ftime_s( &timebuffer );
	ctime_s( timeline, 26, & ( timebuffer.time ) );

	if(changes == TRUE)	// zgrywam tylko jesli by³y zmiany
	{
		fopen_s(&fid,"c:\\ErrorLog.txt","a+");
		fprintf(fid,"\n-- %.19s.%hu %s", timeline, timebuffer.millitm, &timeline[18] );

		tmp = this;
		ilenode = Get_Num_of_Nodes();
		for(a=0;a<ilenode;a++)
		{
			fprintf(fid,"%s\n",tmp->data);
			tmp = tmp->Get_Next();
		}
		fclose(fid);
		changes = FALSE;
	}

}