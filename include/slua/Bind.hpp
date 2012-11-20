/*

*/
#pragma once
#ifndef __SLUA_BIND_HPP__
#define __SLUA_BIND_HPP__

#include "Exception.hpp"
#include "Context.hpp"
#include "Table.hpp"

namespace slua {
        
/**
    class Foo
    {
    static const slua::RegEntry<Foo> Register[];
    };

    const slua::RegEntry<Foo> Foo::Register[] = 
    {
    { "foo", &Foo::foo },
    { 0 }
    };
*/
template<class T>
struct RegEntry
{
    const char *name;
    int(T::*mfunc)(Context&);
};    


template<class T>
struct RegStatus
{
	const char* className;
	const RegEntry<T> Functions[5];
}; 


/**
* Basic Class for binding objects with refcounting memory management
*/
class LuaObject
{
private:
		bool shareable_;
		unsigned short refcount_;
		
public:
	LuaObject();
	~LuaObject();

	void addReference();
	void removeReference();
	bool isShareable();
	void markShareable();
};



//status struct?
    
/**
* 
* slua::Bind::Class<Foo>(state);
    -> Register a complete class
    
* slua::Bind::Object<Foo>(state, this, "foobar");
    -> Register object with name 
    -> possibly to push onto stack only?
    
* slua::Bind::Function(state, lua_func, name);
* slua::Bind::Variable<int>(state, ref int t, name);
*/
class Bind
{
private:
    Bind(){}
    Bind(const Bind&){}
    
public:
    //context instead of lua_State
    
    /**
    * Register a class for usage from lua
    */
    template<class T>
    static void Class(Context& ctx)
    {
		//register metatable
		registerMetaTable<T>(ctx);
		
		//register contructor function
		Table global;
		ctx.pullGlobalTable(global);
		ctx.pushFunc(&Bind::lua_constructor<T>);
		global.assignField(T::Bind.className);
    }
    
    /**
    * Make a instance of an object available for lua
    * in the global table
    */
    template<class T>
    static void Object(Context& ctx, T* instance, const char* name)
    {
        LuaObject* lo = instance;
        lo->addReference();
    }
    
    /**
    * Push a object
    */ 
    template<class T>
    static void PushObject(Context& ctx, T* instance)
    {
		LuaObject* lo = instance;
        lo->addReference();
	}
    
    
    //BindFunction
    //BindVariable
    
    
private:
	//static const char* REFFIELD = "__ref";

	/**
	* Register the class metatable to registry
	*/
	template<class T>
	static void registerMetaTable(Context& ctx)
	{
		static bool registered = false;
		if(registered)
			return;
			
		if(!ctx.pushMetaTable(T::Bind.className))
			throw LuaException("Already registered metatable with this name");
		
		Table meta;
		ctx.pullTable(meta, -1);
		ctx.pushStringLiteral("_gc");
		ctx.pushFunc(&Bind::lua_gc<T>);
		meta.assignField();
		
		//register _newindex
		
		//register _metatable = false
		
		//pops the metatable
		//ctx.pop(meta)
		ctx.pop(1);
		
			
		registered = true;
	}

	/**
	* Pushes a instance table for class type on lua stack
	* TODO luaState -> Context
	*/
	template<class T>
	static void pushInstanceTable(lua_State *L, T* const instance)
	{
		Context ctx(L);
		
		//new table
		ctx.pushTable();
		Table tbl;
		ctx.pullTable(tbl, -1);
		
		//assign reference
		ctx.pushPtr(instance);
		tbl.assignField("__ref");
		
		// assign functions
		//TODO T::Bind.className
		for (int i = 0; T::Bind.Functions[i].name; i++) 
		{
			ctx.pushInteger(i);
			ctx.pushClojure(&Bind::lua_dispatch<T>, 1);
			tbl.assignField(T::Bind.Functions[i].name);
		}
		
		// Check for existing metatable and push it on stack
		// TODO lua error
		if(ctx.pushMetaTable(T::Bind.className))
			throw LuaException("MetaTable was not created for this type");
		
		//assign metatable
		tbl.assignMetaTable();
		
		
		//what when gc disabled?
		
	}

	//------------------------------------------------------------------
	//-- Calls from lua code:
	
	/**
	* Create a new class instance as table 
	*/
	template<class T>
    static int lua_constructor(lua_State *L)
    {
		T* obj = new T();
		LuaObject* lo = obj;
		pushInstanceTable<T>(L, obj);
		return 1;
	}
    
    /**
    * GC call for a class
    */
    template<class T>
    static int lua_gc(lua_State *L)
    {
		Context ctx(L);
		
		//if(ctx.stackCount() == 1)
		//
		//argument is a table?
		//get ref field
		auto ptr = const_cast<void*>(ctx.pullPtr(1));
		auto obj = static_cast<LuaObject*>(ptr);
		obj->removeReference();
		return 0;
	}
	
	/**
	* Protect metatable and class instance pointer from changes
	*/
    static int lua_protect(lua_State *L)
    {
		//Move to Bind.cpp
		
		
		return 0;
	}
	
	/**
	* Dispatches the function
	*/
	template<class T>
    static int lua_dispatch(lua_State *L)
    {
		Context ctx(L);
		
		//get the closure value for functions index
		int funcIndex = ctx.pullInteger(ctx.upIndex(1));
		
		//get the table aka 'self' 
		//it is the first parameter
		Table tbl;
		ctx.pullTable(tbl, 1);
		
		//get ref field
		tbl.pushField("__ref");
		auto obj = static_cast<T*>(const_cast<void*>(ctx.pullPtr(-1)));
		
		//call specific function
		return (obj->*(T::Bind.Functions[funcIndex].mfunc))(ctx);	
	}  
    
};
    
}

#endif // __SLUA_BIND_HPP__
