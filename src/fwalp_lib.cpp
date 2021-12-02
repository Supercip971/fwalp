#include "fwalp_lib.hpp"
#include <assert.h>
#include "backend.hpp"
#include "lua_program.hpp"
#include "utils.hpp"

fwalp::Backend *target_backend;

fwalp::Color last_color = fwalp::Color(255, 255, 255, 255);

void set_program_backend_target(fwalp::Backend *render)
{
    target_backend = render;
}
void dump_stack(lua_State *L)
{
    assert(lua_checkstack(L, 3));
    int top = lua_gettop(L);
    int bottom = 1;
    lua_getglobal(L, "tostring");
    for (int i = top; i >= bottom; i--)
    {
        lua_pushvalue(L, -1);
        lua_pushvalue(L, i);
        lua_pcall(L, 1, 1, 0);
        const char *str = lua_tostring(L, -1);
        if (str)
        {
            printf("%s\n", str);
        }
        else
        {
            printf("%s\n", luaL_typename(L, i));
        }
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}

static int set_color(lua_State *L)
{

    if (lua_gettop(L) != 2) /* at least a [r] g b */
    {
        last_color.b = lua_tointeger(L, 2);
        last_color.g = lua_tointeger(L, 3);
        last_color.r = lua_tointeger(L, 4);
        last_color.a = lua_tointeger(L, 5);
    }
    else
    {
        last_color.raw = lua_tointeger(L, 2);
    }
    return 0;
}

static int draw_rec(lua_State *L)
{
    if (lua_gettop(L) != 5)
    {
        printf("got %i arguments !", lua_gettop(L));
        return luaL_error(L, "expecting 4 argument for %s ! ", __FUNCTION__);
    }

    int x = lua_tonumber(L, 2);
    int y = lua_tonumber(L, 3);
    int w = lua_tonumber(L, 4);
    int h = lua_tonumber(L, 5);

    printf("drawing rec: %i %i %i %i\n", x, y, w, h);
    target_backend->rect(fwalp::Rect(x, y, w, h), last_color);
    return 0;
}

static int screen_width(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        printf("got %i arguments !", lua_gettop(L));
        return luaL_error(L, "expecting 1 argument for %s ! ", __FUNCTION__);
    }
    lua_pushinteger(L, target_backend->width());

    return 1;
}

static int screen_height(lua_State *L)
{
    if (lua_gettop(L) != 1)
    {
        printf("got %i arguments !", lua_gettop(L));
        return luaL_error(L, "expecting 1 argument for %s ! ", __FUNCTION__);
    }
    lua_pushinteger(L, target_backend->height());
    return 1;
}

static int fill(UNUSED lua_State *L)
{
    target_backend->fill(last_color);
    return 0;
}

static const luaL_Reg fwalp_render[] =
    {
        {"draw_rec", draw_rec},
        {"set_color", set_color},
        {"screen_width", screen_width},
        {"screen_height", screen_height},
        {"fill", fill},
        {NULL, NULL},
};

int luaopen_fwalp_renderer(lua_State *L)
{
    luaL_newlib(L, fwalp_render);
    return 1;
}

static const struct
{
    const char *name;
    fwalp::Color col;
} fwalp_color[] = {
    {"red", fwalp::Color(255, 0, 0, 255)},
    {"blue", fwalp::Color(0, 0, 255, 255)},
    {"green", fwalp::Color(0, 255, 0, 255)},
    {"black", fwalp::Color(0, 0, 0, 255)},
    {"white", fwalp::Color(255, 255, 255, 255)},
    {NULL, fwalp::Color(0)},
};

int luaopen_fwalp_color(lua_State *L)
{
    luaL_newlibtable(L, fwalp_color);
    for (int i = 0; fwalp_color[i].name != 0; i++)
    {
        lua_pushstring(L, fwalp_color[i].name);
        lua_pushinteger(L, fwalp_color[i].col.raw);
        printf("color: %s = %x \n", fwalp_color[i].name, fwalp_color[i].col.raw);
        lua_rawset(L, -3);
    }
    return 1;
}
static const luaL_Reg fwalp_libs[] = {
    {"fwalp_renderer", luaopen_fwalp_renderer},
    {"fwalp_color", luaopen_fwalp_color},
    {NULL, NULL},
};

fwalp::Result fwalp::LuaProgram::load_libs()
{
    for (int i = 0; fwalp_libs[i].name != NULL; i++)
    {
        luaL_requiref(_state, fwalp_libs[i].name, fwalp_libs[i].func, 1);
    }
    return fwalp::Result::success();
}
