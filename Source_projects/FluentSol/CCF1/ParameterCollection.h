// ParameterCollection.h : Declaration of the CParameterCollection

#pragma once
#include "resource.h"       // main symbols

#include "CCF1_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

extern "C" void SetOaNoCache(void); 

// CParameterCollection

class ATL_NO_VTABLE CParameterCollection :
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CParameterCollection, &CLSID_ParameterCollection>,
	public IDispatchImpl<IParameterCollection, &IID_IParameterCollection, &LIBID_CCF1Lib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeCollection, &__uuidof(ICapeCollection), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CParameterCollection();
	~CParameterCollection(void);


	DECLARE_REGISTRY_RESOURCEID(IDR_PARAMETERCOLLECTION)


	BEGIN_COM_MAP(CParameterCollection)
		COM_INTERFACE_ENTRY(IParameterCollection)
		COM_INTERFACE_ENTRY2(IDispatch, ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeRoot)
		COM_INTERFACE_ENTRY(ECapeUnknown)
		COM_INTERFACE_ENTRY(ECapeUser)
		COM_INTERFACE_ENTRY(ICapeCollection)
		COM_INTERFACE_ENTRY(ICapeIdentification)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:


	// ECapeRoot Methods
public:
	STDMETHOD(get_name)(BSTR * name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_name)(BSTR * name)\n");
	#endif
		*name = errDesc.Copy();
		return S_OK;
	}

	// ECapeUnknown Methods
public:

	// ECapeUser Methods
public:
	STDMETHOD(get_code)(long * code)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_code)(long * code)\n");
	#endif
		*code = 0;
		return S_OK;
	}
	STDMETHOD(get_description)(BSTR * description)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_description)(BSTR * description)\n");
	#endif
		*description = errDesc.Copy();
		return S_OK;

	}

	STDMETHOD(get_scope)(BSTR * scope)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_scope)(BSTR * scope)\n");
	#endif
		*scope = errScope.Copy();
		return S_OK;
	}

	STDMETHOD(get_interfaceName)(BSTR * interfaceName)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_interfaceName)(BSTR * interfaceName)\n");
	#endif
		*interfaceName = errInterface.Copy();
		return S_OK;
	}
	STDMETHOD(get_operation)(BSTR * operation)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_operation)(BSTR * operation)\n");
	#endif
		CComBSTR myErr(L"Operation not available");
		*operation = myErr.Copy();
		myErr.Empty();
		return S_OK;
	}

	STDMETHOD(get_moreInfo)(BSTR * moreInfo)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_moreInfo)(BSTR * moreInfo)\n");
	#endif
		CComBSTR myErr(L"No more info");
		*moreInfo = myErr.Copy();
		myErr.Empty();
		return S_OK;
	}

	// ICapeCollection Methods
public:
	STDMETHOD(Item)(VARIANT id, LPDISPATCH * Item)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(Item)(VARIANT id, LPDISPATCH * Item)\n");
	#endif
		ICapeParameter *tmp;
		if(id.vt == VT_I4)
		{
			if(id.lVal-1<10)
			{
				parameters[id.lVal-1]->QueryInterface(IID_ICapeParameter,(void**)&tmp);
				*Item = (LPDISPATCH)tmp;
			} else {
				return ECapeUnknownHR;	// error
			}
		}
		return S_OK;
	}

	STDMETHOD(Count)(long * itemsCount)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(Count)(long * itemsCount)\n");
	#endif
		*itemsCount = parameterCount;
		return S_OK;
		}

	// ICapeIdentification Methods
public:
	STDMETHOD(get_ComponentName)(BSTR * name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_ComponentName)(BSTR * name)\n");
	#endif
		*name = myName.Copy();
		return S_OK;
	}
	STDMETHOD(put_ComponentName)(BSTR name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(put_ComponentName)(BSTR name)\n");
	#endif
		myName.Empty();
		myName = name;
		return S_OK;
	}

	STDMETHOD(get_ComponentDescription)(BSTR * desc)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(get_ComponentDescription)(BSTR * desc)\n");
	#endif
		*desc = myDesc.Copy();
		return S_OK;
	}

	STDMETHOD(put_ComponentDescription)(BSTR desc)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CParameterCollection::STDMETHOD(put_ComponentDescription)(BSTR desc)\n");
	#endif
		myDesc.Empty();
		myDesc = desc;
		return S_OK;
	}

private:
	CComBSTR errDesc;
	CComBSTR errInterface;
	CComBSTR errScope;
	CComBSTR myName;
	CComBSTR myDesc;
	int parameterCount;
	ICapeParameter *parameters[10];		// zak³adam w ciemno max 10 parametrów
	FILE *mystream;
	C_Error *err;
	void SetError(BSTR desc, BSTR interf, BSTR scope);
public:
	STDMETHOD(debugfile)(VARIANT* in);
	STDMETHOD(AddParameter)(IDispatch* p);
	STDMETHOD(RemoveParameter)(LONG index);
	STDMETHOD(AddError)(VARIANT* in);
};

OBJECT_ENTRY_AUTO(__uuidof(ParameterCollection), CParameterCollection)
