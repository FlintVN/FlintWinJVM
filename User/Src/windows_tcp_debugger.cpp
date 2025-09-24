
#include "windows_tcp_debugger.h"

WindowsTcpDebugger::WindowsTcpDebugger(void) : FDbg() {
    WSADATA wsaData;
    SOCKADDR_IN serverAddr;

    WSAStartup(MAKEWORD(2, 2), &wsaData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9620);

    ::bind(server, reinterpret_cast<SOCKADDR *>(&serverAddr), sizeof(serverAddr));
    listen(server, 0);
}

bool WindowsTcpDebugger::sendData(uint8_t *data, uint32_t length) {
    return send(client, (const char *)data, length, 0) == length;
}

void WindowsTcpDebugger::receiveTask(void) {
    char buffer[1024];

    SOCKADDR_IN clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    while(1) {
        if((client = accept(server, reinterpret_cast<SOCKADDR *>(&clientAddr), &clientAddrSize)) != INVALID_SOCKET) {
            while(1) {
                int dataSize = recv(client, buffer, sizeof(buffer), 0);
                if(dataSize > 0) {
                    if(!receivedDataHandler((uint8_t *)buffer, dataSize))
                        return;
                }
                else
                    break;
            }
        }
    }
}

WindowsTcpDebugger::~WindowsTcpDebugger(void) {

}
