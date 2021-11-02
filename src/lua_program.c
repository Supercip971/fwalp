#include "lua_program.h"
#include <stdlib.h>
#include "fwalp_lib.h"

LuaProgram *programm_init(void)
{
    LuaProgram *self = malloc(sizeof(LuaProgram));

    self->state = luaL_newstate();

    luaL_openlibs(self->state);

    return self;
}

void program_load_libs(LuaProgram *program)
{
    load_fwalp_lib(program);
}
void programm_deinit(LuaProgram *programm)
{
    lua_close(programm->state);
}

const char *get_error(LuaProgram *programm)
{
    return lua_tostring(programm->state, -1);
}

void programm_start_call(LuaProgram *programm, const char *name)
{
    programm->_current_call_arg_count = 0;
    lua_getglobal(programm->state, name);
}

void programm_end_call(LuaProgram *programm)
{
    lua_pop(programm->state, lua_gettop(programm->state));
}

void programm_do_call(LuaProgram *programm, int return_count)
{
    if (return_count != 0)
    {
        printf("non 0 return are not supported ! \n");
    }

    if (lua_pcall(programm->state, programm->_current_call_arg_count, return_count, 0) != LUA_OK)
    {
        printf("error while calling function: %s", get_error(programm));
        exit(EXIT_FAILURE);
    }
}
