#ifndef CONFIG_H
#define CONFIG_H
#include <stdint.h>

typedef struct
{
    const char *screen_id;
    uint32_t width;
    uint32_t height;
    const char *script_path;
} FWalpConfig;

#endif
