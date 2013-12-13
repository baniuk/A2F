

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Apr 20 10:32:06 2010
 */
/* Compiler settings for .\CCF1.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CCF1_i_h__
#define __CCF1_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IComponentRegistrar_FWD_DEFINED__
#define __IComponentRegistrar_FWD_DEFINED__
typedef interface IComponentRegistrar IComponentRegistrar;
#endif 	/* __IComponentRegistrar_FWD_DEFINED__ */


#ifndef __IUnitOperation_FWD_DEFINED__
#define __IUnitOperation_FWD_DEFINED__
typedef interface IUnitOperation IUnitOperation;
#endif 	/* __IUnitOperation_FWD_DEFINED__ */


#ifndef __IPort_FWD_DEFINED__
#define __IPort_FWD_DEFINED__
typedef interface IPort IPort;
#endif 	/* __IPort_FWD_DEFINED__ */


#ifndef __IPortCollection_FWD_DEFINED__
#define __IPortCollection_FWD_DEFINED__
typedef interface IPortCollection IPortCollection;
#endif 	/* __IPortCollection_FWD_DEFINED__ */


#ifndef __IParameterCollection_FWD_DEFINED__
#define __IParameterCollection_FWD_DEFINED__
typedef interface IParameterCollection IParameterCollection;
#endif 	/* __IParameterCollection_FWD_DEFINED__ */


#ifndef __CompReg_FWD_DEFINED__
#define __CompReg_FWD_DEFINED__

#ifdef __cplusplus
typedef class CompReg CompReg;
#else
typedef struct CompReg CompReg;
#endif /* __cplusplus */

#endif 	/* __CompReg_FWD_DEFINED__ */


#ifndef __UnitOperation_FWD_DEFINED__
#define __UnitOperation_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitOperation UnitOperation;
#else
typedef struct UnitOperation UnitOperation;
#endif /* __cplusplus */

#endif 	/* __UnitOperation_FWD_DEFINED__ */


#ifndef __Port_FWD_DEFINED__
#define __Port_FWD_DEFINED__

#ifdef __cplusplus
typedef class Port Port;
#else
typedef struct Port Port;
#endif /* __cplusplus */

#endif 	/* __Port_FWD_DEFINED__ */


#ifndef __PortCollection_FWD_DEFINED__
#define __PortCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class PortCollection PortCollection;
#else
typedef struct PortCollection PortCollection;
#endif /* __cplusplus */

#endif 	/* __PortCollection_FWD_DEFINED__ */


#ifndef __ParameterCollection_FWD_DEFINED__
#define __ParameterCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class ParameterCollection ParameterCollection;
#else
typedef struct ParameterCollection ParameterCollection;
#endif /* __cplusplus */

#endif 	/* __ParameterCollection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IComponentRegistrar_INTERFACE_DEFINED__
#define __IComponentRegistrar_INTERFACE_DEFINED__

/* interface IComponentRegistrar */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IComponentRegistrar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a817e7a2-43fa-11d0-9e44-00aa00b6770a")
    IComponentRegistrar : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Attach( 
            /* [in] */ BSTR bstrPath) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterAll( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnregisterAll( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetComponents( 
            /* [out] */ SAFEARRAY * *pbstrCLSIDs,
            /* [out] */ SAFEARRAY * *pbstrDescriptions) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterComponent( 
            /* [in] */ BSTR bstrCLSID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UnregisterComponent( 
            /* [in] */ BSTR bstrCLSID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IComponentRegistrarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponentRegistrar * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponentRegistrar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponentRegistrar * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComponentRegistrar * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComponentRegistrar * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComponentRegistrar * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComponentRegistrar * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Attach )( 
            IComponentRegistrar * This,
            /* [in] */ BSTR bstrPath);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RegisterAll )( 
            IComponentRegistrar * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnregisterAll )( 
            IComponentRegistrar * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetComponents )( 
            IComponentRegistrar * This,
            /* [out] */ SAFEARRAY * *pbstrCLSIDs,
            /* [out] */ SAFEARRAY * *pbstrDescriptions);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *RegisterComponent )( 
            IComponentRegistrar * This,
            /* [in] */ BSTR bstrCLSID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UnregisterComponent )( 
            IComponentRegistrar * This,
            /* [in] */ BSTR bstrCLSID);
        
        END_INTERFACE
    } IComponentRegistrarVtbl;

    interface IComponentRegistrar
    {
        CONST_VTBL struct IComponentRegistrarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponentRegistrar_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComponentRegistrar_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComponentRegistrar_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComponentRegistrar_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IComponentRegistrar_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IComponentRegistrar_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IComponentRegistrar_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IComponentRegistrar_Attach(This,bstrPath)	\
    ( (This)->lpVtbl -> Attach(This,bstrPath) ) 

#define IComponentRegistrar_RegisterAll(This)	\
    ( (This)->lpVtbl -> RegisterAll(This) ) 

#define IComponentRegistrar_UnregisterAll(This)	\
    ( (This)->lpVtbl -> UnregisterAll(This) ) 

#define IComponentRegistrar_GetComponents(This,pbstrCLSIDs,pbstrDescriptions)	\
    ( (This)->lpVtbl -> GetComponents(This,pbstrCLSIDs,pbstrDescriptions) ) 

#define IComponentRegistrar_RegisterComponent(This,bstrCLSID)	\
    ( (This)->lpVtbl -> RegisterComponent(This,bstrCLSID) ) 

#define IComponentRegistrar_UnregisterComponent(This,bstrCLSID)	\
    ( (This)->lpVtbl -> UnregisterComponent(This,bstrCLSID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IComponentRegistrar_INTERFACE_DEFINED__ */


#ifndef __IUnitOperation_INTERFACE_DEFINED__
#define __IUnitOperation_INTERFACE_DEFINED__

/* interface IUnitOperation */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IUnitOperation;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1ABD43ED-339F-43ED-9087-396904A85206")
    IUnitOperation : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InvalidateUnit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUnitOperationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitOperation * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitOperation * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitOperation * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUnitOperation * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUnitOperation * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUnitOperation * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUnitOperation * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InvalidateUnit )( 
            IUnitOperation * This);
        
        END_INTERFACE
    } IUnitOperationVtbl;

    interface IUnitOperation
    {
        CONST_VTBL struct IUnitOperationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitOperation_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitOperation_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitOperation_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitOperation_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUnitOperation_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUnitOperation_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUnitOperation_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IUnitOperation_InvalidateUnit(This)	\
    ( (This)->lpVtbl -> InvalidateUnit(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitOperation_INTERFACE_DEFINED__ */


#ifndef __IPort_INTERFACE_DEFINED__
#define __IPort_INTERFACE_DEFINED__

/* interface IPort */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPort;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8B172D11-6ECB-4EF6-82DD-0B36F5ED68AE")
    IPort : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_mydirection( 
            /* [retval][out] */ BYTE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_mydirection( 
            /* [in] */ BYTE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_myName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_myName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_myDesc( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_myDesc( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_unit( 
            /* [in] */ CapeValidationStatus *newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE debugfile( 
            VARIANT *in) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddError( 
            /* [in] */ VARIANT *in) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPort * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPort * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPort * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPort * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPort * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPort * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPort * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mydirection )( 
            IPort * This,
            /* [retval][out] */ BYTE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mydirection )( 
            IPort * This,
            /* [in] */ BYTE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_myName )( 
            IPort * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_myName )( 
            IPort * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_myDesc )( 
            IPort * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_myDesc )( 
            IPort * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_unit )( 
            IPort * This,
            /* [in] */ IDispatch *newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *debugfile )( 
            IPort * This,
            VARIANT *in);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddError )( 
            IPort * This,
            /* [in] */ VARIANT *in);
        
        END_INTERFACE
    } IPortVtbl;

    interface IPort
    {
        CONST_VTBL struct IPortVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPort_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPort_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPort_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPort_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPort_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPort_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPort_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPort_get_mydirection(This,pVal)	\
    ( (This)->lpVtbl -> get_mydirection(This,pVal) ) 

#define IPort_put_mydirection(This,newVal)	\
    ( (This)->lpVtbl -> put_mydirection(This,newVal) ) 

#define IPort_get_myName(This,pVal)	\
    ( (This)->lpVtbl -> get_myName(This,pVal) ) 

#define IPort_put_myName(This,newVal)	\
    ( (This)->lpVtbl -> put_myName(This,newVal) ) 

#define IPort_get_myDesc(This,pVal)	\
    ( (This)->lpVtbl -> get_myDesc(This,pVal) ) 

#define IPort_put_myDesc(This,newVal)	\
    ( (This)->lpVtbl -> put_myDesc(This,newVal) ) 

#define IPort_put_unit(This,newVal)	\
    ( (This)->lpVtbl -> put_unit(This,newVal) ) 

#define IPort_debugfile(This,in)	\
    ( (This)->lpVtbl -> debugfile(This,in) ) 

#define IPort_AddError(This,in)	\
    ( (This)->lpVtbl -> AddError(This,in) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPort_INTERFACE_DEFINED__ */


#ifndef __IPortCollection_INTERFACE_DEFINED__
#define __IPortCollection_INTERFACE_DEFINED__

/* interface IPortCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPortCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C3576B00-A36A-4C58-9311-3F25C0185E2B")
    IPortCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddPort2( 
            /* [in] */ IDispatch *disp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE debugfile( 
            VARIANT *in) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemovePort( 
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddError( 
            /* [in] */ VARIANT *in) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPortCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPortCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPortCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPortCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPortCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPortCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPortCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPortCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddPort2 )( 
            IPortCollection * This,
            /* [in] */ IDispatch *disp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *debugfile )( 
            IPortCollection * This,
            VARIANT *in);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemovePort )( 
            IPortCollection * This,
            /* [in] */ LONG index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddError )( 
            IPortCollection * This,
            /* [in] */ VARIANT *in);
        
        END_INTERFACE
    } IPortCollectionVtbl;

    interface IPortCollection
    {
        CONST_VTBL struct IPortCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPortCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPortCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPortCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPortCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPortCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPortCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPortCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPortCollection_AddPort2(This,disp)	\
    ( (This)->lpVtbl -> AddPort2(This,disp) ) 

#define IPortCollection_debugfile(This,in)	\
    ( (This)->lpVtbl -> debugfile(This,in) ) 

#define IPortCollection_RemovePort(This,index)	\
    ( (This)->lpVtbl -> RemovePort(This,index) ) 

#define IPortCollection_AddError(This,in)	\
    ( (This)->lpVtbl -> AddError(This,in) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPortCollection_INTERFACE_DEFINED__ */


#ifndef __IParameterCollection_INTERFACE_DEFINED__
#define __IParameterCollection_INTERFACE_DEFINED__

/* interface IParameterCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IParameterCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F9FC8344-8D41-4784-A491-925120E09B06")
    IParameterCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddParameter( 
            /* [in] */ IDispatch *p) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveParameter( 
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE debugfile( 
            /* [in] */ VARIANT *in) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddError( 
            /* [in] */ VARIANT *in) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IParameterCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParameterCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IParameterCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IParameterCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IParameterCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IParameterCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IParameterCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IParameterCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddParameter )( 
            IParameterCollection * This,
            /* [in] */ IDispatch *p);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveParameter )( 
            IParameterCollection * This,
            /* [in] */ LONG index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *debugfile )( 
            IParameterCollection * This,
            /* [in] */ VARIANT *in);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddError )( 
            IParameterCollection * This,
            /* [in] */ VARIANT *in);
        
        END_INTERFACE
    } IParameterCollectionVtbl;

    interface IParameterCollection
    {
        CONST_VTBL struct IParameterCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IParameterCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IParameterCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IParameterCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IParameterCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IParameterCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IParameterCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IParameterCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IParameterCollection_AddParameter(This,p)	\
    ( (This)->lpVtbl -> AddParameter(This,p) ) 

#define IParameterCollection_RemoveParameter(This,index)	\
    ( (This)->lpVtbl -> RemoveParameter(This,index) ) 

#define IParameterCollection_debugfile(This,in)	\
    ( (This)->lpVtbl -> debugfile(This,in) ) 

#define IParameterCollection_AddError(This,in)	\
    ( (This)->lpVtbl -> AddError(This,in) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IParameterCollection_INTERFACE_DEFINED__ */



#ifndef __CCF1Lib_LIBRARY_DEFINED__
#define __CCF1Lib_LIBRARY_DEFINED__

/* library CCF1Lib */
/* [custom][helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CCF1Lib;

EXTERN_C const CLSID CLSID_CompReg;

#ifdef __cplusplus

class DECLSPEC_UUID("4E8E6E1F-6001-40D7-A6D5-77C10C0413C8")
CompReg;
#endif

EXTERN_C const CLSID CLSID_UnitOperation;

#ifdef __cplusplus

class DECLSPEC_UUID("060E165D-4FCF-49CB-96B6-427A5CFCB57A")
UnitOperation;
#endif

EXTERN_C const CLSID CLSID_Port;

#ifdef __cplusplus

class DECLSPEC_UUID("2447B9B3-F326-4EFF-864D-41DC22111B4A")
Port;
#endif

EXTERN_C const CLSID CLSID_PortCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("AD8CC3DF-932C-40ED-A6B9-48036BF2C4DE")
PortCollection;
#endif

EXTERN_C const CLSID CLSID_ParameterCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("423EC7B2-0159-4EA7-8751-C44F7203A214")
ParameterCollection;
#endif
#endif /* __CCF1Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


