/* 예제 98 : TCP/IP 정수값 수신 서버 */

#include <stdio.h>
#include <conio.h>
#include <winsock2.h>

void Error(char* szMessage);

int main(void)
{
    SOCKET s;           // 서버 소켓 디스크립터
    SOCKET cs;          // 클라이언트 소켓 디스크립터
    SOCKADDR_IN server; // 소켓 구조체
    SOCKADDR_IN client; // 소켓 구조체
    WSADATA wsaData;    // 스타트업 구조체
    int size;

    int  num;           // 수신된 파일 데이터
    int  value;         // 정수값 수신

    WSAStartup(MAKEWORD(2,2), &wsaData);

    s = socket(AF_INET, SOCK_STREAM, 0);

    if(s == INVALID_SOCKET)
    {
        Error("socket");
    }

    server.sin_family      = AF_INET;           // AF_INET 체계임을 명시
    server.sin_port        = htons(10000);      // 10000 번 포트를 사용
    server.sin_addr.s_addr = htonl(ADDR_ANY);   // 임의의 네트워크 카드 설정
    
    if(bind(s, (SOCKADDR*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        Error("bind");
    }

    if(listen(s, SOMAXCONN) != 0)
    {
        Error("listen");
    }

    printf("클라이언트로부터 접속 대기 중입니다... \n");

    size = sizeof(client);
    cs = accept(s, (SOCKADDR*)&client, &size);

    if(cs == INVALID_SOCKET)
    {
        Error("accept");
    }

    while(1)
    {
        num = recv(cs, (char*)&value, 4, 0);

        if(num == 0 || num == SOCKET_ERROR)
        {
            break;
        }

        printf("정수값 %d 수신\n", value);
    }

    closesocket(s);
    closesocket(cs);

    WSACleanup();


}

void Error(char* szMessage)
{
    printf("Error: [%d] %s \n", WSAGetLastError(), szMessage);
    WSACleanup();
    exit(0);
}