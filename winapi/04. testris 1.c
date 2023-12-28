#define EXAM92
#include "api.h"

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
int lines = 0;          // 파괴된 라인 수

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


BEGIN()

int  x, y;
char buff[100];

EXAM92_BEGIN(1000)

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
    for(y=1; y<BH+1; y++)
    {
        for(x=1; x<BW+1; x++)
        {
            if(BOARD[x][y])
            {
                BRICK_DRAW(x-1, y-1, BOARD[x][y]);
            }
        }
    }

    // 현재 이동 중인 벽돌을 그립니다.
    if(game_start) 
    {
        int i;
        for(i=0; i<4; i++) 
        {
            int x, y;

            x = BX + BRICK_SHAPE[Brick][Rotate][i].x;
            y = BY + BRICK_SHAPE[Brick][Rotate][i].y;

            BRICK_DRAW(x-1, y-1, Brick+1);
        }
    }

    // 현재 이동 중인 벽돌의 그림자를 그립니다.
    if(game_start) 
    {
        int i;
        for(y=BY+1; y<BH+2; y++) 
        {
            if(IsMoveable(BX, y, Brick, Rotate) != EMPTY)
            {
                int by = y-1;
                for(i=0; i<4; i++) 
                {
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
    if(game_start) 
    {
        int i;
        for(i=0; i<4; i++) 
        {
            int x, y;

            x = BRICK_SHAPE[Next_Brick][0][i].x;
            y = BRICK_SHAPE[Next_Brick][0][i].y;

            NEXT_BRICK_DRAW(x, y, Next_Brick+1);
        }
    }

EXAM92_END()   
 
END()

void MakeBrick(void)
{
    int blocks = sizeof(BRICK_SHAPE)/sizeof(BRICK_SHAPE[0]);
    
    Brick = Next_Brick;
    Next_Brick = rand() % (blocks + 1);
    
    if(Next_Brick == blocks)
    {
        Next_Brick = 5;     // 긴 막대
    }

    BX = 5;
    BY = 2;
    Rotate = 0;
}

int MoveBrick(void)
{
    if(IsMoveable(BX, BY+1, Brick, Rotate) != EMPTY)
    {
        CheckGame();
        MakeBrick();
        
        if(IsMoveable(BX, BY+1, Brick, Rotate) != EMPTY)
        {
            GAME_OVER();
        }
        
        return 0;
    }

    BY++;

    return 1;
}

int IsMoveable(int bx, int by, int brick, int rotate)
{
    int i, empty = EMPTY;
    int x, y;

    for(i=0; i<4; i++) 
    {
        x = bx + BRICK_SHAPE[brick][rotate][i].x;
        y = by + BRICK_SHAPE[brick][rotate][i].y;

        empty = max(empty, BOARD[x][y]);
    }

    return empty;
}

int CheckGame(void)
{
    int i, j;
    int bx, by;
    int count = 0;

    for(i=0; i<4; i++) 
    {
        bx = BX + BRICK_SHAPE[Brick][Rotate][i].x;
        by = BY + BRICK_SHAPE[Brick][Rotate][i].y;

        // 이동 중인 블록을 배열에 저장 
        BOARD[bx][by] = Brick+1;
    }

    Brick = -1;

    for(by=1; by<BH+1; by++) 
    {
        for(bx=1; bx<BW+1; bx++)  // 한 줄이 다 찼는지 검사
        {
            if(BOARD[bx][by] == EMPTY) break;
        }

        if(bx == 11)              // 한 줄이 다 찬 경우
        {
            count++;

            for(i=by; i>2; i--) 
            {
                for(j=1; j<BW+1; j++)
                {
                    // 다 찬 블록을 제거하고 한 칸씩 아래로 이동
                    BOARD[j][i] = BOARD[j][i-1];
                }
            }
        }
    }

    score += count * 1234 + (count/2) * 5678;

    if(count)
    {
        lines += count;
        CLEAN_SOUND();
    }

    return 0;
}