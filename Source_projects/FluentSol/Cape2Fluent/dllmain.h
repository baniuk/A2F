// dllmain.h : Declaration of module class.

class CCape2FluentModule : public CAtlDllModuleT< CCape2FluentModule >
{
public :
	DECLARE_LIBID(LIBID_Cape2FluentLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CAPE2FLUENT, "{DD2ED587-A0EA-4875-8656-A085BE2C72BD}")
};

extern class CCape2FluentModule _AtlModule;
