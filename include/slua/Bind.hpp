/*

*/
#pragma once
#ifndef __SLUA_BIND_HPP__
#define __SLUA_BIND_HPP__

#include <iostream> //debug

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
struct BindFunction
{
    const char *name;
    int(T::*mfunc)(Context&);
};    

/**
* Use as bindStatus
*/
template<class T>
struct BindStatus
{
	const char* className;
	//const BindFunction constructor;
	//const BindFunction destructor;
	const BindFunction<T>* Functions;
}; 


/**
* Basic Class for binding objects with refcounting memory management
*/
class LuaObject
{
private:
	bool shareable_;
	unsigned short refcount_;
	
	//luaref
		
public:
	LuaObject();
	~LuaObject();

	void addReference();
	void removeReference();
	bool isShareable();
	void markShareable();
};

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
		ctx.pushGlobalTable();
		Table global;
		global.setto(ctx, -1);
		ctx.pushFunc(&Bind::lua_constructor<T>);
		global.assignField(T::bindStatus.className);
    }
    
    /**
    * Make a instance of an object available for lua
    * in the global table
    */
    template<class T>
    static void Object(Context& ctx, T* instance, const char* name)
    {
		registerMetaTable<T>(ctx);
		
        LuaObject* lo = instance;
        lo->addReference();	
        
        ctx.pushGlobalTable();
        Table global;
		global.setto(ctx, -1);	//access to global table
        ctx.pushString(name);	//name of object
		pushInstanceTable(ctx, instance); //push instance table
		global.assignField();	//assign the tbl to name to global table
		ctx.pop(1); //pop globaltable
    }
    
    /**
    * Push a object ontp stack
    */ 
    template<class T>
    static void PushObject(Context& ctx, T* instance)
    {
		registerMetaTable<T>(ctx);
		
		LuaObject* lo = instance;
        lo->addReference();   
        
        pushInstanceTable(ctx, instance);
        
        //finished
	}
    
    
    //BindFunction
    //BindVariable
    
    
private:
	static const char* REFFIELD;
	
	/**
	* Register the class metatable to registry
	*/
	template<class T>
	inline static void registerMetaTable(Context& ctx)
	{
		static bool registered = false;
		if(registered)
			return;
			
		Table meta;
		if(!ctx.pushMetaTable(T::bindStatus.className))
			throw LuaException("Already registered metatable with this name");	
		meta.setto(ctx, -1);
		
		ctx.pushStringLiteral("__gc");
		ctx.pushFunc(&Bind::lua_gc<T>);
		meta.assignField();
		
		//register index function
		ctx.pushStringLiteral("__index");
		ctx.pushFunc(&Bind::lua_index);
		meta.assignField();
		
		// assign functions
		// for binding in a metatable the metatable requires a __index function
		for (int i = 0; T::bindStatus.Functions[i].name; i++) 
		{
			ctx.pushInteger(i);
			ctx.pushClojure(&Bind::lua_dispatch<T>, 1); //clojure has internal arguments
			meta.assignField(T::bindStatus.Functions[i].name);
		}
		
		//register _newindex to protect index 0
		
		
		//protect metatable
		ctx.pushStringLiteral("__metatable");
		ctx.pushBool(false);
		meta.assignField();
			
		//pops the metatable
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
		tbl.setto(ctx, -1);
		
		ctx.pushInteger(0); //key
		LuaObject* obj = instance;
		ctx.pushPtr(obj);	//pointer
		tbl.assignField();  //assign as field
		
		// Check for existing metatable and push it on stack
		// TODO lua error not an exception
		if(ctx.pushMetaTable(T::bindStatus.className))
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
		LuaObject* lo = obj; //make shure is LuaObject
			
		pushInstanceTable<T>(L, obj);
		
		//call constructor function
		//T::bindStatus.
		return 1;
	}
    
    /**
    * GC call for a class
    */
    template<class T>
    static int lua_gc(lua_State *L)
    {
		Context ctx(L);
		
		Table tbl;
		tbl.setto(ctx, 1); //self table is the first argument
		ctx.pushInteger(0); //ref key
		tbl.pushField();
		
		if(!ctx.isType(-1, LuaType::LIGHTUSERDATA))
			throw LuaException("There seems to be no valid object pointer at table index 0");
		
		//the class pointer is the userdata itself given as self parameter
		auto obj = static_cast<LuaObject*>(const_cast<void*>(ctx.getPtr(-1)));
		ctx.pop(1); //pop reference
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
	
	//__newindex = function(op, k,v) //block k 0
	
	/**
	* Index dispatcher function?
	*/
	static int lua_index(lua_State *L)
	{	
		Context ctx(L);
		
		//ctx.stack top == 2
		if(ctx.isType(2, LuaType::STRING))
		{
			//1 the object
			//2 the key
			if(!ctx.pushMetaTable(1)) //get the metatable
				return 0;
			Table tbl;
			tbl.setto(ctx, -1);  //assign
			ctx.pushCopy(2);	//push copy of key string
			tbl.pushField();	//retrieve key from metatable
			//std::cout << ctx.getTypeString(-1) << std::endl;
			return 1;
		}
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
		int funcIndex = ctx.getInteger(ctx.upIndex(1));
		
		Table tbl;
		tbl.setto(ctx, 1); //self table is the first argument
		ctx.pushInteger(0); //ref key
		tbl.pushField();
		
		if(!ctx.isType(-1, LuaType::LIGHTUSERDATA))
			throw LuaException("There seems to be no valid object pointer at table index 0");
		
		//the class pointer is the userdata itself given as self parameter
		auto obj = static_cast<T*>(const_cast<void*>(ctx.getPtr(-1)));
		ctx.pop(1); //pop reference
		
		//call specific function
		return (obj->*(T::bindStatus.Functions[funcIndex].mfunc))(ctx);	
	}  
    
};

    
}

#endif // __SLUA_BIND_HPP__
