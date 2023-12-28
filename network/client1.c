/* 예제 96 : TCP/IP 클라이언트 프로그램 */

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "wsock32.lib")

void Error(char* szMessage);

int main(void)
{
    SOCKET  s;
    WSADATA wsaData;
    struct sockaddr_in  sin;
    
    WSAStartup(MAKEWORD(2,2), &wsaData);
    
    s = socket(AF_INET, SOCK_STREAM, 0);
    
    if(s == INVALID_SOCKET)
    {
        Error("socket");
        return;
    }
    
    sin.sin_family      = AF_INET;
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_port        = htons(10000);
    
    if(connect(s, (struct sockaddr*)&sin, sizeof(sin)) != 0)
    {
        closesocket(s);
        Error("connect");
        return; 
    }
    
    printf("127.0.0.1의 10000번 포트에 접속을 성공. \n");
    
    closesocket(s);
    
    WSACleanup();


}

void Error(char* szMessage)
{
    printf("Error: [%d] %s \n", WSAGetLastError(), szMessage);
    WSACleanup();
    exit(0);
}