// Socket client example 2

#include "network.h"

#include <conio.h>
#include <stdio.h>
#include <winsock2.h>

int main(void) {
    SOCKET s; // Server socket descriptor
    SOCKADDR_IN client; // Socket structure
    WSADATA wsaData; // Startup structure
    int value;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
        Error("socket");

    client.sin_family = AF_INET; // Set as AF_INET
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = inet_addr(ADDRESS);

    if (connect(s, (SOCKADDR *)&client, sizeof(client)) != 0)
        Error("connect");

    while (1) {
        printf("Enter an integer: ");
        scanf("%d", &value);
        send(s, (char *)&value, 4, 0);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}

void Error(const char *szMessage) {
    printf("Error: [%d] %s \n", WSAGetLastError(), szMessage);
    WSACleanup();
    exit(EXIT_FAILURE);
}
