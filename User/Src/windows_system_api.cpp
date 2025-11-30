
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

uint64_t FlintAPI::System::getNanoTime(void) {
    auto now = std::chrono::high_resolution_clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    return ns.count();
}
