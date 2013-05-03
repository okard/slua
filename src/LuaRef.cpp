
#include <slua/LuaRef.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

using namespace slua;

LuaRef::LuaRef(lua_State* const state) 
	:  state_(state), ref_(0), set_(false)
{
}

LuaRef::~LuaRef()
{
	if(set_)
		unref();
}

void LuaRef::set() 
{ 
	if(set_)
		unref();
		
	ref_ = luaL_ref(state_, LUA_REGISTRYINDEX); 
	set_ = true;
}

void LuaRef::push() 
{ 
	if(set_)
		lua_rawgeti(state_, LUA_REGISTRYINDEX, ref_); 
}

void LuaRef::unref() 
{ 
	luaL_unref(state_, LUA_REGISTRYINDEX, ref_); 
	set_ = false;
}
