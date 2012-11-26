/*

*/
#pragma once
#ifndef __SLUA_CONTEXT_HPP__
#define __SLUA_CONTEXT_HPP__

#include "Value.hpp"
#include "Table.hpp"

struct lua_State;

namespace slua {
	
	
//TODO with available context?
typedef int (*LuaFunction) (lua_State *L);
  
  

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
    * get stack count
    */
    int stackCount() const; 
    
    /**
    * get the grown stack difference
    */
    int stackGrow() const;
    
    /**
    * Reset stack
    */
    void stackReset();
    
    /**
    * Cast Operator for lua_State*
    */
    operator lua_State* const ();
    
    /**
    * Calculate absolute index
    */
    int absIndex(int index);
    
    /**
    * Get the index for c closure parameter
    * (upvalueindex)
    */
    int upIndex(int index);
    
    /**
	* Pop elements
	*/
    void pop(int count = 0);
    
    ////////////////////////////////////////////////////////////////////////////
    // Push API
    ////////////////////////////////////////////////////////////////////////////
    void pushNil();
    void pushBool(bool value);
    void pushInteger(int value);
    void pushStringLiteral(const char* str);
    void pushString(const char* str);
    
    void pushPtr(void* ptr);
    void pushFunc(LuaFunction fn);
    void pushClojure(LuaFunction fn, int args);
    
    void pushTable();
    bool pushMetaTable(const char* key);
    
    ////////////////////////////////////////////////////////////////////////////
    // Pull API
    ////////////////////////////////////////////////////////////////////////////
    
    /**
    * get an integer value
    */
    int pullInteger(int index);
    
    /**
    * pull a ptr from index
    */
    const void* pullPtr(int index);
    
    
    /**
    * Pull the global table
    */
    void pullGlobalTable(Table& tbl);
    
    /**
    * Pull a table from index
    */
    Table& pullTable(Table& table, int index);
    
    
    //error

    
    //LoadScript?
    
private:
	inline void checkValid() const;
};

} //end namespace slua

#endif /* __SLUA CONTEXT_HPP__ */
