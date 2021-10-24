#include "lua_loader.h"
#include <stdlib.h>

int main(int argc, char **argv){

    if(argc <= 1)
    {
        printf("usage: fwalp [script path] \n");

        return 1;
    }


    LuaProgramm* programm = load_programm(argv[1]);


    programm_start_call(programm, "update");
    programm_call_arg(programm, 1.f);

    programm_do_call(programm, 0);

    programm_end_call(programm);

    unload_programm(programm);

    free(programm);
    return 0;
}
