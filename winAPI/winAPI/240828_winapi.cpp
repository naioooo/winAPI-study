// WinApiTest.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#pragma region  WinAPI
/*
▶ API (Application Programming Interface)
-> 운영체제가 응용 프로그램 개발을 위해 제공하는 함수의 집합이라고 할 수 있다.
-> 명령어의 집합으로 어플리케이션 프로그램에서 오퍼레이팅 시스템의 기본적인 기능을 사용할 필요가 있을 경우.
Api에서 명령어 호출이 진행된다.

EX)
하드 웨어 --------------- 운영 체제 (Windows) -------------- 응용 프로그램
(API 함수) -> 사용자가 윈도우에게 필요한 것을 함수형태로 받아온다.

▷ 장
-> 운영체제가 같으면 같은 기능의 장점을 사용하기에 확장성 및 연동성 / 그리고 유지보수에 매우 유리하다.
ㄴ 윈도우즈 != 리눅스


▷ 단
-> 처음하는 프로그래머의 역량에 따라 플랫폼에 대한 고착화가 발생할 수 있다. (WinAPI)
ㄴ C 언어로 개발된 플랫폼의 한계점을 극복하지 못한다는 프로그래머의 모순.
-> 이는 대부분의 타 라이브러리 확장으로 해결은 되지만, 프로그래머의 역량을 많이 요구하기 때문에
    이는 사람입장에서는 단점이라고 할 수 있다.

▷ API 구조
-> 크게 3가지만 기억하면 OK
-> 진입점 / 루프 (메세지) / Window Procedure


*/
#pragma endregion  

#include <Windows.h>
#include <tchar.h>

// 전역 변수
/*
 인스턴스
 -> 윈도우 OS가 현재 실행되고 있는 프로그램을 확인하기 위한 값.
 -> 같은 프로그램이면 일반적으로 같은 인스턴스 값을 가진다.
 -> 클래스가 메모리에 실제로 구현된 실체.
 -> 실행되고 있는 각각의 프로그램들.
*/

HINSTANCE _hInstance;
// 핸들 : 윈도우 창을 의미한다.
HWND _hwnd;
// 윈도우 타이틀
LPTSTR _lpszClass = TEXT("Windows API");
// TCHAR* pszString = _T("Windows API");

/*
LPSTR -> Long Pointer STR  -> char*
LPCSTR -> Long Pointer Const STR -> const char*
LPCTSTR -> const tchar*

▶ TCHAR
 -> 이 자료형은 프로젝트 문자셋 설정에 따라 자동적으로 변환을 해주는 중간 매크로 자료형
 -> Type Casting 을 유발하며, char 또는 Wchar_t로 변환한다.

 -> 멀티와 유니 환경에서 별도의 수정 작업 없이 프로그램을 구동하기 위해서는 TCHAR형으로
  문자열을 표현하는 것을 권장한다.

 -> 윈도우 어플리케이션을 사용하는 프로그램부터는 응용 프로그램에서 문자열 상수를 쓰기 위해서는 중간 설정에 따라
 char* -> wchar_t* 로 변환을 해주는 _T 매크로도 유효하다.

 // 전역 변수:
HINSTANCE hInst;
HWND _hwnd;
LPTSTR _lps2Class = TEXT("Windows API");
TCHAR* ps2String = _T("Windows API");

LPCSTR Scrpit1 = "ABC";
LPCWSTR Scrpit2 = L"ABC";
TCHAR* Scrpit3 = _T("ABC"); // 자동으로 바꿔 주지만, 절차가 생겨 느리다.
*/

// 콜백 함수
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
hInstance 프로그램 인스턴스 핸들
hPrevInstance 이전에 실행된 인스턴스 핸들
IpszCmdParam 명령형으로 입력한 프로그램 인자(수)
nCmdShow 프로그램이 시작될 형태 (최소화 / 보통 크기 등등...)
*/

// wWinMain world wide를 진입점으로 바꾸겠다.
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpszCmdParam,
                     int       nCmdShow)
{
    _hInstance = hInstance;

    /*
    winMain의 역할
    ㄴ 1. 윈도우 창을 세팅 후 화면에 띄우기.
        -> 화면에 창을 띄우기 위해서는 4가지 처리가 선행되어야 한다.
    ㄴ 2. 메세지 루프
    */

    // 1-1 윈도우창 구조체 선언 및 초기화
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // 클래스에 대한 여분 메모리를 할당 할꺼냐. // 클래스 여분 메모리
    wndClass.cbWndExtra = 0; // 윈도우 ``                             // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 배경색을 정의한다.  // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                     // 마우스
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // 화면 왼쪽 위의 아이콘을 다른 곳에서 소스를 불러와 띄우겠다. // 아이콘
    wndClass.hInstance = hInstance; // 윈도우 인스턴스                                   // 소유한 식별자 정보.
    wndClass.lpfnWndProc = (WNDPROC)WndProc; // Long Pointer Function Numbering Window Pocedure  // 윈도우 프로시저
    wndClass.lpszClassName = _lpszClass; // 윈도우 창 이름.                              // 클래스 이름.
    wndClass.lpszMenuName = NULL; // 우측의 메뉴 상자. (최소화, 닫기) // 메뉴이름.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                           // 윈도우 스타일

    // 1-2 윈도우 클래스 등록
    RegisterClass(&wndClass);

    // 1-3 화면에 보여줄 윈도우 창 생성.
    _hwnd = CreateWindow
    (
        _lpszClass,                 // 윈도우 클래스 식별자
        _lpszClass,                 // 윈도우 타이틀 바 이름
        WS_OVERLAPPEDWINDOW,        // 윈도우 스타일
        400,                        // 윈도우 화면 X 좌표
        100,                        // 윈도우 화면 Y 좌표
        800,                        // 윈도우 화면 가로크기.
        800,                        // 윈도우 화면 세로크기
        NULL,         // 부모 윈도우 -> NULL, GetDesktopWindow(), 윈도우 창이 여러개(게임창, 아이템경매장창 등) 필요하면 사용하게 되는 용도이다.
        (HMENU)NULL,                // 메뉴 핸들
        hInstance,                  // 인스턴스 지정
        NULL                        // 윈도우의 자식 윈도우를 생성하면 지정 / 아니라면 NULL
    );

    // 1-4 화면에 윈도우창 보여주기
    ShowWindow(_hwnd, nCmdShow);
    // ex) 플레이어의 위치가 바뀌었을 때 등등 업데이트 (갱신용)
    //UpdateWindow(_hwnd);

    // MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체.
    MSG message;
    // ZeroMemory(&message, nCmdShow);

    // ★★★★★
    // 2. 기본 메시지 루프.
    
    // GetMessage : 메세지를 꺼내올 수 있을때까지 대기.
    // ㄴ 메세지 큐로부터 하나의 메세지를 가져오는 역할을 수행한다.
    // ㄴ 다만 메세지 큐가 비어있을 경우 메세지가 들어올때까지 대기.

    // - PeekMessage : 메세지가 없더라도 반환이 된다. -> 게임에서 쓰인다.

    //while (true)
    //{
    //    if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) // ex) 차가 들어왔나, 안들어왔나 확인하는 도중 차가 확인안할때 들어오면 확인할수없기때문에,
    //                                                        // 따라서 정밀한 시간의 Tick을 사용해서 업데이트하게 만들어야 확인할수있다.
    //    {
    //        if (message.message == WM_QUIT) break;
    //        TranslateMessage(&message);
    //        DispatchMessage(&message);
    //    }
    //}

    while (GetMessage(&message, 0, 0, 0))
    {
        //if (!TranslateAccelerator(message.hwnd, hAccelTable, &message)) // 시동코드
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    /*
    TranslateMessage : 키보드의 입력 메세지 처리를 담당한다. 입력된 키가 문자 키인지 확인하고, 대문자 혹은 소문자,
    한글, 영문인지에 대한 wM_CHAR 메세지를 발생 시킨다.

    DispatchMessage : 윈도우 프로시저에서 전달된 메세지를 실제 윈도우로 전달한다.
    */

    return (int)message.wParam;
}



//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

// 윈도우 프로시저
// hwnd : 어느 윈도우에서 발생한 메세지 인지 구분.
// IMessage : 메세지 구분 번호
// wParam : unsigned int 마우스 버튼의 상태 / 키보드 조합 키의 상태를 전달한다.
// lParam : unsigned long 마우스 클릭 좌표를 전달
LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    /*
    Window Procedure

    - 메세지를 운영체제에 전달 -> 운영체제는 강제로 호출이 된다.
       ㄴ WinMain이 아닌 운영체제에 의해 호출이 되는 콜백 함수라고 할 수 있다.
       ㄴ 윈도우를 생성할때는 반드시 지정을 해주어야 한다.

    - 윈도우 프로시저 내부에서는 윈도우에서 발생한 모든 메세지를 처리한느 것이 아니라 특정 메세지만을 처리하고,
    나머지 메세지는 DefWindowProc 함수가 처리하도록 로직을 설계하는 것이 일반적.    
    */

    //★★★★★
    HDC hdc; // -> Handle Device Context ->GDI를 쓰기위한 객체 -> GDI는 Grapic Device Interface로 화면처리와 그래픽등 모든 출력장치를 제어한다.
    // GDI는 BMP로 이루어져 있는데 장점으로 화소가 좋다. 단점으로 용량이 크다, A(알파, 투명도)의 부재.
    // PNG는 보간이 이루어지는데, 두 색의 중간값을 찾아 보간한다.
    // 보간이 안들어가면 회전이 괴롭힌다? -> 마우스에 따라 회전하며 움직이는 총(ex)엔터더건전)
    // A가 생긴 GDI+가 있다.

    PAINTSTRUCT ps;

    const char str[] = "오케이";
    // ㄴ char[]
    // ㄴ char*

    // RECT -> 정적, *LPRECT -> 가변, 동적
    // 사각형의 좌표를 저장하기 위한 자료형.
    // ㄴ 시작점 SX, SY (L, T) / 끝점 EX, EY (R, B)가 존재한다.
    RECT rc = { 100, 100, 200, 200 };
    /*
     도형 : 삼,   사,    원,    다.
     ->   애매,  좋음,  죄악,  애매
        (정밀도)       필요악 (너무)

     -> 삼각형과 다각형은 폴리곤으로 그릴순있다.

    */

    switch (IMessage)
    {
    case WM_CREATE: // 생성자

        break;

    /*
    WM_pAINT
        
    - 윈도우를 다시 그려야 할 때 발생하는 메세지

    ㄴ 윈도우가 처음 만들어 졌을때 발생한다.
    ㄴ 윈도우 크기를 조절할때
    ㄴ 윈도우가 다른 윈도우에 가려졌다가 다시 보일때
    ㄴ 관련 함수가 호출될 때.        
    */
    // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형등등 화면에 보이는 모든 것)
    case WM_PAINT: // 그리는기능
    {
        hdc = BeginPaint(hWnd, &ps);

        SetPixel(hdc, 300, 200, RGB(255, 0, 0));

        for (int i = 0; i < 10000; i++)
        {
            SetPixel(hdc, rand() % 800, rand() % 800, RGB(rand()%255, rand() % 255, rand() % 255,));
        }

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                SetPixel(hdc, 400 + i, 300 + j, RGB(255, i * 2, j * 2));
            }
        }

        // 원 그리기
        Ellipse(hdc, 300, 100, 200, 200);

        // 사각형 그리기
        Rectangle(hdc, 100, 100, 200, 200);        
        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
        
        // TODO: 여기에 hdc를 사용하는  그리기 코드를 추가합니다...
        /*
        문자셋
        (멀티바이트)    (유니코드World Wide)    (컴퓨터한테 맡기는것)
        strlen(x, y) -> wcslen -> _tcslen 
        strcpy(x, y) -> wcscpy -> _tcscpy
        strcmp(x, y) -> ....
        strcat(x, y) -> ....
        +
        strtok(x) 문자열 자르기 -> ....

        strchar 문자 찾기 -> ....
        strstr 문자열 찾기 -> ....

        strlen()
        strnlen()
        strlen_s()
        */

        // 문자열 / 문자열 길이
        // ㄴ strlen() 할당 받은 메모리에 바인딩 된 문자열에서 NULL 값을 제외한 문자열 길이.
        TextOut(hdc, 300, 300, _T("과제가 너무 재밌다^^"), strlen("과제가 너무 재밌다^^"));

        SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, 300, 400, _T("더 많은 과제가 필요하다."), strlen("더 많은 과제가 필요하다."));

        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 400);
        /*
        WINGDIAPI BOOL  WINAPI TextOutA( _In_ HDC hdc, _In_ int x, _In_ int y, _In_reads_(c) LPCSTR lpString, _In_ int c);
        // _In_reads_ 는 읽기만하고, 포인터는 받지 않는다.
        // _outpu_reads는 무조건 읽기만. 읽기전용.
        */

        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 200);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);

        SetTextColor(hdc, RGB(0, 0, 255));

        TextOut(hdc, 350, 500, str, strlen(str));
        ReleaseDC(hWnd, hdc);
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
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_DESTROY:
        // PostQuitMessage : 이 함수는 메세지 큐에 QUIT 메세지를 보내는 역할을 수행.
        // Quit 메세지를 수신하는 순간 GetMessage가 FALSE를 반환하므로 메세지 루프는 종료된다.
        PostQuitMessage(0);
        break;
    }
    
    return (DefWindowProc(hWnd, IMessage, wParam, lParam));
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}



/*
과제1.

한줄 조사.
- 노트에 열심히 적어온다. (+공부)
 ㄴ CallBack Function에 대해서, DC, GetDC, ReleaseDC, BeginPaint / EndPaint, WM_PAINT, PAINTSTRUCT

 타임어택. 윈도우 창 만들기
 - 시간은 10분.
 -> 실패시 깜지 -> 못한 인원 x 2

*/


// 8 / 28
/*
과제1.
 WinApi 출력
 -> MovetoEx() + LineTo()를 이용할것.
 -> 자기 이름 출력 (한글) + UnrealEngine (영문)
  ㄴ 크기는 800 x 800 기준 화면에 절반을 채우는 크기로 양분할것.

 - 마우스 왼쪽을 누르면 한글자씩 출력 되고, 우 클릭을 하면 한글자씩 지워진다. (이름에만 적용)

 ※ 도형 관련 함수 사용 금지.

 과제2. 구구단

 -> 예외처리 필수
  ㄴ 구구단의 본질 (1단 이하 X / 9단 이상 X)

-> 마우스 왼쪽 클릭을 했을 시 1단씩 출력이 되고, 우클릭을 하면 1단씩 지워진다.
-> 그리고 3단계 마다 개행을 한다.

목요일까지
과제3. 애플 로고 출력. 색깔 잇는 것으로.
-> SetPixel()을 이용해서 만든다.
-> 근성 OK / 반복문 OK / 꼼수 X

한줄 조사.
 -> SetTimer
 -> KillTimer
 -> InvaildateRect -> 1, 2번 과제에 필요할것.

*/