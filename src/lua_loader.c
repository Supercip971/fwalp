#include "lua_loader.h"
#include <stdlib.h>

LuaProgramm* load_programm(const char* path)
{
    LuaProgramm* programm = programm_init();

    if(luaL_dofile(programm->state, path) != LUA_OK) 
    {
        fprintf(stderr, "lua error while loading: %s \n", get_error(programm));
        exit(EXIT_FAILURE);
    }
    else {
        lua_pop(programm->state, lua_gettop(programm->state)); 
    }

    return programm;
}

void unload_programm(LuaProgramm* programm)
{
    programm_deinit(programm);
}
