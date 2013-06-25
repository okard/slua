/*

*/
#pragma once
#ifndef __SLUA_CONTEXT_HPP__
#define __SLUA_CONTEXT_HPP__

#include <slua/Type.hpp>

struct lua_State;

namespace slua {
	
	
class State;
		
//TODO with available context?
typedef int (*LuaFunction) (lua_State *L);

typedef void* lightdata;
  
/**
* Higher Level Access to LuaState
* Provides utility functions for lua_State
* Interact with the lua stack
*/
class Context
{
private:

    ///lua state
    lua_State* state_;
    
    ///stack size at start
    int stacksize_;
      
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
    
    //isValidIndex(index)
    
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
    void pushFloat(float f);
    void pushDouble(double d);
    void pushStringLiteral(const char* str);
    void pushString(const char* str);
    
    void pushPtr(void* ptr);
    void pushFunc(LuaFunction fn);
    void pushClojure(LuaFunction fn, int args);
    
    void pushTable();
    bool pushMetaTable(const char* key);
    bool pushMetaTable(int index);
    
    void pushGlobalTable();
    
    void pushCopy(int index);
    
    void pushGlobal(const char* key);
    
    ////////////////////////////////////////////////////////////////////////////
    // Get API
    ////////////////////////////////////////////////////////////////////////////
    
    /// Get Boolean
	bool getBoolean(int index);
        
    /// get an integer value
    int getInteger(int index);
    
    ///get float
    float getFloat(int index);
    
    ///get double
    double getDouble(int index);
    
    ///get a ptr from index
    const void* getPtr(int index);
    
    /// Get string
    const char* getString(int index);
    
	/**
	* Get type string
	*/
	const char* getTypeString(int index);
    
    /**
    * is the type at index
    */
    bool isType(int index, LuaType type);
    
    
    ////////////////////////////////////////////////////////////////////////////
    // Special API
    ////////////////////////////////////////////////////////////////////////////
    
    /**
    * Assign meta table
    */
    void assignMetaTable(int index);
    
    /**
    * Call function with args arguments and results 
    */
    void call(int args, int results);
    
    //error
    //LoadScript?
    
    
    State& getState();
private:
	inline void checkValid() const;
};

} //end namespace slua

#endif /* __SLUA CONTEXT_HPP__ */
