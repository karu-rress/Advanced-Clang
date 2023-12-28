#define API__5
#include "api.h"

#define SPEED   1000

#define PX      130
#define PY        1
#define PW       20

#define BW       10
#define BH       22

#define BLACK_COLOR     RGB(0,0,0)
#define WHITE_COLOR     RGB(255,255,255)
#define BACKGROUND      RGB(255,0,0)
#define EMPTY           0


int game_start;         // 게임이 시작되었는지를 나타내는 플레그

int Brick;              // 현재 이동 중인 블록의 형태
int Next_Brick;         // 다음에 나올 블록의 형태
int Rotate;             // 현재 이동 중인 블록의 회전 상태

int BOARD[BW+2][BH+2];  // 테트리스 전체 블록 영역에 대한 배열

int level = 1;          // 현재 레벨
int score = 10000;      // 현재 점수
int lines = 0;          // 파괴한 라인 수

POINT BRICK_SHAPE[][4][4] =
{
    { // ㄴ자의 4가지 형태
        { 0, 0,-1, 0, 1, 0,-1,-1 }, 
        { 0, 0, 0,-1, 0, 1,-1, 1 }, 
        { 0, 0,-1, 0, 1, 0, 1, 1 }, 
        { 0, 0, 0,-1, 0, 1, 1,-1 } 
    },
    { // ㄴ자의 역방향 4가지 형태
        { 0, 0, 1, 0,-1, 0, 1,-1 }, 
        { 0, 0, 0, 1, 0,-1,-1,-1 }, 
        { 0, 0, 1, 0,-1, 0,-1, 1 }, 
        { 0, 0, 0,-1, 0, 1, 1, 1 } 
    },
    { // ㄹ자의 4가지 형태
        { 0, 0,-1, 0, 0,-1, 1,-1 }, 
        { 0, 0, 0, 1,-1, 0,-1,-1 }, 
        { 0, 0,-1, 0, 0,-1, 1,-1 }, 
        { 0, 0, 0, 1,-1, 0,-1,-1 } 
    },
    { // ㄹ자의 역방향 4가지 형태
        { 0, 0,-1,-1, 0,-1, 1, 0 }, 
        { 0, 0,-1, 0,-1, 1, 0,-1 }, 
        { 0, 0,-1,-1, 0,-1, 1, 0 }, 
        { 0, 0,-1, 0,-1, 1, 0,-1 } 
    },
    { // ㅗ자의 4가지 형태
        { 0, 0,-1, 0, 1, 0, 0,-1 }, 
        { 0, 0,-1, 0, 0,-1, 0, 1 }, 
        { 0, 0,-1, 0, 1, 0, 0, 1 }, 
        { 0, 0, 0,-1, 0, 1, 1, 0 }
    },
    { // 긴 막대의 4가지 형태
        { 0, 0, 1, 0, 2, 0,-1, 0 }, 
        { 0, 0, 0, 1, 0, 2, 0,-1 }, 
        { 0, 0, 1, 0, 2, 0,-1, 0 }, 
        { 0, 0, 0, 1, 0, 2, 0,-1 } 
    },
    { // 사각형의 4가지 형태
        { 0, 0, 1, 0, 0, 1, 1, 1 }, 
        { 0, 0, 1, 0, 0, 1, 1, 1 }, 
        { 0, 0, 1, 0, 0, 1, 1, 1 }, 
        { 0, 0, 1, 0, 0, 1, 1, 1 } 
    },
};

#define SERVER      1
#define SERVERON    2
#define CLIENTON    3

SOCKET g_s, g_cs;
char szServerIP[] = "127.0.0.1";
int  m_nMode;

void SocketInit();
void SocketServer();
void SocketAccept();
void SocketConnect();
void SocketClose();
void InsertBlock(int line);

BEGIN()

int  x, y;
char buff[100];

EXAM92_BEGIN(SPEED)

    RECTANGLE(0 , 0  , 350       , PY+(PW*BH)+2, BACKGROUND);
    RECTANGLE(1 , 1  , PX-1      , 150         , BLACK_COLOR);
    RECTANGLE(1 , 151, PX-1      , PY+(PW*BH)+1, BLACK_COLOR);
    RECTANGLE(PX, PY , PX+(PW*10), PY+(PW*BH)+1, BLACK_COLOR);

    DISPLAY(25,   7, "다음 블록", 15);
    DISPLAY(15, 177, "레벨"     , 15);
    DISPLAY(15, 207, "점수"     , 15);
    DISPLAY(15, 237, "줄수"     , 15);

    sprintf(buff, "%d", level);
    DISPLAY(50, 177, buff, 15);

    sprintf(buff, "%d", score);
    DISPLAY(50, 207, buff, 15);

    sprintf(buff, "%d", lines);
    DISPLAY(50, 237, buff, 15);

    // 전체 벽돌을 그립니다.
    for (y = 1; y < BH+1; y++) {
        for (x = 1; x < BW+1; x++) {
            if (BOARD[x][y]) {
                BRICK_DRAW(x-1, y-1, BOARD[x][y]);
            }
        }
    }

    // 현재 이동 중인 벽돌을 그립니다.
    if (game_start) {
        int i;
        for (i = 0; i < 4; i++) {
            int x, y;
            
            x = BX + BRICK_SHAPE[Brick][Rotate][i].x;
            y = BY + BRICK_SHAPE[Brick][Rotate][i].y;
            
            BRICK_DRAW(x-1, y-1, Brick+1);
        }
    }

    // 현재 이동 중인 벽돌의 그림자를 그립니다.
    if (game_start)  {
        int i;
        for (y =BY+1; y < BH+2; y++) {
            if (IsMoveable(BX, y, Brick, Rotate) != EMPTY) {
                int by = y-1;
                for (i = 0; i < 4; i++) {
                    int x;
                    x = BX + BRICK_SHAPE[Brick][Rotate][i].x;
                    y = by + BRICK_SHAPE[Brick][Rotate][i].y;
                    BRICK_SHADOW(x-1, y-1, Brick+1);
                }
                break;
            }
        }
    }
    
    // 다음에 사용할 블록을 그립니다.
    if (game_start) {
        int i;
        for (i = 0; i < 4; i++) {
            int x, y;
            
            x = BRICK_SHAPE[Next_Brick][0][i].x;
            y = BRICK_SHAPE[Next_Brick][0][i].y;
            
            NEXT_BRICK_DRAW(x, y, Next_Brick+1);
        }
    }

EXAM92_END()   

END()

void MakeBrick(void) {
    int blocks = sizeof(BRICK_SHAPE)/sizeof(BRICK_SHAPE[0]);
    
    
    Brick = Next_Brick;
    Next_Brick = rand() % (blocks + 1);
    
    if (Next_Brick == blocks) {
        Next_Brick = 5;     // 긴 막대
    }

    BX = 5;
    BY = 2;
    Rotate = 0;
}

int MoveBrick(void) {
    if (IsMoveable(BX, BY+1, Brick, Rotate) != EMPTY) {
        CheckGame();
        MakeBrick();
        
        if (IsMoveable(BX, BY+1, Brick, Rotate) != EMPTY) {
            GAME_OVER();
        }
        
        return 0;
    }

    BY++;
    return 1;
}

int IsMoveable(int bx, int by, int brick, int rotate) {
    int i, empty = EMPTY;
    int x, y;
    int line = 0;
    
    if (m_nMode == SERVERON) {
        if (recv(g_cs, (char*)&line, 4, 0) == 4) {
            InsertBlock(line);
        }
    }
    else if (m_nMode == CLIENTON) {
        if (recv(g_s,  (char*)&line, 4, 0) == 4) {
            InsertBlock(line);
        }
    }
    
    for (i = 0; i < 4; i++) {
        x = bx + BRICK_SHAPE[brick][rotate][i].x;
        y = by + BRICK_SHAPE[brick][rotate][i].y;
        
        empty = max(empty, BOARD[x][y]);
    }
    
    return empty;
}

int CheckGame(void) {
    int i, j;
    int bx, by;
    int count = 0;
    
    for (i = 0; i < 4; i++) {
        bx = BX + BRICK_SHAPE[Brick][Rotate][i].x;
        by = BY + BRICK_SHAPE[Brick][Rotate][i].y;
        
        // 이동 중인 블록을 배열에 저장 
        BOARD[bx][by] = Brick+1;
    }
    
    Brick = -1;
    
    for (by = 1; by < BH+1; by++) {
        for (bx = 1; bx < BW+1; bx++)  // 한 줄이 다 찼는지 검사
        {
            if (BOARD[bx][by] == EMPTY) break;
        }
        
        if (bx == 11)              // 한 줄이 다 찬 경우
        {
            count++;
            
            for (i=by; i>=2; i--) 
            {
                for (j = 1; j< BW+1; j++)
                {
                    // 다 찬 블록을 제거하고 한 칸씩 아래로 이동
                    BOARD[j][i] = BOARD[j][i-1];
                }
            }
        }
    }

    score += count * 1234 + (count/2) * 5678;
    
    if (count)
    {
        CLEAN_SOUND();
        
        if (m_nMode == SERVERON)
        {
            send(g_cs, (char*)&count, 4, 0);
        }
        else if (m_nMode == CLIENTON)
        {
            send(g_s, (char*)&count, 4, 0);
        }
        
        lines += count;
    }
    
    return 0;
}

void SocketInit() {
    WSADATA wsaData;    // 스타트업 구조체
    
    WSAStartup(MAKEWORD(2,2), &wsaData);
    
    g_s = socket(AF_INET, SOCK_STREAM, 0);
    if (g_s == INVALID_SOCKET)
    {
        ERROR_SOCKET("socket");
    }
}

void SocketServer() {
    SOCKADDR_IN server; // 소켓 구조체
    unsigned long on;   // 비동기 모드로 전환
    
    // 비동기 모드 전환
    on = 1;
    ioctlsocket(g_s, FIONBIO, &on);
    
    server.sin_family      = AF_INET;           // AF_INET 체계임을 명시
    server.sin_port        = htons(10000);      // 10000 번 포트를 사용
    server.sin_addr.s_addr = htonl(ADDR_ANY);   // 임의의 네트워크 카드 설정
    
    if (bind(g_s, (SOCKADDR*)&server, sizeof(server)) == SOCKET_ERROR)
    {
        ERROR_SOCKET("bind");
    }
    
    if (listen(g_s, 5) != 0)
    {
        ERROR_SOCKET("listen");
    }
    
    m_nMode = SERVER;
    MSG("서버가 시작되었습니다.");
}

void SocketAccept() {
    int size;
    SOCKADDR_IN client; // 소켓 구조체
    
    if (m_nMode != SERVER) {
        return;
    }
    
    size = sizeof(client);
    g_cs = accept(g_s, (SOCKADDR*)&client, &size);
    
    if (g_cs == INVALID_SOCKET) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            ERROR_SOCKET("accept");
        }
        return;
    }
    
    m_nMode = SERVERON;
    //MSG("클라이언트가 접속되었습니다.");
}

void SocketConnect()
{
    SOCKADDR_IN client; // 소켓 구조체
    unsigned long on;   // 비동기 모드로 전환
    
    client.sin_family      = AF_INET;                   // 주소 체계 설정
    client.sin_port        = htons(10000);            // 포트 번호 설정
    client.sin_addr.s_addr = inet_addr(szServerIP);   // 접속 주소 설정
    
    if (connect(g_s, (SOCKADDR*)&client, sizeof(client)) != 0)
    {
        ERROR_SOCKET("connect");
    }
    else
    {
        m_nMode = CLIENTON;
        
        // 비동기 모드 전환
        on = 1;
        ioctlsocket(g_s, FIONBIO, &on);
        MSG("클라이언트가 시작되었습니다.");
    }
}

void SocketClose()
{
    closesocket(g_s);
    closesocket(g_cs);
    WSACleanup();
}

void InsertBlock(int line)
{
    int x, y;
    
    for (y =line+1; y < BH+1; y++) 
    {
        for (x = 1; x < BW+1; x++)
        {
            // 상대편으로부터 날아온 블록을 채우기 위해 위로 이동
            BOARD[x][y-line] = BOARD[x][y];
        }
    }
    
    for (y = BH; y>BH-line; y--)
    {
        int space = rand()%BW + 1;
        
        for (x = 1; x < BW+1; x++)
        {
            if (x == space)
            {
                BOARD[x][y] = 0;
            }
            else
            {
                BOARD[x][y] = 8;
            }
        }
    }
}
