

#include <slua/Context.hpp>

using namespace slua;

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


/**
* Lua Context
*/
Context::Context()
    : state_(nullptr),
    stacksize_(0)
{
}
        
/**
* Creates a new LuaContext for given lua_State
*/
Context::Context(lua_State* state)
    : state_(state),
    stacksize_(lua_gettop(state))
{
}

/**
* Copy Constructor
*/
Context::Context(const Context& ctx)
    : state_(ctx.state_),
    stacksize_(ctx.stacksize_)
{
}

/**
* Destructor
*/
Context::~Context()
{
}

/**
* Assign Context to a lua_State
*/
void Context::assign(lua_State* const state)
{
    state_ = state;
    stacksize_ = lua_gettop (state_);
}

/**
* validate the lua stack
*/
bool Context::validate()
{
    return (stacksize_ == this->stackCount());
}

/**
* validate grow of lua lua stack
*/
bool Context::validate(unsigned int grow)
{
    return (stacksize_ + grow == this->stackCount());
}

/**
* get stack count
*/
int Context::stackCount() const
{
    return lua_gettop (state_);
}


void Context::get(Value& val, int index)
{
	switch(lua_type (state_, index))
	{
		case LUA_TNIL: 
			break;
		case LUA_TNUMBER: break; 
		case LUA_TBOOLEAN: break;
		case LUA_TSTRING: break; 
		case LUA_TTABLE: break; 
		case LUA_TFUNCTION: break; 
		case LUA_TUSERDATA: break; 
		case LUA_TTHREAD: break;
		case LUA_TLIGHTUSERDATA: break;
		//default: //error
	}
}

// LUA_REGISTRYINDEX is a table


//Whenever Lua calls C, the called function gets a new stack, which is independent of previous stacks 
//and of stacks of C functions that are still active. This stack initially contains any arguments to 
//the C function and it is where the C function pushes its results to be returned to the caller (see lua_CFunction). 

// Instead, they can refer to any element in the stack by using an index: A positive index represents 
// an absolute stack position (starting at 1); a negative index represents an offset relative to the
// top of the stack.
