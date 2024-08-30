#include "Stdafx.h"

// ���� ����:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

HINSTANCE _hInstance;
HWND      _hWnd;

RECT rc;
RECT rc1, rc2;

int centerX;
int centerY;

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

    static POINT pt = {0, 0};
    char strPT[120];

    switch (message)
    {
    case WM_CREATE:
        rc = RectMakeCenter(400, 400, 100, 100);
        rc1 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
        rc2 = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

        centerX = WINSIZE_X / 2;
        centerY = WINSIZE_Y / 2;
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        wsprintf(strPT, "X: %d   Y : %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));

        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
        DrawRect(hdc, rc);


        Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
        Rectangle(hdc, rc2.left, rc2.top, rc2.right, rc2.bottom);

        DrawEllipseCenter(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);
        
        Rectangle(hdc, centerX, centerY, 100, 100);

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_MOUSEMOVE:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        InvalidateRect(hwnd, NULL, true);
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
    case WM_LBUTTONDOWN:
        centerX = RND->getInt(WINSIZE_X);
        centerY = RND->getInt(WINSIZE_Y);

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

    //������ ũ������
    AdjustWindowRect(&rc, WINSTYLE, false);

    //�簢���� ������ ������ ������� ����
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

}

/*
����

1. �簢�� 4�ܹб�
 �簢���� ������ 4��
 ���츣�� ȭ�鿡 �׷��� 4���� �簢���� �ƹ��ų� �����Ӱ� ������ �� �־�� �Ѵ�
 �����ӵ� �����ϰ� ũ����� ������ �����ؾ���
 ���콺 ��/ ��
 ���콺�� �����̰� �ִ� �簢���� �ٸ� �簢���� �浹�ϸ� �ڿ������� �з�����

 �浹�Լ� ��� ����

2. ���콺�� ������ ������ ���
 ���콺�� Ŭ���� ��ǥ�� ������ ������ ����Ѵ�
 ������ ũ�� ��� �������� �������� ����
 ������ ������ �ﰢ�� �簢�� �� / ���� : �ٰ���
 �ﰢ�� / �ٰ��� -> Polygon

����ȭ��
3. ���� �׸���
 ������ ���� ������ �ؿð�


��������
1. ���� ȸ��
 �簢���� ȸ�� ��Ų��
 �ܺζ��̺귯�� x ���� api�θ� ����
 hdc�� ����ϰ� rectangle�Լ��� ����ᷯ
 ȸ������ �ٲ���¸� �����ǥ�� �̵��ϰ� �����ؿ���


*/