

-- test bindings script

print("start lua");

print(TestClass)

local test = TestClass();

print(test:test_simple());

tbl = { 
	foo = "test",
	abc = { a=1, b=2, c=3 },
	one = "one"
}


test:test_simple(tbl, "test", 14);



print("end lua");
