

#include <iostream>

#include <slua/State.hpp>
#include <slua/Bind.hpp>
#include <slua/Debug.hpp>



class TestClass : public slua::LuaObject
{
private:
	int id_;
public:
	static const slua::BindStatus<TestClass> bindStatus;
	
	int test_simple(slua::Context& ctx)
	{
		std::cout << "ID: " << id_ << " The upvalue of clojure: " << ctx.upIndex(1) << std::endl;
		
		//the last value is alway the clojure data
		std::cout << "Calling 'test_simple' with " << ctx.stackCount() << " arguments" << std::endl;
		
		//only when there are arguments
		//if(ctx.stackCount() > 1)
		//	slua::Debugger::DumpStack(ctx);
			
				
		//function to retrieve LuaObject of table parameter so it can stored here
			
		
		ctx.pushInteger(10);
		std::cout << "Stack Grow: " << ctx.stackGrow() << std::endl;
		return ctx.stackGrow();
	}
	
	static int count;
	
	TestClass()
	{
		id_ = count;
		count++;
		std::cout << "TestClass created: " << id_ << std::endl;
	}
	
	~TestClass()
	{
		std::cout << "TestClass destroyed " << id_ << std::endl;
	}
};

int TestClass::count = 0;

static const slua::BindFunction<TestClass> function[]=
{
	{"test_simple", &TestClass::test_simple},
	{0,0}
};

const slua::BindStatus<TestClass> TestClass::bindStatus = 
{
	.className = "TestClass",
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
