/*

*/
#pragma once
#ifndef __SLUA_STATE_HPP__
#define __SLUA_STATE_HPP__

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
    operator lua_State* const ();
    
    /**
    * Get the lua state manually
    */
    lua_State* const getState() const;  
    
    
    //ref to global table?
};

} //end namespace slua

#endif /* __SLUA_STATE_HPP__ */
