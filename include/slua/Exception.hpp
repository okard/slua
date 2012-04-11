/*

*/
#pragma once
#ifndef __SLUA_EXCEPTION_HPP__
#define __SLUA EXCEPTION_HPP__

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

} //end namespace slua


#endif /* __SLUA EXCEPTION_HPP__ */