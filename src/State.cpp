
#include <slua/State.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

using namespace slua;


/**
* Creates a new State
*/
State::State()
    : state_(luaL_newstate())
{
    luaL_openlibs(state_);
}

/**
* Destructor
*/
State::~State()
{
}

/**
* Load a file
*/
void State::LoadFile(const char* file)
{
    
}

/**
* Execute Lua Scripts
*/
int State::Execute()
{
}



/**
* Get the lua state manually
*/
lua_State* const State::getState() const
{
    return state_;
}