/*

*/
#pragma once
#ifndef __SLUA_TABLE_HPP__
#define __SLUA_TABLE_HPP__

#include "Context.hpp"
#include "Value.hpp"


namespace slua {
  
//LuaTable Handling
class Table : public Value
{
private:
    
    //metatable flag
    
    int ref_; //int luaL_ref (lua_State *L, int t);
    
    Table();
    ~Table();
    
public:
    //create a table and assign to name
    
    
    //get the registry table
    //static Table* const getRegistryTable(const Context& ctx)
    
    void setField(int index);
    
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
