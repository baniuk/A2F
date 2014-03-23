#pragma once
#include <exception>

class Exception :
	public std::exception
{
public:
	Exception(const char* desc);
	~Exception(void) throw();
	const char* what() const throw();
private:
	const char* desc;		// exception description
};

