/**
 * \file Exception.h
 * \brief Header of Exception class
 * \author PB
 * \date 2014/03/24
 */
#ifndef Exception_h__
#define Exception_h__

#include <exception>

/**
 * \class Exception
 * \brief Simple exception object with description
 * \details Implements exception obiect based on std::exception byt with description
 * \author PB
 * \date 2014/03/24
 * \see std::exception
 * \note Exception class inherites also default constructor with no parameters
*/
class Exception :
	public std::exception
{
public:
	/// Construct Exception obiect with description
	Exception(const char* desc);
	~Exception(void) throw();
	/// Description accessor
	const char* what() const throw();
private:
	const char* desc;		// exception description
};

#endif // Exception_h__


