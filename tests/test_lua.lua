

-- test bindings script

print("start lua");

print(TestClass)

local test = TestClass();

test:test_simple();
test:test_simple("foo", 1);

print("end lua");
