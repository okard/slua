#pragma once
#ifndef __SLUA_LUAALLOCATOR_HPP__
#define __SLUA_LUAALLOCATOR_HPP__

#include <cstddef>

namespace slua {
	
class State;

/**
* Custom Lua Allocator
*/
class LuaAllocator
{
public:
	virtual void* alloc(State& state, void *ptr, size_t osize, size_t nsize)=0;
};

	
} //end namespace slua


#endif 
