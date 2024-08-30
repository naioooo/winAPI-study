#include "Stdafx.h"

// 전역 변수:
HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR _lpszClass = _TEXT("WINDOW API"); // 이거 두개

bool CollisionCheck(RECT a, RECT b);
bool CollisionCheckMap(RECT rc);
bool CollisionInside(RECT parent, RECT child);
void Move(RECT &rc, WPARAM wParam, int speed);

vector<RECT> rc1;
vector<RECT> rc2;
int speed = 5;
int turn = 1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


#define MAX_WIDTH 800
#define MAX_HEIGHT 800

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
        MAX_WIDTH, //너비
        MAX_HEIGHT, // 높이
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
        rc1.push_back( RectMakeCenter(300, 400, 150, 150));
        rc1.push_back(RectMakeCenter(300, 400, 50, 50));
        rc2.push_back(RectMakeCenter(500, 400, 150, 150));
        rc2.push_back(RectMakeCenter(500, 400, 50, 50));
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        DrawRect(hdc, rc1[0]);
        DrawRect(hdc, rc2[0]);

        if (turn == 0)
        {
            DrawRect(hdc, rc1[1]);
        }
        if (turn == 1)
        {
            DrawRect(hdc, rc2[1]);
        }

        string str = to_string(turn);
        LPCTSTR lpText = str.c_str();  // LPCTSTR 또는 LPWSTR로 변환

        TextOut(hdc, 100, 100, lpText, strlen(lpText));

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_KEYDOWN:

        RECT newRc;
        RECT newChideRc;
        RECT OtherRc;

        if (turn == 0)
        {
            newRc = rc1[0];
            newChideRc = rc1[1];
            OtherRc = rc2[0];
        }
        else if (turn == 1)
        {
            newRc = rc2[0];
            newChideRc = rc2[1];
            OtherRc = rc1[0];
        }

        Move(newRc, wParam, speed);

        if (CollisionInside(newRc, newChideRc))
        {
            Move(newChideRc, wParam, speed);
        }
        
        if (CollisionCheck(newRc, OtherRc))
        {
            if (turn == 0)
                turn = 1;
            else if (turn == 1)
                turn = 0;
        }
        else if (!CollisionCheckMap(newRc))
        {
            if (turn == 0)
            {
                rc1[0] = newRc;
                rc1[1] = newChideRc;
            }
            else if (turn == 1)
            {
                rc2[0] = newRc;
                rc2[1] = newChideRc;
            }
        }
        
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

bool CollisionCheckMap(RECT rc)
{
    if (rc.right >= MAX_WIDTH || rc.left < 0 || rc.top < 0 || rc.bottom >= MAX_HEIGHT)
    {
        return true;
    }

    return false;
}

bool CollisionCheck(RECT a, RECT b)
{
    if (a.right > b.left && a.left < b.right)
    {
        if (a.bottom > b.top && a.top < b.bottom)
        {
            return true;
        }
    }

    return false;
}

bool CollisionInside(RECT parent, RECT child)
{
    if (parent.right < child.right || parent.left > child.left || parent.top > child.top || parent.bottom < child.bottom)
    {
        return true;
    }

    return false;
}

void Move(RECT &rc, WPARAM wParam, int speed)
{
    switch (wParam)
    {
    case VK_LEFT:
        rc.left -= speed;
        rc.right -= speed;
        break;
    case VK_RIGHT:
        rc.left += speed;
        rc.right += speed;
        break;
    case VK_UP:
        rc.top -= speed;
        rc.bottom -= speed;
        break;
    case VK_DOWN:
        rc.top += speed;
        rc.bottom += speed;
        break;
    }
}