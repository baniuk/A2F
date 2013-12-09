// _myDialogParam.cpp : implementation file
//

#include "stdafx.h"
#include "_myDialogParam.h"


// C_myDialogParam dialog

IMPLEMENT_DYNAMIC(C_myDialogParam, CDialog)

C_myDialogParam::C_myDialogParam(CWnd* pParent /*=NULL*/)
	: CDialog(C_myDialogParam::IDD, pParent)
{

}

C_myDialogParam::~C_myDialogParam()
{
}

void C_myDialogParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(C_myDialogParam, CDialog)
END_MESSAGE_MAP()


// C_myDialogParam message handlers

BOOL C_myDialogParam::Create(LPCTSTR WindowTitle, DWORD dwStyle, CWnd* pParent)
{
	CBrush WhiteBrush(RGB(255,255,255));
	CString ChildWindowClass = AfxRegisterWndClass(
				CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
				LoadCursor(NULL,IDC_CROSS),
				(HBRUSH)WhiteBrush.GetSafeHandle(),
				LoadIcon(NULL,IDI_APPLICATION));
//	pMainWindow=pParent;
	CRect ChildRect(0, 0, 100, 100);
	CWnd::CreateEx(NULL,ChildWindowClass, WindowTitle, dwStyle,
						ChildRect, NULL, NULL);
	return TRUE;
}
