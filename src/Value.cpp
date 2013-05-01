
#include <slua/Value.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <slua/Context.hpp>
#include <slua/Type.hpp>
#include <slua/Exception.hpp>


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


inline LuaType fromLua(int type)
{
	switch(type)
	{
		case LUA_TNIL: return LuaType::NIL;
		case LUA_TNUMBER: return LuaType::NUMBER;
		case LUA_TBOOLEAN: return LuaType::BOOLEAN;
		case LUA_TSTRING: return LuaType::STRING;
		case LUA_TTABLE: return LuaType::TABLE;
		case LUA_TFUNCTION: return LuaType::FUNCTION;
		case LUA_TUSERDATA: return LuaType::USERDATA;
		case LUA_TTHREAD: return LuaType::THREAD;
		case LUA_TLIGHTUSERDATA: return LuaType::LIGHTUSERDATA;
		default: 
			throw LuaException("Invalid Lua Type");
	}
}



Value::Value()
	: type_(LuaType::DYNAMIC), index_(0), state_(nullptr)
{
}

Value::Value(LuaType type)
	: type_(type), index_(0), state_(nullptr)
{
	
}


Value::~Value()
{
}

void Value::setto(const lua_State* const state, int index)
{
	state_= state;
	index_ = index;
	
	if(valid())
		throw LuaException("Invalid Lua type at the value positon");
}

bool Value::valid() const
{
	if(state_ == nullptr)
		return false;
		
	//check for absolute and relative index
	
	Context ctx(const_cast<lua_State*>(state_));
	//if(ctx.stackCount() < index_)
		//return false;
		
	switch(type_)
	{
		case LuaType::DYNAMIC: //dynamic accepts all types
			break;
		default:
			if(fromLua(lua_type(const_cast<lua_State*>(state_), index_)) != type_)
				return false;
	}
	
	return true;
}

//Return the real lua type at the stack position
LuaType Value::getRealType() const
{
	return fromLua(lua_type(const_cast<lua_State*>(state_), index_));
}

LuaType Value::getLuaType(lua_State* state, int index)
{
	return fromLua(lua_type(state, index));
}
