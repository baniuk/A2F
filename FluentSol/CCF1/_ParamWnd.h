#pragma once


// C_ParamWnd dialog

class C_ParamWnd : public CDialog
{
	DECLARE_DYNAMIC(C_ParamWnd)

public:
	C_ParamWnd(CWnd* pParent = NULL);   // standard constructor
	virtual ~C_ParamWnd();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
