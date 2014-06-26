/**
 * \file C_RegistrySupport.cpp
 * \brief Body of C_RegistryClass
 * \author PB
 * \date 2014/06/26
 */
#include "stdafx.h"
#include "C_RegistrySupport.h"


C_RegistrySupport::C_RegistrySupport(void)
{
}


C_RegistrySupport::~C_RegistrySupport(void)
{
}

/**
 * \brief Read text key from registry
 * \details Open and reads \c subKey from registry \c key. The \c subKey must be text
 * \param[in] key - name of the key to read from, e.g. \a HKEY_CURRENT_USER
 * \param[in] subKey - name of the subkey to read from, e.g. \a "Software\\Cape2Fluent"
 * \param[in] value - name of the value to read from, e.g. \a InstallDir
 * \param[out] outval - string from subKey.
 * \return If the function succeeds, the return value is ERROR_SUCCESS.
 * If the function fails, the return value is a nonzero error code defined in Winerror.h. You can use the FormatMessage function with the FORMAT_MESSAGE_FROM_SYSTEM flag to get a generic description of the error.
 * \retval \c LONG
 * \author PB
 * \date 2014/06/26
 * \note On error outval can be undefined
*/
LONG C_RegistrySupport::GetStringforKey( HKEY key, const TCHAR* subKey, const TCHAR* value, std::string& outval )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	HKEY hKey;
	LONG lResult;
	TCHAR szBuffer[512];
	DWORD dwBufferSize = sizeof(szBuffer);
	outval.clear();
	PANTHEIOS_TRACE_DEBUG(PSTR("Opening "), subKey);
	lResult = RegOpenKeyEx(key, subKey, 0, KEY_READ, &hKey);
	if(lResult != ERROR_SUCCESS)
	{
		PANTHEIOS_TRACE_ERROR(PSTR("RegOpenKeyEx cant open key or subkey"));
		return lResult;	// exit on error
	}
	PANTHEIOS_TRACE_DEBUG(PSTR("Opening "), value);
	lResult = RegQueryValueEx(hKey, value, NULL, NULL, (LPBYTE)szBuffer, &dwBufferSize);
	if(lResult != ERROR_SUCCESS)
	{
		PANTHEIOS_TRACE_ERROR(PSTR("RegQueryValueEx cant open value"));
		RegCloseKey(hKey);
		return lResult;	// exit on error
	}
	outval = szBuffer;
	PANTHEIOS_TRACE_DEBUG(PSTR("Value read: "), szBuffer);

	RegCloseKey(hKey);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return lResult;
}
