
#include <slua/Table.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}


#include <slua/Exception.hpp>

using namespace slua;


Table::Table()
	: Value(TYPE_TABLE)
{
}

Table::~Table()
{
}


void Table::pull(const lua_State* const state, int index)
{
	if(!lua_istable (const_cast<lua_State*>(state), index))
		throw LuaException("Value is not a table");
	
	//check stacksize
	state_ = state;
	index_ = index;
}


/**
* Pops 2 value from stack
* on top of stack the value
* under the value the key
*/
void Table::assignField()
{
	valid();
	lua_settable(const_cast<lua_State*>(state_), index_);
}

/**
* Assign value fom top of the stack
*/
void Table::assignField(const char* key)
{
	valid();
	lua_setfield (const_cast<lua_State*>(state_), index_, key);
}

/**
* Key on stack top
* pushes the field of the table
*/
void Table::pushField()
{
	valid();
	lua_gettable (const_cast<lua_State*>(state_), index_);
}


/**
* Pushes a table field onto stack
*/
void Table::pushField(const char* key)
{
	valid();
	lua_getfield (const_cast<lua_State*>(state_), index_, key);
}

 //The thread environment (where global variables live) is always at pseudo-index LUA_GLOBALSINDEX.
 //The environment of the running C function is always at pseudo-index LUA_ENVIRONINDEX. 


//void lua_setfield (lua_State *L, int index, const char *k);
	//table have to lie on top
	
//lua_settable (lua_State *L, int index);


//void lua_gettable (lua_State *L, int index);
//void lua_getfield (lua_State *L, int index, const char *k);
