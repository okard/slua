
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
		
		//Fixed types
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
    const Type type_;
    
protected:
    /// positive absolute index
    int index_;
    
    /// lua state
    const lua_State* state_;
    
public:

	/**
	* Creates a dynamic value type
	*/
	Value();
	
	/**
	* Create a value for type
	*/
	Value(Type type);

	/**
	* Destructor
	*/
	~Value();
	
	/**
	* Assign a lua stack object to value
	*/
	virtual void pull(const lua_State* const state, int index);
	
	/**
	* Is this value valid?
	*/
    virtual bool valid() const;
    
    /**
    * Get Value Type
    */
    Type getType() const;
    
    /**
    * Get index position
    */
    inline int getIndex() const;
};
    
    
}


#endif // __SLUA_VALUE__
