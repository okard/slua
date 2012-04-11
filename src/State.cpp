
#include <slua/State.hpp>

#include <slua/Exception.hpp>

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
    lua_close(state_);
    state_ = nullptr;
}

/**
* Load a file
*/
void State::LoadFile(const char* file)
{
    int status = luaL_loadfile(state_, file);
    if (status)
    {
        throw LuaException("Can't load lua file");
        //LOG("Couldn't load file: " << lua_tostring(state, -1))
    }
}

/**
* Execute Lua Scripts
*/
int State::Execute()
{
    return lua_pcall(state_, 0, LUA_MULTRET, 0);
}

/**
* Cast to lua_State
*/
State::operator lua_State* const()
{
    return state_;
}

/**
* Get the lua state manually
*/
lua_State* const State::getState() const
{
    return state_;
}