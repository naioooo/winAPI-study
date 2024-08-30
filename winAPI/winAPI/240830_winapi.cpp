#include "Stdafx.h"

// 전역 변수:

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

    //윈도우 크기조정
    AdjustWindowRect(&rc, WINSTYLE, false);

    //사각형의 정보를 윈도우 사이즈로 지정
    SetWindowPos(_hWnd, NULL,
        x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);

}

/*
과제

1. 사각형 4단밀기
 사각형의 갯수는 4개
 마우르소 화면에 그려진 4개의 사각형중 아무거나 자유롭게 움직일 수 있어야 한다
 움직임도 가능하고 크기또한 조절이 가능해야함
 마우스 왼/ 오
 마우스로 움직이고 있는 사각형이 다른 사각형과 충돌하면 자연스럽게 밀려나다

 충돌함수 사용 금지

2. 마우스로 무작위 도형을 출력
 마우스로 클린한 좌표에 무작위 도형을 출력한다
 도형의 크기 모양 종류까지 무작위로 설정
 도형의 종류는 삼각형 사각형 원 / 선택 : 다각형
 삼각형 / 다각형 -> Polygon

담주화욜
3. 내얼굴 그리기
 도형을 통해 과제를 해올것


도전과제
1. 도형 회전
 사각형을 회전 시킨다
 외부라이브러리 x 순수 api로만 구현
 hdc를 사용하고 rectangle함수를 사용햐러
 회전축이 바뀐상태면 상대좌표로 이동하게 구현해오기


*/