#ifndef LUA_PROGRAMM_H
#define LUA_PROGRAMM_H

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

typedef struct
{
    lua_State *state;
    int _current_call_arg_count;
} LuaProgram;

LuaProgram *programm_init(void);

void programm_deinit(LuaProgram *programm);

const char *get_error(LuaProgram *programm);

void programm_start_call(LuaProgram *programm, const char *name);

void programm_end_call(LuaProgram *programm);

void programm_do_call(LuaProgram *programm, int return_count);

void program_load_libs(LuaProgram *program);
#define programm_call_arg(programm, arg)              \
    _Generic(arg,                                     \
             int                                      \
             : lua_pushinteger,                       \
               float                                  \
             : lua_pushnumber,                        \
               double                                 \
             : lua_pushnumber)(programm->state, arg); \
    programm->_current_call_arg_count++;

#endif
