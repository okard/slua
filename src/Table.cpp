
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
	: Value(LuaType::TABLE)
{
}

Table::~Table()
{
}


void Table::setto(Context& ctx, int index)
{
	if(!lua_istable (ctx, index))
		throw LuaException("Value is not a table");
	
	//check stacksize
	state_ = ctx;
	index_ = ctx.absIndex(index);
}


/**
* Pops 2 value from stack
* on top of stack the value
* under the value the key
*/
void Table::assignField()
{
	if(!valid())
		throw LuaException("not a valid table object anymore");
		
	lua_settable(const_cast<lua_State*>(state_), index_);
}

/**
* Assign value fom top of the stack
*/
void Table::assignField(const char* key)
{
	if(!valid())
		throw LuaException("not a valid table object anymore");
		
	lua_setfield (const_cast<lua_State*>(state_), index_, key);
}

/**
* Key on stack top
* pushes the field of the table
*/
void Table::pushField()
{
	if(!valid())
		throw LuaException("not a valid table object anymore");
		
	lua_gettable (const_cast<lua_State*>(state_), index_);
}


/**
* Pushes a table field onto stack
*/
void Table::pushField(const char* key)
{
	if(!valid())
		throw LuaException("not a valid table object anymore");
		
	lua_getfield (const_cast<lua_State*>(state_), index_, key);
}

/**
* Get the field with the key at index
*/
void Table::pushRaw(const int keyIndex)
{
	if(!valid())
		throw LuaException("not a valid table object anymore");
		
	//TODO Check of keyIndex is valid
	lua_rawgeti(const_cast<lua_State*>(state_), index_, keyIndex);
}

/**
* Assign the table on stack as metatable
*/
void Table::assignMetaTable()
{
	if(!valid())
		throw LuaException("not a valid table object anymore");
		
	//check value on top is a table?
	if(Value::getLuaType(const_cast<lua_State*>(state_), -1) != LuaType::TABLE)
		throw LuaException("No table on top of stack to assign as metatable");
	
	lua_setmetatable(const_cast<lua_State*>(state_), index_);
}

/**
* Pushes the MetaTable of the current tbl on stack
*/
bool Table::pushMetaTable()
{
	if(!valid())
		throw LuaException("not a valid table object anymore");
		
	return lua_getmetatable(const_cast<lua_State*>(state_), index_);		
}
	

 //The thread environment (where global variables live) is always at pseudo-index LUA_GLOBALSINDEX.
 //The environment of the running C function is always at pseudo-index LUA_ENVIRONINDEX. 


//void lua_setfield (lua_State *L, int index, const char *k);
	//table have to lie on top
	
//lua_settable (lua_State *L, int index);


//void lua_gettable (lua_State *L, int index);
//void lua_getfield (lua_State *L, int index, const char *k);
