// winAPIproject.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include <windows.h>
#include <tchar.h>

#pragma region WinAPI
/*
API
 운영체제가 응용프로그램 개발을 위해 제공하는 함수의 집합
 명령어 집합으로 어플리케이션 프로그램에서 오퍼레이팅 시스템의 기본적인 기능을 사용할 필요가 있을경우 API의 명령에 호출이 진행

 하드웨어            운영체제           응용프로그램
  API함수

장점
 운영체제가 같으면 같은 기능의 집합을 사용하기에 확장성 및 연동성 유지보수에 매우 유리
 윈도우스 != 리눅스

단점 
 사용하는 프로그래머의 역량에 따라 플랫폼에 대한 고착화가 발생
 C언어로 개발된 플랫폼의 한계를 극복하지 못한다 프로그래머의 모순?
 라이브러리 확장으로 해결할 수 있지만 역량이 많이 요구되기에 초심자는 힘드러보여..

API 구조
 진입점 / 루프 / Window Procedure 

*/
#pragma endregion

// 전역 변수:
HINSTANCE _hInstance;                              
/*
인스턴스 
 윈도우 os가 실행되고 있는 프로그램을 확인하기 위한 값
 같은 프로그램이면 일반적으로 같은 인스턴스 값을 가진다
 클래스가 메모리가 실제로 구현된 실체
 실행되고 있는 각각의 프로그램들

*/
HWND _hwnd; // 윈도우 창
LPCTSTR _IpszClass = _TEXT("WINDOW API");
const TCHAR* pszString = _T("WINDOW API");

/*
TCHAR는 프로젝트 문자셋 설정에 따라 자동적으로 변환 해주는 중간 매크로 자료형
타입 캐스팅을 유발해 char 또는 wchar로 변환
멀티와 유니코드 환경에서 별도의 수정 작업 없이 프로그램을 구동하기 위해서는 tchar문자열로 표현 권장
윈도우 어플에 사용하는 프로그램부턴 응용프로그램에서 문자열 상수를 쓰기위해서는 
중간 설정에 따라 char* -> wchar*로변환하는 _T매크로가 유용
*/

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

/*
 hInstance
  프로그램 인스턴스 핸들
 hPrevInstance
  이전의 실행된 인스턴스 핸들
 lpszCmdParam
  명령형으로 입력된 프로그램 인자
 nCmdShow
  프로그램이 시작된 형태
*/

int APIENTRY WinMain(_In_     HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_     LPSTR     lpszCmdParam,
                     _In_     int       nCmdShow)
{         
    /*
    윈메인의 역할
     윈도우 창을 세팅후 화면에 띄우기
      창을 띄우기 위해선 4가지 처리가 선행
     메세지 루프를 시작
    */

    _hInstance = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 윈도우 창 구조체 선언
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0; //클래스 여분 메모리
    wndClass.cbWndExtra = 0; //윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 백그라운드
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW); // 커서
    wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // 아이 콘
    wndClass.hInstance = hInstance; // 식별자
    wndClass.lpfnWndProc = WndProc; // 롱포인트 펑션 윈도우 프로시져
    wndClass.lpszClassName = pszString; // 클래스 이름
    wndClass.lpszMenuName = NULL; // 메뉴이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 스타일

    RegisterClass(&wndClass);

    // 화면에 윈도우창 생성
    _hwnd = CreateWindow
    (
        _IpszClass, // 클래스 식별자
        _IpszClass, // 윈도우 타이틀 바 이름
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
        MessageBox(NULL, TEXT("CreateWindow failed!"), TEXT("Error"), MB_OK); // 실패했다는 메세지 박스 출력
        return false;
    }

    ShowWindow(_hwnd, nCmdShow);
    //UpdateWindow(hWnd);

    // 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
    MSG message;
    //ZeroMemory(&message, sizeof(message)); 메세지를 0으로 초기화

    /*
     ★
      기본 메시지 루프입니다 
      GetMessage 메세지를 꺼내올 수 있을때 까지 대기
      메세지 큐로보터 하나의 메세지를 가져오는 역할을 수행
      다만 메세지 큐가 비어있을경우 메세지가 올때까지 대기
     
      peekMessage 메세지가 없더라도 반환이 된다
    */
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message); 
        DispatchMessage(&message);
    }

    /*
    TranslateMessage 
     키보드의 입력 메세지 처리를 담당한다
     입력된 키가 문자키인지 확인하고 대소문자 한명인지 WH_CHAR메세지를 발생

    DispatchMessage
     윈도우 프로시져에서 전달된 메세지를 실체 윈도우로 전달
              
    */
    return (int)message.wParam;
}

/*
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// HWND : 어느 윈도우에게 발생한 메세지인지 구분
// message : 메세지 구분 번호
// wParam : unsigned int 마우스 버튼의 상태/ 키보드 조합키의 상태를 전달
// lParam : unsigned int 마우스 클릭좌표를 전달
// 
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    /*
    WindowProcedure
     메세지를 운영체제에 전달 -> 운영체제는 강제로 호출이 된다
      윈메인이 아닌 운영체제에 의해 호출이 되는 콜백 함수이다
      윈도우 생성할 때는 반드시 지정을 해줘야한다
     윈도우 프로시저 내부에선 윈도우에서 발생한 모든 메세지를 처리하는 것이 아니라 특정 메세지만을 처리하고
     나머지 메세지는 DefwindowProc함수가 처리하는 로직설계가 일반적이다
    */

    HDC hdc;
    hdc->unused;

    switch (message)
    {
    case WM_CREATE:
        // 클래스의 생성자와 같은 기능 
        break;
    case WM_PAINT:
    {
            // 화면에 도형 그리기
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0); // 메세지 큐에 QUIT을 보내는 역할을 수행
                                     //Quit 메세지를 수신하는 GetMessage가 False를 반환하므로 메세지루프는 종료
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


/*
과제

타임어택 윈도우창 만들기
 10분?


한줄조사
 노트에 열심히 적어온다
 CallBack function, DC, GetDC, ReleaseDC, BeginPaint, WM_PAINT, PAINTSTRUCT

*/