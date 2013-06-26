

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


MIDL_DEFINE_GUID(IID, IID_IUnitOperation,0x1ABD43ED,0x339F,0x43ED,0x90,0x87,0x39,0x69,0x04,0xA8,0x52,0x06);


MIDL_DEFINE_GUID(IID, IID_IPort,0x8B172D11,0x6ECB,0x4EF6,0x82,0xDD,0x0B,0x36,0xF5,0xED,0x68,0xAE);


MIDL_DEFINE_GUID(IID, IID_IPortCollection,0xC3576B00,0xA36A,0x4C58,0x93,0x11,0x3F,0x25,0xC0,0x18,0x5E,0x2B);


MIDL_DEFINE_GUID(IID, IID_IParameterCollection,0xF9FC8344,0x8D41,0x4784,0xA4,0x91,0x92,0x51,0x20,0xE0,0x9B,0x06);


MIDL_DEFINE_GUID(IID, LIBID_CCF1Lib,0x57DD3450,0x4BD1,0x485B,0xAD,0x22,0xB0,0x05,0x7D,0x38,0x19,0x1D);


MIDL_DEFINE_GUID(CLSID, CLSID_CompReg,0x4E8E6E1F,0x6001,0x40D7,0xA6,0xD5,0x77,0xC1,0x0C,0x04,0x13,0xC8);


MIDL_DEFINE_GUID(CLSID, CLSID_UnitOperation,0x060E165D,0x4FCF,0x49CB,0x96,0xB6,0x42,0x7A,0x5C,0xFC,0xB5,0x7A);


MIDL_DEFINE_GUID(CLSID, CLSID_Port,0x2447B9B3,0xF326,0x4EFF,0x86,0x4D,0x41,0xDC,0x22,0x11,0x1B,0x4A);


MIDL_DEFINE_GUID(CLSID, CLSID_PortCollection,0xAD8CC3DF,0x932C,0x40ED,0xA6,0xB9,0x48,0x03,0x6B,0xF2,0xC4,0xDE);


MIDL_DEFINE_GUID(CLSID, CLSID_ParameterCollection,0x423EC7B2,0x0159,0x4EA7,0x87,0x51,0xC4,0x4F,0x72,0x03,0xA2,0x14);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



