

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

//TODO copy constructor

/**
* Destructor
*/
Context::~Context()
{
}

/**
* Assign Context to a lua_State
*/
void Context::assign(lua_State* state)
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
