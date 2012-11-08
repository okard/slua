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
    int(T::*mfunc)(lua_State*);
};    


template<class T>
struct RegStatus
{
	const char* className;
	const RegEntry<T> Register[];
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
    
    template<class T>
    static void Class(Context& ctx)
    {
		registerMetaTable<T>(ctx);
		
		
		
        //register constructor
        //register metatable 
    }
    
    template<class T>
    static void Object(lua_State *L, T* instance, const char* name)
    {
        
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
		meta.pull(ctx, ctx.absIndex(-1));
		ctx.pushStringLiteral("_gc");
		ctx.pushFunc(&Bind::lua_gc<T>);
		
		//assign field
		
		//register all required metatable function
		
		
			
		registered = true;
	}

	/**
	* Pushes a instance table for class type on lua stack
	*/
	template<class T>
	void pushInstanceTable(lua_State *L, T* const instance)
	{
		//new table
		//register reference
		
		//register functions
		
		//set metatable
		
		
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
		pushInstanceTable<T>(L, new T);
		return 1;
	}
    
    /**
    * GC call for a class
    */
    template<class T>
    static int lua_gc(lua_State *L)
    {
		
		return 0;
	}
	
	/**
	* Protect metatable and class instance pointer from changes
	*/
    static int lua_protect(lua_State *L)
    {
		return 0;
	}
	
	/**
	* Dispatches the function
	*/
	template<class T>
    static int lua_dispatch(lua_State *L)
    {
		//get obj, function_index
		
		//int i;
		//get(&i, &obj, T::className)
		
		//T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
		//return ((*obj)->*(T::Register[i].mfunc))(L);
	}  
    
};
    
}

#endif // __SLUA_BIND_HPP__
