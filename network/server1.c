#include <stdio.h>
#include <winsock2.h>
#include "network.h"

int main(void) {
    SOCKET s, cs;
    WSADATA wsaData;
    struct sockaddr_in sin;
    struct sockaddr_in cli_addr;
    int size = sizeof(cli_addr);
    
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        Error("socket");
        return 1;
    }
    
    sin.sin_family = AF_INET;          // AF_INET 체계임을 명시
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = htonl(ADDR_ANY);  // 자동 네트워크 카드 설정
    
    if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR) {
        closesocket(s);
        Error("bind");
        return 1;
    }
    
    if (listen(s, SOMAXCONN) != 0) {
        closesocket(s);
        Error("listen");
        return 1;
    }
    
    printf("클라이언트로부터 접속을 기다리고 있습니다...\n");
    
    cs = accept(s, (struct sockaddr*)&cli_addr, &size);
    if (cs == INVALID_SOCKET) {
        closesocket(s);
        Error("accept");
        return;
    }
    
    printf("클라이언트가 접속되었습니다.\n");
    printf("IP = %s, PORT = %d\n", 
        inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
    
    closesocket(cs);
    closesocket(s);
    WSACleanup();

    return 0;
}

void Error(const char* szMessage)
{
    printf("Error: [%d] %s \n", WSAGetLastError(), szMessage);
    WSACleanup();
    exit(EXIT_FAILURE);
}