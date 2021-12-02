#ifndef LUA_PROGRAMM_H
#define LUA_PROGRAMM_H

extern "C"
{
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
#include <string>
#include "utils.hpp"
namespace fwalp
{
class LuaProgram
{
    lua_State *_state;
    int _current_call_arg_count;

    template <typename T>
    void push_argument(T arg);

    Result push_arg_rec()
    {
        return Result::success();
    }
    template <typename cur>
    Result push_arg_rec(cur current)
    {
        push_argument(current);
        return Result::success();
    }
    template <typename cur, typename... T>
    Result push_arg_rec(cur current, T... args)
    {
        push_argument(current);
        return push_arg_rec(args...);
    }

public:
    LuaProgram() = default;
    Result load_program(const std::string &filename);
    Result init();
    Result deinit();
    std::string get_error();
    Result load_libs(); // implemented in fwalp_libs.cpp

    template <typename... T>
    Result call(int return_count, std::string name, T... arg)
    {
        _current_call_arg_count = 0;
        lua_getglobal(_state, name.c_str());
        push_arg_rec(arg...);

        if (lua_pcall(_state, _current_call_arg_count, return_count, 0) != LUA_OK)
        {
            return Result::failure("error while calling function: " + get_error());
        }

        lua_pop(_state, lua_gettop(_state));

        return Result::success();
    }
};
} // namespace fwalp

#endif
