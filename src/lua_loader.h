#ifndef LUA_LOADER_H
#define LUA_LOADER_H 

#include "lua_programm.h"

LuaProgramm* load_programm(const char* path);

void unload_programm(LuaProgramm* programm);

#endif
