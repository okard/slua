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
	unsigned short refcount_;
	bool shareable_;
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
	
	LuaObjectPtr(const LuaObject* lo)
		: obj_(const_cast<LuaObject*>(lo))
	{
		//no add reference for direct assign //the main ptr
		//LuaObjectPtr lop = new LuaObject();
	}
	
	~LuaObjectPtr()
	{
		if(obj_)
			obj_->removeReference();
		obj_ = nullptr;
	}
	
	
	//assign
	LuaObjectPtr& operator=(const LuaObject& lo)
	{
		if(obj_)
			obj_->removeReference();
		
		obj_ = const_cast<LuaObject*>(&lo);
		obj_->addReference();
		
		return *this;
	}
	
	//assign
	LuaObjectPtr& operator=(const LuaObjectPtr& lop)
	{
		if(&lop != this)
		{
			if(obj_)
				obj_->removeReference();
			
			obj_ = lop.obj_;
			obj_->addReference();
		}
		
		return *this;
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
