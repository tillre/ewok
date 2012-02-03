#include "LuaScript.h"


namespace ewok {

  
  void LuaRegisterCFunction(lua_State *L, const char *name, lua_CFunction func)
  {
    lua_pushstring(L, name);
    lua_pushcclosure(L, func, 1);
    lua_setglobal(L, name);
  }

  
  void LuaLogCFunctionInvocation(lua_State *L)
  {
    // int numArgs = lua_gettop(L);
    // const char *fname = lua_tostring(L, lua_upvalueindex(1));
    // LogInfo << "lua is calling: " << fname << " with " << numArgs << " arguments";
  }


} // namespace ewok
