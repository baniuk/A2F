// _ParamWnd.cpp : implementation file
//

#include "stdafx.h"
#include "_ParamWnd.h"


// C_ParamWnd dialog

IMPLEMENT_DYNAMIC(C_ParamWnd, CDialog)

C_ParamWnd::C_ParamWnd(CWnd* pParent /*=NULL*/)
	: CDialog(C_ParamWnd::IDD, pParent)
{

}

C_ParamWnd::~C_ParamWnd()
{
}

void C_ParamWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_ParamWnd, CDialog)
END_MESSAGE_MAP()


// C_ParamWnd message handlers
