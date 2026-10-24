#define API__5
#include "api.h"

#define SPEED   1000

#define PX 130
#define PY 1
#define PW 20

#define BW 10
#define BH 22

#define BLACK_COLOR RGB(0,0,0)
#define WHITE_COLOR RGB(255,255,255)
#define BACKGROUND RGB(255,0,0)
#define EMPTY 0

int game_start; // Whether the game has started or not

int Brick; // Shape of the current moving brick
int Next_Brick; // Shape of the next brick
int Rotate; // Rotation of the current moving brick

int BOARD[BW + 2][BH + 2];

int level = 1;
int score = 10000;
int lines = 0; // Number of lines destroyed

POINT BRICK_SHAPE[][4][4] =
{
    { // ㄴ
        { 0, 0,-1, 0, 1, 0,-1,-1 },
        { 0, 0, 0,-1, 0, 1,-1, 1 },
        { 0, 0,-1, 0, 1, 0, 1, 1 },
        { 0, 0, 0,-1, 0, 1, 1,-1 }
    },
    {
        { 0, 0, 1, 0,-1, 0, 1,-1 },
        { 0, 0, 0, 1, 0,-1,-1,-1 },
        { 0, 0, 1, 0,-1, 0,-1, 1 },
        { 0, 0, 0,-1, 0, 1, 1, 1 }
    },
    { // ㄹ
        { 0, 0,-1, 0, 0,-1, 1,-1 },
        { 0, 0, 0, 1,-1, 0,-1,-1 },
        { 0, 0,-1, 0, 0,-1, 1,-1 },
        { 0, 0, 0, 1,-1, 0,-1,-1 }
    },
    {
        { 0, 0,-1,-1, 0,-1, 1, 0 },
        { 0, 0,-1, 0,-1, 1, 0,-1 },
        { 0, 0,-1,-1, 0,-1, 1, 0 },
        { 0, 0,-1, 0,-1, 1, 0,-1 }
    },
    { // ㅗ
        { 0, 0,-1, 0, 1, 0, 0,-1 },
        { 0, 0,-1, 0, 0,-1, 0, 1 },
        { 0, 0,-1, 0, 1, 0, 0, 1 },
        { 0, 0, 0,-1, 0, 1, 1, 0 }
    },
    { // ㅣ
        { 0, 0, 1, 0, 2, 0,-1, 0 },
        { 0, 0, 0, 1, 0, 2, 0,-1 },
        { 0, 0, 1, 0, 2, 0,-1, 0 },
        { 0, 0, 0, 1, 0, 2, 0,-1 }
    },
    { // ㅁ
        { 0, 0, 1, 0, 0, 1, 1, 1 },
        { 0, 0, 1, 0, 0, 1, 1, 1 },
        { 0, 0, 1, 0, 0, 1, 1, 1 },
        { 0, 0, 1, 0, 0, 1, 1, 1 }
    },
};

#define SERVER 1
#define SERVERON 2
#define CLIENTON 3

SOCKET g_s, g_cs;
char szServerIP[] = "127.0.0.1";
int m_nMode;

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

    RECTANGLE(0, 0, 350, PY + (PW * BH) + 2, BACKGROUND);
    RECTANGLE(1, 1, PX - 1, 150, BLACK_COLOR);
    RECTANGLE(1, 151, PX - 1, PY + (PW * BH) + 1, BLACK_COLOR);
    RECTANGLE(PX, PY, PX + (PW * 10), PY + (PW * BH) + 1, BLACK_COLOR);

    DISPLAY(25, 7, "Next Brick", 15);
    DISPLAY(15, 177, "Level", 15);
    DISPLAY(15, 207, "Score", 15);
    DISPLAY(15, 237, "Lines", 15);

    sprintf(buff, "%d", level);
    DISPLAY(50, 177, buff, 15);

    sprintf(buff, "%d", score);
    DISPLAY(50, 207, buff, 15);

    sprintf(buff, "%d", lines);
    DISPLAY(50, 237, buff, 15);

    // Draw all bricks
    for (y = 1; y < BH + 1; y++) {
        for (x = 1; x < BW + 1; x++) {
            if (BOARD[x][y])
                BRICK_DRAW(x - 1, y - 1, BOARD[x][y]);
        }
    }

    // Draw the current moving brick
    if (game_start) {
        for (int i = 0; i < 4; i++) {
            int x = BX + BRICK_SHAPE[Brick][Rotate][i].x;
            int y = BY + BRICK_SHAPE[Brick][Rotate][i].y;

            BRICK_DRAW(x - 1, y - 1, Brick + 1);
        }
    }

    // Draw the shadow of the current moving brick
    if (game_start) {
        for (y = BY + 1; y < BH + 2; y++) {
            if (IsMoveable(BX, y, Brick, Rotate) != EMPTY) {
                int by = y - 1;
                for (int i = 0; i < 4; i++) {
                    int x = BX + BRICK_SHAPE[Brick][Rotate][i].x;
                    y = by + BRICK_SHAPE[Brick][Rotate][i].y;
                    BRICK_SHADOW(x - 1, y - 1, Brick + 1);
                }

                break;
            }
        }
    }

    // Draw the next brick
    if (game_start) {
        for (int i = 0; i < 4; i++) {
            int x = BRICK_SHAPE[Next_Brick][0][i].x;
            int y = BRICK_SHAPE[Next_Brick][0][i].y;

            NEXT_BRICK_DRAW(x, y, Next_Brick + 1);
        }
    }

EXAM92_END()

END()

void MakeBrick(void) {
    int blocks = sizeof(BRICK_SHAPE) / sizeof(BRICK_SHAPE[0]);

    Brick = Next_Brick;
    Next_Brick = rand() % (blocks + 1);

    if (Next_Brick == blocks) {
        Next_Brick = 5; // Long brick
    }

    BX = 5;
    BY = 2;
    Rotate = 0;
}

int MoveBrick(void) {
    if (IsMoveable(BX, BY + 1, Brick, Rotate) != EMPTY) {
        CheckGame();
        MakeBrick();

        if (IsMoveable(BX, BY + 1, Brick, Rotate) != EMPTY) {
            GAME_OVER();
        }
        return 0;
    }

    BY++;
    return 1;
}

int IsMoveable(int bx, int by, int brick, int rotate) {
    int empty = EMPTY;
    int line = 0;

    if (m_nMode == SERVERON) {
        if (recv(g_cs, (char *)&line, 4, 0) == 4) {
            InsertBlock(line);
        }
    }
    else if (m_nMode == CLIENTON) {
        if (recv(g_s, (char *)&line, 4, 0) == 4) {
            InsertBlock(line);
        }
    }

    for (int i = 0; i < 4; i++) {
        int x = bx + BRICK_SHAPE[brick][rotate][i].x;
        int y = by + BRICK_SHAPE[brick][rotate][i].y;

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

        // Move the current moving brick to the board
        BOARD[bx][by] = Brick + 1;
    }

    Brick = -1;

    for (by = 1; by < BH + 1; by++) {
        for (bx = 1; bx < BW + 1; bx++) { // Check if the line is full
            if (BOARD[bx][by] == EMPTY)
                break;
        }

        if (bx == 11) { // Line is full
            count++;

            for (i = by; i > 2; i--) {
                for (j = 1; j < BW + 1; j++) {
                    // Remove the line and move down the above lines
                    BOARD[j][i] = BOARD[j][i - 1];
                }
            }
        }
    }

    score += count * 1234 + (count / 2) * 5678;

    if (count) {
        CLEAN_SOUND();

        if (m_nMode == SERVERON) {
            send(g_cs, (char *)&count, 4, 0);
        }
        else if (m_nMode == CLIENTON) {
            send(g_s, (char *)&count, 4, 0);
        }

        lines += count;
    }

    return 0;
}

void SocketInit() {
    WSADATA wsaData; // Startup structure

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    g_s = socket(AF_INET, SOCK_STREAM, 0);
    if (g_s == INVALID_SOCKET) {
        ERROR_SOCKET("socket");
    }
}

void SocketServer() {
    SOCKADDR_IN server; // Socket structure
    unsigned long on; // Switch to asynchronous mode

    on = 1;
    ioctlsocket(g_s, FIONBIO, &on);

    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = htonl(ADDR_ANY);

    if (bind(g_s, (SOCKADDR *)&server, sizeof(server)) == SOCKET_ERROR) {
        ERROR_SOCKET("bind");
    }

    if (listen(g_s, 5) != 0) {
        ERROR_SOCKET("listen");
    }

    m_nMode = SERVER;
    MSG("Server has started.");
}

void SocketAccept() {
    int size;
    SOCKADDR_IN client;

    if (m_nMode != SERVER) {
        return;
    }

    size = sizeof(client);
    g_cs = accept(g_s, (SOCKADDR *)&client, &size);

    if (g_cs == INVALID_SOCKET) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            ERROR_SOCKET("accept");
        }
        return;
    }

    m_nMode = SERVERON;
    // MSG("Client has connected.");
}

void SocketConnect() {
    SOCKADDR_IN client;
    unsigned long on;

    client.sin_family = AF_INET;
    client.sin_port = htons(10000);
    client.sin_addr.s_addr = inet_addr(szServerIP);

    if (connect(g_s, (SOCKADDR *)&client, sizeof(client)) != 0) {
        ERROR_SOCKET("connect");
    }
    else {
        m_nMode = CLIENTON;

        // Switch to non-blocking mode
        on = 1;
        ioctlsocket(g_s, FIONBIO, &on);
        MSG("Client has started.");
    }
}

void SocketClose() {
    closesocket(g_s);
    closesocket(g_cs);
    WSACleanup();
}

void InsertBlock(int line) {
    for (int y = line + 1; y < BH + 1; y++) {
        for (int x = 1; x < BW + 1; x++) {
            BOARD[x][y - line] = BOARD[x][y];
        }
    }

    for (int y = BH; y > BH - line; y--) {
        int space = rand() % BW + 1;

        for (int x = 1; x < BW + 1; x++) {
            if (x == space)
                BOARD[x][y] = 0;

            else
                BOARD[x][y] = 8;
        }
    }
}
