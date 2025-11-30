
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include "flint.h"
#include "windows_tcp_debugger.h"

int main(int argc, char *argv[]) {
    WindowsTcpDebugger dbg;

    bool isRunDebug = false;
    const char *program = NULL;

    for(uint32_t i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-g") == 0)
            isRunDebug = true;
        else if(!program)
            program = argv[i];
    }

    if(isRunDebug || program == NULL) {
        Flint::setDebugger(&dbg);
        std::cout << "FlintJVM debug server is started" << std::endl;
        FlintAPI::Thread::sleep(10);
        dbg.receiveTask();
    }
    else {
        Flint::setProgram(program);
        Flint::start();
        while(Flint::isRunning())
            FlintAPI::Thread::yield();
        Flint::freeAll();
    }

    return 0;
}
