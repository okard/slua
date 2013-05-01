

#include <slua/Debug.hpp>

//Lua Includes
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

#include <cstdio>

using namespace slua;

//debugging function



static void PrintValue(Context& ctx, int index)
{
	int type = lua_type(ctx, index);
    switch (type)
    {
		case LUA_TSTRING:  /* strings */
			printf("\"%s\"", lua_tostring(ctx, index));
            break;
    
		case LUA_TBOOLEAN:  /* booleans */
            printf("%s", lua_toboolean(ctx, index) ? "true" : "false");
            break;
    
		case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(ctx, index));
            break;
            
        case LUA_TTABLE:
			printf("Table:");
			lua_pushnil(ctx);
			while(lua_next(ctx, index) != 0)
			{
				printf("\n");
				//key:
				PrintValue(ctx, lua_absindex(ctx, -2));
				printf(" -> "); 
				//value
				PrintValue(ctx, lua_absindex(ctx,-1));
				lua_pop(ctx, 1);
			}
			
			//metatable
			if(lua_getmetatable(ctx, index) > 0)
			{
				printf("\n[Meta]");
				PrintValue(ctx, lua_absindex(ctx,-1));
				lua_pop(ctx, 1);
			}
			
			break;
			
		case  LUA_TFUNCTION:
			if(lua_iscfunction(ctx, index))
				printf("cfunction");
			else
				printf("function");
			break;
			
		default:  /* other values */
            printf("%s", luaL_typename(ctx, index));
            break;	
	}
}

void Debugger::DumpStack(Context& ctx)
{
	printf("--STACKDUMP---------------------------------\n");
	int i;
	int top = lua_gettop(ctx);
	for (i = 1; i <= top; i++) 
	{
		printf("%d:\t", i);
		PrintValue(ctx, i);
        printf("\n");  /* put a separator */
	}
	printf("--END_STACKDUMP---------------------------------\n");  /* end the listing */
}

/*
typedef struct lua_Debug {
  int event;
  const char *name;           //(n) 
  const char *namewhat;       // (n) 
  const char *what;           // (S) 
  const char *source;         // (S) 
  int currentline;            // (l) 
  int nups;                   // (u) number of upvalues 
  int linedefined;            // (S) 
  int lastlinedefined;        // (S) 
  char short_src[LUA_IDSIZE]; // (S) 
  // private part
  other fields
} lua_Debug;
*/

//int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar);
//const char *lua_getlocal (lua_State *L, lua_Debug *ar, int n);
//int lua_getstack (lua_State *L, int level, lua_Debug *ar);

//const char *lua_setlocal (lua_State *L, lua_Debug *ar, int n);


//hooks static functions no instance callback?
//typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);
//int lua_sethook (lua_State *L, lua_Hook f, int mask, int count);
