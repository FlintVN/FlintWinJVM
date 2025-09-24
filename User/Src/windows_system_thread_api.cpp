
#include <windows.h>
#include "flint_system_api.h"

ThreadHandle FlintAPI::Thread::create(void (*task)(void *), void *param, uint32_t stackSize) {
    return CreateThread(
        NULL,                           /* Default security attributes */
        stackSize,                      /* Default stack size */
        (LPTHREAD_START_ROUTINE)task,   /* Thread function */
        param,                          /* Parameter to thread function */
        0,                              /* Default creation flags */
        NULL
    );
}

ThreadHandle FlintAPI::Thread::getCurrentThread(void) {
    return (ThreadHandle)GetCurrentThreadId();
}

void FlintAPI::Thread::terminate(ThreadHandle handle) {
    if(handle) {
        TerminateThread(handle, 0);
        CloseHandle(handle);
    }
}

void FlintAPI::Thread::sleep(uint32_t ms) {
    Sleep(ms);
}

void FlintAPI::Thread::yield(void) {
    Sleep(0);
}
