#include "Stdafx.h"

// ���� ����:
HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR _lpszClass = _TEXT("WINDOW API"); // �̰� �ΰ�

bool CollisionCheck(RECT a, RECT b);
bool CollisionCheckMap(RECT rc);
void Move(RECT& rc, WPARAM wParam, int speed);
RECT rc1;
RECT rc2;
int speed = 5;

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

    wndClass.cbClsExtra = 0; //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; //������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW); // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Ŀ��
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // ������
    wndClass.hInstance = _hInstance; // �ĺ���
    wndClass.lpfnWndProc = WndProc; // ������Ʈ ��� ������ ���ν���
    wndClass.lpszClassName = _lpszClass; // Ŭ���� �̸�
    wndClass.lpszMenuName = NULL; // �޴��̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ ��Ÿ��

    RegisterClass(&wndClass);

    _hwnd = CreateWindow
    (
        _lpszClass, // Ŭ���� �ĺ���
        _lpszClass, // ������ Ÿ��Ʋ �� �̸�
        WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
        400, //X
        100, //Y
        MAX_WIDTH, //�ʺ�
        MAX_HEIGHT, // ����
        NULL, // �θ�������
        (HMENU)NULL, // �޴��ڵ�
        _hInstance, // �ν��Ͻ� ����
        NULL // �ڽ������츦 �����ϸ� ����
    );

    if (!_hwnd) // ���� ���н� ����
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
        rc1 = RectMakeCenter(300, 400, 150, 150);
        rc2 = RectMakeCenter(500, 400, 150, 150);
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        DrawRect(hdc, rc1);
        DrawRect(hdc, rc2);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_KEYDOWN:
        RECT newRect1 = rc1;
        RECT newRect2 = rc2;
        
        Move(newRect1, wParam, speed);

        if (CollisionCheck(newRect1, newRect2))
        {
            Move(newRect2, wParam, speed);
        }

        if (!CollisionCheckMap(newRect1) && !CollisionCheckMap(newRect2))
        {
            rc1 = newRect1;
            rc2 = newRect2;
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

void Move(RECT& rc, WPARAM wParam, int speed)
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