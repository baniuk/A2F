// Port.cpp : Implementation of CPort

#include "stdafx.h"
#include "Port.h"


// CPort
CPort::CPort()
{
	SetOaNoCache();
	mydirection = CAPE_INLET_OUTLET;
	myNamePort = L"Unknown1";
	myDesc = L"Unknown1";
	myconnectedObject = NULL;
	addrefcount = 0;
//	err = new C_Error("CPort");
}

CPort::~CPort(void)
{
#ifdef PRINTOUT
	fprintf(mystream,"CPort::~CPort(void)\n");
#endif
	myNamePort.Empty();
	myDesc.Empty();
//	delete err;
}

STDMETHODIMP CPort::AddError(VARIANT* in)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	err = (C_Error*)in->byref;

	return S_OK;
}

STDMETHODIMP CPort::debugfile(VARIANT* in)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	mystream = (FILE*)in->byref;

	return S_OK;
}

STDMETHODIMP CPort::get_direction(BYTE* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef PRINTOUT
	fprintf(mystream,"CPort::get_mydirection(BYTE* pVal)\n");
#endif
	*pVal = mydirection;
	return S_OK;
}

STDMETHODIMP CPort::put_direction(BYTE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef PRINTOUT
	fprintf(mystream,"CPort::put_mydirection(BYTE newVal)\n");
#endif
	switch(newVal)
	{
	case 0:
		mydirection = CAPE_INLET;
		break;
	case 1:
		mydirection = CAPE_OUTLET;
		break;
	case 2:
		mydirection = CAPE_INLET_OUTLET;
		break;
	}
	return S_OK;
}

STDMETHODIMP CPort::get_myName(BSTR* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef PRINTOUT
	fprintf(mystream,"CPort::get_myName(BSTR* pVal)\n");
#endif
	*pVal = myNamePort.Copy();

	return S_OK;
}

STDMETHODIMP CPort::put_myName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef PRINTOUT
	fprintf(mystream,"CPort::put_myName(BSTR newVal)\n");
#endif
//	SysReAllocString(&myNamePort,newVal);
	myNamePort.Empty();
	myNamePort = newVal;
	return S_OK;
}

STDMETHODIMP CPort::get_myDesc(BSTR* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef PRINTOUT
	fprintf(mystream,"CPort::get_myDesc(BSTR* pVal)\n");
#endif
	*pVal = myDesc.Copy(); 

	return S_OK;
}

STDMETHODIMP CPort::put_myDesc(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef PRINTOUT
	fprintf(mystream,"CPort::put_myDesc(BSTR newVal)\n");
#endif
//	SysReAllocString(&myDesc,newVal);
	myDesc.Empty();
	myDesc = newVal;

	return S_OK;
}

STDMETHODIMP CPort::put_unit(BYTE* newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

#ifdef PRINTOUT
	fprintf(mystream,"CPort::put_unit1(IDispatch* newVal)\n");
#endif
	pmyValStatus = (CapeValidationStatus*)newVal;
	return S_OK;
}

void CPort::SetError(BSTR desc, BSTR interf, BSTR scope)
{		
#ifdef PRINTOUT
	fprintf(mystream,"CPort::SetError(BSTR desc, BSTR interf, BSTR scope)\n");
#endif
	errDesc.Empty(); errDesc = desc;
	errInterface.Empty(); errInterface = interf;
	errScope.Empty(); errScope = scope;
}