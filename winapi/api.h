#ifndef __API_H__
#define __API_H__

#include <windows.h>
#include <winsock2.h>

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

HINSTANCE hInst;
HDC hdc;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int WIDTH, HEIGHT;
int MY_COLOR = RGB(0,255,0);




#ifdef EXAM89
#define BEGIN() int WINAPI WinMain(                                    \
        HINSTANCE hInstance, HINSTANCE hPrevInstance,                   \
        LPSTR     lpCmdLine,                                            \
        int       nCmdShow)                                            \
{                                                                       \
	WNDCLASSEX wcex;                                                    \
    HWND hWnd;                                                          \
	MSG msg;                                                            \
                                                                        \
	wcex.cbSize = sizeof(WNDCLASSEX);                                 \
                                                                        \
	wcex.style			= CS_HREDRAW | CS_VREDRAW;                      \
	wcex.lpfnWndProc	= (WNDPROC) WndProc;                            \
	wcex.cbClsExtra		= 0;                                            \
	wcex.cbWndExtra		= 0;                                            \
	wcex.hInstance		= hInstance;                                    \
	wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);        \
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                  \
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                     \
	wcex.lpszMenuName	= NULL;                                         \
	wcex.lpszClassName	= "C-Guide";                                    \
	wcex.hIconSm		= LoadIcon(wcex.hInstance, IDI_APPLICATION);  \
                                                                        \
	RegisterClassEx(&wcex);                                           \
                                                                        \
    hInst = hInstance;                                                  \
                                                                        \
    hWnd = CreateWindow("C-Guide",                                     \
                         "공튀기기",                                    \
                         WS_OVERLAPPED     |                            \
                         WS_CAPTION        |                            \
                         WS_SYSMENU        |                            \
                         WS_MINIMIZEBOX    |                            \
                         WS_MAXIMIZEBOX,                                \
                         CW_USEDEFAULT,                                 \
                         0,                                             \
                         CW_USEDEFAULT,                                 \
                         0,                                             \
                         NULL,                                          \
                         NULL,                                          \
                         hInstance,                                     \
                         NULL);                                        \
                                                                        \
    if (!hWnd)                                                          \
    {                                                                   \
        return FALSE;                                                   \
    }                                                                   \
                                                                        \
    ShowWindow  (hWnd, nCmdShow);                                     \
    UpdateWindow(hWnd);                                               \
                                                                        \
    while(GetMessage(&msg, NULL, 0, 0))                               \
    {                                                                   \
        TranslateMessage(&msg);                                         \
        DispatchMessage(&msg);                                          \
    }                                                                   \
                                                                        \
    return msg.wParam;                                                  \
}                                                                       \
                                                                        \
LRESULT CALLBACK WndProc(                                              \
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  {      \


#define END()                                               \
    if(message == WM_DESTROY)                             \
    {                                                       \
        KillTimer(hWnd, 1000);                            \
        PostQuitMessage(0);                                 \
        return 0;                                           \
    }                                                       \
                                                            \
    return DefWindowProc(hWnd, message, wParam, lParam);    \
}
#elif defined EXAM90
#define BEGIN() int WINAPI WinMain(                                    \
        HINSTANCE hInstance, HINSTANCE hPrevInstance,                   \
        LPSTR     lpCmdLine,                                            \
        int       nCmdShow)                                            \
{                                                                       \
	WNDCLASSEX wcex;                                                    \
    HWND hWnd;                                                          \
	MSG msg;                                                            \
                                                                        \
	wcex.cbSize = sizeof(WNDCLASSEX);                                 \
                                                                        \
	wcex.style			= CS_HREDRAW | CS_VREDRAW;                      \
	wcex.lpfnWndProc	= (WNDPROC) WndProc;                            \
	wcex.cbClsExtra		= 0;                                            \
	wcex.cbWndExtra		= 0;                                            \
	wcex.hInstance		= hInstance;                                    \
	wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);        \
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                  \
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                     \
	wcex.lpszMenuName	= NULL;                                         \
	wcex.lpszClassName	= "C-Guide";                                    \
	wcex.hIconSm		= LoadIcon(wcex.hInstance, IDI_APPLICATION);  \
                                                                        \
	RegisterClassEx(&wcex);                                           \
                                                                        \
    hInst = hInstance;                                                  \
                                                                        \
    hWnd = CreateWindow("C-Guide",                                     \
                         "사인곡선",                 \
                         WS_OVERLAPPEDWINDOW,                           \
                         CW_USEDEFAULT,                                 \
                         0,                                             \
                         CW_USEDEFAULT,                                 \
                         0,                                             \
                         NULL,                                          \
                         NULL,                                          \
                         hInstance,                                     \
                         NULL);                                        \
                                                                        \
    if (!hWnd)                                                          \
    {                                                                   \
        return FALSE;                                                   \
    }                                                                   \
                                                                        \
    ShowWindow  (hWnd, nCmdShow);                                     \
    UpdateWindow(hWnd);                                               \
                                                                        \
    while(GetMessage(&msg, NULL, 0, 0))                               \
    {                                                                   \
        TranslateMessage(&msg);                                         \
        DispatchMessage(&msg);                                          \
    }                                                                   \
                                                                        \
    return msg.wParam;                                                  \
}                                                                       \
                                                                        \
LRESULT CALLBACK WndProc(                                              \
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  {      \


#define END()                                               \
    if(message == WM_DESTROY)                             \
    {                                                       \
        PostQuitMessage(0);                                 \
        return 0;                                           \
    }                                                       \
                                                            \
    return DefWindowProc(hWnd, message, wParam, lParam);    \
}
#elif defined EXAM91
int CheckGame(int x, int y, int stone);

#define BEGIN() int WINAPI WinMain(                                    \
        HINSTANCE hInstance, HINSTANCE hPrevInstance,                   \
        LPSTR     lpCmdLine,                                            \
        int       nCmdShow)                                            \
{                                                                       \
	WNDCLASSEX wcex;                                                    \
    HWND hWnd;                                                          \
	MSG msg;                                                            \
                                                                        \
	wcex.cbSize = sizeof(WNDCLASSEX);                                 \
                                                                        \
	wcex.style			= CS_HREDRAW | CS_VREDRAW;                      \
	wcex.lpfnWndProc	= (WNDPROC) WndProc;                            \
	wcex.cbClsExtra		= 0;                                            \
	wcex.cbWndExtra		= 0;                                            \
	wcex.hInstance		= hInstance;                                    \
	wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);        \
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                  \
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                     \
	wcex.lpszMenuName	= NULL;                                         \
	wcex.lpszClassName	= "C-Guide";                                    \
	wcex.hIconSm		= LoadIcon(wcex.hInstance, IDI_APPLICATION);  \
                                                                        \
	RegisterClassEx(&wcex);                                           \
                                                                        \
    hInst = hInstance;                                                  \
                                                                        \
    hWnd = CreateWindow("C-Guide",                                     \
                         "오목 게임",                 \
                         WS_OVERLAPPED     |                            \
                         WS_CAPTION        |                            \
                         WS_SYSMENU        |                            \
                         WS_MINIMIZEBOX,                                \
                         CW_USEDEFAULT,                                 \
                         0,                                             \
                         (PX*1)+(PW*19)+ 1,                             \
                         (PX*2)+(PW*19)+ 7,                             \
                         NULL,                                          \
                         NULL,                                          \
                         hInstance,                                     \
                         NULL);                                        \
                                                                        \
    if (!hWnd)                                                          \
    {                                                                   \
        return FALSE;                                                   \
    }                                                                   \
                                                                        \
    ShowWindow  (hWnd, nCmdShow);                                     \
    UpdateWindow(hWnd);                                               \
                                                                        \
    while(GetMessage(&msg, NULL, 0, 0))                               \
    {                                                                   \
        TranslateMessage(&msg);                                         \
        DispatchMessage(&msg);                                          \
    }                                                                   \
                                                                        \
    return msg.wParam;                                                  \
}                                                                       \
                                                                        \
LRESULT CALLBACK WndProc(                                              \
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  {      \


#define END()                                               \
    if(message == WM_DESTROY)                             \
    {                                                       \
        KillTimer(hWnd, 1000);                            \
        PostQuitMessage(0);                                 \
        return 0;                                           \
    }                                                       \
                                                            \
    return DefWindowProc(hWnd, message, wParam, lParam);    \
}

#elif defined EXAM92
HWND hMainWnd;
HWND hBtnWnd;
int  MY_TIMER;
int  MY_NEW_TIMER;
int  BX, BY;

int  IsMoveable(int bx, int by, int brick, int rotate);
int  MoveBrick(void);
void MakeBrick(void);
int  CheckGame(void);

#define BEGIN() int WINAPI WinMain(                                    \
        HINSTANCE hInstance, HINSTANCE hPrevInstance,                   \
        LPSTR     lpCmdLine,                                            \
        int       nCmdShow)                                            \
{                                                                       \
	WNDCLASSEX wcex;                                                    \
    HWND hWnd;                                                          \
	MSG msg;                                                            \
	int cx, cy;                                                         \
                                                                        \
	wcex.cbSize = sizeof(WNDCLASSEX);                                 \
                                                                        \
	wcex.style			= CS_HREDRAW | CS_VREDRAW;                      \
	wcex.lpfnWndProc	= (WNDPROC) WndProc;                            \
	wcex.cbClsExtra		= 0;                                            \
	wcex.cbWndExtra		= 0;                                            \
	wcex.hInstance		= hInstance;                                    \
	wcex.hIcon			= LoadIcon(hInstance, IDI_APPLICATION);        \
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                  \
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                     \
	wcex.lpszMenuName	= NULL;                                         \
	wcex.lpszClassName	= "C-Guide";                                    \
	wcex.hIconSm		= LoadIcon(wcex.hInstance, IDI_APPLICATION);  \
                                                                        \
	RegisterClassEx(&wcex);                                           \
                                                                        \
    hInst = hInstance;                                                  \
                                                                        \
    cx = (GetSystemMetrics(SM_CXSCREEN) - 337) / 2;                   \
    cy = (GetSystemMetrics(SM_CYSCREEN) - 475) / 2;                   \
                                                                        \
    hWnd = CreateWindow("C-Guide",                                     \
                         "테트리스 게임",             \
                         WS_OVERLAPPED     |                            \
                         WS_CAPTION        |                            \
                         WS_SYSMENU        |                            \
                         WS_MINIMIZEBOX,                                \
                         cx,                                            \
                         cy,                                            \
                         337,                                           \
                         475,                                           \
                         NULL,                                          \
                         NULL,                                          \
                         hInstance,                                     \
                         NULL);                                        \
                                                                        \
    if(!hWnd)                                                         \
    {                                                                   \
        return FALSE;                                                   \
    }                                                                   \
                                                                        \
    hMainWnd = hWnd;                                                    \
                                                                        \
    ShowWindow  (hWnd, nCmdShow);                                     \
    UpdateWindow(hWnd);                                               \
                                                                        \
    while(GetMessage(&msg, NULL, 0, 0))                               \
    {                                                                   \
        TranslateMessage(&msg);                                         \
        DispatchMessage(&msg);                                          \
    }                                                                   \
                                                                        \
    return msg.wParam;                                                  \
}                                                                       \
                                                                        \
LRESULT CALLBACK WndProc(                                              \
        HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)         \
{                                                                       \


#define END()                                               \
    if(message == WM_DESTROY)                             \
    {                                                       \
        KillTimer(hWnd, 1000);                            \
        PostQuitMessage(0);                                 \
        return 0;                                           \
    }                                                       \
                                                            \
    return DefWindowProc(hWnd, message, wParam, lParam);    \
}

#elif defined EXAM100


HWND hMainWnd;
HWND hBtnWnd;
HWND hSrvWnd;
HWND hConWnd;
int  MY_TIMER;
int  MY_NEW_TIMER;
int  BX, BY;

int  IsMoveable(int bx, int by, int brick, int rotate);
int  MoveBrick(void);
void MakeBrick(void);
int  CheckGame(void);

#define BEGIN() int WINAPI WinMain(                                    \
    HINSTANCE hInstance, HINSTANCE hPrevInstance,                       \
    LPSTR     lpCmdLine,                                                \
    int       nCmdShow)                                                \
{                                                                       \
    WNDCLASSEX wcex;                                                    \
    HWND hWnd;                                                          \
    MSG msg;                                                            \
    int cx, cy;                                                         \
                                                                        \
    wcex.cbSize = sizeof(WNDCLASSEX);                                 \
                                                                        \
    wcex.style          = CS_HREDRAW | CS_VREDRAW;                      \
    wcex.lpfnWndProc    = (WNDPROC) WndProc;                            \
    wcex.cbClsExtra     = 0;                                            \
    wcex.cbWndExtra     = 0;                                            \
    wcex.hInstance      = hInstance;                                    \
    wcex.hIcon          = LoadIcon(hInstance, IDI_APPLICATION);        \
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);                  \
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);                     \
    wcex.lpszMenuName   = NULL;                                         \
    wcex.lpszClassName  = "C-Guide";                                    \
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);  \
                                                                        \
    RegisterClassEx(&wcex);                                           \
                                                                        \
    hInst = hInstance;                                                  \
                                                                        \
    cx = (GetSystemMetrics(SM_CXSCREEN) - 337) / 2;                   \
    cy = (GetSystemMetrics(SM_CYSCREEN) - 475) / 2;                   \
                                                                        \
    hWnd = CreateWindow("C-Guide",                                     \
        "C ��� ������� - ��Ʈ���� ����",                              \
        WS_OVERLAPPED     |                                             \
        WS_CAPTION        |                                             \
        WS_SYSMENU        |                                             \
        WS_MINIMIZEBOX,                                                 \
        cx,                                                             \
        cy,                                                             \
        337,                                                            \
        475,                                                            \
        NULL,                                                           \
        NULL,                                                           \
        hInstance,                                                      \
        NULL);                                                         \
                                                                        \
    if(!hWnd)                                                         \
    {                                                                   \
        return FALSE;                                                   \
    }                                                                   \
                                                                        \
    hMainWnd = hWnd;                                                    \
                                                                        \
    ShowWindow  (hWnd, nCmdShow);                                     \
    UpdateWindow(hWnd);                                               \
                                                                        \
    while(GetMessage(&msg, NULL, 0, 0))                               \
    {                                                                   \
        TranslateMessage(&msg);                                         \
        DispatchMessage(&msg);                                          \
    }                                                                   \
                                                                        \
    return msg.wParam;                                                  \
}                                                                       \
                                                                        \
LRESULT CALLBACK WndProc(                                              \
HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)                 \
{                                                                       \
    

#define END()                                               \
    if(message == WM_DESTROY)                             \
    {                                                       \
        SocketClose();                                      \
        KillTimer(hWnd, 1000);                            \
        PostQuitMessage(0);                                 \
        return 0;                                           \
    }                                                       \
                                                            \
    return DefWindowProc(hWnd, message, wParam, lParam);    \
}
#endif


#include "exam.h"

#endif