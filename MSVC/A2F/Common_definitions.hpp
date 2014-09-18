/**
* \file Common_definitions.hpp
* \brief This file contains common definitions used in different projects
* \author PB
* \date 2014/09/09
*/

#ifndef Common_definitions_h__
#define Common_definitions_h__

#include <cstdlib>	// for size_t
/**
* \class PropertyName
* \brief Defines names of physical properties of materials
* \author PB
* \date 2014/09/09
*/
enum class PropertyName : std::size_t
{
	Temperature = 0,	///< Temperature
	Pressure,			///< Pressure
	Fraction,			///< Fraction
	Flow				///< Flow
};

#endif // Common_definitions_h__