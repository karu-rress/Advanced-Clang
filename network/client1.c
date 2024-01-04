#include <stdio.h>
#include <winsock2.h>
#include "network.h"

int main(void) {
    SOCKET s;
    WSADATA wsaData;
    struct sockaddr_in sin;
    
    WSAStartup(MAKEWORD(2,2), &wsaData);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        Error("socket");
        return 1;
    }
    
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ADDRESS);
    sin.sin_port = htons(PORT);
    
    if (connect(s, (struct sockaddr*)&sin, sizeof(sin)) != 0) {
        closesocket(s);
        Error("connect");
        return 1; 
    }
    
    printf("%s의 %d번 포트에 접속을 성공.\n", ADDRESS, PORT);
    closesocket(s);
    WSACleanup();

    return 0;
}

void Error(const char* szMessage) {
    printf("Error: [%d] %s\n", WSAGetLastError(), szMessage);
    WSACleanup();
    exit(EXIT_FAILURE);
}