

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
* Assign operator
*/
Context& Context::operator=(const Context& ctx)
{
	if (this != &ctx)
	{
		this->assign(ctx.state_);
	}
	return *this;
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

/**
* Reset to beginning
*/
void Context::stackReset()
{
	lua_settop(state_, stacksize_);
}

/**
* Cast Operator for lua_State*
*/
Context::operator lua_State* const ()
{
	if(state_ == nullptr)
		throw "Error";
		
	return state_;
}


/*



void Context::get(Value& val, int index)
{
	//val.getType should match
	
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

*/


// LUA_REGISTRYINDEX is a table

//


//Whenever Lua calls C, the called function gets a new stack, which is independent of previous stacks 
//and of stacks of C functions that are still active. This stack initially contains any arguments to 
//the C function and it is where the C function pushes its results to be returned to the caller (see lua_CFunction). 

// Instead, they can refer to any element in the stack by using an index: A positive index represents 
// an absolute stack position (starting at 1); a negative index represents an offset relative to the
// top of the stack.

/* 
 * 
 *  //lua_checkstack
    
    //lua_pop
        
    //lua_remove
    //lua_replace
    * 
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
*/
