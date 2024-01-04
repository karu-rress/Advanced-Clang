#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include "network.h"

int main(void) {
    SOCKET s;           // 서버 소켓 디스크립터
    SOCKADDR_IN client; // 소켓 구조체
    WSADATA wsaData;    // 스타트업 구조체
    int value;         // 파일 송신 버퍼

    WSAStartup(MAKEWORD(2,2), &wsaData);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) 
        Error("socket");

    client.sin_family = AF_INET; // 주소 체계 설정
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = inet_addr(ADDRESS);

    if (connect(s, (SOCKADDR*)&client, sizeof(client)) != 0) 
        Error("connect");

    while (1) {
        printf("정수값 입력 : ");
        scanf("%d", &value);
        send(s, (char*)&value, 4, 0);
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