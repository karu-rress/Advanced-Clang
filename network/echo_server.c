// Usage:
// telnet 127.0.0.1 10000

#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include "network.h"

int main(void) {
    SOCKET s;           // 서버 소켓 디스크립터
    SOCKET cs;          // 클라이언트 소켓 디스크립터
    SOCKADDR_IN server; // 소켓 구조체
    SOCKADDR_IN client; // 소켓 구조체
    WSADATA wsaData;    // 스타트업 구조체

    int  num;           // 수신된 데이터 크기
    char buff[100];     // 데이터 수신 버퍼
    int size;

    WSAStartup(MAKEWORD(2,2), &wsaData);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) {
        Error("socket");
    }

    server.sin_family = AF_INET;           // AF_INET 체계임을 명시
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(ADDR_ANY);   // 자동 네트워크 카드 설정
    
    if (bind(s, (SOCKADDR*)&server, sizeof(server)) == SOCKET_ERROR) 
        Error("bind");

    if (listen(s, SOMAXCONN) != 0) 
        Error("listen");

    printf("클라이언트로부터 접속 대기 중입니다... \n");

    size = sizeof(client);
    cs = accept(s, (SOCKADDR*)&client, &size);
    if (cs == INVALID_SOCKET) 
        Error("accept");

    while (1) {
        memset(buff, 0, sizeof(buff));

        num = recv(cs, buff, sizeof(buff), 0);
        if (num == 0 || num == SOCKET_ERROR)
            break;

        puts(buff);
        send(cs, buff, num, 0);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}

void Error(const char* szMessage) {
    printf("Error: [%d] %s \n", WSAGetLastError(), szMessage);
    WSACleanup();
    exit(EXIT_FAILURE);
}