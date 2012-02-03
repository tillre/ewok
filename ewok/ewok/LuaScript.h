#ifndef LUASCRIPT_H_
#define LUASCRIPT_H_


#include <cmath>
#include "lua.hpp"
#include "Log.h"
#include "FileData.h"


namespace ewok {


  void LuaRegisterCFunction(lua_State *L, const char *name, lua_CFunction func);
  
  void LuaLogCFunctionInvocation(lua_State *L);

  
  // ----------------------------------------------------------------------
  // LuaTypes
  // ----------------------------------------------------------------------
  
  
  class LuaFloat {
  public:
    typedef float ValueType;

    static void set(lua_State *L, ValueType value)
    {
      lua_pushnumber(L, value);
    }

    static ValueType get(lua_State *L, int pos)
    {
      Assert(lua_isnumber(L, pos), "No number on lua stack");
      return lua_tonumber(L, pos);
    }
  };



  class LuaInt {
  public:
    typedef int ValueType;

    static void set(lua_State *L, ValueType value)
    {
      lua_pushinteger(L, value);
    }

    static ValueType get(lua_State *L, int pos)
    {
      Assert(lua_isnumber(L, pos), "No integer on lua stack");
      return lua_tointeger(L, pos);
    }
  };


  class LuaUInt {
  public:
    typedef unsigned ValueType;

    static void set(lua_State *L, ValueType value)
    {
      lua_pushinteger(L, value);
    }

    static ValueType get(lua_State *L, int pos)
    {
      Assert(lua_isnumber(L, pos), "No integer on lua stack");
      return lua_tointeger(L, pos);
    }
  };


  template<typename T>
  class LuaPointer {
  public:
    typedef T* ValueType;

    static void set(lua_State *L, ValueType value)
    {
      lua_pushlightuserdata(L, value);
    }

    static ValueType get(lua_State *L, int pos)
    {
      Assert(lua_islightuserdata(L, pos), "No lightuserdata on lua stack");
      // cast away the constness
      return (ValueType)lua_topointer(L, pos);
    }
  };


  class LuaString {
  public:
    typedef std::string ValueType;

    static void set(lua_State *L, ValueType value)
    {
      lua_pushstring(L, value.c_str());
    }

    static ValueType get(lua_State *L, int pos)
    {
      Assert(lua_isstring(L, pos), "No string on lua stack");
      size_t len = 0;
      const char *str = lua_tolstring(L, pos, &len);
      std::string result = str;
      return result;
    }
  };


  // ----------------------------------------------------------------------
  // LuaCMemberFunction
  // ----------------------------------------------------------------------

  
  template<typename T,
           void(T::*F)()>  
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -1);
    (obj->*F)();
    return 0;
  }
  
  
  template<typename T, typename P1,
           void (T::*F)(typename P1::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -2);
    typename P1::ValueType p1 = P1::get(L, -1);
    (obj->*F)(p1);
    return 0;
  }


  template<typename T, typename P1, typename P2,
           void (T::*F)(typename P1::ValueType, typename P2::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -3);    
    typename P1::ValueType p1 = P1::get(L, -2);
    typename P2::ValueType p2 = P2::get(L, -1);
    (obj->*F)(p1, p2);
    return 0;
  }


  template<typename T, typename P1, typename P2, typename P3,
           void (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -4);
    typename P1::ValueType p1 = P1::get(L, -3);
    typename P2::ValueType p2 = P2::get(L, -2);
    typename P3::ValueType p3 = P3::get(L, -1);
    (obj->*F)(p1, p2, p3);
    return 0;
  }


  template<typename T, typename P1, typename P2, typename P3, typename P4,
           void (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                        typename P4::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -5);
    typename P1::ValueType p1 = P1::get(L, -4);
    typename P2::ValueType p2 = P2::get(L, -3);
    typename P3::ValueType p3 = P3::get(L, -2);
    typename P4::ValueType p4 = P4::get(L, -1);
    (obj->*F)(p1, p2, p3, p4);
    return 0;
  }


  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5,
           void (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                        typename P4::ValueType, typename P5::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -6);    
    typename P1::ValueType p1 = P1::get(L, -5);
    typename P2::ValueType p2 = P2::get(L, -4);
    typename P3::ValueType p3 = P3::get(L, -3);
    typename P4::ValueType p4 = P4::get(L, -2);
    typename P4::ValueType p5 = P5::get(L, -1);
    (obj->*F)(p1, p2, p3, p4, p5);
    return 0;
  }

  // LuaCMemberFunction that returns a value
  
  
  template<typename T, typename R,
           typename R::ValueType(T::*F)()>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -1);
    R::set(L, (obj->*F)());
    return 1;
  }


  template<typename T, typename R, typename P1,
           typename R::ValueType(T::*F)(typename P1::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -2);
    typename P1::ValueType p1 = P1::get(L, -1);
    R::set(L, (obj->*F)(p1));
    return 1;
  }

  
  template<typename T, typename R, typename P1, typename P2,
           typename R::ValueType(T::*F)(typename P1::ValueType, typename P2::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -3);
    typename P1::ValueType p1 = P1::get(L, -2);
    typename P2::ValueType p2 = P2::get(L, -1);
    R::set(L, (obj->*F)(p1, p2));
    return 1;
  }
  

  template<typename T, typename R, typename P1, typename P2, typename P3,
           typename R::ValueType(T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);
    T* obj = LuaPointer<T>::get(L, -4);
    typename P1::ValueType p1 = P1::get(L, -3);
    typename P2::ValueType p2 = P2::get(L, -2);
    typename P3::ValueType p3 = P3::get(L, -1);
    R::set(L, (obj->*F)(p1, p2, p3));
    return 1;
  }

  
  template<typename T, typename R, typename P1, typename P2, typename P3, typename P4,
           typename R::ValueType(T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                                        typename P4::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -5);
    typename P1::ValueType p1 = P1::get(L, -4);
    typename P2::ValueType p2 = P2::get(L, -3);
    typename P3::ValueType p3 = P3::get(L, -2);
    typename P4::ValueType p4 = P4::get(L, -1);
    R::set(L, (obj->*F)(p1, p2, p3, p4));
    return 1;
  }


  template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5,
           typename R::ValueType(T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                                        typename P4::ValueType, typename P5::ValueType)>
  int LuaCMemberFunction(lua_State *L)
  {
    LuaLogCFunctionInvocation(L);    
    T* obj = LuaPointer<T>::get(L, -6);
    typename P1::ValueType p1 = P1::get(L, -5);
    typename P2::ValueType p2 = P2::get(L, -4);
    typename P3::ValueType p3 = P3::get(L, -3);
    typename P4::ValueType p4 = P4::get(L, -2);
    typename P5::ValueType p5 = P5::get(L, -1);
    R::set(L, (obj->*F)(p1, p2, p3, p4, p5));
    return 1;
  }

  
  
  // ----------------------------------------------------------------------
  // LuaScript
  // ----------------------------------------------------------------------
  
  
  class LuaScript {
  public:
    LuaScript()
      : L(NULL)
    {
    }


    void init(const FileData &fd)
    {
      Assert(L == NULL, "Init has probably already been called");
      L = luaL_newstate();
      luaL_openlibs(L);

      int err = luaL_loadbuffer(L, fd.bytes(), fd.size(), fd.name().c_str());
      if (err) {
        LogError << "Cannot load script: " << fd.name();
        logError();
        return;
      }
      
      err = lua_pcall(L, 0, 0, 0);
      if (err) {
        LogError << "Error in pcall with script: " << fd.name();
        logError();
      }
    }


    void close()
    {
      if (L) {
        lua_close(L);
      }
    }


    void logError()
    {
      if (lua_gettop(L)) {
        LogError << "LuaError: " << std::endl << lua_tostring(L, -1);
        lua_pop(L, 1);  // pop error message from the stack 
      }
    }


    // registerMemberFunction --------------------------------------------------


    template<typename T,
             void (T::*F)()>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, F>);
    }
    
    
    template<typename T, typename P1,
             void (T::*F)(typename P1::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, P1, F>);
    }

    
    template<typename T, typename P1, typename P2,
             void (T::*F)(typename P1::ValueType, typename P2::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, P1, P2, F>);
    }

    
    template<typename T, typename P1, typename P2, typename P3,
             void (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, P1, P2, P3, F>);
    }


    template<typename T, typename P1, typename P2, typename P3, typename P4,
             void (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                          typename P4::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, P1, P2, P3, P4, F>);
    }

    
    template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5,
             void (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                          typename P4::ValueType, typename P5::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, P1, P2, P3, P4, P5, F>);
    }


    // registerMemberFunctions that return a value --------------------
    
    template<typename T, typename R,
             typename R::ValueType (T::*F)()>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, R, F>);
    }


    template<typename T, typename R, typename P1,
             typename R::ValueType (T::*F)(typename P1::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, R, P1, F>);
    }


    template<typename T, typename R, typename P1, typename P2,
             typename R::ValueType (T::*F)(typename P1::ValueType, typename P2::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, R, P1, P2, F>);
    }

    
    template<typename T, typename R, typename P1, typename P2, typename P3,
             typename R::ValueType (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, R, P1, P2, P3, F>);
    }


    template<typename T, typename R, typename P1, typename P2, typename P3, typename P4,
             typename R::ValueType (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                                           typename P4::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, R, P1, P2, P3, P4, F>);
    }


    template<typename T, typename R, typename P1, typename P2, typename P3, typename P4, typename P5,
             typename R::ValueType (T::*F)(typename P1::ValueType, typename P2::ValueType, typename P3::ValueType,
                                           typename P4::ValueType, typename P5::ValueType)>
    void registerMemberFunction(const char *name)
    {
      LuaRegisterCFunction(L, name, LuaCMemberFunction<T, R, P1, P2, P3, P4, P5, F>);
    }

    
    // call ------------------------------------------------------------
    

    void call(const char *name)
    {
      lua_getglobal(L, name);
      if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        LogError << "Call to lua function: " << name << " failed";
        logError();
      }
    }

    
    template<typename P1>
    void call(const char *name, typename P1::ValueType p1)
    {
      lua_getglobal(L, name);
      P1::set(L, p1);
      if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
        LogError << "Call to lua function: " << name << " failed";
        logError();
      }
    }

    
    template<typename P1, typename P2>
    void call(const char *name, typename P1::ValueType p1, typename P2::ValueType p2)
    {
      lua_getglobal(L, name);
      P1::set(L, p1);
      P2::set(L, p2);
      if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
        LogError << "Call to lua function: " << name << " failed";
        logError();
      }
    }


    // call functions that return --------------------


    template<typename R>
    typename R::ValueType call(const char *name)
    {
      lua_getglobal(L, name);
      lua_pcall(L, 0, 1, 0);
      typename R::ValueType r = R::get(L, -1);
      return r;
    }


    template<typename R, typename P1>
    typename R::ValueType call(const char *name, typename P1::ValueType p1)
    {
      lua_getglobal(L, name);
      P1::set(L, p1);
      lua_pcall(L, 1, 1, 0);
      typename R::ValueType r = R::get(L, -1);
      return r;
    }

  private:
    lua_State *L;
  };

  
} // namespace ewok


#endif // LUASCRIPT_H_
