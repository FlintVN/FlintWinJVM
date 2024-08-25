
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include "flint.h"
#include "windows_tcp_debugger.h"

using namespace std;

int main(int argc, char *argv[]) {
    Flint &flint = Flint::getInstance();
    WindowsTcpDebugger dbg(flint);

    bool isRunDebug = false;
    char *mainClass = 0;

    for(uint32_t i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-g") == 0)
            isRunDebug = true;
        else if(!mainClass)
            mainClass = argv[i];
    }

    if(isRunDebug || mainClass == 0) {
        flint.setDebugger(&dbg);
        FlintAPI::Thread::sleep(10);
        std::cout << "FlintJVM debug server is started" << std::endl;
        setlocale(LC_CTYPE, "");
        _setmode(_fileno(stdout), 0x00020000);
        _setmode(_fileno(stdin), 0x00020000);
        dbg.receiveTask();
    }
    else {
        _setmode(_fileno(stdout), 0x00020000);
        _setmode(_fileno(stdin), 0x00020000);
        flint.runToMain(mainClass);
        while(flint.isRunning())
            FlintAPI::Thread::yield();
    }

    return 0;
}
