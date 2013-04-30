

#include <slua/Context.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <slua/Exception.hpp>

using namespace slua;


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
* get the grown stack difference
*/
int Context::stackGrow() const
{
	checkValid();
	return stackCount() - stacksize_;
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
	checkValid();
	lua_settop(state_, stacksize_);
}

/**
* Cast Operator for lua_State*
*/
Context::operator lua_State* const ()
{
	if(state_ == nullptr)
		throw LuaException("Context is not assigned to a lua state");
		
	return state_;
}

/**
* Pop elements
*/
void Context::pop(int count)
{
	if(count <= 0)
		throw LuaException("Only positive numbers are allowed");
		
	checkValid();
	
	if(stackGrow() > count)
		throw LuaException("Want to pop more elements as available");
	
	lua_pop(state_, count);
}

/**
* Check if the current context is valid
*/
void Context::checkValid() const
{
	if(state_ == nullptr)
		throw LuaException("Context is not assigned to a lua state");
	
	if(stackCount() < stacksize_)
		throw LuaException("Current stack count is below context count");
}

/**
* Calculate absolute index
*/
int Context::absIndex(int index)
{
	if(index > 0)
		return index;
		
	return index + stackCount();
}

/**
* Get the index for c closure parameter
* (upvalueindex)
*/
int Context::upIndex(int index)
{
	if(index <= 0)
		throw LuaException("Invalid value for index");
		
	return lua_upvalueindex(index);
}

void Context::pushNil()
{
	checkValid();
	lua_pushnil(state_);
}

void Context::pushBool(bool value)
{
	checkValid();
	lua_pushboolean (state_, value);
}

void Context::pushInteger(int value)
{
	checkValid();
	lua_pushinteger (state_, value);
}

void Context::pushStringLiteral(const char* str)
{
	checkValid();
	//from macro lua_pushliteral
	lua_pushlstring(state_, str, (sizeof(str)/sizeof(char))-1);
}

void Context::pushString(const char* str)
{
	checkValid();
	lua_pushstring(state_, str);
}

void Context::pushPtr(void* ptr)
{
	checkValid();
	lua_pushlightuserdata(state_, ptr);
}

void Context::pushFunc(LuaFunction fn)
{
	checkValid();
	lua_pushcfunction(state_, fn);
}

void Context::pushClojure(LuaFunction fn, int args)
{
	checkValid();
	lua_pushcclosure(state_, fn, args);
}

void Context::pushTable()
{
	checkValid();
	lua_createtable(state_, 0, 0);
}

//return created true/false
bool Context::pushMetaTable(const char* key)
{
	checkValid();
	return luaL_newmetatable (state_, key);
}

/**
* get an integer value
*/
int Context::pullInteger(int index)
{
	checkValid();
	return lua_tointeger(state_, index);
}


void Context::pullGlobalTable(Table& tbl)
{
	/*lua 5.2
	 pushNumber(LUA_RIDX_GLOBALS)
	 lua_gettable(lua_State *L, LUA_REGISTRYINDEX);
	*/
	//pushglobaltable
	
	//tbl.pull(state_, LUA_GLOBALSINDEX);
}


/**
* Pull a table from index
*/
Table& Context::pullTable(Table& table, int index)
{
	table.pull(*this, absIndex(index));
	return table;
}

/**
* pull a ptr from index
*/
const void* Context::pullPtr(int index)
{
	auto ptr = lua_topointer(state_, index);
	if(ptr == NULL)
		throw LuaException("Is not a pointer");
	return ptr;
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
	int luaL_error (lua_State *L, const char *fmt, ...);
	* 
 *  //lua_checkstack
    
    //lua_pop
        
    //lua_remove
    //lua_replace
    * 
    //Push-Methods
    //-------------
    * 
    //void lua_pushnil (lua_State *L);
    //void lua_pushboolean (lua_State *L, int b);
    //void lua_pushinteger (lua_State *L, lua_Integer n);
    
    //void lua_pushnumber (lua_State *L, lua_Number n);
    
    //void lua_pushliteral (lua_State *L, const char *s);
    //void lua_pushlstring (lua_State *L, const char *s, size_t len);
	//void lua_pushstring (lua_State *L, const char *s);
    //const char *lua_pushfstring (lua_State *L, const char *fmt, ...);
    //const char *lua_pushvfstring (lua_State *L, const char *fmt, va_list argp); 
    
    //void lua_pushcclosure (lua_State *L, lua_CFunction fn, int n);
    //void lua_pushcfunction (lua_State *L, lua_CFunction f);
    //void lua_pushlightuserdata (lua_State *L, void *p);

	//int lua_pushthread (lua_State *L);
	//void lua_pushvalue (lua_State *L, int index);
	 
*/
