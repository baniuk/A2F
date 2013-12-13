// PortCollection.h : Declaration of the CPortCollection

#pragma once
#include "resource.h"       // main symbols

#include "Cape2Fluent_i.h"
#include "Port.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

extern "C" void SetOaNoCache(void); 

// CPortCollection

class ATL_NO_VTABLE CPortCollection :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPortCollection, &CLSID_PortCollection>,
	public IDispatchImpl<IPortCollection, &IID_IPortCollection, &LIBID_Cape2FluentLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IDispatchImpl<ECapeRoot, &__uuidof(ECapeRoot), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUnknown, &__uuidof(ECapeUnknown), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ECapeUser, &__uuidof(ECapeUser), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeCollection, &__uuidof(ICapeCollection), &LIBID_CAPEOPEN100, /* wMajor = */ 1>,
	public IDispatchImpl<ICapeIdentification, &__uuidof(ICapeIdentification), &LIBID_CAPEOPEN100, /* wMajor = */ 1>
{
public:
	CPortCollection();
	~CPortCollection(void);

	DECLARE_REGISTRY_RESOURCEID(IDR_PORTCOLLECTION)


	BEGIN_COM_MAP(CPortCollection)
		COM_INTERFACE_ENTRY(IPortCollection)
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

	STDMETHOD(AddError)(VARIANT* in);
	STDMETHOD(debugfile)(VARIANT* in);
	STDMETHOD(AddPort2)(IDispatch* disp);
	STDMETHOD(RemovePort)(LONG index);

	// ECapeRoot Methods
public:
	STDMETHOD(get_name)(BSTR * name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_name)(BSTR * name)\n");
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
		fprintf(mystream,"CPortCollection::STDMETHOD(get_code)(long * code)\n");
	#endif
		*code = 0;
		return S_OK;
	}
	STDMETHOD(get_description)(BSTR * description)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_description)(BSTR * description)\n");
	#endif
		*description = errDesc.Copy();
		return S_OK;
	}

	STDMETHOD(get_scope)(BSTR * scope)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_scope)(BSTR * scope)\n");
	#endif
		*scope = errScope.Copy();
		return S_OK;
	}

	STDMETHOD(get_interfaceName)(BSTR * interfaceName)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_interfaceName)(BSTR * interfaceName)\n");
	#endif
		*interfaceName = errInterface.Copy();
		return S_OK;
	}

	STDMETHOD(get_operation)(BSTR * operation)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_operation)(BSTR * operation)\n");
	#endif
		CComBSTR myErr(L"Operation not available");
		*operation = myErr.Copy();
		myErr.Empty();
		return S_OK;
	}

	STDMETHOD(get_moreInfo)(BSTR * moreInfo)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_moreInfo)(BSTR * moreInfo)\n");
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
		unsigned int a;
		CComBSTR bstrtmp;
		CComBSTR bstrtmp1;
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(Item)(VARIANT id, LPDISPATCH * Item)\n");
	#endif
		IPort *tmp;
		if(id.vt == VT_I4)	// port jako numer
		{
			ports[id.lVal-1]->QueryInterface(IID_IPort,(void**)&tmp);
			*Item = (LPDISPATCH)tmp; //tmp->AddRef();
		} else 
			if(id.vt == VT_BSTR)
			{
				bstrtmp1 = id.bstrVal;
				for(a=0;a<portCount;a++)	{
					ports[a]->get_myName(&bstrtmp);
					if(bstrtmp1==bstrtmp)	{
						ports[a]->QueryInterface(IID_IPort,(void**)&tmp);
						*Item = (LPDISPATCH)tmp; //tmp->AddRef();
					}
				}
			} else
				SetError(L"Invalid port ID: index out of range",L"ICapeCollection",L"Item");
		return S_OK;
	}

	STDMETHOD(Count)(long * itemsCount)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(Count)(long * itemsCount)\n");
	#endif	
		*itemsCount = portCount;
		return S_OK;
	}

	// ICapeIdentification Methods
public:
	STDMETHOD(get_ComponentName)(BSTR * name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_ComponentName)(BSTR * name)\n");
	#endif
		*name = myName.Copy();
		return S_OK;
	}
	STDMETHOD(put_ComponentName)(BSTR name)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(put_ComponentName)(BSTR name)\n");
	#endif
//		SysReAllocString(&myName,name);
		myName.Empty();
		myName = name;
		return S_OK;
	}
	STDMETHOD(get_ComponentDescription)(BSTR * desc)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(get_ComponentDescription)(BSTR * desc)\n");
	#endif
		*desc = myDesc.Copy();
		return S_OK;
	}
	STDMETHOD(put_ComponentDescription)(BSTR desc)
	{
	#ifdef PRINTOUT
		fprintf(mystream,"CPortCollection::STDMETHOD(put_ComponentDescription)(BSTR desc)\n");
	#endif
		myDesc.Empty();
		myDesc = desc;
		return S_OK;
	}
private:
	CComBSTR errDesc;
	CComBSTR errInterface;
	CComBSTR errScope;
//	_COM_SMARTPTR_TYPEDEF(IPort, __uuidof(IPort));
	IPort *ports[NUM_OF_INPUTS+NUM_OF_OUTPUTS];
	FILE *mystream;
	CComBSTR myName;
	CComBSTR myDesc;
	int portCount;
	C_Error *err;
	void SetError(BSTR desc, BSTR interf, BSTR scope);
};

OBJECT_ENTRY_AUTO(__uuidof(PortCollection), CPortCollection)
