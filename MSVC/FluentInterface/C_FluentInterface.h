/**
 * \file C_FluentInterface.h
 * \brief Header of C_FluentInterface class
 * \author PB
 * \date 2014/06/21
 */
#ifndef C_FluentInterface_h__
#define C_FluentInterface_h__

#include "..\Common_utilities\Pantheios_header.h"
#include <fstream> 
#include "gtest/gtest.h"

using namespace std;
/**
 * \class C_FluentInterface
 * \brief Supports input/output operations between Fluent and PMC
 * \detail Contains methods of low-level operations on output files. Defined for testing purposes mainly. It opens given profile fila and then allows to perform
 * several operations on it according to its content. Class can read selected data on demand.
 * \author PB
 * \date 2014/06/21
 * \see CUnitOperations
*/
class C_FluentInterface
{
	friend class _FluentInterface; 
	FRIEND_TEST(_FluentInterface,_getSurfaceOffset);
	FRIEND_TEST(_FluentInterface,_getFunctionOffset);
	FRIEND_TEST(_FluentInterface,_getFunctionOffsetWrong);
	FRIEND_TEST(_FluentInterface,_getSurfaceOffsetWrong);
	FRIEND_TEST(_FluentInterface,_getMean);
public:
	C_FluentInterface(const char* profileName );
	~C_FluentInterface(void);
	/// Gets mean value of fluentFunc of given fluentSurface
	double GetMean(const char* fluentSurface, const char* fluentFunc);

private:
	string profileFileName; // keep name of the file to open
	std::ifstream profileFileHandle; // handle of file
	/// Finds offset of surface part in prof file
	streampos getSurfaceOffset( const char* fluentSurface);
	/// Finds offset of function within surface part in prof file
	streampos getFunctionOffset(const char* fluentFunc, streampos startOffset);
};


#endif // C_FluentInterface_h__


