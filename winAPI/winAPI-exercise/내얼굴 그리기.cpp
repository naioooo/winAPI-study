#include "Stdafx.h"

// 전역 변수:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

HINSTANCE _hInstance;
HWND      _hWnd;
POINT     _ptMouse;

POINT cen;

int APIENTRY WinMain(_In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPSTR     lpszCmdParam,
    _In_     int       nCmdShow)
{
    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0; //클래스 여분 메모리
    wndClass.cbWndExtra = 0; //윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW); // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // 커서
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // 아이콘
    wndClass.hInstance = _hInstance; // 식별자
    wndClass.lpfnWndProc = WndProc; // 롱포인트 펑션 윈도우 프로시져
    wndClass.lpszClassName = WINNAME; // 클래스 이름
    wndClass.lpszMenuName = NULL; // 메뉴이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 스타일

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME, // 클래스 식별자
        WINNAME, // 윈도우 타이틀 바 이름
        WINSTYLE, // 윈도우 스타일
        WINSTART_X, //X
        WINSTART_Y, //Y
        WINSIZE_X, //너비
        WINSIZE_Y, // 높이
        NULL, // 부모윈도우
        (HMENU)NULL, // 메뉴핸들
        _hInstance, // 인스턴스 지정
        NULL // 자식윈도우를 생성하면 지정
    );

    if (!_hWnd) // 생성 실패시 종료
    {
        return false;
    }

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    MSG message;

    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return (int)message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH hBrush; 
    HBRUSH hOldBrush;

    switch (message)
    {
    case WM_CREATE:
        cen.x = WINSIZE_X / 2;
        cen.y = WINSIZE_Y / 2;
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        hBrush = CreateSolidBrush(COLOR_BODY);

        // 몸통

        // 얼굴
        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawEllipseCenter(hdc, cen.x, cen.y, 400, 450);
        SelectObject(hdc, hOldBrush);

        // 눈
        hBrush = CreateSolidBrush(COLOR_WHITE);
        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawEllipseCenter(hdc, cen.x - 80, cen.y - 80, 80, 30);
        DrawEllipseCenter(hdc, cen.x + 80, cen.y - 80, 80, 30);
        SelectObject(hdc, hOldBrush);

        // 눈동자
        hBrush = CreateSolidBrush(COLOR_BLACK);
        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawEllipseCenter(hdc, cen.x - 80, cen.y - 80, 40, 20);
        DrawEllipseCenter(hdc, cen.x + 80, cen.y - 80, 40, 20);
        SelectObject(hdc, hOldBrush);

        // 코
        hBrush = CreateSolidBrush(COLOR_BODY);
        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawtriangleCenter(hdc, cen.x, cen.y, 30, 70);
        SelectObject(hdc, hOldBrush);

        // 입
        hBrush = CreateSolidBrush(COLOR_RED);
        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawtriangleCenter(hdc, cen.x, cen.y, 30, 70);
        SelectObject(hdc, hOldBrush);

        // 귀

        // 눈썹

        // 머리

        // 

        

        DeleteObject(hBrush);
        EndPaint(hwnd, &ps);

    }
    break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        case VK_UP:
            break;
        case VK_DOWN:
            break;
        case VK_ESCAPE:
            PostMessage(hwnd, WM_DESTROY, 0, 0);
            break;

        }
        InvalidateRect(hwnd, NULL, true);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    //윈도우 크기조정
    AdjustWindowRect(&rc, WINSTYLE, false);

    //사각형의 정보를 윈도우 사이즈로 지정
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

}

//
//담주화욜
//3. 내얼굴 그리기
//도형을 통해 과제를 해올것
