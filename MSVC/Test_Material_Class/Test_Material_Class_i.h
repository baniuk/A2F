

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Mon Jan 06 16:56:13 2014
 */
/* Compiler settings for Test_Material_Class.idl:
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

#ifndef __Test_Material_Class_i_h__
#define __Test_Material_Class_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICapeMaterialObject_FWD_DEFINED__
#define __ICapeMaterialObject_FWD_DEFINED__
typedef interface ICapeMaterialObject ICapeMaterialObject;

#endif 	/* __ICapeMaterialObject_FWD_DEFINED__ */


#ifndef __Ixx_FWD_DEFINED__
#define __Ixx_FWD_DEFINED__
typedef interface Ixx Ixx;

#endif 	/* __Ixx_FWD_DEFINED__ */


#ifndef __CapeMaterialObject_FWD_DEFINED__
#define __CapeMaterialObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class CapeMaterialObject CapeMaterialObject;
#else
typedef struct CapeMaterialObject CapeMaterialObject;
#endif /* __cplusplus */

#endif 	/* __CapeMaterialObject_FWD_DEFINED__ */


#ifndef __xx_FWD_DEFINED__
#define __xx_FWD_DEFINED__

#ifdef __cplusplus
typedef class xx xx;
#else
typedef struct xx xx;
#endif /* __cplusplus */

#endif 	/* __xx_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICapeMaterialObject_INTERFACE_DEFINED__
#define __ICapeMaterialObject_INTERFACE_DEFINED__

/* interface ICapeMaterialObject */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ICapeMaterialObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("13DE0C3A-0CF7-42AF-8634-41879FADFFEE")
    ICapeMaterialObject : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct ICapeMaterialObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICapeMaterialObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICapeMaterialObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICapeMaterialObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICapeMaterialObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICapeMaterialObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICapeMaterialObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICapeMaterialObject * This,
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
    } ICapeMaterialObjectVtbl;

    interface ICapeMaterialObject
    {
        CONST_VTBL struct ICapeMaterialObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICapeMaterialObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICapeMaterialObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICapeMaterialObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICapeMaterialObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICapeMaterialObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICapeMaterialObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICapeMaterialObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICapeMaterialObject_INTERFACE_DEFINED__ */


#ifndef __Ixx_INTERFACE_DEFINED__
#define __Ixx_INTERFACE_DEFINED__

/* interface Ixx */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_Ixx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F61A9DA7-98F6-47C2-8749-3013C7490373")
    Ixx : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IxxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            Ixx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            Ixx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            Ixx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            Ixx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            Ixx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            Ixx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            Ixx * This,
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
    } IxxVtbl;

    interface Ixx
    {
        CONST_VTBL struct IxxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ixx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define Ixx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define Ixx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define Ixx_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define Ixx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define Ixx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define Ixx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __Ixx_INTERFACE_DEFINED__ */



#ifndef __Test_Material_ClassLib_LIBRARY_DEFINED__
#define __Test_Material_ClassLib_LIBRARY_DEFINED__

/* library Test_Material_ClassLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Test_Material_ClassLib;

EXTERN_C const CLSID CLSID_CapeMaterialObject;

#ifdef __cplusplus

class DECLSPEC_UUID("E28C0506-E0BA-4D5C-973A-812141857D46")
CapeMaterialObject;
#endif

EXTERN_C const CLSID CLSID_xx;

#ifdef __cplusplus

class DECLSPEC_UUID("96BDEA21-36C7-4323-B361-5682A345B202")
xx;
#endif
#endif /* __Test_Material_ClassLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


