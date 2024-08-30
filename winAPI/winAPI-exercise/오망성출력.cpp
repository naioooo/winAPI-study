#include "Stdafx.h"

// 전역 변수:
HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR _lpszClass = _TEXT("WINDOW API"); // 이거 두개

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
    wndClass.lpszClassName = _lpszClass; // 클래스 이름
    wndClass.lpszMenuName = NULL; // 메뉴이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 스타일

    RegisterClass(&wndClass);

    _hwnd = CreateWindow
    (
        _lpszClass, // 클래스 식별자
        _lpszClass, // 윈도우 타이틀 바 이름
        WS_OVERLAPPEDWINDOW, // 윈도우 스타일
        400, //X
        100, //Y
        800, //너비
        800, // 높이
        NULL, // 부모윈도우
        (HMENU)NULL, // 메뉴핸들
        _hInstance, // 인스턴스 지정
        NULL // 자식윈도우를 생성하면 지정
    );

    if (!_hwnd) // 생성 실패시 종료
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        vector<POINT> points;

        int radious = 300;
        for (int i = 0; i < 300; i++)
        {
            float x = sqrt((radious * radious) - (i * i));

            POINT point;
            point.x = x + 400;
            point.y = i + 400;
            
            points.push_back(point);
        }
        for (int i = 0; i < radious; i++)
        {
            float x = sqrt((radious * radious) - (i * i));

            POINT point;
            point.x = -i + 400;
            point.y = x + 400;

            points.push_back(point);
        }
        for (int i = 0; i < radious; i++)
        {
            float x = sqrt((radious * radious) - (i * i));

            POINT point;
            point.x = -x + 400;
            point.y = -i + 400;

            points.push_back(point);
        }
        for (int i = 0; i < radious; i++)
        {
            float x = sqrt((radious * radious) - (i * i));

            POINT point;
            point.x = i + 400;
            point.y = -x + 400;

            points.push_back(point);
        }

        MoveToEx(hdc, points[0].x, points[0].y, NULL);
        for (const auto point : points)
        {
            LineTo(hdc, point.x, point.y);
        }
        LineTo(hdc, points[0].x, points[0].y);

        float py = -100;
        float px = sqrt((radious * radious) - (py * py));
        MoveToEx(hdc, px + 400, py + 400, NULL);
        LineTo(hdc, -px + 400, py + 400);

        px = 200;
        py = sqrt((radious * radious) - (px * px));
        LineTo(hdc, px + 400, py + 400);

        py = -300;
        px = sqrt((radious * radious) - (py * py));
        LineTo(hdc, px + 400, py + 400);

        px = -200;
        py = sqrt((radious * radious) - (px * px));
        LineTo(hdc, px + 400, py + 400);

        py = -100;
        px = sqrt((radious * radious) - (py * py));
        LineTo(hdc, px + 400, py + 400);

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
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

//1. 오망성 출력
//오망성을 마법진처럼 출력
//양식 및 사용 문법은 본인자유 삼각함수x
