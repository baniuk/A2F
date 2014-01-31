

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Fri Jan 31 11:22:02 2014
 */
/* Compiler settings for A2F.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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

#ifndef __A2F_i_h__
#define __A2F_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IUnitOperations_FWD_DEFINED__
#define __IUnitOperations_FWD_DEFINED__
typedef interface IUnitOperations IUnitOperations;

#endif 	/* __IUnitOperations_FWD_DEFINED__ */


#ifndef __IPortCollection_FWD_DEFINED__
#define __IPortCollection_FWD_DEFINED__
typedef interface IPortCollection IPortCollection;

#endif 	/* __IPortCollection_FWD_DEFINED__ */


#ifndef __IUnitPort_FWD_DEFINED__
#define __IUnitPort_FWD_DEFINED__
typedef interface IUnitPort IUnitPort;

#endif 	/* __IUnitPort_FWD_DEFINED__ */


#ifndef __IParameterCollection_FWD_DEFINED__
#define __IParameterCollection_FWD_DEFINED__
typedef interface IParameterCollection IParameterCollection;

#endif 	/* __IParameterCollection_FWD_DEFINED__ */


#ifndef __IUnitPortEx_FWD_DEFINED__
#define __IUnitPortEx_FWD_DEFINED__
typedef interface IUnitPortEx IUnitPortEx;

#endif 	/* __IUnitPortEx_FWD_DEFINED__ */


#ifndef __UnitOperations_FWD_DEFINED__
#define __UnitOperations_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitOperations UnitOperations;
#else
typedef struct UnitOperations UnitOperations;
#endif /* __cplusplus */

#endif 	/* __UnitOperations_FWD_DEFINED__ */


#ifndef __PortCollection_FWD_DEFINED__
#define __PortCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class PortCollection PortCollection;
#else
typedef struct PortCollection PortCollection;
#endif /* __cplusplus */

#endif 	/* __PortCollection_FWD_DEFINED__ */


#ifndef __UnitPort_FWD_DEFINED__
#define __UnitPort_FWD_DEFINED__

#ifdef __cplusplus
typedef class UnitPort UnitPort;
#else
typedef struct UnitPort UnitPort;
#endif /* __cplusplus */

#endif 	/* __UnitPort_FWD_DEFINED__ */


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


#ifndef __IUnitOperations_INTERFACE_DEFINED__
#define __IUnitOperations_INTERFACE_DEFINED__

/* interface IUnitOperations */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IUnitOperations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6EB158D-ECFB-4FCC-804A-B5DA52D4450F")
    IUnitOperations : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitOperationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitOperations * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitOperations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitOperations * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUnitOperations * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUnitOperations * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUnitOperations * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUnitOperations * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IUnitOperationsVtbl;

    interface IUnitOperations
    {
        CONST_VTBL struct IUnitOperationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitOperations_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitOperations_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitOperations_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitOperations_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUnitOperations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUnitOperations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUnitOperations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitOperations_INTERFACE_DEFINED__ */


#ifndef __IPortCollection_INTERFACE_DEFINED__
#define __IPortCollection_INTERFACE_DEFINED__

/* interface IPortCollection */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPortCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("373AF87E-7579-43F8-B97D-045DCCE88E9E")
    IPortCollection : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IPortCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPortCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
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


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPortCollection_INTERFACE_DEFINED__ */


#ifndef __IUnitPort_INTERFACE_DEFINED__
#define __IUnitPort_INTERFACE_DEFINED__

/* interface IUnitPort */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IUnitPort;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EBBFAD37-B5F7-489E-87E2-C0DAA10D6D79")
    IUnitPort : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitPortVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitPort * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitPort * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitPort * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IUnitPort * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IUnitPort * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IUnitPort * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IUnitPort * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IUnitPortVtbl;

    interface IUnitPort
    {
        CONST_VTBL struct IUnitPortVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitPort_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitPort_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitPort_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitPort_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IUnitPort_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IUnitPort_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IUnitPort_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitPort_INTERFACE_DEFINED__ */


#ifndef __IParameterCollection_INTERFACE_DEFINED__
#define __IParameterCollection_INTERFACE_DEFINED__

/* interface IParameterCollection */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IParameterCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8DF9EFD1-9C1A-46A5-B3AF-2BEAB2067E46")
    IParameterCollection : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IParameterCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IParameterCollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
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
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
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


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IParameterCollection_INTERFACE_DEFINED__ */


#ifndef __IUnitPortEx_INTERFACE_DEFINED__
#define __IUnitPortEx_INTERFACE_DEFINED__

/* interface IUnitPortEx */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IUnitPortEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("874DE9E2-3053-4B49-98F4-B0F0653ADB8F")
    IUnitPortEx : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE put_direction( 
            /* [in] */ int portDirection) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IUnitPortExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IUnitPortEx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IUnitPortEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IUnitPortEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *put_direction )( 
            IUnitPortEx * This,
            /* [in] */ int portDirection);
        
        END_INTERFACE
    } IUnitPortExVtbl;

    interface IUnitPortEx
    {
        CONST_VTBL struct IUnitPortExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUnitPortEx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnitPortEx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IUnitPortEx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IUnitPortEx_put_direction(This,portDirection)	\
    ( (This)->lpVtbl -> put_direction(This,portDirection) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUnitPortEx_INTERFACE_DEFINED__ */



#ifndef __A2FLib_LIBRARY_DEFINED__
#define __A2FLib_LIBRARY_DEFINED__

/* library A2FLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_A2FLib;

EXTERN_C const CLSID CLSID_UnitOperations;

#ifdef __cplusplus

class DECLSPEC_UUID("A9129436-FB2C-4D26-B88D-A61E4D594BCB")
UnitOperations;
#endif

EXTERN_C const CLSID CLSID_PortCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("B837F485-6A5A-4B3C-A6CA-2D5A0440060F")
PortCollection;
#endif

EXTERN_C const CLSID CLSID_UnitPort;

#ifdef __cplusplus

class DECLSPEC_UUID("323340E4-D19F-44F4-AF0E-A051D407FC45")
UnitPort;
#endif

EXTERN_C const CLSID CLSID_ParameterCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("517833D9-2895-4588-AE54-2D3F4473A3C5")
ParameterCollection;
#endif
#endif /* __A2FLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


