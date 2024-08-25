
#include <windows.h>
#include "flint_system_api.h"

FlintAPI::Thread::LockHandle *FlintAPI::Thread::createLockHandle(void) {
    FlintAPI::Thread::LockHandle *lockHandle;
    lockHandle = (FlintAPI::Thread::LockHandle *)FlintAPI::System::malloc(sizeof(FlintAPI::Thread::LockHandle));
    lockHandle->mutexHandle = (void *)CreateSemaphore(NULL, 1, 1, NULL);
    lockHandle->lockThreadId = 0;
    lockHandle->lockNest = 0;
    return lockHandle;
}

void FlintAPI::Thread::lock(FlintAPI::Thread::LockHandle *lockHandle) {
    DWORD currentThreadId = GetCurrentThreadId();
    while(1) {
        WaitForSingleObject((HANDLE)lockHandle->mutexHandle, INFINITE);
        if(lockHandle->lockThreadId == 0) {
            lockHandle->lockNest = 1;
            lockHandle->lockThreadId = (void *)currentThreadId;
            ReleaseSemaphore((HANDLE)lockHandle->mutexHandle, 1, NULL);
            return;
        }
        else if(lockHandle->lockThreadId == (void *)currentThreadId) {
            lockHandle->lockNest++;
            ReleaseSemaphore((HANDLE)lockHandle->mutexHandle, 1, NULL);
            return;
        }
        ReleaseSemaphore((HANDLE)lockHandle->mutexHandle, 1, NULL);
        FlintAPI::Thread::yield();
    }
}

void FlintAPI::Thread::unlock(FlintAPI::Thread::LockHandle *lockHandle) {
    WaitForSingleObject((HANDLE)lockHandle, INFINITE);
    if(--lockHandle->lockNest == 0)
        lockHandle->lockThreadId = 0;
    ReleaseSemaphore((HANDLE)lockHandle, 1, NULL);
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
