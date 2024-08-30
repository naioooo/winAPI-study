#include "Stdafx.h"

// 전역 변수:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);
bool CollisionCheck(RECT a, RECT b);
bool collisionPTCheck(POINT pt, RECT rc);
bool CollisionCheckMap(RECT rc);

HINSTANCE _hInstance;
HWND      _hWnd;
POINT     _ptMouse;
POINT     _prePtMouse;
RECT*     _moveRect = NULL;
RECT*     _sizeRect = NULL;

int dirX = 0;
int dirY = 0;

std::vector<RECT*> rects;
int choice;

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

    static POINT pt = { 0, 0 };
    _prePtMouse = pt;
    char strPT[120];

    switch (message)
    {
    case WM_CREATE:
        rects.push_back(new RECT(RectMakeCenter((WINSIZE_X / 2) - 200, (WINSIZE_Y / 2) - 200, 100, 100)));
        rects.push_back(new RECT(RectMakeCenter((WINSIZE_X / 2) + 200, (WINSIZE_Y / 2) - 200, 100, 100)));
        rects.push_back(new RECT(RectMakeCenter((WINSIZE_X / 2) + 200, (WINSIZE_Y / 2) + 200, 100, 100)));
        rects.push_back(new RECT(RectMakeCenter((WINSIZE_X / 2) - 200, (WINSIZE_Y / 2) + 200, 100, 100)));

        choice = 0;
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        for (const auto& rect : rects)
        {
            DrawRect(hdc, *rect);
        }


        wsprintf(strPT, "X: %d   Y : %d ", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        wsprintf(strPT, "X: %d   Y : %d ", _prePtMouse.x, _prePtMouse.y);
        TextOut(hdc, 10, 20, strPT, strlen(strPT));

        if (_moveRect != nullptr)
        {
            wsprintf(strPT, "rect ");
            TextOut(hdc, 10, 30, strPT, strlen(strPT));
        }
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (_moveRect == NULL)
        {
            for (auto& rect : rects)
            {
                if (collisionPTCheck(pt, *rect))
                {
                    _moveRect = rect;
                    _prePtMouse = pt;
                    break;
                }
            }
        }

        InvalidateRect(hwnd, NULL, TRUE);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (_sizeRect == NULL)
        {
            for (auto& rect : rects)
            {
                if (collisionPTCheck(pt, *rect))
                {
                    _sizeRect = rect;
                    _prePtMouse = pt;

                    int centerX = _sizeRect->left + ((_sizeRect->right - _sizeRect->left) / 2);
                    int centerY = _sizeRect->top + ((_sizeRect->bottom - _sizeRect->top) / 2);

                    if (pt.x > centerX)
                    {
                        dirX = 1;
                    }
                    else
                    {
                        dirX = 0;
                    }

                    if (pt.y > centerY)
                    {
                        dirY = 1;
                    }
                    else
                    {
                        dirY = 0;
                    }
             
                    break;
                }
            }
        }

        InvalidateRect(hwnd, NULL, TRUE);
        break;
    }

    case WM_MOUSEMOVE:
    {
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        if (_moveRect != NULL)
        {
            bool check = false;

            RECT newRect = *_moveRect;
            vector<RECT> newCollisionRect;
            newCollisionRect.resize(4);

            newRect.left += pt.x - _prePtMouse.x;
            newRect.right += pt.x - _prePtMouse.x;
            newRect.top += pt.y - _prePtMouse.y;
            newRect.bottom += pt.y - _prePtMouse.y;

            for (int i = 0; i < rects.size(); i++)
            {
                if (_moveRect == rects[i])
                {
                    newCollisionRect[i] = newRect;
                }

                newCollisionRect[i] = *rects[i];
                if (CollisionCheck(newRect, newCollisionRect[i]))
                {
                    newCollisionRect[i].left += pt.x - _prePtMouse.x;
                    newCollisionRect[i].right += pt.x - _prePtMouse.x;
                    newCollisionRect[i].top += pt.y - _prePtMouse.y;
                    newCollisionRect[i].bottom += pt.y - _prePtMouse.y;
                }
            }

            for (auto rect : newCollisionRect)
            {
                if (CollisionCheckMap(rect))
                {
                    check = true;
                    break;
                }
            }

            if (!check)
            {
                for (int i = 0; i < rects.size(); i++)
                {
                    *rects[i] = newCollisionRect[i];
                }

                *_moveRect = newRect;
            }

            _prePtMouse = pt;
        }

        if (_sizeRect != NULL)
        {
            int centerX = _sizeRect->left + ((_sizeRect->right - _sizeRect->left) / 2);
            int centerY = _sizeRect->top + ((_sizeRect->bottom - _sizeRect->top) / 2);

            if (dirX == 1)
            {
                _sizeRect->right += pt.x - _prePtMouse.x;
            }
            else if (dirX == 0)
            {
                _sizeRect->left += pt.x - _prePtMouse.x;
            }

            if (dirY == 1)
            {
                _sizeRect->bottom += pt.y - _prePtMouse.y;
            }
            else if (dirY == 0)
            {
                _sizeRect->top += pt.y - _prePtMouse.y;
            }          

            _prePtMouse = pt;
        }
        InvalidateRect(hwnd, NULL, true);
    }
        break;
    case WM_LBUTTONUP:
        _moveRect = NULL;
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_RBUTTONUP:
        _sizeRect = NULL;


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

bool collisionPTCheck(POINT pt, RECT rc)
{
    if (rc.left <= pt.x && pt.x <= rc.right &&
        rc.top <= pt.y && pt.y <= rc.bottom)
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

bool CollisionCheckMap(RECT rc)
{
    if (rc.right >= WINSIZE_X || rc.left < 0 || rc.top < 0 || rc.bottom >= WINSIZE_Y)
    {
        return true;
    }

    return false;
}

/*
 1. 사각형 4단밀기
 사각형의 갯수는 4개
 마우스로 화면에 그려진 4개의 사각형중 아무거나 자유롭게 움직일 수 있어야 한다
 움직임도 가능하고 크기또한 조절이 가능해야함
 마우스 왼 / 오
 마우스로 움직이고 있는 사각형이 다른 사각형과 충돌하면 자연스럽게 밀려나다
 
 충돌함수 사용 금지
*/