
#pragma once
#ifndef __SLUA_VALUE__
#define __SLUA_VALUE__

#include <slua/Type.hpp>
#include <slua/Context.hpp>

namespace slua {
	
/**
* Lua Value
*/   
class Value
{   
private:
    /// The type of the value
    const LuaType type_;
    
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
	Value(LuaType type);

	/**
	* Destructor
	*/
	virtual ~Value();
	
	/**
	* Let the value point to the right state and to index
	*/
	virtual void setto(Context& ctx, int index);
	
	/**
	* Is this value valid?
	*/
    virtual bool valid() const;
    
    /**
    * Get Value Type
    */
    inline LuaType getType() const { return type_; }
    
    /**
    * Get index position
    */
    inline int getIndex() const { return index_; }
    
    /**
    * Get the real type at the position of the value
    */
    LuaType getRealType() const;
    
    /**
    * Get the lua type for a state at index position
    */
    static LuaType getLuaType(lua_State* state, int index); 
};
    
    
}


#endif // __SLUA_VALUE__
