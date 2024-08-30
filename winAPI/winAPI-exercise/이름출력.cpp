#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR lpszString = _TEXT("win");
int cnt = 0;

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
void DrawName(HDC hdc, int cnt, int start_x);
void DrawUnreal(HDC hdc, int start_x);
void DrawCircle(HDC hdc, float start_angle, float end_angle, int centerX, int centerY, int radius);

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
    HDC hdc = GetDC(hwnd);
    switch (message)
    {
    case WM_CREATE:
        break;

    case WM_PAINT:
    {
        HDC hdc = GetDC(hwnd);
        DrawName(hdc, cnt, 10);
        DrawUnreal(hdc, 410);
        ReleaseDC(hwnd, hdc);
    }
    break;
    case WM_LBUTTONDOWN:
        cnt++;
        if (cnt > 3)
            cnt = 3;
        InvalidateRect(hwnd, NULL, TRUE); 
        break;
    case WM_RBUTTONDOWN:
        cnt--;
        if (cnt < 0)
            cnt = 0;
        InvalidateRect(hwnd, NULL, TRUE); 
        break;    
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

void DrawName(HDC hdc, int cnt, int start_x)
{
    int y = 250;

    if (cnt > 0)
    {
        MoveToEx(hdc, start_x, y, NULL);
        LineTo(hdc, start_x + 50, y);
        LineTo(hdc, start_x, y + 50);

        MoveToEx(hdc, start_x + 70, y - 20, NULL);
        LineTo(hdc, start_x + 70, y + 70);

        MoveToEx(hdc, start_x + 20, y + 100, NULL);
        LineTo(hdc, start_x + 70, y + 100);
        LineTo(hdc, start_x + 70, y + 150);
        LineTo(hdc, start_x + 20, y + 150);
        LineTo(hdc, start_x + 20, y + 100);
    }

    if (cnt > 1)
    {
        MoveToEx(hdc, start_x + 120, y + 0, NULL);
        LineTo(hdc, start_x + 170, y + 0);
        LineTo(hdc, start_x + 170, y + 50);
        LineTo(hdc, start_x + 120, y + 50);
        LineTo(hdc, start_x + 120, y + 0);

        MoveToEx(hdc, start_x + 200, y - 20, NULL);
        LineTo(hdc, start_x + 200, y + 70);

        MoveToEx(hdc, start_x + 150, y + 100, NULL);
        LineTo(hdc, start_x + 150, y + 150);
        LineTo(hdc, start_x + 200, y + 150);
    }

    if (cnt > 2)
    {
        MoveToEx(hdc, start_x + 250, y + 20, NULL);
        LineTo(hdc, start_x + 300, y + 20);
        LineTo(hdc, start_x + 300, y + 70);

        MoveToEx(hdc, start_x + 230, y + 100, NULL);
        LineTo(hdc, start_x + 330, y + 100);
        MoveToEx(hdc, start_x + 260, y + 100, NULL);
        LineTo(hdc, start_x + 260, y + 150);
        MoveToEx(hdc, start_x + 300, y + 100, NULL);
        LineTo(hdc, start_x + 300, y + 150);
    }

}
//UNREAL ENGINE
void DrawUnreal(HDC hdc, int start_x)
{
    int x = start_x;
    int y = 200;
    //UNREAL
    //U
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x, y + 30);
    MoveToEx(hdc, x + 50, y, NULL);
    LineTo(hdc, x + 50, y + 30);
    DrawCircle(hdc, 180, 360, x + 25, y + 25, 25);

    x += 70;
    
    //N
    MoveToEx(hdc, x, y + 50, NULL);
    LineTo(hdc, x, y);
    LineTo(hdc, x + 50, y + 50);
    LineTo(hdc, x + 50, y);

    x += 70;

    //R
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x , y + 50);
    MoveToEx(hdc, x, y + 25, NULL);
    LineTo(hdc, x + 40, y + 50);
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + 20, y );
    MoveToEx(hdc, x, y + 25, NULL);
    LineTo(hdc, x + 20, y + 25);
    DrawCircle(hdc, 0, 90, x + 20, y + 12, 12);
    DrawCircle(hdc, 240, 360, x + 20, y + 12, 12);

    x += 60;

    //E
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x, y + 50);
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + 25, y);
    MoveToEx(hdc, x, y + 25, NULL);
    LineTo(hdc, x + 25, y + 25);
    MoveToEx(hdc, x, y + 50, NULL);
    LineTo(hdc, x + 25, y + 50);

    x += 40;

    //A
    MoveToEx(hdc, x + 20, y, NULL);
    LineTo(hdc, x, y + 50);
    MoveToEx(hdc, x + 20, y, NULL);
    LineTo(hdc, x + 40, y + 50);
    MoveToEx(hdc, x + 10, y + 25, NULL);
    LineTo(hdc, x + 30, y + 25);

    x += 60;

    //L
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x, y + 50);
    LineTo(hdc, x + 25, y + 50);

    y += 200;
    x = start_x;
    //ENGINE

    //E
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x, y + 50);
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + 25, y);
    MoveToEx(hdc, x, y + 25, NULL);
    LineTo(hdc, x + 25, y + 25);
    MoveToEx(hdc, x, y + 50, NULL);
    LineTo(hdc, x + 25, y + 50);

    x += 50;

    //N
    MoveToEx(hdc, x, y + 50, NULL);
    LineTo(hdc, x, y);
    LineTo(hdc, x + 50, y + 50);
    LineTo(hdc, x + 50, y);

    x += 60;
    //G
    DrawCircle(hdc, 40, 300, x + 25, y + 25, 25);
    MoveToEx(hdc, x + 35, y + 50, NULL);
    LineTo(hdc, x + 35, y + 25);
    LineTo(hdc, x + 15, y + 25);

    x += 60;
    //I
    MoveToEx(hdc, x + 20, y, NULL);
    LineTo(hdc, x + 20, y + 50 );
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + 40, y);
    MoveToEx(hdc, x, y + 50, NULL);
    LineTo(hdc, x + 40, y + 50);

    x += 60;
    //N
    MoveToEx(hdc, x, y + 50, NULL);
    LineTo(hdc, x, y);
    LineTo(hdc, x + 50, y + 50);
    LineTo(hdc, x + 50, y);

    x += 60;
    //E
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x, y + 50);
    MoveToEx(hdc, x, y, NULL);
    LineTo(hdc, x + 25, y);
    MoveToEx(hdc, x, y + 25, NULL);
    LineTo(hdc, x + 25, y + 25);
    MoveToEx(hdc, x, y + 50, NULL);
    LineTo(hdc, x + 25, y + 50);
}

void DrawCircle(HDC hdc, float start_angle, float end_angle, int centerX, int centerY, int radius)
{
    vector<POINT> points;

    // 각도를 기준으로 원의 점을 계산
    for (int i = start_angle; i <= end_angle; i++)
    {
        double a = (2 * 3.14f * i) / 360;

        POINT newP;
        newP.x = centerX + (int)(radius * cos(a));
        newP.y = (centerY + (int)(radius * sin(-a)));
        points.push_back(newP);
    }

    // 원을 그리기
    MoveToEx(hdc, points[0].x, points[0].y, NULL);
    for (const auto point : points)
    {
        LineTo(hdc, point.x, point.y);
    }
}

//WinApi 출력
//->MovetoEx() + LineTo()를 이용할것.
//->자기 이름 출력(한글) + UnrealEngine(영문)
//ㄴ 크기는 800 x 800 기준 화면에 절반을 채우는 크기로 양분할것.
//
//- 마우스 왼쪽을 누르면 한글자씩 출력 되고, 우 클릭을 하면 한글자씩 지워진다. (이름에만 적용)
//
//※ 도형 관련 함수 사용 금지.