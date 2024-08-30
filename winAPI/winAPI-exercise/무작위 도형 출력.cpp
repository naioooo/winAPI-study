#include "Stdafx.h"

// 전역 변수:

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
            //사각형
        case 0:
            RECT rc = RectMakeCenter(pt.x, pt.y, RND->getInt(200), RND->getInt(200));
            DrawRect(hdc, rc);
            break;
            // 원
        case 1:
            DrawEllipseCenter(hdc, pt.x, pt.y, RND->getInt(200), RND->getInt(200));
            break;
            // 삼각형
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

    //윈도우 크기조정
    AdjustWindowRect(&rc, WINSTYLE, false);

    //사각형의 정보를 윈도우 사이즈로 지정
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

}

//
//2. 마우스로 무작위 도형을 출력
//마우스로 클린한 좌표에 무작위 도형을 출력한다
//도형의 크기 모양 종류까지 무작위로 설정
//도형의 종류는 삼각형 사각형 원 / 선택 : 다각형
//삼각형 / 다각형->Polygon
