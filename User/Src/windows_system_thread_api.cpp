
#include <windows.h>
#include "flint_system_api.h"

static int32_t lockNest = 0;
static volatile DWORD lockThreadId = 0;
static HANDLE semaphore = CreateSemaphore(NULL, 1, 1, NULL);

void FlintAPI::Thread::lock(void) {
    DWORD currentThreadId = GetCurrentThreadId();
    while(1) {
        WaitForSingleObject(semaphore, INFINITE);
        if(lockThreadId == 0) {
            lockNest = 1;
            lockThreadId = currentThreadId;
            ReleaseSemaphore(semaphore, 1, NULL);
            return;
        }
        else if(lockThreadId == currentThreadId) {
            lockNest++;
            ReleaseSemaphore(semaphore, 1, NULL);
            return;
        }
        ReleaseSemaphore(semaphore, 1, NULL);
        FlintAPI::Thread::yield();
    }
}

void FlintAPI::Thread::unlock(void) {
    WaitForSingleObject(semaphore, INFINITE);
    if(--lockNest == 0)
        lockThreadId = 0;
    ReleaseSemaphore(semaphore, 1, NULL);
}

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

void FlintAPI::Thread::yield(void) {
    Sleep(0);
}
