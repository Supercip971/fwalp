#include "lua_program.hpp"
#include <stdlib.h>
#include "fwalp_lib.hpp"

namespace fwalp
{
Result LuaProgram::init(void)
{
    _state = luaL_newstate();
    luaL_openlibs(_state);
    return Result::success();
}
Result LuaProgram::deinit(void)
{
    lua_close(_state);
    return Result::success();
}

std::string LuaProgram::get_error(void)
{
    return lua_tostring(_state, -1);
}

template <>
void LuaProgram::push_argument(double arg)
{
    _current_call_arg_count++;
    lua_pushnumber(_state, arg);
}
template <>
void LuaProgram::push_argument(float arg)
{
    _current_call_arg_count++;
    lua_pushnumber(_state, arg);
}
template <>
void LuaProgram::push_argument(int arg)
{
    _current_call_arg_count++;
    lua_pushinteger(_state, arg);
}
Result LuaProgram::load_program(const std::string &filename)
{
    init();
    load_libs();

    if (luaL_dofile(_state, filename.c_str()) != LUA_OK)
    {
        return Result::failure("can't load file:" + get_error());
    }
    else
    {
        lua_pop(_state, lua_gettop(_state));
    }

    return load_libs();
}
} // namespace fwalp
