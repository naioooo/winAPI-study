#include "Stdafx.h"

// ���� ����:
HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR _lpszClass = _TEXT("WINDOW API"); // �̰� �ΰ�

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
        800, //�ʺ�
        800, // ����
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

//1. ������ ���
//�������� ������ó�� ���
//��� �� ��� ������ �������� �ﰢ�Լ�x
