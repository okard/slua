/*

*/
#pragma once
#ifndef __SLUA_LUACONTEXT_HPP__
#define __SLUA LUACONTEXT_HPP__

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
    int stacksize;
    
    ///lua state
    lua_State* luaState;
      
public:
        
    /**
    * Lua Context
    */
    Context();
            
    /**
    * Creates a new LuaContext for given lua_State
    */
    Context(lua_State* state);
    
    //TODO copy constructor
    
    /**
    * Destructor
    */
    ~Context();
    
    /**
    * Assign Context to a lua_State
    */
    void assign(lua_State* state);
    
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
    int stackCount();
    

    //Push-Methods
    //* String
    //* Function
    
    
    //Get-Methods
    //* Number
    //* String
    
    //Call
    
    //Create-Methods
    //* CreateTable
    
    
    //LoadScript?
};

} //end namespace slua

#endif /* __SLUA LUACONTEXT_HPP__ */