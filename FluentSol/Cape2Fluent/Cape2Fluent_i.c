

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Mon Sep 09 16:55:55 2013
 */
/* Compiler settings for Cape2Fluent.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IComponentRegistrar,0xa817e7a2,0x43fa,0x11d0,0x9e,0x44,0x00,0xaa,0x00,0xb6,0x77,0x0a);


MIDL_DEFINE_GUID(IID, IID_IUnitOperation,0x439937D7,0xDF7A,0x4A90,0x97,0x2E,0x77,0x98,0x24,0xDC,0x8C,0x76);


MIDL_DEFINE_GUID(IID, IID_IPort,0x7369F1D6,0xFC5C,0x4671,0x83,0x2D,0xE2,0xB0,0xE5,0x95,0xC7,0x07);


MIDL_DEFINE_GUID(IID, IID_IParameterCollection,0x4B96ACBB,0xFF51,0x4DE7,0xB2,0x1A,0xE3,0x68,0x44,0x6C,0x89,0x7D);


MIDL_DEFINE_GUID(IID, IID_IPortCollection,0x711072EC,0x6409,0x44EF,0x87,0x5A,0x11,0xA9,0x88,0xC0,0xB2,0x5C);


MIDL_DEFINE_GUID(IID, LIBID_Cape2FluentLib,0xA41DD893,0x4E3F,0x45A6,0xBB,0xEF,0x42,0x5E,0xCE,0x7F,0xA6,0x37);


MIDL_DEFINE_GUID(CLSID, CLSID_CompReg,0x72A2CC99,0x2D19,0x4E9F,0x89,0xC4,0xC3,0x0C,0x98,0x39,0xDB,0x87);


MIDL_DEFINE_GUID(CLSID, CLSID_UnitOperation,0x687728BA,0x9FC0,0x4F97,0xA1,0x43,0xEB,0xEE,0x07,0x35,0xC1,0x8F);


MIDL_DEFINE_GUID(CLSID, CLSID_Port,0x4C56EFAA,0xDE81,0x47B4,0x85,0xD6,0x6E,0x87,0xEF,0xBC,0x36,0xEC);


MIDL_DEFINE_GUID(CLSID, CLSID_ParameterCollection,0x7C2975A7,0x663A,0x4BAD,0xA9,0x9E,0x07,0x5A,0xF4,0x78,0xAC,0x51);


MIDL_DEFINE_GUID(CLSID, CLSID_PortCollection,0x821998BE,0x7720,0x4F7F,0x97,0x78,0x52,0xC6,0x1D,0xDA,0x28,0x88);


MIDL_DEFINE_GUID(IID, DIID_I_myDialog,0x2B01BBFA,0xBEB6,0x47AB,0xB9,0xF5,0x17,0x4F,0x58,0x98,0xA6,0x97);


MIDL_DEFINE_GUID(CLSID, CLSID__myDialog,0xA899055E,0x2A8D,0x4E3F,0x9D,0xA4,0x5D,0x9F,0x01,0xE6,0xE2,0xF0);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



