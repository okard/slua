

-- test bindings script

print("start lua");

print(TestClass)

local test = TestClass();

print(test:test_simple());

tbl = { 
	foo = "test",
	abc = { a=1, b=2, c=3 },
	"one",
	"two"
}

test:test_simple(tbl, "test", 14);



-- -------------------------------

local test2 = TestClass();

function test2:test_function()
	print("test function called");
	self.x = 555;
end

test2:test_function();
test2:test_simple(test2);
print(test2.x);

--setmetatable(test2, {});
--test2:test_simple();


print("end lua");
