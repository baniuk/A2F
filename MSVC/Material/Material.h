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
/**
 * \class Material
 *
 * \brief Class implementing basic tools for managing Cape-Open materials
 *
 * Class Class implementing basic tools for managing Cape-Open materials. Holds pointer to ICapePortMaterial directly and can operate on it. 
 * This class AddRefs and Releases this pointer.
 *
 * \author PB
 *
 * \date 2013/12/30
 */
class Material
{
public:
	/// main constructor
	Material(ICapeThermoMaterialObject *mat);
	/// gets four basic material properties for all material's id
//	HRESULT GetMaterialPropertes()
	~Material(void);
protected:
	ICapeThermoMaterialObject *mat; /*!< reference to the actual underlying version 1.0 Material Object, which is implemented by the simulation environment */
};
#endif // Material_h__

