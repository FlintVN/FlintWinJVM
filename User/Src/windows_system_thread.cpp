
#include <windows.h>
#include "flint_system_api.h"

void *FlintSystem_ThreadCreate(void (*task)(void *), void *param, uint32_t stackSize) {
    return CreateThread(
        NULL,                           // Default security attributes
        stackSize,                      // Default stack size
        (LPTHREAD_START_ROUTINE)task,   // Thread function
        param,                          // Parameter to thread function
        0,                              // Default creation flags
        NULL
    );
}

void FlintSystem_ThreadTerminate(void *threadHandle) {
    TerminateThread(threadHandle, 0);
    CloseHandle(threadHandle);
}

void FlintSystem_ThreadSleep(uint32_t ms) {
    Sleep(ms);
}
