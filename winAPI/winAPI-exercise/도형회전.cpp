
#include "Stdafx.h"

// 전역 변수:

struct Pointdouble
{
    double x;
    double y;

    Pointdouble(double _x, double _y) : x(_x), y(_y) {}
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
POINT rotate(const POINT& pt, double angleDegrees);

HINSTANCE _hInstance;
HWND      _hWnd;
POINT     _ptMouse;

vector<POINT> points;

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

    switch (message)
    {
    case WM_CREATE:
        RECT rc = RectMakeCenter(400, 400, 100, 100);
        points.push_back({ rc.left, rc.top });
        points.push_back({rc.right, rc.top});
        points.push_back({rc.right, rc.bottom});
        points.push_back({rc.left, rc.bottom });

        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
    
        Polygon(hdc, points.data(), 4);

        EndPaint(hwnd, &ps);

    }
    break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            for (auto& point : points)
            {
                point = rotate(point, -10);
            }
            break;
        case VK_RIGHT:
            for (auto& point : points)
            {
                point = rotate(point, +10);
            }
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

POINT rotate(const POINT& pt, double angleDegrees)
{
    double angleRadians = angleDegrees * (M_PI / 180.0);


    double centerX = points[0].x + ((points[1].x - points[0].x) / 2);
    double centerY = points[0].y + ((points[3].y - points[3].y) / 2);

    double x = pt.x - centerX;
    double y = pt.y - centerY;

    // 회전 변환 수행
    double xNew = x * cos(angleRadians) - y * sin(angleRadians);
   // double yNew = x * sin(angleRadians) + y * cos(angleRadians);

    return { int(xNew + centerX), pt.y };
}

//1. 도형 회전
//사각형을 회전 시킨다
//외부라이브러리 x 순수 api로만 구현
//hdc를 사용하고 rectangle함수를 사용햐러
//회전축이 바뀐상태면 상대좌표로 이동하게 구현해오기