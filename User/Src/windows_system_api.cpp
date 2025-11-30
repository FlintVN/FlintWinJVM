
#include <iostream>
#include <stdint.h>
#include <chrono>
#include "flint_system_api.h"

void FlintAPI::System::reset(void) {
    /* DO NOTHING */
}

void *FlintAPI::System::malloc(uint32_t size) {
    return ::malloc(size);
}

void *FlintAPI::System::realloc(void *p, uint32_t size) {
    return ::realloc(p, size);
}

void FlintAPI::System::free(void *p) {
    ::free(p);
}

void FlintAPI::System::consoleWrite(uint8_t *utf8, uint32_t length) {
    printf("%.*s", length, utf8);
}

int64_t FlintAPI::System::getTimeNanos(void) {
    auto now = std::chrono::high_resolution_clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    return ns.count();
}

int64_t FlintAPI::System::getTimeMillis(void) {
    auto now = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return ms.count();
}

const char *FlintAPI::System::getClassPath(uint32_t index) {
    static const char *jars[] = {
        "java.base.jar",
    };
    if(index < LENGTH(jars))
        return jars[index];
    return NULL;        
}

JNMPtr FlintAPI::System::findNativeMethod(MethodInfo *methodInfo) {
    (void)methodInfo;
    return (JNMPtr)0;
}
