
#pragma once
#ifndef __SLUA_VALUE__
#define __SLUA_VALUE__

struct lua_State;

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
		TYPE_VALUE, //variable type
		
		TYPE_NIL,
		TYPE_BOOLEAN,
		TYPE_NUMBER,
        TYPE_STRING,
        TYPE_TABLE,
        TYPE_FUNCTION,
        TYPE_USERDATA,
        TYPE_LIGHTUSERDATA,
        TYPE_THREAD
    };
    
private:
    
    /// The type of the value
    Type type_;
    
    /// positive absolute index
    int index_;
    
public:

	Value();

	Value(const lua_State* const state);
	
	~Value();
    
    virtual bool valid() const;
    
    Type getType() const;
    
    int getIndex() const;
};
    
    
}


#endif // __SLUA_VALUE__
