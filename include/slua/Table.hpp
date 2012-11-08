/*

*/
#pragma once
#ifndef __SLUA_TABLE_HPP__
#define __SLUA_TABLE_HPP__

#include "Value.hpp"

namespace slua {
  
//LuaTable Handling
class Table : public Value
{
private:
    
    //metatable flag
    
    int ref_; //int luaL_ref (lua_State *L, int t);
    

    
public:
    Table();
    ~Table();

	virtual void pull(const lua_State* const state, int index);
	
	/**
	* Pops 2 value from stack
	* on top of stack the value
	* under the value the key
	*/
	void assignField();
	
	/**
	* Assign value fom top of the stack
	*/
	void assignField(const char* key);
	
	/**
	* Key on stack top
	* pushes the field of the table
	*/
	void pushField();
	
	/**
	* Pushes a table field onto stack
	*/
	void pushField(const char* key);
	

	//pushMetaTable()
	//setMetaTable()
	
	
	
	//assign
	

    //void setField(int index);
    
    //validate 
    //int lua_setmetatable (lua_State *L, int index);
    
    //lua_settable
    
    //set metatable
    //setMetaTable (const Table& tbl)
    
    //store userdata
    //store string
    //store number
};
    
    
    
}

#endif /* __SLUA_TABLE_HPP__ */
