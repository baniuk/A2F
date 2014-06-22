/**
 * \file C_FluentInterface.cpp
 * \brief Body of C_FluentInterface class
 * \author PB
 * \date 2014/06/21
 */
#include "stdafx.h"
#include "C_FluentInterface.h"


/**
 * \brief Assign profile file to obiect
 * \details Allow to perform operations on selected profile file. The structure of profile file is as follows: \n
 * It contains selected parameters for selected surfaces. All parameters are the same for all surfaces. It is assumed to be not possible to 
 * have different sets of parameters for surfaces. The structure of the file:
 * \code
 * ((anode-outlet point 420) <- name of the surface
 * (x <-x coord list
 * 4.2799311e-05
 * ...
 * )
 * (y <- y coord list
 * ...
 * )
 * (z <- z coord list
 * ...
 * )
 * (velocity-magnitude <- name of the function
 * ... <- function values
 * )
 * (molef-o2 <- name of the next function
 * ... <- function values
 * )
 * ) <- end of the surface
 * \param[in] profileName - profile file name and path
 * \author PB
 * \date 2014/06/22
 * \note It is assumed to be not possible to have different sets of parameters for surfaces
 * \exception Throws exceptions std::ios_base::failure on file fail open
 * \see http://www.cplusplus.com/reference/ios/ios/exceptions/
 * \see http://www.cplusplus.com/reference/ios/ios/setstate/
 * \see http://msdn.microsoft.com/query/dev11.query?appId=Dev11IDEF1&l=EN-US&k=k(string%2Fstd%3A%3Agetline);k(std%3A%3Agetline);k(getline);k(DevLang-C%2B%2B);k(TargetOS-Windows)&rd=true
*/
C_FluentInterface::C_FluentInterface(const char* profileName )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	profileFileName = profileName;
	profileFileHandle.open(profileName,std::ifstream::in);
	profileFileHandle.exceptions(profileFileHandle.failbit|profileFileHandle.badbit); // will throw exceptions of these errors
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}


C_FluentInterface::~C_FluentInterface(void)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	profileFileHandle.close();
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
}

/**
 * \brief Gets mean value of given fluent function for given surface
 * \details Analyses output profile file and reads data for given surface and given properties. Surface and properties must exist in profile file.
 * \param[in] fluentSurface - name of the surface in fluent model to read from. Must exist in prof file
 * \param[in] fluentFunc - name of the function in fluent used to get data of surface. Must exist in prof file
 * \return Mean value of fluentFunc on fluentSurface
 * \retval \c double
 * \author PB
 * \date 2014/06/22
 * \exception Throw exception on any error
*/
double C_FluentInterface::GetMean( const char* fluentSurface, const char* fluentFunc )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));

	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
	return 0.0;
}



/**
 * \brief Finds offset of line in prof file where surface starts
 * \details Returns offset in bytes (with LFCR) to point the line where surface starts
 * \param[in] fluentSurface - name of the surface to find
 * \return Offset to line where surface definition starts
 * \retval \c std::streampos
 * \author PB
 * \date 2014/06/22
 * \warning Can be problem with find method - if names will be similar (finds substring, eg fluentSurface=xxx will find xxx1 xxx2 ...)
 * \exception std::logic_error if surface not found
*/
streampos C_FluentInterface::getSurfaceOffset( const char* fluentSurface)
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	streampos offset = 0;
	string line = "";
	profileFileHandle.seekg(0);	// od pocz¹tku
	try
	{
		while (getline(profileFileHandle, line))	// all lines
		{
			if(line.find(fluentSurface)!=string::npos)
			{
				PANTHEIOS_TRACE_DEBUG(PSTR("Found surface: "),fluentSurface,PSTR(" at "),pantheios::integer(offset));
				PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
				return offset;
			}
			offset+=(line.length() + 2);					// offset po przeczytaniu + CRLF na koñcu linii - offset pokazuje pocz¹tek kolejnej liniii
		}
		profileFileHandle.exceptions(profileFileHandle.failbit|profileFileHandle.badbit); // will throw exceptions of these errors
	}
	//If the function (getline) extracts no elements, it calls setstate(failbit). In any case, it returns _Istr.
	// setstate -> Note that changing the state may throw an exception, depending on the latest settings passed to member exceptions.
	// exceptions are set in constructor to throw exception
	catch(std::ios_base::failure& ex)
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_FluentInterface::getSurfaceOffset caught exception: "),ex.what());	
		throw std::logic_error("Surface not found");
	}
	PANTHEIOS_TRACE_EMERGENCY(PSTR("should be never here because getline throws exception on eof (set in constructor)"));
	return 0;	// should be never here because getline throws exception on eof (set in constructor);
}
// can throw exception (badbit)
/**
 * \brief Finds offset of line in prof file where function starts
 * \details Returns offset in bytes (with LFCR) to point the line where function starts
 * \param[in] fluentFunc - name of the surface to find
 * \param[in] startOffset - offset to start seek from - mainly it should be offset of surface returned by streampos C_FluentInterface::getSurfaceOffset( const char* fluentSurface)
 * \return Offset to line where function definition starts
 * \retval \c std::streampos
 * \author PB
 * \date 2014/06/22
 * \warning Can be problem with find method - if names will be similar (finds substring, eg fluentSurface=xxx will find xxx1 xxx2 ...)
 * \exception std::logic_error if surface not found or std::ios_base
*/
streampos C_FluentInterface::getFunctionOffset( const char* fluentFunc, streampos startOffset )
{
	PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Entering"));
	string line = "";
	streampos offset = startOffset;
	try
	{
		profileFileHandle.seekg(startOffset); // startOffset points to line with surface name
		getline(profileFileHandle,line);	  // we read this line to remove ((
		while(!profileFileHandle.eof())
		{
			getline(profileFileHandle,line);
			if(line.find("((")!=string::npos)	// znaleŸliœmy pocz¹tek kolejnej surface!
				throw std::logic_error("Function not found - end of surface!!");
			if(line.find(fluentFunc)!=string::npos)	// function found found
			{
				PANTHEIOS_TRACE_DEBUG(PSTR("Found function: "),fluentFunc,PSTR(" at "),pantheios::integer(offset));
				PANTHEIOS_TRACE_INFORMATIONAL(PSTR("Leaving"));
				return offset;
			}
			offset+=(line.length() + 2);					// offset po przeczytaniu + CRLF na koñcu linii - offset pokazuje pocz¹tek kolejnej liniii
		}
		profileFileHandle.exceptions(profileFileHandle.failbit|profileFileHandle.badbit); // will throw exceptions of these errors
	}
	//If the function (getline) extracts no elements, it calls setstate(failbit). In any case, it returns _Istr.
	// setstate -> Note that changing the state may throw an exception, depending on the latest settings passed to member exceptions.
	// exceptions are set in constructor to throw exception
	catch(std::ios_base::failure& ex)
	{
		PANTHEIOS_TRACE_CRITICAL(PSTR("C_FluentInterface::getFunctionOffset caught exception: "),ex.what());	
		throw std::logic_error("Function not found");
	}
	PANTHEIOS_TRACE_EMERGENCY(PSTR("should be never here because getline throws exception on eof (set in constructor)"));
	return 0;	// should be never here because getline throws exception on eof (set in constructor);
}






