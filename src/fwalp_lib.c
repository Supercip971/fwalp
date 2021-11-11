#include "fwalp_lib.h"
#include <assert.h>
FWalpRenderer *target_renderer;
Color last_color = (Color){255, 255, 255, 255};

void set_program_render_target(FWalpRenderer *render)
{
    target_renderer = render;
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
        last_color = (Color){.b = lua_tointeger(L, 2), .g = lua_tointeger(L, 3), .r = lua_tointeger(L, 4), .a = lua_tointeger(L, 5)};
    }
    else
    {

        last_color.raw = lua_tointeger(L, 2);
    }
    return 0;
}
static int draw_rec(lua_State *L)
{
    dump_stack(L);
    if (lua_gettop(L) != 5)
    {
        printf("got %i arguments !", lua_gettop(L));
        return luaL_error(L, "expecting 4 argument for %s ! ", __FUNCTION__);
    }

    int x = lua_tointeger(L, 2);
    int y = lua_tointeger(L, 3);
    int w = lua_tointeger(L, 4);
    int h = lua_tointeger(L, 5);

    printf("drawing rec: %i %i %i %i\n", x, y, w, h);
    render_rect(target_renderer, (Rect){x, y, w, h}, last_color);
    return 0;
}
static int fill(lua_State *L)
{
    render_fill(target_renderer, last_color);
    return 0;
}

static const luaL_Reg fwalp_render[] =
    {
        {"draw_rec", draw_rec},
        {"set_color", set_color},
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
    Color col;
} fwalp_color[] =
    {
        {"red", make_color$(255, 0, 0, 255)},
        {"blue",  make_color$(0, 0, 255, 255)},
        {"green", make_color$(0, 255, 0, 255)},
        {"black", make_color$(0, 0, 0, 255)},
        {"white", make_color$(255, 255, 255, 255)},
        {NULL, NULL},
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
static const luaL_Reg fwalp_libs[] =
    {
        {"fwalp_renderer", luaopen_fwalp_renderer},
        {"fwalp_color", luaopen_fwalp_color},
        {NULL, NULL}};

void load_fwalp_lib(LuaProgram *target)
{
    for (int i = 0; fwalp_libs[i].name != NULL; i++)
    {
        luaL_requiref(target->state, fwalp_libs[i].name, fwalp_libs[i].func, 1);
    }
}
