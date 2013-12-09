#pragma once


// Okno dialog

class Okno : public CDialog
{
	DECLARE_DYNAMIC(Okno)

public:
	Okno(CWnd* pParent = NULL);   // standard constructor
	virtual ~Okno();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
