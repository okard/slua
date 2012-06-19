/*
* SLUA Library
*/
#pragma once
#ifndef __SLUA_LIB_HPP__
#define __SLUA_LIB_HPP__

//Lua Includes
extern "C" {
    #include <lauxlib.h>
}


namespace slua {
    
    /**
    * Register slua lua library
    */
    LUALIB_API int luaopen_slua(lua_State *L);
    
}


#endif // __SLUA_LIB_HPP__