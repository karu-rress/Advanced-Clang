#define API__3
#include "api.h"

int BOARD[20][20];

#define PX  20
#define PY  20
#define PW  25

#define BLACK_STONE     1
#define WHITE_STONE     2
#define BLACK_COLOR     RGB(0,0,0)
#define WHITE_COLOR     RGB(255,255,255)
#define BACKGROUND      RGB(242,215,149)

BEGIN()

int x, y;

EXAM91_BEGIN()

    RECTANGLE(PX - 20, PY - 20, PX + PW*18 + 20, PY + PW*18 + 20, BACKGROUND);

    for (x = 0; x < PW * 19; x += PW)
        LINE(PX + x, PY, PX + x, PY + PW*18);

    for (y = 0; y < PW*19; y += PW) 
        LINE(PX, PY+y, PX+(PW*18), PY+y);

    for (x = PX + PW*4; x < PW*19; x += PW*6) {
        for (y=PX + PW*4; y < PW*19; y += PW*6) 
            PUTXY(x, y);
    }

    for (x = 1; x <= 19; x++) {
        for (y = 1; y <= 19; y++) {
            if (BOARD[x][y]) {
                int color;

                color = BOARD[x][y] == BLACK_STONE ? BLACK_COLOR : WHITE_COLOR;
                PUT_STONE(x, y, color);
            }
        }
    }

EXAM91_END()   
 
END()

int CheckGame(int x, int y, int stone) {
    int px;
    int py;
    int count;

    // 가로 방향 검사
    px = x, py = y, count = 0;
    
    while (px > 1 && BOARD[px-1][y] == stone)
        px--;
    while (px <= 19 && BOARD[px++][y] == stone)
        count++;
    
    if (count == 5)
        return 1;       // 승리
    
    // 세로 방향 검사
    px = x, py = y, count = 0;
    
    while (py > 1 && BOARD[x][py-1] == stone) 
        py--;
    while (py <= 19 && BOARD[x][py++] == stone) 
        count++;
    
    if (count == 5)
        return 1;
    
    // 대각선 방향 검사 (왼쪽위 -> 오른쪽아래)
    px = x, py = y, count = 0;
    
    while (px > 1 && py > 1 && BOARD[px-1][py-1] == stone)
        px--, py--;
    

    while (px <= 19 && py <= 19 && BOARD[px++][py++] == stone)
        count++;
      
    if (count == 5)
        return 1;

    // 대각선 방향 검사 (오른쪽위 -> 왼쪽아래)
    px = x, py = y, count = 0;
    
    while (px < 19 && py > 1 && BOARD[px+1][py-1] == stone)
        px++, py--;
    

    while (px >= 1 && py <= 19 && BOARD[px--][py++] == stone)
        count++;
    
    if (count == 5)
        return 1;
    
    return 0;       // 아직 끝나지 않음
}