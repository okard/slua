
#include <slua/Value.hpp>

using namespace slua;


Value::Value()
{
}

Value::Value(Context& context)
{
}

Value::~Value()
{
}

bool Value::valid()
{
	if(index_ <= 0)
		return false;
		
	switch(type_)
	{
		//validate index for context
	}
}


Value::Type Value::getType()
{
	return type_;
}


int Value::getIndex()
{
	//assert index_ >= 1
	return index_;
}
