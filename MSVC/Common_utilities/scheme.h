/**
* \file scheme.h
* \brief Autogenerated by Scheme2Str tool
* \details Generated on basis Scheme.cfg file which is used with config4cpp tool
*/
const char* schema[] = {
	"@typedef _ASSIGNS						=	tuple[string,component, string,PMC_stream_name, string,surface]",				
	"@typedef _EXPORTS						=	tuple[string,reportType, string,surface, string,variable]",	
	"@typedef _SURFACES						=	tuple[string,surface, float,area]",
	"@required DATA_PATH					=	string",																
	"@required FLUENT_PATH					=	string",
	"@required PROCESS_NAME					=	string",
	"@required STACK_NUM					=	int",
	"ASSIGNS								=	scope",
	"EXPORTS								=	scope",
	"SURFACES								=	scope",
	"BOUND_COND								=	string",
	"@required NUMOFITER					=	int",
	"@required CASE_NAME					=	string",
	"@required COMMAND_LINE					=	string",
	"ASSIGNS.uid-ASSIGN						=	_ASSIGNS", 
	"EXPORTS.uid-EXPORTED_VALUE				=	_EXPORTS",
	"SURFACES.uid-SURFACE					=	_SURFACES",
};
