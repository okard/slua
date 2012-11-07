
#include <slua/Table.hpp>

using namespace slua;


//create a new anonymous table on the stack
Table* const Table::create(const Context& ctx)
{
	//void lua_newtable (lua_State *L);
	//void lua_createtable (lua_State *L, int narr, int nrec);
}

//load a table from the top of the stack
Table* const Table::load(const Context& ctx)
{
	//top of the stack is table
}


void Table::setTable(int index)
{
	//-1
	//-2
	//-3
	//if(lua_istable(ctx, index))
}



 //The thread environment (where global variables live) is always at pseudo-index LUA_GLOBALSINDEX.
 //The environment of the running C function is always at pseudo-index LUA_ENVIRONINDEX. 


//void lua_setfield (lua_State *L, int index, const char *k);
//lua_settable (lua_State *L, int index);


//void lua_gettable (lua_State *L, int index);
//void lua_getfield (lua_State *L, int index, const char *k);
