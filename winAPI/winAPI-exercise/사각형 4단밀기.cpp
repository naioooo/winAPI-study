#include "Stdafx.h"

// ���� ����:

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

    wndClass.cbClsExtra = 0; //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; //������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW); // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ��
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // ������
    wndClass.hInstance = _hInstance; // �ĺ���
    wndClass.lpfnWndProc = WndProc; // ������Ʈ ��� ������ ���ν���
    wndClass.lpszClassName = WINNAME; // Ŭ���� �̸�
    wndClass.lpszMenuName = NULL; // �޴��̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ ��Ÿ��

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME, // Ŭ���� �ĺ���
        WINNAME, // ������ Ÿ��Ʋ �� �̸�
        WINSTYLE, // ������ ��Ÿ��
        WINSTART_X, //X
        WINSTART_Y, //Y
        WINSIZE_X, //�ʺ�
        WINSIZE_Y, // ����
        NULL, // �θ�������
        (HMENU)NULL, // �޴��ڵ�
        _hInstance, // �ν��Ͻ� ����
        NULL // �ڽ������츦 �����ϸ� ����
    );

    if (!_hWnd) // ���� ���н� ����
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

    //������ ũ������
    AdjustWindowRect(&rc, WINSTYLE, false);

    //�簢���� ������ ������ ������� ����
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
 1. �簢�� 4�ܹб�
 �簢���� ������ 4��
 ���콺�� ȭ�鿡 �׷��� 4���� �簢���� �ƹ��ų� �����Ӱ� ������ �� �־�� �Ѵ�
 �����ӵ� �����ϰ� ũ����� ������ �����ؾ���
 ���콺 �� / ��
 ���콺�� �����̰� �ִ� �簢���� �ٸ� �簢���� �浹�ϸ� �ڿ������� �з�����
 
 �浹�Լ� ��� ����
*/