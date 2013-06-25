/*

*/
#pragma once
#ifndef __SLUA_STATE_HPP__
#define __SLUA_STATE_HPP__

#include "Context.hpp"

#include <cstddef>

struct lua_State;


namespace slua {
	
class LuaAllocator;

//TODO Add Script.Load to vm at creation


/**
* Lua State
*/
class State
{
private:
	/// Allocator
    LuaAllocator& allocator_;
    
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
    * Cast operator for context
    */
    inline operator Context& ()  { return ctx_; }
    
    /**
    * Get the lua state manually
    */
    inline lua_State* const getState() const { return state_; }
    
    
    /**
    * Get the default context
    */
    inline Context& getContext() { return ctx_; }
    
    /**
    * Get allocator
    */
	const LuaAllocator& allocator() const { return allocator_; }
     
    /**
    * Get the lua state object from lua_State handle
    */
    static State& getState(lua_State* state);
    
    /**
    * Default lua allocator
    */
    static LuaAllocator& defaultAllocator();
    
    //ref to global table?
private:
	// static allocation function for bind
	static void* lua_alloc(void *ud, void *ptr, size_t osize, size_t nsize);
};


//replace with anyptr?
template<typename T>
class StateEx : public slua::State
{
private:
	T obj_;
public:
	inline void set(T obj) { obj_ = obj; }
	inline T get() { return obj_; }
};


} //end namespace slua

#endif /* __SLUA_STATE_HPP__ */
