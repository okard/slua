

#include <iostream>

#include <slua/State.hpp>
#include <slua/Bind.hpp>
#include <slua/Debug.hpp>



class TestClass : public slua::LuaObject
{
public:
	static const slua::BindStatus<TestClass> bindStatus;
	
	int test_simple(slua::Context& ctx)
	{
		//the last value is alway the clojure data
		std::cout << "Calling 'test_simple' with " << ctx.stackCount() << " arguments" << std::endl;
		slua::Debugger::DumpStack(ctx);
		return 0;
	}
	
};

static const slua::BindFunction<TestClass> function[]=
{
	{"test_simple", &TestClass::test_simple},
	{0,0}
};

const slua::BindStatus<TestClass> TestClass::bindStatus = 
{
	.className = "TestClass",
	.metatableRegisted = false, //remove
	.Functions = function	
};


class TestInstance
{
	
	
};

//benching

int main(int argc, char **argv)
{
	std::cout << "Begin" << std::endl;
	slua::State state;
	
	slua::Bind::Class<TestClass>(state);
	
	state.LoadFile("test_lua.lua");
	state.Execute();
	std::cout << "End" << std::endl;
}
