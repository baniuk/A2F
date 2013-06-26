#pragma once


// C_myDialogParam dialog

class C_myDialogParam : public CDialog
{
	DECLARE_DYNAMIC(C_myDialogParam)

public:
	C_myDialogParam(CWnd* pParent = NULL);   // standard constructor
	virtual ~C_myDialogParam();
	CWnd* pMainWindow;

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL Create(LPCTSTR WindowTitle, DWORD dwStyle, CWnd* pParent);
};
