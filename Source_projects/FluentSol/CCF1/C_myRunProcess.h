#pragma once

class C_myRunProcess
{
public:
	C_myRunProcess(C_Error* perr,C_Params* params);
	~C_myRunProcess(void);
	LPCWSTR procname;
	LPWSTR parname;
	TCHAR *subprocname;
	BOOL StartFluent(void);
private:
	CComBSTR FLUENT_PATH;
	CComBSTR COMMAND_LINE;
	CComBSTR fulloutname;	// nazwa pliku wyj�ciowego
	BOOL WaitForStart(TCHAR* nazwa, unsigned int obrot, unsigned int czas);
	BOOL WaitForProcess(TCHAR* nazwa);
	BOOL PrintProcessNameAndID(DWORD processID, TCHAR* nazwa);
	double pressure;
	double totalflow;
	double fraction;
	double temperature;
//	Data_To_Read EXPORTS;		// nazwy exportowanych zeczy, potrzebne zeby wiedzie� jakie dane mamy
	double SR[MAX_EXPORTS];				// tu przechowuj� zaimportowane parametry, wa�nych jest tylko EXPORTS.ile parametr�w
	double SUM[MAX_EXPORTS];				// tu przechowuj� zaimportowane parametry, wa�nych jest tylko EXPORTS.ile parametr�w
	unsigned int ile_danych;	// ile jest element�w w prof
	void RemoveDoubleSlash(char* in); // usuwa podw�jnego slaska do �ciezek
	C_Params* copyparams;
	C_Error *err;
public:
	// Tworzy �rodowisko do uruchomienia fluenta - generuje scm oraz journalC_Params
	BOOL CreateEnv(void);
	BOOL ImportData(void);
	BOOL paramsval;	//jesli 1 to parametry aktualne
	// pobiera parametry z klasy
	void GetParams(double& temp, double& fract, double& flow, double& pres);
	// wpisuje parametry do klasy
	void PutParams(double temp, double *fract, double flow, double pres);
};
