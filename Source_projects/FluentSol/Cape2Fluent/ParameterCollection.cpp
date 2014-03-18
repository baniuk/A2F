// ParameterCollection.cpp : Implementation of CParameterCollection

#include "stdafx.h"
#include "ParameterCollection.h"


CParameterCollection::CParameterCollection()
{
	SetOaNoCache();
	parameterCount = 0;
	errDesc = L"";
	errInterface = L"";
	errScope = L"";
//	err = new C_Error("CParameterCollection");
}

CParameterCollection::~CParameterCollection(void)
{
	errDesc.Empty();
	errInterface.Empty();
	errScope.Empty();
//	delete err;

}

void CParameterCollection::SetError(BSTR desc, BSTR interf, BSTR scope)
{
	errDesc.Empty(); errDesc = desc;
	errInterface.Empty(); errInterface = interf;
	errScope.Empty(); errScope = scope;
}


STDMETHODIMP CParameterCollection::AddError(VARIANT* in)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	err = (C_Error*)in->byref;

	return S_OK;
}

STDMETHODIMP CParameterCollection::debugfile(VARIANT* in)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	mystream = (FILE*)in->byref;

	return S_OK;
}

STDMETHODIMP CParameterCollection::AddParameter(IDispatch* p)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	p->QueryInterface(IID_ICapeParameter,(void**)&parameters[parameterCount]);
	parameterCount++;
	return S_OK;
}

STDMETHODIMP CParameterCollection::RemoveParameter(LONG index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	parameters[index]->Release();	// trzeba zrobic sortowanie zeby postych miejsc nie by³o
	parameterCount--;
	return S_OK;
}
