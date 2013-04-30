
#pragma once
#ifndef __SLUA_TYPE_HPP__
#define __SLUA_TYPE_HPP__


namespace slua {
	
/**
* Lua Types
*/ 
enum class LuaType
{
	DYNAMIC, //dynamic datatype
		
	//Fixed types
	NIL,
	BOOLEAN,
	NUMBER,
    STRING,
    TABLE,
    FUNCTION,
    USERDATA,
	LIGHTUSERDATA,
	THREAD
};

LuaType fromLua(int type);


	
};

#endif
