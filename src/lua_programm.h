#ifndef LUA_PROGRAMM_H
#define LUA_PROGRAMM_H

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

typedef struct
{
    lua_State *state;
    int _current_call_arg_count;
} LuaProgramm;

LuaProgramm *programm_init(void);

void programm_deinit(LuaProgramm *programm);

const char* get_error(LuaProgramm* programm);

void programm_start_call(LuaProgramm* programm, const char* name);

void programm_end_call(LuaProgramm* programm);

void programm_do_call(LuaProgramm* programm, int return_count);
#define programm_call_arg(programm, arg) \
  _Generic(arg,\
      int: lua_pushinteger, \
      float: lua_pushnumber, \
      double: lua_pushnumber \
  )(programm->state, arg); programm->_current_call_arg_count++;


#endif
