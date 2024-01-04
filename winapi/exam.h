#ifdef API__1
#define CIRCLE(x, y, w, h)                    \
    Ellipse(hdc, x, y, x+w, y+h);             \

#define EXAM89_BEGIN(timer)                     \
    if (message == WM_CREATE) {                   \
        SetTimer(hWnd, 1000, timer, NULL);    \
        return 0;                               \
    }                                           \
                                                \
    if (message == WM_LBUTTONDOWN) {             \
        if (MY_COLOR < 0xFFFFFF)               \
            MY_COLOR <<= 1;                     \
        else                                    \
            MY_COLOR = 1;                       \
        return 0;                               \
    }                                           \
                                                \
    if (message == WM_TIMER)  {                     \
        InvalidateRect(hWnd, NULL, TRUE);     \
        return 0;                               \
    }                                           \
                                                \
    if (message == WM_PAINT)                   \
    {                                           \
        RECT r;                                 \
        PAINTSTRUCT ps;                         \
        HBRUSH brush, oldBrush;                 \
                                                \
        GetClientRect(hWnd, &r);              \
        WIDTH  = r.right;                       \
        HEIGHT = r.bottom;                      \
        hdc = BeginPaint(hWnd, &ps);          \
                                                \
        brush = CreateSolidBrush(MY_COLOR);   \
        oldBrush = SelectObject(hdc, brush);  \
        {                                       \

#define EXAM89_END()                            \
        }                                       \
        SelectObject(hdc, oldBrush);          \
        EndPaint(hWnd, &ps);                  \
                                                \
        DeleteObject(brush);                  \
        return 0;                               \
    }                                           \

#elif defined API__2
#define CIRCLE(x, y, w, h)                    \
    Ellipse(hdc, x, y, x+w, y+h);             \

#define LINE(x1, y1, x2, y2)                  \
    MoveToEx(hdc, x1, y1, NULL);              \
    LineTo(hdc, x2, y2);                      \

#define PIXEL(x, y)                           \
    SetPixel(hdc, x, y, RGB(255,0,0));        \

#define EXAM90_BEGIN()                          \
    if (message == WM_LBUTTONDOWN)             \
    {                                           \
        if (MY_COLOR < 0xFFFFFF)               \
            MY_COLOR <<= 1;                     \
        else                                    \
            MY_COLOR = 1;                       \
        return 0;                               \
    }                                           \
                                                \
    if (message == WM_PAINT) {                    \
        RECT r;                                 \
        PAINTSTRUCT ps;                         \
        HBRUSH brush, oldBrush;                 \
                                                \
        GetClientRect(hWnd, &r);              \
        WIDTH  = r.right;                       \
        HEIGHT = r.bottom;                      \
        hdc = BeginPaint(hWnd, &ps);          \
                                                \
        brush = CreateSolidBrush(MY_COLOR);   \
        oldBrush = SelectObject(hdc, brush);  \
        {                                       \

  
#define EXAM90_END()                            \
        }                                       \
        SelectObject(hdc, oldBrush);          \
        EndPaint(hWnd, &ps);                  \
                                                \
        DeleteObject(brush);                  \
                                                \
        return 0;                               \
    }                                           \

#elif defined API__3
#define PUTXY(x, y)                           \
{                                               \
    HBRUSH brush, *oldBrush;                    \
                                                \
    brush = CreateSolidBrush(RGB(0,0,0));     \
    oldBrush = SelectObject(memdc, brush);    \
                                                \
    Ellipse(memdc, x-4, y-4, x+4, y+4);       \
                                                \
    SelectObject(memdc, oldBrush);            \
    DeleteObject(brush);                      \
}                                               \

#define RECTANGLE(x1, y1, x2, y2, color)      \
{                                               \
    HPEN pen, *oldPen;                          \
    HBRUSH brush, *oldBrush;                    \
                                                \
    pen    = CreatePen(PS_SOLID, 1, color);   \
    oldPen = SelectObject(memdc, pen);        \
                                                \
    brush    = CreateSolidBrush(color);       \
    oldBrush = SelectObject(memdc, brush);    \
                                                \
    Rectangle(memdc, x1, y1, x2, y2);         \
                                                \
    SelectObject(memdc, oldPen);              \
    SelectObject(memdc, oldBrush);            \
    DeleteObject(pen);                        \
    DeleteObject(brush);                      \
}                                               \


#define PUT_STONE(x, y, color)                        \
{                                                       \
    HBRUSH brush, *oldBrush;                            \
                                                        \
    brush = CreateSolidBrush(color);                  \
    oldBrush = SelectObject(memdc, brush);            \
                                                        \
    Ellipse(memdc, PX+((x-1)*PW)-(PW*2)/4+1,           \
                    PY+((y-1)*PW)-(PW*2)/4+1,           \
                    PX+((x-1)*PW)+(PW*2)/4-1,           \
                    PY+((y-1)*PW)+(PW*2)/4-1);         \
                                                        \
    SelectObject(memdc, oldBrush);                    \
    DeleteObject(brush);                              \
}                                                       \


#define LINE(x1, y1, x2, y2)                          \
    MoveToEx(memdc, x1, y1, NULL);                    \
    LineTo  (memdc, x2, y2);                          \


#define PIXEL(x, y)                                   \
    SetPixel(memdc, x, y, RGB(255,0,0));              \

#define EXAM91_BEGIN()                                              \
    if (message == WM_CREATE)                                      \
    {                                                               \
        SetTimer(hWnd, 1000, 100, NULL);                          \
        return 0;                                                   \
    }                                                               \
                                                                    \
    if (message == WM_LBUTTONDOWN)                                 \
    {                                                               \
        int x, y;                                                   \
        RECT r;                                                     \
        POINT pt;                                                   \
        static int game_stone = BLACK_STONE;                        \
                                                                    \
        pt.x = LOWORD(lParam);                                    \
        pt.y = HIWORD(lParam);                                    \
                                                                    \
        for (x=PX; x <PX+(PW*19); x+=PW)                            \
        {                                                           \
            for (y=PY; y <PY+(PW*19); y+=PW)                        \
            {                                                       \
                r.left   = x - (PW/2) + 1;                          \
                r.top    = y - (PW/2) + 1;                          \
                r.right  = x + (PW/2) - 1;                          \
                r.bottom = y + (PW/2) - 1;                          \
                                                                    \
                if (PtInRect(&r, pt))                            \
                {                                                   \
                    int px, py;                                     \
                                                                    \
                    px = (x-PX)/PW+1;                               \
                    py = (y-PY)/PW+1;                               \
                                                                    \
                    if (BOARD[px][py]) {                          \
                        MessageBox(hWnd, "돌이 있음",              \
                                          "게임 정보", MB_OK);     \
                        return 0;                                   \
                    }                                               \
                                                                    \
                    BOARD[px][py] = game_stone;                     \
                                                                    \
                    if (CheckGame(px, py, game_stone))             \
                    {                                               \
                        if (game_stone == BLACK_STONE)             \
                            MessageBox(hWnd, "흑 승리", "게임 종료", MB_OK);     \
                        else                                        \
                            MessageBox(hWnd, "백 승리", "게임 종료", MB_OK);     \
                                                                    \
                        game_stone = BLACK_STONE;                   \
                        memset(BOARD, 0, sizeof(BOARD));          \
                        InvalidateRect(hWnd, NULL, FALSE);        \
                        return 0;                                   \
                    }                                               \
                                                                    \
                    if (game_stone == BLACK_STONE)                 \
                        game_stone = WHITE_STONE;                   \
                    else                                            \
                        game_stone = BLACK_STONE;                   \
                                                                    \
                    return 0;                                       \
                }                                                   \
            }                                                       \
        }                                                           \
                                                                    \
        return 0;                                                   \
    }                                                               \
                                                                    \
    if (message == WM_TIMER) {                                     \
        InvalidateRect(hWnd, NULL, FALSE);                        \
        return 0;                                                   \
    }                                                               \
                                                                    \
    if (message == WM_PAINT) {                                                               \
        RECT r;                                                     \
        PAINTSTRUCT ps;                                             \
        HBITMAP bitmap, oldBitmap;                                  \
	    HDC memdc;                                                  \
                                                                    \
        GetClientRect(hWnd, &r);                                  \
        WIDTH  = r.right;                                           \
        HEIGHT = r.bottom;                                          \
        hdc = BeginPaint(hWnd, &ps);                              \
                                                                    \
        bitmap = CreateCompatibleBitmap(hdc, r.right, r.bottom);  \
                                                                    \
        memdc = CreateCompatibleDC(hdc);                          \
        oldBitmap = (HBITMAP)SelectObject(memdc, bitmap);         \
	    FillRect(memdc, &r, GetSysColorBrush(COLOR_WINDOW));      \
                                                                    \
        {                                                           \

  
#define EXAM91_END()                                                 \
        }                                                            \
                                                                     \
        BitBlt(hdc, 0, 0, r.right, r.bottom, memdc, 0, 0, SRCCOPY);\
                                                                     \
        SelectObject(memdc, oldBitmap);                            \
        DeleteObject(bitmap);                                      \
        DeleteDC(memdc);                                           \
                                                                     \
        EndPaint(hWnd, &ps);                                       \
        return 0;                                                    \
    }                                                                \


#elif defined API__4
#define CLEAN_SOUND()                           \
{                                               \
}

#define RECTANGLE(x1, y1, x2, y2, color)      \
{                                               \
    HPEN pen, oldPen;                           \
    HBRUSH brush, oldBrush;                     \
                                                \
    pen    = CreatePen(PS_SOLID, 1, color);   \
    oldPen = SelectObject(memdc, pen);        \
                                                \
    brush    = CreateSolidBrush(color);       \
    oldBrush = SelectObject(memdc, brush);    \
                                                \
    Rectangle(memdc, x1, y1, x2, y2);         \
                                                \
    SelectObject(memdc, oldPen);              \
    SelectObject(memdc, oldBrush);            \
    DeleteObject(pen);                        \
    DeleteObject(brush);                      \
}                                               \

#define DISPLAY(x, y, str, h)                             \
{                                                           \
	LOGFONT logfont;                                        \
    HFONT font, oldFont;                                    \
                                                            \
	logfont.lfHeight		 = -h;                          \
	logfont.lfWidth			 = 0;                           \
	logfont.lfEscapement	 = 0;                           \
	logfont.lfOrientation	 = 0;                           \
	logfont.lfWeight		 = FW_BOLD;                     \
	logfont.lfItalic		 = FALSE;                       \
	logfont.lfUnderline		 = FALSE;                       \
	logfont.lfStrikeOut		 = FALSE;                       \
	logfont.lfCharSet		 = DEFAULT_CHARSET;             \
	logfont.lfOutPrecision	 = OUT_CHARACTER_PRECIS;        \
	logfont.lfClipPrecision	 = CLIP_CHARACTER_PRECIS;       \
	logfont.lfQuality		 = DEFAULT_QUALITY;             \
	logfont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;   \
	strcpy(logfont.lfFaceName, "Verdana");                \
                                                            \
	font = CreateFontIndirect(&logfont);                  \
	oldFont = SelectObject(memdc, font);                  \
                                                            \
    SetBkMode(memdc, TRANSPARENT);                        \
    SetTextColor(memdc, RGB(255,255,128));                \
                                                            \
    TextOut(memdc, x, y, str, strlen(str));               \
                                                            \
    SelectObject(memdc, oldFont);                         \
    DeleteObject(font);                                   \
}

#define LINE(x1, y1, x2, y2)                          \
    MoveToEx(memdc, x1, y1, NULL);                    \
    LineTo  (memdc, x2, y2);                          \


#define PIXEL(x, y)                                   \
    SetPixel(memdc, x, y, RGB(255,0,0));              \


#define BRICK_DRAW(x1, y1, brick)                       \
{                                                         \
    HPEN pen, oldPen;                                     \
    RECT r;                                               \
    COLORREF color[] =                                    \
    {                                                     \
        RGB( 0,  0,  0),                                 \
        RGB( 0,225,225),                                 \
        RGB(255, 64,255),                                 \
        RGB(255,160, 64),                                 \
        RGB(47, 47,255),                                 \
        RGB(64,255, 64),                                 \
        RGB(255, 32, 32),                                 \
        RGB(255,255, 64),                                 \
    };                                                    \
                                                          \
    r.left   = PX+((x1)*PW);                              \
    r.top    = PY+((y1)*PW);                              \
    r.right  = PX+((x1)*PW+PW-1);                         \
    r.bottom = PY+((y1)*PW+PW-1);                         \
                                                          \
    /* 1 : 라인 */                                        \
    pen    = CreatePen(PS_SOLID, 1, color[brick]);      \
    oldPen = SelectObject(memdc, pen);                  \
    SelectObject(memdc, GetStockObject(NULL_BRUSH));    \
                                                          \
    Rectangle(memdc, r.left, r.top, r.right, r.bottom); \
                                                          \
    MoveToEx(memdc, r.left , r.top, NULL);              \
    LineTo  (memdc, r.right, r.bottom);                 \
                                                          \
    MoveToEx(memdc, r.left , r.bottom-1, NULL);         \
    LineTo  (memdc, r.right, r.top);                    \
                                                          \
    SelectObject(memdc, oldPen);                        \
    DeleteObject(pen);                                  \
}                                                         \
  

#define GAME_OVER() {                                                 \
    char szMessage[] = "게임을 다시 할까요?";                       \
    char szCaption[] = "테트리스";                                  \
    int  ret;                                                       \
    int  x, y;                                                      \
                                                                    \
	score = 0;                                                      \
    KillTimer(hMainWnd, 1);                                       \
                                                                    \
    ret = MessageBox(hMainWnd, szMessage, szCaption, MB_YESNO);   \
                                                                    \
    if (ret == IDYES)                                              \
    {                                                               \
		game_start = 1;                                             \
                                                                    \
        memset(BOARD, 0, sizeof(BOARD));                          \
                                                                    \
        for (x = 0; x < BW+2; x++)                                     \
        {                                                           \
			for (y = 0; y < BH+2; y++)                                 \
            {                                                       \
				if (x == 0 || y == 0 || x == BW+1 || y == BH+1)    \
                {                                                   \
                    BOARD[x][y] = 1  ;                              \
                }                                                   \
            }                                                       \
		}                                                           \
                                                                    \
        SetTimer(hMainWnd, 1, MY_NEW_TIMER, NULL);                \
        MY_TIMER = MY_NEW_TIMER;                                    \
        MakeBrick();                                                \
    }                                                               \
    else                                                            \
    {                                                               \
		ShowWindow(hBtnWnd, SW_SHOW);                             \
		SetWindowText(hBtnWnd, "게임 시작");                      \
		game_start = 0;                                             \
    }                                                               \
}                                                                   \

  
#define NEXT_BRICK_DRAW(x, y, brick)                    \
{                                                         \
    HPEN pen, oldPen;                                     \
    RECT r;                                               \
    COLORREF color[] =                                    \
    {                                                     \
        RGB( 0,  0,  0),                                 \
        RGB( 0,225,225),                                 \
        RGB(255, 64,255),                                 \
        RGB(255,160, 64),                                 \
        RGB(47, 47,255),                                 \
        RGB(64,255, 64),                                 \
        RGB(255, 32, 32),                                 \
        RGB(255,255, 64),                                 \
    };                                                    \
                                                          \
    r.left   = 45+((x)*PW);                               \
    r.top    = 70+((y)*PW);                               \
    r.right  = 65+((x)*PW-1);                             \
    r.bottom = 90+((y)*PW-1);                             \
                                                          \
    /* 1 : 라인 */                                        \
    pen    = CreatePen(PS_SOLID, 1, color[brick]);      \
    oldPen = SelectObject(memdc, pen);                  \
    SelectObject(memdc, GetStockObject(NULL_BRUSH));    \
                                                          \
    Rectangle(memdc, r.left, r.top, r.right, r.bottom); \
                                                          \
    SelectObject(memdc, oldPen);                        \
    DeleteObject(pen);                                  \
} 

#define BRICK_SHADOW(x, y, brick)                       \
{                                                         \
    HPEN pen, oldPen;                                     \
    COLORREF color[] =                                    \
    {                                                     \
        RGB(255,221,221),                                 \
    };                                                    \
                                                          \
    pen    = CreatePen(PS_SOLID, 1, color[0]);          \
    oldPen = SelectObject(memdc, pen);                  \
    SelectObject(memdc, GetStockObject(NULL_BRUSH));    \
                                                          \
    Rectangle(memdc, PX+((x)*PW)   , PY+((y)*PW),        \
                      PX+((x)*PW+19), PY+((y)*PW)+19);   \
                                                          \
    SelectObject(memdc, oldPen);                        \
    DeleteObject(pen);                                  \
} 

#define EXAM92_BEGIN(timer)                                             \
    if (message == WM_CREATE)                                          \
    {                                                                   \
        hBtnWnd = CreateWindow("BUTTON", "게임 시작",                  \
                WS_CHILD | WS_VISIBLE |                                 \
                BS_PUSHBUTTON | WS_CLIPCHILDREN,                        \
                25, PY*(15*19), 80, 30, hWnd, (HMENU)0, hInst, NULL);  \
        srand(time(NULL));                                            \
        MY_TIMER = MY_NEW_TIMER = timer;                                \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (message == WM_COMMAND)                                         \
    {                                                                   \
	    if (LOWORD(wParam) == 0 && !game_start)                        \
		{                                                               \
            int x, y;                                                   \
                                                                        \
            SetTimer(hWnd, 1, MY_TIMER, NULL);                        \
		    ShowWindow(hBtnWnd, SW_HIDE);                             \
		    game_start = 1;                                             \
                                                                        \
            memset(BOARD, 0, sizeof(BOARD));                          \
                                                                        \
            for (x = 0; x < BW+2; x++)                                     \
            {                                                           \
				for (y = 0; y < BH+2; y++)                                 \
                {                                                       \
					if (x == 0 || y == 0 || x == BW+1 || y == BH+1)    \
                    {                                                   \
                        BOARD[x][y] = 1;                                \
                    }                                                   \
                }                                                       \
			}                                                           \
                                                                        \
            MakeBrick();                                                \
                                                                        \
            InvalidateRect(hWnd, NULL, FALSE);                        \
        }                                                               \
	    else if (game_start)                                           \
		{                                                               \
            KillTimer(hWnd, 1);                                       \
		    SetWindowText(hBtnWnd, "게임 시작");                      \
		    game_start = 0;                                             \
        }                                                               \
		return 0;                                                       \
    }                                                                   \
                                                                        \
    if (message == WM_TIMER)                                           \
    {                                                                   \
        MoveBrick();                                                    \
        InvalidateRect(hWnd, NULL, FALSE);                            \
                                                                        \
        if (lines % 15 == 0)                                           \
        {                                                               \
            static int llines = 0;                                      \
                                                                        \
            if (llines != lines)                                       \
            {                                                           \
                if (MY_TIMER > 200)                                    \
                {                                                       \
                    MY_TIMER -= 70;                                     \
                }                                                       \
                else                                                    \
                {                                                       \
                    MY_TIMER -= 5;                                      \
                    if (MY_TIMER < 70)                                 \
                    {                                                   \
                        MY_TIMER = 50;                                  \
                    }                                                   \
                }                                                       \
                                                                        \
                level++;                                                \
                KillTimer(hMainWnd, 1);                               \
                SetTimer (hMainWnd, 1, MY_TIMER, NULL);               \
            }                                                           \
                                                                        \
            llines = lines;                                             \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
                                                                        \
	if (message == WM_KEYDOWN)                                         \
    {                                                                   \
		if (!game_start)                                               \
            return 0;                                                   \
                                                                        \
		switch(wParam)                                                \
        {                                                               \
		case VK_LEFT:                                                   \
			if (IsMoveable(BX-1, BY, Brick, Rotate) == EMPTY)        \
				BX--;                                                   \
			break;                                                      \
                                                                        \
		case VK_RIGHT:                                                  \
			if (IsMoveable(BX+1, BY, Brick, Rotate) == EMPTY)        \
				BX++;                                                   \
			break;                                                      \
                                                                        \
		case VK_UP:                                                     \
            {                                                           \
                int tmp = Rotate == 3 ? 0 : Rotate + 1;                 \
			    if (IsMoveable(BX, BY, Brick, tmp) == EMPTY)          \
				    Rotate = tmp;                                       \
            }                                                           \
			break;                                                      \
                                                                        \
		case VK_DOWN:                                                   \
			MoveBrick();                                                \
			break;                                                      \
                                                                        \
		case VK_SPACE:                                                  \
			while (MoveBrick())                                        \
            {                                                           \
                InvalidateRect(hWnd, NULL, FALSE);                    \
	            UpdateWindow(hWnd);                                   \
            }                                                           \
			break;                                                      \
		}                                                               \
                                                                        \
        InvalidateRect(hWnd, NULL, FALSE);                            \
                                                                        \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (message == WM_PAINT)                                           \
    {                                                                   \
        RECT r;                                                         \
        PAINTSTRUCT ps;                                                 \
        HBITMAP bitmap, oldBitmap;                                      \
	    HDC memdc;                                                      \
                                                                        \
        GetClientRect(hWnd, &r);                                      \
        WIDTH  = r.right;                                               \
        HEIGHT = r.bottom;                                              \
        hdc = BeginPaint(hWnd, &ps);                                  \
                                                                        \
        bitmap = CreateCompatibleBitmap(hdc, r.right, r.bottom);      \
                                                                        \
        memdc = CreateCompatibleDC(hdc);                              \
        oldBitmap = (HBITMAP)SelectObject(memdc, bitmap);             \
	    FillRect(memdc, &r, GetSysColorBrush(COLOR_WINDOW));          \
                                                                        \
        {                                                               \

  
#define EXAM92_END()                                                 \
        }                                                            \
                                                                     \
        BitBlt(hdc, 0, 0, r.right, r.bottom, memdc, 0, 0, SRCCOPY);\
                                                                     \
        SelectObject(memdc, oldBitmap);                            \
        DeleteObject(bitmap);                                      \
        DeleteDC(memdc);                                           \
                                                                     \
        EndPaint(hWnd, &ps);                                       \
        return 0;                                                    \
    }                                                                \

#elif defined API__5
#define MSG(msg)                                                \
{                                                               \
    MessageBox(hMainWnd, msg, "테트리스", MB_OK);             \
}                                                               \

#define ERROR_SOCKET(msg)                                       \
{                                                               \
    LPVOID lpMsgBuf;                                            \
                                                                \
    FormatMessage(                                             \
        FORMAT_MESSAGE_ALLOCATE_BUFFER |                        \
        FORMAT_MESSAGE_FROM_SYSTEM,                             \
        NULL, WSAGetLastError(),                                \
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),              \
        (LPTSTR)&lpMsgBuf, 0, NULL);                            \
                                                                \
    MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);   \
                                                                \
    LocalFree(lpMsgBuf);                                      \
}                                                               \


#define CLEAN_SOUND()                           \
{                                               \
}

#define RECTANGLE(x1, y1, x2, y2, color)      \
{                                               \
    HPEN pen, oldPen;                           \
    HBRUSH brush, oldBrush;                     \
                                                \
    pen    = CreatePen(PS_SOLID, 1, color);   \
    oldPen = SelectObject(memdc, pen);        \
                                                \
    brush    = CreateSolidBrush(color);       \
    oldBrush = SelectObject(memdc, brush);    \
                                                \
    Rectangle(memdc, x1, y1, x2, y2);         \
                                                \
    SelectObject(memdc, oldPen);              \
    SelectObject(memdc, oldBrush);            \
    DeleteObject(pen);                        \
    DeleteObject(brush);                      \
}                                               \

#define DISPLAY(x, y, str, h)                             \
{                                                           \
    LOGFONT logfont;                                        \
    HFONT font, oldFont;                                    \
                                                            \
    logfont.lfHeight		 = -h;                          \
    logfont.lfWidth			 = 0;                           \
    logfont.lfEscapement	 = 0;                           \
    logfont.lfOrientation	 = 0;                           \
    logfont.lfWeight		 = FW_BOLD;                     \
    logfont.lfItalic		 = FALSE;                       \
    logfont.lfUnderline		 = FALSE;                       \
    logfont.lfStrikeOut		 = FALSE;                       \
    logfont.lfCharSet		 = DEFAULT_CHARSET;             \
    logfont.lfOutPrecision	 = OUT_CHARACTER_PRECIS;        \
    logfont.lfClipPrecision	 = CLIP_CHARACTER_PRECIS;       \
    logfont.lfQuality		 = DEFAULT_QUALITY;             \
    logfont.lfPitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;   \
    strcpy(logfont.lfFaceName, "Verdana");                \
                                                            \
    font = CreateFontIndirect(&logfont);                  \
    oldFont = SelectObject(memdc, font);                  \
                                                            \
    SetBkMode(memdc, TRANSPARENT);                        \
    SetTextColor(memdc, RGB(255,255,128));                \
                                                            \
    TextOut(memdc, x, y, str, strlen(str));               \
                                                            \
    SelectObject(memdc, oldFont);                         \
    DeleteObject(font);                                   \
}

#define LINE(x1, y1, x2, y2)                          \
    MoveToEx(memdc, x1, y1, NULL);                    \
    LineTo  (memdc, x2, y2);                          \


#define PIXEL(x, y)                                   \
    SetPixel(memdc, x, y, RGB(255,0,0));              \


#define BRICK_DRAW(x1, y1, brick)                       \
{                                                         \
    HPEN pen, oldPen;                                     \
    RECT r;                                               \
    COLORREF color[] =                                    \
    {                                                     \
        RGB( 0,  0,  0),                                 \
        RGB( 0,225,225),                                 \
        RGB(255, 64,255),                                 \
        RGB(255,160, 64),                                 \
        RGB(47, 47,255),                                 \
        RGB(64,255, 64),                                 \
        RGB(255, 32, 32),                                 \
        RGB(255,255, 64),                                 \
        RGB(128,128,128),                                 \
    };                                                    \
                                                          \
    r.left   = PX+((x1)*PW);                              \
    r.top    = PY+((y1)*PW);                              \
    r.right  = PX+((x1)*PW+PW-1);                         \
    r.bottom = PY+((y1)*PW+PW-1);                         \
                                                          \
    /* 1 : 라인 */                                        \
    pen    = CreatePen(PS_SOLID, 1, color[brick]);      \
    oldPen = SelectObject(memdc, pen);                  \
    SelectObject(memdc, GetStockObject(NULL_BRUSH));    \
                                                          \
    Rectangle(memdc, r.left, r.top, r.right, r.bottom); \
                                                          \
    MoveToEx(memdc, r.left , r.top, NULL);              \
    LineTo  (memdc, r.right, r.bottom);                 \
                                                          \
    MoveToEx(memdc, r.left , r.bottom-1, NULL);         \
    LineTo  (memdc, r.right, r.top);                    \
                                                          \
    SelectObject(memdc, oldPen);                        \
    DeleteObject(pen);                                  \
}                                                         \
  

#define GAME_OVER()                                                 \
{                                                                   \
    char szMessage[] = "게임을 다시 할까요?";                       \
    char szCaption[] = "테트리스";                                  \
    int  ret;                                                       \
    int  x, y;                                                      \
                                                                    \
    score = 10000;                                                  \
    lines = 0;                                                      \
    level = 0;                                                      \
    KillTimer(hMainWnd, 1);                                       \
                                                                    \
    ret = MessageBox(hMainWnd, szMessage, szCaption, MB_YESNO);   \
                                                                    \
    if (ret == IDYES)                                              \
    {                                                               \
        int tmp;                                                    \
        game_start = 1;                                             \
                                                                    \
        memset(BOARD, 0, sizeof(BOARD));                          \
        for (x = 0; x < BW+2; x++)                                     \
        {                                                           \
            for (y = 0; y < BH+2; y++)                                 \
                if (x == 0 || y == 0 || x == BW+1 || y == BH+1)    \
                    BOARD[x][y] = 1  ;                              \
        }                                                           \
                                                                    \
        if (m_nMode == SERVERON)                                   \
            while (recv(g_cs, (char*)&tmp, 4, 0) > 0);           \
        else                                                        \
            while (recv(g_s, (char*)&tmp, 4, 0) > 0);            \
                                                                    \
        SetTimer(hMainWnd, 1, MY_NEW_TIMER, NULL);                \
        MY_TIMER = MY_NEW_TIMER;                                    \
                                                                    \
        MakeBrick();                                                \
    }                                                               \
    else                                                            \
    {                                                               \
        ShowWindow(hBtnWnd, SW_SHOW);                             \
        ShowWindow(hSrvWnd, SW_SHOW);                             \
        ShowWindow(hConWnd, SW_SHOW);                             \
        SetWindowText(hBtnWnd, "게임 시작");                      \
        game_start = 0;                                             \
    }                                                               \
}                                                                   \

  
#define NEXT_BRICK_DRAW(x, y, brick)                    \
{                                                         \
    HPEN pen, oldPen;                                     \
    RECT r;                                               \
    COLORREF color[] =                                    \
    {                                                     \
        RGB( 0,  0,  0),                                 \
        RGB( 0,225,225),                                 \
        RGB(255, 64,255),                                 \
        RGB(255,160, 64),                                 \
        RGB(47, 47,255),                                 \
        RGB(64,255, 64),                                 \
        RGB(255, 32, 32),                                 \
        RGB(255,255, 64),                                 \
    };                                                    \
                                                          \
    r.left   = 45+((x)*PW);                               \
    r.top    = 70+((y)*PW);                               \
    r.right  = 65+((x)*PW-1);                             \
    r.bottom = 90+((y)*PW-1);                             \
                                                          \
    /* 1 : 라인 */                                        \
    pen    = CreatePen(PS_SOLID, 1, color[brick]);      \
    oldPen = SelectObject(memdc, pen);                  \
    SelectObject(memdc, GetStockObject(NULL_BRUSH));    \
                                                          \
    Rectangle(memdc, r.left, r.top, r.right, r.bottom); \
                                                          \
    SelectObject(memdc, oldPen);                        \
    DeleteObject(pen);                                  \
} 

#define BRICK_SHADOW(x, y, brick)                       \
{                                                         \
    HPEN pen, oldPen;                                     \
    COLORREF color[] = { RGB(255,221,221), };             \
                                                          \
    pen    = CreatePen(PS_SOLID, 1, color[0]);          \
    oldPen = SelectObject(memdc, pen);                  \
    SelectObject(memdc, GetStockObject(NULL_BRUSH));    \
                                                          \
    Rectangle(memdc, PX+((x)*PW)   , PY+((y)*PW),        \
                      PX+((x)*PW+19), PY+((y)*PW)+19);   \
                                                          \
    SelectObject(memdc, oldPen);                        \
    DeleteObject(pen);                                  \
} 

#define EXAM92_BEGIN(timer)                                             \
    if (message == WM_CREATE)                                          \
    {                                                                   \
        hBtnWnd = CreateWindow("BUTTON", "게임 시작",                  \
            WS_CHILD | WS_VISIBLE |                                     \
            BS_PUSHBUTTON | WS_CLIPCHILDREN,                            \
            25, PY*(15*19), 80, 30, hWnd, (HMENU)0, hInst, NULL);      \
        hSrvWnd = CreateWindow("BUTTON", "서버 시작",                  \
            WS_CHILD | WS_VISIBLE |                                     \
            BS_PUSHBUTTON | WS_CLIPCHILDREN,                            \
            25, PY*(17*19), 80, 30, hWnd, (HMENU)1, hInst, NULL);      \
        hConWnd = CreateWindow("BUTTON", "서버 접속",                  \
            WS_CHILD | WS_VISIBLE |                                     \
            BS_PUSHBUTTON | WS_CLIPCHILDREN,                            \
            25, PY*(19*19), 80, 30, hWnd, (HMENU)2, hInst, NULL);      \
        srand(time(NULL));                                            \
        MY_TIMER = MY_NEW_TIMER = timer;                                \
        SocketInit();                                                   \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (message == WM_COMMAND)                                         \
    {                                                                   \
        if (LOWORD(wParam) == 0 && !game_start)                        \
        {                                                               \
            int x, y;                                                   \
                                                                        \
            SetTimer(hWnd, 1, MY_TIMER, NULL);                        \
            ShowWindow(hBtnWnd, SW_HIDE);                             \
            ShowWindow(hSrvWnd, SW_HIDE);                             \
            ShowWindow(hConWnd, SW_HIDE);                             \
            game_start = 1;                                             \
                                                                        \
            memset(BOARD, 0, sizeof(BOARD));                          \
            for (x = 0; x < BW+2; x++)                                     \
            {                                                           \
                for (y = 0; y < BH+2; y++)                                 \
                    if (x == 0 || y == 0 || x == BW+1 || y == BH+1)    \
                        BOARD[x][y] = 1  ;                              \
            }                                                           \
                                                                        \
            MakeBrick();                                                \
            InvalidateRect(hWnd, NULL, FALSE);                        \
        }                                                               \
	                                                                    \
        if (LOWORD(wParam) == 1)                                       \
        {                                                               \
            SocketServer();                                             \
            EnableWindow(hSrvWnd, FALSE);                             \
            EnableWindow(hConWnd, FALSE);                             \
        }                                                               \
	                                                                    \
        if (LOWORD(wParam) == 2)                                       \
        {                                                               \
            SocketConnect();                                            \
            EnableWindow(hSrvWnd, FALSE);                             \
            EnableWindow(hConWnd, FALSE);                             \
        }                                                               \
                                                                        \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (message == WM_TIMER)                                           \
    {                                                                   \
        MoveBrick();                                                    \
        InvalidateRect(hWnd, NULL, FALSE);                            \
        SocketAccept();                                                 \
                                                                        \
        if (lines % 15 == 0)                                           \
        {                                                               \
            static int llines = 0;                                      \
                                                                        \
            if (llines != lines)                                       \
            {                                                           \
                if (MY_TIMER > 200)                                    \
                    MY_TIMER -= 70;                                     \
                else                                                    \
                {                                                       \
                    MY_TIMER -= 5;                                      \
                    if (MY_TIMER < 70)                                 \
                        MY_TIMER = 50;                                  \
                }                                                       \
                                                                        \
                level++;                                                \
                KillTimer(hMainWnd, 1);                               \
                SetTimer (hMainWnd, 1, MY_TIMER, NULL);               \
            }                                                           \
                                                                        \
            llines = lines;                                             \
        }                                                               \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (message == WM_KEYDOWN)                                         \
    {                                                                   \
        if (!game_start)                                               \
            return 0;                                                   \
                                                                        \
        switch(wParam)                                                \
        {                                                               \
        case VK_LEFT:                                                   \
            if (IsMoveable(BX-1, BY, Brick, Rotate) == EMPTY)        \
                BX--;                                                   \
            break;                                                      \
                                                                        \
        case VK_RIGHT:                                                  \
            if (IsMoveable(BX+1, BY, Brick, Rotate) == EMPTY)        \
                BX++;                                                   \
            break;                                                      \
                                                                        \
        case VK_UP:                                                     \
            {                                                           \
                int tmp = Rotate == 3 ? 0 : Rotate + 1;                 \
                if (IsMoveable(BX, BY, Brick, tmp) == EMPTY)          \
                    Rotate = tmp;                                       \
            }                                                           \
            break;                                                      \
                                                                        \
        case VK_DOWN:                                                   \
            MoveBrick();                                                \
            break;                                                      \
                                                                        \
        case VK_SPACE:                                                  \
            while (MoveBrick())                                        \
            {                                                           \
                InvalidateRect(hWnd, NULL, FALSE);                    \
                UpdateWindow(hWnd);                                   \
            }                                                           \
            break;                                                      \
        }                                                               \
                                                                        \
        InvalidateRect(hWnd, NULL, FALSE);                            \
                                                                        \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (message == WM_PAINT)                                           \
    {                                                                   \
        RECT r;                                                         \
        PAINTSTRUCT ps;                                                 \
        HBITMAP bitmap, oldBitmap;                                      \
        HDC memdc;                                                      \
                                                                        \
        GetClientRect(hWnd, &r);                                      \
        WIDTH  = r.right;                                               \
        HEIGHT = r.bottom;                                              \
        hdc = BeginPaint(hWnd, &ps);                                  \
                                                                        \
        bitmap = CreateCompatibleBitmap(hdc, r.right, r.bottom);      \
                                                                        \
        memdc = CreateCompatibleDC(hdc);                              \
        oldBitmap = (HBITMAP)SelectObject(memdc, bitmap);             \
        FillRect(memdc, &r, GetSysColorBrush(COLOR_WINDOW));          \
                                                                        \
        {                                                               \

  
#define EXAM92_END()                                                 \
        }                                                            \
                                                                     \
        BitBlt(hdc, 0, 0, r.right, r.bottom, memdc, 0, 0, SRCCOPY);\
                                                                     \
        SelectObject(memdc, oldBitmap);                            \
        DeleteObject(bitmap);                                      \
        DeleteDC(memdc);                                           \
                                                                     \
        EndPaint(hWnd, &ps);                                       \
        return 0;                                                    \
    }                                                                \

#endif