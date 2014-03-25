/**
* \file scheme.h
* \brief Autogenerated by Scheme2Str tool
* \details Generated on basis Scheme.cfg file which is used with config4cpp tool
*/
const char* schema[] = {
	"@typedef _AspenProp					=	enum[temperature, totalflow, pressure, fraction]",
	"@typedef _ASSIGNS						=	tuple[string,component, int,PMC_input, string,surface]",				
	"@typedef _EXPORTS						=	tuple[string,Fluent_Func, _AspenProp,Aspen_Prop, string,Component]",	
	"@typedef _SURFACES						=	tuple[string,surface, float,area]",
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
	"SURFACES.INPUT1						=	_SURFACES",
	"SURFACES.INPUT2						=	_SURFACES",
	"SURFACES.OUTPUT1						=	_SURFACES"
};
