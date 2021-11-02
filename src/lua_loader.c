#include "lua_loader.h"
#include <stdlib.h>

LuaProgram *load_programm(const char *path)
{
    LuaProgram *programm = programm_init();

    program_load_libs(programm);
    if (luaL_dofile(programm->state, path) != LUA_OK)
    {
        fprintf(stderr, "lua error while loading: %s \n", get_error(programm));
        exit(EXIT_FAILURE);
    }
    else
    {
        lua_pop(programm->state, lua_gettop(programm->state));
    }

    return programm;
}

void unload_programm(LuaProgram *programm)
{
    programm_deinit(programm);
}
