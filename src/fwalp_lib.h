#ifndef FWALP_LIB_H
#define FWALP_LIB_H

#include "lua_program.h"

#include "render.h"

void load_fwalp_lib(LuaProgram* target);

void set_program_render_target(FWalpRenderer* render);
#endif
