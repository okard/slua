#pragma once
#ifndef __SLUA_DEBUG_HPP__
#define __SLUA_DEBUG_HPP__

#include "Context.hpp"

namespace slua {
	
struct lua_Debug;

	
class Debugger
{
private:
	lua_Debug* debug_;
	Context& ctx_;
public:	

	Debugger(Context& ctx);
	~Debugger();



	static void DumpStack(Context& ctx);
	
};
 

    
    
}

#endif // __SLUA_DEBUG_HPP__
