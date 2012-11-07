

#include <slua/Debug.hpp>


using namespace slua;

//debugging function

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
