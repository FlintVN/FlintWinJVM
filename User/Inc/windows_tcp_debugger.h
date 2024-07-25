
#include <future>
#include <winsock2.h>
#include "flint.h"
#include "flint_system_api.h"

class WindowsTcpDebugger : public FlintDebugger {
private:
    HANDLE hThread;
    SOCKET server;
    SOCKET client;
public:
    WindowsTcpDebugger(Flint &flint);

    bool sendData(uint8_t *data, uint32_t length);
    void receiveTask(void);

    ~WindowsTcpDebugger(void);
private:
    WindowsTcpDebugger(const WindowsTcpDebugger &) = delete;
    void operator=(const WindowsTcpDebugger &) = delete;
};
