/*

*/
#pragma once
#ifndef __SLUA_CONTEXT_HPP__
#define __SLUA_CONTEXT_HPP__

#include "Value.hpp"

struct lua_State;

namespace slua {

/**
* Higher Level Access to LuaState
* Provides utility functions for lua_State
*/
class Context
{
private:
    ///stack size at start
    int stacksize_;
    
    ///lua state
    lua_State* state_;
      
public:
        
    /**
    * Lua Context
    */
    Context();
            
    /**
    * Creates a new LuaContext for given lua_State
    */
    Context(lua_State* state);
    
    /**
    * Copy Constructor
    */
    Context(const Context& ctx);
    
    /**
    * Destructor
    */
    ~Context();
    
    /**
    * Assign Context to a lua_State
    */
    void assign(lua_State* const state);
    
    /**
    * validate the lua stack
    */
    bool validate();
    
    /**
    * validate grow of lua lua stack
    */
    bool validate(unsigned int grow);

    /**
    * get stack count
    */
    int stackCount() const; 
    
    //lua_checkstack
    
    //lua_pop
        
    //lua_remove
    //lua_replace
    
    
    //Get-Methods
    //* Number
    //* String
    void get(Value& val, int index = 0);
    

    //Push-Methods
    //-------------
    //void lua_pushboolean (lua_State *L, int b);
    //void lua_pushcclosure (lua_State *L, lua_CFunction fn, int n);
    //void lua_pushcfunction (lua_State *L, lua_CFunction f);
    //const char *lua_pushfstring (lua_State *L, const char *fmt, ...);
    //void lua_pushinteger (lua_State *L, lua_Integer n);
    //void lua_pushlightuserdata (lua_State *L, void *p);
    //void lua_pushliteral (lua_State *L, const char *s);
    //void lua_pushlstring (lua_State *L, const char *s, size_t len);
    //void lua_pushnil (lua_State *L);
    //void lua_pushnumber (lua_State *L, lua_Number n);
    //void lua_pushstring (lua_State *L, const char *s);
	//int lua_pushthread (lua_State *L);
	//void lua_pushvalue (lua_State *L, int index);
	//const char *lua_pushvfstring (lua_State *L, const char *fmt, va_list argp);
    
    //Call
    

    //LoadScript?
};

} //end namespace slua

#endif /* __SLUA CONTEXT_HPP__ */
