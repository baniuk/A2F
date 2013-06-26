// PortCollection.cpp : Implementation of CPortCollection

#include "stdafx.h"
#include "PortCollection.h"


// CPortCollection

CPortCollection::CPortCollection()
{
	SetOaNoCache();
	portCount = 0;
	myName = L"PortCollection";
	myDesc = L"Collection of ports for CAPE-OPEN unit operation";
	errDesc = L"";
	errInterface = L"";
	errScope = L"";
//	err = new C_Error("CPortCollection");

}

CPortCollection::~CPortCollection()
{
#ifdef PRINTOUT
	fprintf(mystream,"CPortCollection::~CPortCollection()\n");
#endif
	myName.Empty();
	myDesc.Empty();
	errDesc.Empty();
	errInterface.Empty();
	errScope.Empty();
//	for(int a=0;a<portCount;a++)
//		if(ports[a]!=NULL)
//			ports[a]->Release();
//	delete err;

}

STDMETHODIMP CPortCollection::AddPort2(IDispatch* disp)
{
#ifdef PRINTOUT
	fprintf(mystream,"CPortCollection::AddPort2(IDispatch* disp)\n");
	fprintf(mystream,"	- count %d\n",portCount);
#endif
	disp->QueryInterface(IID_IPort,(void**)&ports[portCount]);
	portCount++;
	return S_OK;
}

STDMETHODIMP CPortCollection::RemovePort(LONG index)
{
	ports[index-1]->Release();
	portCount--;
	return S_OK;
}

STDMETHODIMP CPortCollection::debugfile(VARIANT* in)
{
	mystream = (FILE*)in->byref;

	return S_OK;
}

void CPortCollection::SetError(BSTR desc, BSTR interf, BSTR scope)
{
#ifdef PRINTOUT
	fprintf(mystream,"CPortCollection::SetError(BSTR desc, BSTR interf, BSTR scope)\n");
#endif

	errDesc.Empty(); errDesc = desc;
	errInterface.Empty(); errInterface = interf;
	errScope.Empty(); errScope = scope;

}

STDMETHODIMP CPortCollection::AddError(VARIANT* in)
{
	err = (C_Error*)in->byref;
	return S_OK;
}
