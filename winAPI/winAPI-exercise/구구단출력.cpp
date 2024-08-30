#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR lpszString = _TEXT("win");
int cnt = 1;

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);
void Draw_gugudan(HDC hdc, int cnt, int start_x);

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
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW); // Ŀ��
    wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // ���� ��
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
        Draw_gugudan(hdc, cnt, 50);
        ReleaseDC(hwnd, hdc);
    }
    break;
    case WM_LBUTTONDOWN:
        cnt++;
        if (cnt > 9)
            cnt = 9;
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case WM_RBUTTONDOWN:
        cnt--;
        if (cnt < 1)
            cnt = 1;
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

void Draw_gugudan(HDC hdc, int cnt, int start_x)
{
    int y = start_x;

    for (int i = 2; i <= cnt; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            string str = to_string(i) + " x " + to_string(j) + " = " + to_string(i * j);
            LPCTSTR lpText = str.c_str();  // LPCTSTR �Ǵ� LPWSTR�� ��ȯ

            int w = (i - 2) % 3;
            int h = (i - 2) / 3;
            TextOut(hdc, start_x + (w * 200), y + h * 200 + (j * 20), lpText, strlen(lpText));
        }
    } 
}


//����2.������
//
//->����ó�� �ʼ�
//�� �������� ����(1�� ���� X / 9�� �̻� X)
//
//->���콺 ���� Ŭ���� ���� �� 1�ܾ� ����� �ǰ�, ��Ŭ���� �ϸ� 1�ܾ� ��������.
//->�׸��� 3�ܰ� ���� ������ �Ѵ�.