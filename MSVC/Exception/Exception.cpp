#include "stdafx.h"
#include "Exception.h"

/// \todo Document these classes
Exception::Exception(const char* desc)
{
	this->desc = desc;
}


Exception::~Exception(void) throw()
{
}

const char* Exception::what() const throw()
{ 
	return desc;
};