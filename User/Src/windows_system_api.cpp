
#include <iostream>
#include <stdint.h>
#include <time.h>
#include "flint_system_api.h"

void *FlintAPI::System::malloc(uint32_t size) {
    return ::malloc(size);
}

void *FlintAPI::System::realloc(void *p, uint32_t size) {
    return ::realloc(p, size);
}

void FlintAPI::System::free(void *p) {
    ::free(p);
}

void FlintAPI::System::print(const char *text, uint32_t length, uint8_t coder) {
    if(coder == 0) {
        for(uint32_t i = 0; i < length; i++)
            std::wcout << (wchar_t)(uint8_t)text[i];
    }
    else {
        for(uint32_t i = 0; i < length; i++)
            std::wcout << (wchar_t)((uint16_t *)text)[i];
    }
}

int64_t FlintAPI::System::getNanoTime(void) {
    return clock();
}

FlintNativeMethodPtr FlintAPI::System::findNativeMethod(const FlintMethodInfo &methodInfo) {
    (void)methodInfo;
    return (FlintNativeMethodPtr)0;
}
