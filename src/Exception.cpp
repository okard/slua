#include <slua/Exception.hpp>

#include <cstdarg>
#include <cstdio>

using namespace slua;

/**
* Constructor
*/
LuaFormatException::LuaFormatException(const char* msg, ...)
{
	va_list argument_list;
	va_start(argument_list, msg);
	
	int len = vsnprintf(msg_, buf_size - 2, msg, argument_list);  
	if(len < 0 || len > buf_size - 2)  
	{
		len = buf_size - 2;
	}
	msg_[len] = '\0';

	va_end(argument_list);
}

LuaFormatException::~LuaFormatException()
{
}

const char* LuaFormatException::what() const throw()
{
	return msg_;
}
