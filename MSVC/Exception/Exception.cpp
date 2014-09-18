/**
* \file Exception.cpp
* \brief Implementation of Exception class
* \author PB
* \date 2014/03/24
* \deprecated Not used in project
*/
#include "stdafx.h"
#include "Exception.h"

/**
* \brief Construct Exception obiect with description
* \details This class inherites also default constructor with no parmaeters. In this case description is undefined.
* \param[in] desc - description of the exception
* \author PB
* \date 2014/03/24
* \note
* \warning In case of default constructor \c desc is undefined
* \see std::exception
* \deprecated Not used in project
* \remarks Excption class defined by MS differs from std:exception. It has parametrized constructor and allows to provide error message.
* http://msdn.microsoft.com/en-us/library/c4ts6d5a.aspx. But in general every exception should be defined separatelly without providing error message
* as in this example: http://www.cplusplus.com/doc/tutorial/exceptions/ or
* using predefined ones: http://stackoverflow.com/questions/688447/best-practices-for-defining-your-own-exception-classes
*/
Exception::Exception(const char* desc)
{
	this->desc = desc;
}

Exception::~Exception(void) throw()
{
}

/**
* \brief Gets description of the exception
* \return Description of the exception stored in the obiect
* \retval \c const char*
* \author PB
* \date 2014/03/24
*/
const char* Exception::what() const throw()
{
	return desc;
};