#include <stdlib.h>
#include "backend.hpp"
#include "backend/sdl/sdl_render.hpp"
#include "fwalp_lib.hpp"
#include "lua_program.hpp"

int main(int argc, char **argv)
{

    if (argc <= 1)
    {
        printf("usage: fwalp [script path] \n");

        return 1;
    }

    fwalp::Config conf = {};
    conf.height = 100;
    conf.width = 100;
    conf.screen_id = std::string("");
    fwalp::Backend *backend = new fwalp::SDLBackend();

    backend->init(&conf).expect_success();

    fwalp::LuaProgram *program = new fwalp::LuaProgram();

    program->load_program(argv[1]).expect_success();
    set_program_backend_target(backend);

    float time = backend->ticks();
    float delta_time = 0;
    backend->update();
    while (backend->should_close() == 0)
    {
        backend->update().expect_success();
        program->call(0, "update", time / 1000.0f, delta_time).expect_success();
        program->call(0, "draw").expect_success();

        backend->flip().expect_success();

        float new_time = backend->ticks();
        delta_time = (new_time - time) / 1000.0f;
        time = new_time;
    }

    program->deinit().expect_success();
    delete program;

    backend->deinit();
    delete backend;

    return 0;
}
