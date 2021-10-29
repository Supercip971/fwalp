#ifndef LUA_LOADER_H
#define LUA_LOADER_H

#include "lua_program.h"

LuaProgram *load_programm(const char *path);

void unload_programm(LuaProgram *programm);

#endif
