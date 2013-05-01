
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
    : state_(luaL_newstate()),
	  ctx_(state_)
{
    luaL_openlibs(state_);
    
    
    //register panic function:
	//lua_atpanic
	//lua_CFunction lua_atpanic (lua_State *L, lua_CFunction panicf);
	//using debugger?
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
        throw LuaFormatException("Error loading file: %s", lua_tostring(state_, -1));
    }
}

/**
* Execute Lua Scripts
*/
int State::Execute()
{
    return lua_pcall(state_, 0, LUA_MULTRET, 0);
}




/*
Sets a new panic function and returns the old one.
If an error happens outside any protected environment, Lua calls a panic function and then calls exit(EXIT_FAILURE), thus exiting the host application. Your panic function can avoid this exit by never returning (e.g., doing a long jump).
The panic function can access the error message at the top of the stack. 
*/
