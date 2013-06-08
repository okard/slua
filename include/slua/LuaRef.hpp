
#pragma once
#ifndef __SLUA_LUAREF_HPP__
#define __SLUA_LUAREF_HPP__

struct lua_State;

namespace slua {

/**
* A Lua Reference
*/ 
class LuaRef
{
private:
	int ref_;
	lua_State* state_;
	bool set_;
public:

	/**
	* Create lua ref for state
	*/
	LuaRef(lua_State* const state);
	
	/**
	* Destroy lua ref
	*/
	~LuaRef();

	/**
	* Set the reference to the top of the object and pops it
	*/
	void set();
	
	/**
	* Push the reference object onto stack
	*/
	void push();
	
	/**
	* Delete the reference
	*/
	void unref();
	
	/**
	* LuaRef is set
	*/
	inline bool isSet() const { return set_; }
	
	/**
	* Get lua_State 
	*/ 
	inline operator lua_State* const () { return state_; }
};


} //end namespace slau

#endif
