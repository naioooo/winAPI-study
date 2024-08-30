#include "Stdafx.h"

// ���� ����:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

HINSTANCE _hInstance;
HWND      _hWnd;
POINT     _ptMouse;

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

    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

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

            InvalidateRect(hwnd, NULL, true);
        }
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