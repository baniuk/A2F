/**
 * \file    UnitOperations.cpp
 * \brief   COClass for unit operations
 * \details Implements basic interfaces required by CAPE-OPEN. Contains also initialization of Pantheios API. It seems that after adding model to workspace
 *			destructor is also called. Object is created, ask about ports and deleted.
 * \author  PB
 * \date    2013/09/10
 * \version 0.5
 */

#include "stdafx.h"
#include "UnitOperations.h"

/// Log file name and initialization of Pantheios API
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("A2F");
/**
 * \brief Struktura okreœlaj¹ca minimalny poziom b³edu który trafia do danego logu
 *
 * DEBUG jest poziomem najni¿szym, co znaczy ¿e do pliku trafi wszystko. Ta struktura dzia³a
 * jedynie gdy linkuje siê do biblioteki be.N. Kolejnoœæ b³êdów:
 * -# DEBUG
 * -# INFORMATIONAL
 * -# NOTICE
 * -# WARNING
 * -# ERROR
 * -# CRITICAL
 * -# ALERT
 * -# EMERGENCY
 * \n
 * Do konsoli trafi wszystko powy¿ej ERROR
 */
pan_fe_N_t PAN_FE_N_SEVERITY_CEILINGS[]  = {
    { toFile,  PANTHEIOS_SEV_DEBUG },
    PANTHEIOS_FE_N_TERMINATOR_ENTRY(PANTHEIOS_SEV_CRITICAL)
};

/**
 * \brief Struktura ³¹cz¹ca poziom b³edu z konkretnym wyjœciem
 *
 * LOGI::File i LOGI::Console ³¹cz¹ siê z pozycjami w PAN_FE_N_SEVERITY_CEILINGS
 */
pan_be_N_t PAN_BE_N_BACKEND_LIST[] = {
    PANTHEIOS_BE_N_STDFORM_ENTRY(toFile, pantheios_be_file, 0),
    PANTHEIOS_BE_N_TERMINATOR_ENTRY
};

// CUnitOperations

CUnitOperations::CUnitOperations()
{
	
}

CUnitOperations::~CUnitOperations()
{

}

/**
* \details  COM initialization method called after construction of the object. Other interfaces should be created here.
*			Initializes also logging API and sets output log file.
* \return   Return S_OK on success or one of the standard error HRESULT values.
* \retval   status   The program status.
*                     \li E_FAIL = on Pantheios initialization fail (file and api)
*                     \li S_OK = Success
* \see
*			\li http://msdn.microsoft.com/en-us/library/afkt56xx(v=vs.110).aspx
*			\li http://www.murrayc.com/learning/windows/usecomfromatl.shtml
*/
HRESULT CUnitOperations::FinalConstruct()
{
	// Logging API initialization
	if(pantheios::init()<0)
		return E_FAIL;
	// set file name and path
	pantheios_be_file_setFilePath(PSTR(PANTHEIOS_LOG_FILE_NAME), PANTHEIOS_BEID_ALL);
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("LOG API Initialized"));
	return S_OK;
}

/**
* \details  Close log file and un-initialize Pantheios API
* \return   none
*/
void CUnitOperations::FinalRelease()
{
	// closing log file
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("LOG API Closing"));
	pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);
	pantheios::uninit();
}

STDMETHODIMP CUnitOperations::get_ports( LPDISPATCH * ports )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	PANTHEIOS_TRACE_DEBUG(PSTR("x = "),pantheios::real(10.5));
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ValStatus( CapeValidationStatus * ValStatus )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Calculate()
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Validate( BSTR * message, VARIANT_BOOL * isValid )
{
	return E_NOTIMPL;
}


STDMETHODIMP CUnitOperations::get_name( BSTR * name )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_code( long * code )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_description( BSTR * description )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_scope( BSTR * scope )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_interfaceName( BSTR * interfaceName )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_operation( BSTR * operation )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_moreInfo( BSTR * moreInfo )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ComponentName( BSTR * name )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_ComponentName( BSTR name )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_ComponentDescription( BSTR * desc )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_ComponentDescription( BSTR desc )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_parameters( LPDISPATCH * parameters )
{
	return E_NOTIMPL;
}

/**
* \details  Initialize allows the unit to initialize itself. It is called once when the unit operation model is instantiated in a particular flowsheet.
*			The Initialize method must not change the current working directory: if it does Aspen Plus will not be able to access its own files and will fail.
*			If the Initialize method needs to display a dialog to allow a user to open a file, it must ensure that the current working directory is restored
*			after a file is selected.
* \return   CapeError
* \retval   status   The program status.
*                     \li S_OK = Success
* \see      AspenPlusUserModelsV8_2-Ref.pdf pp. 286
* \note		Any initialization that could fail must be placed here instead of the constructor.
*/
STDMETHODIMP CUnitOperations::Initialize()
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Initialize"));
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_simulationContext( LPDISPATCH )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Edit()
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::Terminate()
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_reports( VARIANT * reports )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::get_selectedReport( BSTR * report )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::put_selectedReport( BSTR report )
{
	return E_NOTIMPL;
}

STDMETHODIMP CUnitOperations::ProduceReport( BSTR * message )
{
	return E_NOTIMPL;
}

