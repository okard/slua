#pragma once
#ifndef __SLUA_LUAOBJECT_HPP__
#define __SLUA_LUAOBJECT_HPP__

namespace slua {
	
/**
* Basic Class for binding objects with refcounting memory management
* Move to seperate files?
*/
class LuaObject
{
private:
	bool shareable_;
	unsigned short refcount_;
	
	//luaref
		
public:
	LuaObject();
	virtual ~LuaObject();

	void addReference();
	void removeReference();
	bool isShareable();
	void markShareable();
};

	
} //end namespace slua

#endif
