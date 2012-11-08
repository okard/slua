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
    * Assign operator
    */
    Context& operator=(const Context& ctx);
    
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
    
    /**
    * Reset stack
    */
    void stackReset();
    
    /**
    * Cast Operator for lua_State*
    */
    operator lua_State* const ();
    
    
    
    //pushMetaTable();
    //pull(Table& table);
    
    
    //pull
    
    //create -> pushValue and makes a pull on stack top & pull
    

    //LoadScript?
};

} //end namespace slua

#endif /* __SLUA CONTEXT_HPP__ */
