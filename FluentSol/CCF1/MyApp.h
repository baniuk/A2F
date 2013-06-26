#pragma once
#include "afxwin.h"

class CMyApp :
	public CWinApp
{
public:
	CMyApp(void);
	~CMyApp(void);
	virtual BOOL InitInstance();
    virtual int ExitInstance();
protected:
    BOOL m_bRun;

};
