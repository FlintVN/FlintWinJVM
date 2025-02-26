
#include <iostream>
#include <stdint.h>
#include <time.h>
#include "flint_system_api.h"

static void *heapStart = (void *)-1;
static void *heapEnd = (void *)0;

void FlintAPI::System::reset(Flint &flint) {
    /* DO NOTHING */
}

static void *updateHeapRegion(void *p) {
    if(heapStart > p)
        heapStart = p;
    if(p > heapEnd)
        heapEnd = p;
    return p;
}

void *FlintAPI::System::malloc(uint32_t size) {
    return updateHeapRegion(::malloc(size));
}

void *FlintAPI::System::realloc(void *p, uint32_t size) {
    return updateHeapRegion(::realloc(p, size));
}

void FlintAPI::System::free(void *p) {
    ::free(p);
}

bool FlintAPI::System::isInHeapRegion(void *addr) {
    return (heapStart <= addr) && (addr <= heapEnd);
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

uint64_t FlintAPI::System::getNanoTime(void) {
    return clock();
}

FlintNativeMethodPtr FlintAPI::System::findNativeMethod(const FlintMethodInfo &methodInfo) {
    (void)methodInfo;
    return (FlintNativeMethodPtr)0;
}
