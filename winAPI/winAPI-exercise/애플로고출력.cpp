#include "Stdafx.h"

// 전역 변수:
HINSTANCE _hInstance;
HWND _hwnd;
LPCTSTR _lpszClass = _TEXT("WINDOW API"); // 이거 두개
string filePath = "애플.txt";
ifstream file;
std::random_device rd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
bool InsideCheck(POINT p, int radious, int cenX, int cenY);
void DrawPicture(HDC hdc);
void DrawPixel(HDC hdc);
void DrawEllipselePixel(HDC hdc, int radious, POINT center, int maxCnt);
void DrawIntersectEllipselePixel(HDC hdc, int radiousA, POINT centerA, int radiousB, POINT centerB, int maxCnt);
void DrawIntersectMinusEllipselePixel(HDC hdc, int radiousA, POINT centerA, int radiousB, POINT centerB, int maxCnt);
COLORREF SelectColor(int y);

struct Ellipse
{
    int radious;
    POINT center;
};

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
    wndClass.lpszClassName = _lpszClass; // 클래스 이름
    wndClass.lpszMenuName = NULL; // 메뉴이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 스타일

    RegisterClass(&wndClass);

    _hwnd = CreateWindow
    (
        _lpszClass, // 클래스 식별자
        _lpszClass, // 윈도우 타이틀 바 이름
        WS_OVERLAPPEDWINDOW, // 윈도우 스타일
        400, //X
        100, //Y
        800, //너비
        800, // 높이
        NULL, // 부모윈도우
        (HMENU)NULL, // 메뉴핸들
        _hInstance, // 인스턴스 지정
        NULL // 자식윈도우를 생성하면 지정
    );

    if (!_hwnd) // 생성 실패시 종료
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
        file = ifstream(filePath);
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        DrawPicture(hdc);

        DrawPixel(hdc);
        

        EndPaint(hwnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

bool InsideCheck(POINT p, int radious, int cenX, int cenY)
{
    int x = p.x - cenX;
    int y = p.y - cenY;

    if (x * x + y * y <= radious * radious)
    {
        return true;
    }

    return false;
}

COLORREF SelectColor(int y)
{
    COLORREF color;

    y /= 2;

    if (y < 125)
    {
        color = RGB(0, 255, 0);
    }
    else if (y < 160)
    {
        color = RGB(255, 255, 0);
    }
    else if (y < 205)
    {
        color = RGB(255, 165, 0);
    }
    else if (y < 250)
    {
        color = RGB(255, 0, 0);
    }
    else if (y < 295)
    {
        color = RGB(238, 130, 238);
    }
    else
    {
        color = RGB(0, 0, 255);
    }

    return color;
}

void DrawPicture(HDC hdc)
{
    std::string line;

    while (std::getline(file, line))
    {
        std::cout << line << std::endl;

        int start = 0;
        int end = 0;
        int x = 0;
        int y = 0;

        while (true)
        {

            if (line.length() < end)
                break;

            if (line[end] == ' ')
            {
                x = stoi(line.substr(start, end - start));
                start = end + 1;
            }
            else if (line[end] == ',')
            {
                y = stoi(line.substr(start, end - start));
                start = end + 1;

                COLORREF color = SelectColor(y);
                SetPixel(hdc, x, y, color);
            }

            end++;
        }
    }
}

void DrawPixel(HDC hdc)
{
    int centerX = 500;
    int centerY = 500;
    //DrawEllipselePixel(hdc, 200, POINT{ 400, 400 }, 100000);
   // DrawIntersectEllipselePixel(hdc, 200, POINT{ 300, 400 }, 200, POINT{ 500, 400 }, 100000);
   // DrawIntersectMinusEllipselePixel(hdc, 200, POINT{ 300, 400 }, 200, POINT{ 500, 400 }, 100000);

    DrawIntersectMinusEllipselePixel(hdc, 200, POINT{ centerX, centerY },
                                          100, POINT{ centerX + 200, centerY - 60 }, 100000);

    DrawEllipselePixel(hdc, 150, POINT{ centerX - 100, centerY - 100 }, 100000);

    DrawIntersectMinusEllipselePixel(hdc, 150, POINT{ centerX + 100, centerY - 100 },
                                          100, POINT{ centerX + 200, centerY - 60 }, 100000);

    DrawIntersectEllipselePixel(hdc, 120, POINT{ centerX, centerY - 400 },
                                          120, POINT{ centerX + 100, centerY - 280 }, 100000);

    DrawIntersectMinusEllipselePixel(hdc, 70, POINT{ centerX - 80, centerY + 150 },
                                          200, POINT{ centerX, centerY }, 100000);
    DrawIntersectMinusEllipselePixel(hdc, 70, POINT{ centerX + 80, centerY + 150 },
                                          200, POINT{ centerX, centerY }, 100000);

    DrawEllipselePixel(hdc, 50, POINT{ centerX - 160, centerY + 80 }, 10000);
    DrawEllipselePixel(hdc, 35, POINT{ centerX + 175, centerY + 100 }, 10000);

 
}

void DrawEllipselePixel(HDC hdc, int radious, POINT center, int maxCnt)
{
    int cnt = 0;

    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> disX(center.x - radious, center.x + radious);
    std::uniform_int_distribution<int> disY(center.y - radious, center.y + radious);

    while (true)
    {
        if (cnt > maxCnt)
            break;

        POINT newPos = { disX(gen), disY(gen) };
        if (InsideCheck(newPos, radious, center.x, center.y))
        {
            COLORREF color = SelectColor(newPos.y);
            SetPixel(hdc, newPos.x, newPos.y, color);
            cnt++;
        }
    }
}

void DrawIntersectEllipselePixel(HDC hdc, int radiousA, POINT centerA, int radiousB, POINT centerB, int maxCnt)
{
    int cnt = 0;

    int minX = min(centerA.x - radiousA, centerB.x - radiousB);
    int minY = min(centerA.y - radiousA, centerB.y - radiousB);
    int maxX = max(centerA.x + radiousA, centerB.x + radiousB);
    int maxY = max(centerA.y + radiousA, centerB.y + radiousB);

    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> disX(minX, maxX);
    std::uniform_int_distribution<int> disY(minY, maxY);

    while (true)
    {
        if (cnt > maxCnt)
            break;

        POINT newPos = { disX(gen), disY(gen) };
        if (InsideCheck(newPos, radiousA, centerA.x, centerA.y) && InsideCheck(newPos, radiousB, centerB.x, centerB.y))
        {
            COLORREF color = SelectColor(newPos.y);
            SetPixel(hdc, newPos.x, newPos.y, color);
            cnt++;
        }
    }
}

void DrawIntersectMinusEllipselePixel(HDC hdc, int radiousA, POINT centerA, int radiousB, POINT centerB, int maxCnt)
{
    int cnt = 0;

    int minX = min(centerA.x - radiousA, centerB.x - radiousB);
    int minY = min(centerA.y - radiousA, centerB.y - radiousB);
    int maxX = max(centerA.x + radiousA, centerB.x + radiousB);
    int maxY = max(centerA.y + radiousA, centerB.y + radiousB);

    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> disX(minX, maxX);
    std::uniform_int_distribution<int> disY(minY, maxY);

    while (true)
    {
        if (cnt > maxCnt)
            break;

        POINT newPos = { disX(gen), disY(gen) };
        if (InsideCheck(newPos, radiousA, centerA.x, centerA.y) && !InsideCheck(newPos, radiousB, centerB.x, centerB.y))
        {
            COLORREF color = SelectColor(newPos.y);
            SetPixel(hdc, newPos.x, newPos.y, color);
            cnt++;
        }
    }
}
//목요일까지
//과제3.애플 로고 출력.색깔 잇는 것으로.
//->SetPixel()을 이용해서 만든다.
//->근성 OK / 반복문 OK / 꼼수 X