#include <stdlib.h>
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

    while (render_update(renderer))
    {
        printf("render: \n");
        render_rect(renderer, (Rect){.x = 100, .y = 100, .w = 500, .h = 500}, (Color){.raw = 0xffffffff});

        render_flip(renderer);
    }
    LuaProgram *programm = load_programm(argv[1]);

    programm_start_call(programm, "update");
    programm_call_arg(programm, 1.f);

    programm_do_call(programm, 0);

    programm_end_call(programm);

    unload_programm(programm);

    free(programm);

    render_deinit(renderer);
    return 0;
}
