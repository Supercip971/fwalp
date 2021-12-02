#pragma once
#include <cstdlib>
#include <string>
#define UNUSED __attribute__((unused))

namespace fwalp
{
class Result
{
    bool _success;
    std::string _message;

public:
    Result(bool success, std::string message) : _success(success), _message(message){};

    operator bool() const { return _success; };

    std::string message() const { return _message; };
    bool is_successful() const { return _success; };

    static Result success() { return Result(true, ""); };

    static Result failure(std::string message) { return Result(false, message); }

    void expect_success() const
    {
        if (!_success)
        {
            printf("expected successful, error: %s\n", _message.c_str());
            exit(1);
        }
    }
};
} // namespace fwalp
