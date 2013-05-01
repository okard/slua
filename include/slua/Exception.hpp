/*

*/
#pragma once
#ifndef __SLUA_EXCEPTION_HPP__
#define __SLUA_EXCEPTION_HPP__

#include <exception>

namespace slua {

/**
* Engine Exception
*/
class LuaException : public std::exception
{
private:
    /// exception msg
    const char* msg;

public:
    /**
    * Constructor
    */
    LuaException(const char* msg)
        : msg(msg)
    {
    }
    
    /**
    * Description
    */
    virtual const char* what() const throw()
    {
        return msg;
    }
};


/**
* Engine Exception
*/
class LuaFormatException : public std::exception
{
private:
	static const int buf_size = 1024;
    char msg_[buf_size];

public:
    /**
    * Constructor
    */
    LuaFormatException(const char* msg, ...);
    
    /**
    * Destructor
    */
    ~LuaFormatException();
    
    /**
    * Description
    */
    virtual const char* what() const throw();
};


//Format Exception


} //end namespace slua


#endif /* __SLUA EXCEPTION_HPP__ */
