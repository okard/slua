
#include <slua/Value.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <slua/Context.hpp>


using namespace slua;

class LuaRef
{
private:
	int ref_;
	lua_State* state_;
public:

	LuaRef(lua_State* const state) :  state_(state), ref_(0) {}

	void set(lua_State* const state) { ref_ = luaL_ref(state, LUA_REGISTRYINDEX); }
	void push(lua_State* const state) { lua_rawgeti(state, LUA_REGISTRYINDEX, ref_); }
	void unref(lua_State* const state) { luaL_unref(state, LUA_REGISTRYINDEX, ref_); }
	
	inline operator lua_State* const () { return state_; }
};




Value::Value()
	: type_(TYPE_VALUE), index_(0), state_(nullptr)
{
}

Value::Value(Type type)
	: type_(type), index_(0), state_(nullptr)
{
	
}


Value::~Value()
{
}


void Value::pull(const lua_State* const state, int index)
{
	state_= state;
	
	//TODO index validation
	
	if(index < 1)
		throw "Error wrong index";
		
	index_ = index;
}

bool Value::valid() const
{
	if(state_ == nullptr)
		return false;
	
	if(index_ <= 0)
		return false;
		
	Context ctx(const_cast<lua_State*>(state_));
	if(ctx.stackCount() < index_)
		return false;
		
	switch(type_)
	{
		case TYPE_VALUE:
			break;
	
	}
	
	return true;
}
