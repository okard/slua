/*

*/
#pragma once
#ifndef __SLUA_STATE_HPP__
#define __SLUA_STATE_HPP__

#include "Context.hpp"


struct lua_State;


namespace slua {

//TODO Add Script.Load to vm at creation

/**
* Lua State
*/
class State
{
  private:
    /// the lua state
    lua_State* state_;
    
    /// default lua context
    Context ctx_;
    
  public:
    /**
    * Creates a new LuaState
    */
    State();
    
    /**
    * Destructor
    */
    ~State();
    
    /**
    * Load a file
    */
    void LoadFile(const char* file);
    
    /**
    * Execute Lua Scripts
    */
    int Execute();
    
    /**
    * Cast Operator for lua_State*
    */
    inline operator lua_State* const () { return state_; }
    
    /**
    * Get the lua state manually
    */
    inline lua_State* const getState() const { return state_; }
    
    
    /**
    * Get the default context
    */
    inline Context& getContext() { return ctx_; }
    
    //
    
    //ref to global table?
};

} //end namespace slua

#endif /* __SLUA_STATE_HPP__ */
