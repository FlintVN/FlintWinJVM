
#ifndef __FLINT_CONF_H
#define __FLINT_CONF_H

#include "flint_common.h"

#define KILO_BYTE(_value)           ((_value) * 1024)
#define MEGA_BYTE(_value)           ((_value) * KILO_BYTE(1024))

#define FLINT_VARIANT_NAME          "Windows FlintJVM"

#define FILE_NAME_BUFF_SIZE         256

#define DEFAULT_STACK_SIZE          KILO_BYTE(1000)
#define OBJECT_COUNT_TO_GC          10000

#define MAX_OF_BREAK_POINT          20
#define DBG_TX_BUFFER_SIZE          KILO_BYTE(1)
#define DBG_CONSOLE_BUFFER_SIZE     KILO_BYTE(1)

#endif /* __FLINT_CONF_H */
