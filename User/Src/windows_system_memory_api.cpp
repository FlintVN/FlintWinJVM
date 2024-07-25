
#include <stdlib.h>
#include "flint_system_api.h"

void *FlintSystem_Malloc(uint32_t size) {
    return malloc(size);
}

void *FlintSystem_Realloc(void *p, uint32_t size) {
    return realloc(p, size);
}

void FlintSystem_Free(void *p) {
    free(p);
}
