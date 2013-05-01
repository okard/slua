

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


void Debugger::DumpStack(Context& ctx)
{
	int i;
	int top = lua_gettop(ctx);
	for (i = 1; i <= top; i++) 
	{
		int t = lua_type(ctx, i);
		
		printf("%d:\t", i);
        
        switch (t) 
        {
          case LUA_TSTRING:  /* strings */
            printf("`%s'", lua_tostring(ctx, i));
            break;
    
          case LUA_TBOOLEAN:  /* booleans */
            printf(lua_toboolean(ctx, i) ? "true" : "false");
            break;
    
          case LUA_TNUMBER:  /* numbers */
            printf("%g", lua_tonumber(ctx, i));
            break;
    
          default:  /* other values */
            printf("%s", lua_typename(ctx, t));
            break;
    
        }
        printf("\n");  /* put a separator */
      }
      printf("\n");  /* end the listing */
}


static void stackDump (lua_State *L) {
    
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
