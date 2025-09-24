
#ifndef __WINDOWS_TCP_DEBUGGER_H
#define __WINDOWS_TCP_DEBUGGER_H

#include <future>
#define byte win_byte_override
#include <winsock2.h>
#undef byte
#include "flint_std.h"
#include "flint_debugger.h"

class WindowsTcpDebugger : public FDbg {
private:
    HANDLE hThread;
    SOCKET server;
    SOCKET client;
public:
    WindowsTcpDebugger(void);

    bool sendData(uint8_t *data, uint32_t length);
    void receiveTask(void);

    ~WindowsTcpDebugger(void);
private:
    WindowsTcpDebugger(const WindowsTcpDebugger &) = delete;
    void operator=(const WindowsTcpDebugger &) = delete;
};

#endif /* __WINDOWS_TCP_DEBUGGER_H */
