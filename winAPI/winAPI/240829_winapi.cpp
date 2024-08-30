#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR lpszString = _TEXT("win");
RECT rc;

LRESULT CALLBACK WinProc(HWND, UINT, WPARAM, LPARAM);

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
    HDC hdc;
    PAINTSTRUCT ps;
    switch (message)
    {
    case WM_CREATE:
        rc = RectMakeCenter(400, 400, 100, 100);
        break;

    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        EndPaint(hwnd, &ps);
        break;
    }
    break;
    case WM_LBUTTONDOWN:
        break;
    case WM_RBUTTONDOWN:

        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            break;
        case VK_RIGHT:
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


/*
����

1. ������ ���
 �������� ������ó�� ���
 ��� �� ��� ������ �������� �ﰢ�Լ�x

2. �簢�� 2�� �����̱�
 �� �簢���� 2��
 �ϳ��� ������ �� �ִ� �簢��, �ٸ��ϳ��� ������ �� ����
 �����̴� �簢���� ������ �ϳ��� �о �� �ִ�
 2���ǻ簢���� ȭ�� ������ ���� �� ����
 2���� �簢���� �ʱ� ��ġ�� �ű�� ��ɵ� �߰�
 �浹�Լ� ������

���� �������
3. �簢�� ��ȥ �о�ֱ�
 ������ ū �簢�� 2���� ���� �簢�� 1��
 ���� ������ ���ִ� �簢�� �ȿ��� ���� �簢���� �ִ�
 �簢���� �����̸� ���� �簢�� ���� �����̰ų� / ū�簢���� ���������Ѵ�
  �������� �� ��õ
 ����ó�� : ���� �簢���� ū �簢���� ��� �� ����
 ū�簢������ �浹�� �Ǹ� ���� �簢���� �浹�� �� �ݴ��� �簢������ �̵��Ѵ�
 �̶� ������ �� �ִ� �ֵ����� ���� �簢���� �����ϰ� �մ� ū�簢��
 �𼭸��� ���� ����ó��

*/