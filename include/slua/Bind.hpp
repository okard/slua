/*

*/
#pragma once
#ifndef __SLUA_BIND_HPP__
#define __SLUA_BIND_HPP__

extern "C" 
{
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

#include "Exception.hpp"
#include "Context.hpp"


namespace slua {
        
/**
* 
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
    static void Class(lua_State *L)
    {
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
    template<class T>
    static int ObjectCallDispatch(lua_State *L)
    {
		//get obj, function_index
		
		//int i;
		//get(&i, &obj, T::className)
		
		//T** obj = static_cast<T**>(luaL_checkudata(L, -1, T::className));
		//return ((*obj)->*(T::Register[i].mfunc))(L);
	}
    
    
    
    
};
    
}
