
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

void Value::setto(Context& ctx, int index)
{
	state_= ctx;
	index_ = ctx.absIndex(index);
	
	if(valid())
		throw LuaException("Invalid Lua type at the value positon");
}

bool Value::valid() const
{
	if(state_ == nullptr)
		return false;
	
	if(index_ == 0)
		return false;
		

	//Most query functions accept as indices any value inside the available stack space, that is, 
	//indices up to the maximum stack size you have set through lua_checkstack. 
	// Such indices are called acceptable indices. More formally, we define an acceptable index as follows:
	//(index < 0 && abs(index) <= top) ||
    //(index > 0 && index <= stackspace)
	// Note that 0 is never an acceptable index. 
		
	//check for absolute and relative index
	
	Context ctx(const_cast<lua_State*>(state_));
	//is a absolute index
	if(ctx.stackCount() < index_)
		return false;
		
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
