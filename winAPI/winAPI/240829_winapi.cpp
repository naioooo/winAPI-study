#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR lpszString = _TEXT("win");
RECT rc;

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPSTR     lpszCmdParam,
    _In_     int       nCmdShow)
{
    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW); // 커서
    wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // 아이 콘
    wndClass.hInstance = _hInstance;
    wndClass.lpfnWndProc = WinProc;
    wndClass.lpszClassName = lpszString;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);

    _hwnd = CreateWindow
    (
        lpszString,
        lpszString,
        WS_OVERLAPPEDWINDOW,
        400,
        100,
        800,
        800,
        NULL,
        (HMENU)NULL,
        _hInstance,
        NULL
    );

    if (!_hwnd)
    {
        return false;
    }

    ShowWindow(_hwnd, nCmdShow);

    MSG message;

    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return (int)message.wParam;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    switch (message)
    {
    case WM_CREATE:
        rc = RectMakeCenter(400, 400, 100, 100);
        break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
        break;
    }
    break;
    case WM_LBUTTONDOWN:
        break;
    case WM_RBUTTONDOWN:

        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        case VK_ESCAPE:
            PostMessage(hwnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}


/*
과제

1. 오망성 출력
 오망성을 마법진처럼 출력
 양식 및 사용 문법은 본인자유 삼각함수x

2. 사각형 2개 움직이기
 총 사각형은 2개
 하나는 움직일 수 있는 사각형, 다른하나는 움직일 수 없다
 움직이는 사각형은 나머지 하나를 밀어낼 수 있다
 2개의사각형은 화면 밖으로 나갈 수 없다
 2개의 사각형의 초기 위치로 옮기는 기능도 추가
 충돌함수 사용금지

담주 월욜까지
3. 사각형 영혼 밀어넣기
 시작은 큰 사각형 2개와 작은 사각형 1개
 내가 움직일 수있는 사각형 안에는 작은 사각형이 있다
 사각형을 움직이면 작은 사각형 역시 움직이거나 / 큰사각형에 끌려가야한다
  끌려가는 것 추천
 예외처리 : 작은 사각형은 큰 사각형을 벗어날 수 없다
 큰사각형끼리 충돌이 되면 작은 사각형은 충돌이 된 반대편 사각형으로 이동한다
 이때 움직일 수 있는 주도원은 작은 사각형을 소유하고 잇는 큰사각형
 모서리에 대한 예외처리

*/