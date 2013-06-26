// dllmain.h : Declaration of module class.

class CCCF1Module : public CAtlDllModuleT< CCCF1Module >
{
public :
	DECLARE_LIBID(LIBID_CCF1Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CCF1, "{F8F48D0D-3F48-4C03-8214-E563C2FFF278}")
};

extern class CCCF1Module _AtlModule;
