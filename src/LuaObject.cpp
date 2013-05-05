
#include <slua/LuaObject.hpp>

#include <slua/Exception.hpp>

using namespace slua;

LuaObject::LuaObject()
	: refcount_(1), shareable_(false)
{
}

LuaObject::~LuaObject()
{
}

void LuaObject::addReference()
{
	if(!shareable_)
		throw LuaException("Object is not shareable");
		
	refcount_++;
}

void LuaObject::removeReference()
{
	refcount_--;
	if(refcount_ == 0)
		delete this;
}

bool LuaObject::isShareable()
{
	return shareable_;
}

void LuaObject::markShareable()
{
	shareable_ = true;
}
