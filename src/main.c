#include <stdlib.h>
#include "fwalp_lib.h"
#include "lua_loader.h"
#include "render.h"

int main(int argc, char **argv)
{

    if (argc <= 1)
    {
        printf("usage: fwalp [script path] \n");

        return 1;
    }

    FWalpConfig conf = {};
    conf.height = 100;
    conf.width = 100;
    conf.screen_id = NULL;
    FWalpRenderer *renderer = render_init(&conf);
    LuaProgram *programm = load_programm(argv[1]);
    set_program_render_target(renderer);
    float time = 0.0f;
    while (render_update(renderer))
    {
        programm_start_call(programm, "update");
        programm_call_arg(programm, time);
        programm_do_call(programm, 0);
        programm_end_call(programm);

        programm_start_call(programm, "draw");
        programm_do_call(programm, 0);
        programm_end_call(programm);
        
        render_flip(renderer);
        time += 0.1f;
    }
    unload_programm(programm);

    free(programm);

    render_deinit(renderer);
    return 0;
}
