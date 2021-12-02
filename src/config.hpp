#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>
#include <string>
namespace fwalp
{

struct Config
{
    std::string screen_id;
    uint32_t width;
    uint32_t height;
    std::string script_path;
};

} // namespace fwalp
#endif
