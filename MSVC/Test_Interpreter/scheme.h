String schema[] = new String[] {
	"@typedef _AspenProp					=	enum[temperature, totalflow, pressure, fraction]",
	"@typedef _ASSIGNS						=	tuple[string,component, int,PMC_input, string,surface]",				
	"@typedef _EXPORTS						=	tuple[string,Fluent_Func, _AspenProp,Aspen_Prop, string,Component]",	
	"@required DATA_PATH					=	string",																
	"@required FLUENT_PATH					=	string",
	"ASSIGNS								=	scope",
	"EXPORTS								=	scope",
	"SURFACES								=	scope",
	"BOUND_COND								=	string",
	"NUMOFITER								=	int",
	"CASE_NAME								=	string",
	"COMMAND_LINE							=	string",
	"ASSIGNS.uid-ASSIGN						=	_ASSIGNS", 
	"EXPORTS.uid-EXPORTED_VALUE				=	_EXPORTS",
	"SURFACES.uid-INPUT						=	list[string]",
	"SURFACES.uid-OUTPUT					=	list[string]"
};
