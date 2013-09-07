// dllmain.h : Declaration of module class.

class CA2FModule : public ATL::CAtlDllModuleT< CA2FModule >
{
public :
	DECLARE_LIBID(LIBID_A2FLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_A2F, "{D2858D3A-91E7-4565-BF65-CF4F26573135}")
};

extern class CA2FModule _AtlModule;
