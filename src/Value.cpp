
#include <slua/Value.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <slua/Context.hpp>


using namespace slua;


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


Value::Type Value::getType() const
{
	return type_;
}


int Value::getIndex() const
{
	//assert index_ >= 1
	return index_;
}
