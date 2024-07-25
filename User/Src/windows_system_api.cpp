
#include <iostream>
#include <stdint.h>
#include <time.h>
#include "flint_system_api.h"

void FlintSystem_Write(const char *text, uint32_t length, uint8_t coder) {
    if(coder == 0) {
        for(uint32_t i = 0; i < length; i++)
            std::wcout << (wchar_t)(uint8_t)text[i];
    }
    else {
        for(uint32_t i = 0; i < length; i++)
            std::wcout << (wchar_t)((uint16_t *)text)[i];
    }
}

int64_t FlintSystem_GetNanoTime(void) {
    return clock();
}
