
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
		TYPE_NOTSET,
		TYPE_NIL,
		TYPE_BOOLEAN,
		TYPE_NUMBER,
        TYPE_STRING,
        TYPE_TABLE,
        TYPE_FUNCTION
 
        //TYPE_USERDATA
        //TYPE_LIGHTUSERDATA
        //TYPE_THREAD
    };
    
private:
    
    /// The type of the value
    Type type_;
    
    /// positive absolute index
    int index_;
    
    
    //context?
public:
    
    //virtual bool valid()
    
    Type getType();
};
    
    
}


#endif // __SLUA_VALUE__
