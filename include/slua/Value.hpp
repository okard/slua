
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
    * TODO class enum
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
	//flags? initialized etc
	
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
	* setto
	*/
	virtual void pull(const lua_State* const state, int index);
	
	
	virtual void setto(const lua_State* const state, int index);
	
	/**
	* Is this value valid?
	*/
    virtual bool valid() const;
    
    /**
    * Get Value Type
    */
    inline Type getType() const { return type_; }
    
    /**
    * Get index position
    */
    inline int getIndex() const { return index_; }
    
    
    //set/getValue<T>
    
};
    
    
}


#endif // __SLUA_VALUE__
