
#include <windows.h>
#include "flint_system_api.h"

void *FlintAPI::Thread::create(void (*task)(void *), void *param, uint32_t stackSize) {
    return CreateThread(
        NULL,                           /* Default security attributes */
        stackSize,                      /* Default stack size */
        (LPTHREAD_START_ROUTINE)task,   /* Thread function */
        param,                          /* Parameter to thread function */
        0,                              /* Default creation flags */
        NULL
    );
}

void FlintAPI::Thread::terminate(void *threadHandle) {
    if(threadHandle) {
        TerminateThread(threadHandle, 0);
        CloseHandle(threadHandle);
    }
}

void FlintAPI::Thread::sleep(uint32_t ms) {
    Sleep(ms);
}
