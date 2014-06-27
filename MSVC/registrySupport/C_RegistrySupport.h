/**
 * \file C_RegistrySupport.h
 * \brief Header for C_RegistrySupportClass
 * \author PB
 * \date 2014/06/26
 */
#ifndef C_RegistrySupport_h__
#define C_RegistrySupport_h__

#include <string.h>
#include <iostream>
#include <windows.h>

/**
 * \class C_RegistrySupport
 * \brief Supports basic registry access
 * \details Reads certain key in registry and returns patch for config file
 * \author PB
 * \date 2014/06/26
*/
class C_RegistrySupport
{
private:
	C_RegistrySupport(void);
	~C_RegistrySupport(void);
public:
	/// Opens string form given key
	static LONG GetStringforKey(HKEY key, const TCHAR* subKey, const TCHAR* value, std::string& outval);
};
#endif // C_RegistrySupport_h__

