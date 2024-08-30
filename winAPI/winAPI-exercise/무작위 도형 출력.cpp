#include "Stdafx.h"

// ���� ����:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

HINSTANCE _hInstance;
HWND      _hWnd;
POINT     _ptMouse;

int random;
POINT pt;

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

        vector<POINT> points;
        int cnt;

        switch (random)
        {
            //�簢��
        case 0:
            RECT rc = RectMakeCenter(pt.x, pt.y, RND->getInt(200), RND->getInt(200));
            DrawRect(hdc, rc);
            break;
            // ��
        case 1:
            DrawEllipseCenter(hdc, pt.x, pt.y, RND->getInt(200), RND->getInt(200));
            break;
            // �ﰢ��
        case 2:
            points.push_back({ pt.x + RND->getFromIntTo(-100, 100), pt.y + RND->getFromIntTo(-100, 100) });
            points.push_back({ pt.x + RND->getFromIntTo(-100, 100), pt.y + RND->getFromIntTo(-100, 100) });
            points.push_back({ pt.x + RND->getFromIntTo(-100, 100), pt.y + RND->getFromIntTo(-100, 100) });

            Polygon(hdc, points.data(), 3);
            break;

        case 3:
            cnt = RND->getFromIntTo(5, 10);

            for (int i = 0; i < cnt; i++)
            {
                points.push_back({ pt.x + RND->getFromIntTo(-100, 100), pt.y + RND->getFromIntTo(-100, 100) });
            }

            Polygon(hdc, points.data(), cnt);
            break;

        default:
            break;
        }

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:

        //random = RND->getInt(3); 
        random = 3; 

        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

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

//
//2. ���콺�� ������ ������ ���
//���콺�� Ŭ���� ��ǥ�� ������ ������ ����Ѵ�
//������ ũ�� ��� �������� �������� ����
//������ ������ �ﰢ�� �簢�� �� / ���� : �ٰ���
//�ﰢ�� / �ٰ���->Polygon
