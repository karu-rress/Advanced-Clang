// Socket server example 2

#include "network.h"

#include <conio.h>
#include <stdio.h>
#include <winsock2.h>

int main(void) {
    SOCKET s; // Server socket descriptor
    SOCKET cs; // Client socket descriptor
    SOCKADDR_IN server; // Socket structure
    SOCKADDR_IN client; // Socket structure
    WSADATA wsaData; // Startup structure
    int size;
    int num;
    int value; // Received integer value

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        Error("socket");
    }

    server.sin_family = AF_INET; // Set as AF_INET
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(ADDR_ANY); // Set any network card automatically

    if (bind(s, (SOCKADDR *)&server, sizeof(server)) == SOCKET_ERROR)
        Error("bind");

    if (listen(s, SOMAXCONN) != 0)
        Error("listen");

    printf("Waiting for a client to connect... \n");

    size = sizeof(client);
    cs = accept(s, (SOCKADDR *)&client, &size);
    if (cs == INVALID_SOCKET)
        Error("accept");

    while (1) {
        num = recv(cs, (char *)&value, 4, 0);
        if (num == 0 || num == SOCKET_ERROR)
            break;

        printf("Received integer value %d\n", value);
    }

    closesocket(s);
    closesocket(cs);
    WSACleanup();

    return 0;
}

void Error(const char *szMessage) {
    printf("Error: [%d] %s \n", WSAGetLastError(), szMessage);
    WSACleanup();
    exit(EXIT_FAILURE);
}
