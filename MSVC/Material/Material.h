/**
 * \file    Material.h
 * \brief   Includes and definitions for Material class
 * \details Provides tools for handling Cape-Open materials
 * \author  PB
 * \date    2013/12/30
 * \version 0.5
 */
#ifndef Material_h__
#define Material_h__

// include Pantheios stuff
#include "..\A2F\Pantheios_header.h"
#import "c:\Program Files (x86)\Common Files\CAPE-OPEN\CAPE-OPENv1-0-0.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids, auto_search
#include <atlbase.h>
#include <atlsafe.h>
#include <atlcom.h>
#include <atlctl.h>

/**
 * Status of the material object.
 * VALIDATED after use of the MaterialFlash method INVALIDATED othervise
 */ 
enum MaterialStatus
{
	VALIDATED,
	INVALIDATED
};
/**
 * \class Material
 *
 * \brief Class implementing basic tools for managing Cape-Open materials
 *
 * Class Class implementing basic tools for managing Cape-Open materials. Holds pointer to ICapePortMaterial directly and can operate on it. 
 * This class AddRefs and Releases this pointer.
 *
 * \author PB
 * \warning Must be ATL before ATL classes or ATL namespace - it is not added by default
 * \cite http://ctrlf5.net/?p=197
 * \date 2013/12/30
 */
class Material
{
	friend class _MaterialTest;
public:
	/// main constructor
	Material(ICapeThermoMaterialObject *mat);
	/// Flashes Material internal structures
	HRESULT FlashMaterialObject();

	

	~Material(void);
private:
	/// Extract basic information on stram structure
	HRESULT get_Composition();
	/// Extract physical properties from materials
	HRESULT get_PhysicalProp();	
protected:
	ICapeThermoMaterialObject *mat; /*!< reference to the actual underlying version 1.0 Material Object, which is implemented by the simulation environment */
	LONG numComp;			/*< Number of components in stream */
	ATL::CComSafeArray<BSTR> phases;		/*< Phases in the stream */
	ATL::CComSafeArray<BSTR> compIds;		/*< Id of components in the stream */
	ATL::CComSafeArray<double> temperatures; /*< Holds temperatures of all components (all will be the same) */
private:
	MaterialStatus isValidated; 
};
#endif // Material_h__

