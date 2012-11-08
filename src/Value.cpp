
#include <slua/Value.hpp>

using namespace slua;


Value::Value()
	: type_(TYPE_VALUE), index_(0)
{
}


Value::Value(const lua_State* const state)
{
}

Value::~Value()
{
}

bool Value::valid() const
{
	if(index_ <= 0)
		return false;
		
	switch(type_)
	{
		//validate index for context
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
