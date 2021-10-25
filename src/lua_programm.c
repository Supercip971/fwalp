#include "lua_programm.h"
#include <stdlib.h>

LuaProgramm *programm_init(void)
{
    LuaProgramm* self = malloc(sizeof(LuaProgramm));

    self->state = luaL_newstate();

    luaL_openlibs(self->state);

    return self;
}

void programm_deinit(LuaProgramm *programm)
{
    lua_close(programm->state);
}

const char* get_error(LuaProgramm* programm)
{
    return lua_tostring(programm->state, -1);
}

void programm_start_call(LuaProgramm* programm, const char* name)
{
    programm->_current_call_arg_count = 0;
    lua_getglobal(programm->state, name);
}

void programm_end_call(LuaProgramm* programm) 
{
    lua_pop(programm->state, lua_gettop(programm->state));
}

void programm_do_call(LuaProgramm* programm, int return_count)
{
    if(return_count != 0)
    {
        printf("non 0 return are not supported ! \n");
    }

    if(lua_pcall(programm->state, programm->_current_call_arg_count, return_count, 0) != LUA_OK)
    {
        printf("error while calling function: %s", get_error(programm));
        exit(EXIT_FAILURE);
    }
}
