// Okno.cpp : implementation file
//

#include "stdafx.h"
#include "Okno.h"


// Okno dialog

IMPLEMENT_DYNAMIC(Okno, CDialog)

Okno::Okno(CWnd* pParent /*=NULL*/)
	: CDialog(Okno::IDD, pParent)
{

}

Okno::~Okno()
{
}

void Okno::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Okno, CDialog)
END_MESSAGE_MAP()


// Okno message handlers
