
#pragma once
#ifndef __SLUA_VALUE__
#define __SLUA_VALUE__


namespace slua {
 
/**
* Lua Value
*/   
class Value
{
public:
    /**
    * LUA data types
    */
    enum Type
    {
        LUA_TYPE_STRING,
        LUA_TYPE_TABLE,
        LUA_TYPE_NUMBER
    };
    
private:
    
    Type type_;
    
public:
    
    
    Type getType();
};
    
    
}


#endif // __SLUA_VALUE__
