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
	//id 
		
public:
	LuaObject();
	virtual ~LuaObject();

	void addReference();
	void removeReference();
	bool isShareable();
	void markShareable();
	
	inline unsigned short refCount() const { return refcount_; }
};

/**
* Pointer 
*/
class LuaObjectPtr
{
private:
	LuaObject* obj_;
public:
	
	LuaObjectPtr()
		: obj_(nullptr)
	{
	}
	
	LuaObjectPtr(const LuaObjectPtr& lop)
		: obj_(lop.obj_)
	{
		obj_->addReference();
	}

	LuaObjectPtr(const LuaObject& lo)
		: obj_(const_cast<LuaObject*>(&lo))
	{
		obj_->addReference();
	}
	
	~LuaObjectPtr()
	{
		if(obj_)
			obj_->removeReference();
	}
	
	
	//assign
	LuaObjectPtr& operator=(const LuaObject& lo)
	{
		if(obj_)
			obj_->removeReference();
		
		obj_ = const_cast<LuaObject*>(&lo);
		obj_->addReference();
	}
	
	//assign
	LuaObjectPtr& operator=(const LuaObjectPtr& lop)
	{
		if(obj_)
			obj_->removeReference();
		
		obj_ = lop.obj_;
		obj_->addReference();
	}
	
	//retrieve
	
	bool valid()
	{
		if(obj_)
			return true;
		else
			return false;
	}
	
	inline LuaObject& get()
	{
		return *obj_;
	}
	
	
	void detach()
	{
		if(obj_)
			obj_->removeReference();
		obj_ = nullptr;
	}
};

	
} //end namespace slua

#endif
