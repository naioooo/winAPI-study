// WinApiTest.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//

#pragma region  WinAPI
/*
�� API (Application Programming Interface)
-> �ü���� ���� ���α׷� ������ ���� �����ϴ� �Լ��� �����̶�� �� �� �ִ�.
-> ��ɾ��� �������� ���ø����̼� ���α׷����� ���۷����� �ý����� �⺻���� ����� ����� �ʿ䰡 ���� ���.
Api���� ��ɾ� ȣ���� ����ȴ�.

EX)
�ϵ� ���� --------------- � ü�� (Windows) -------------- ���� ���α׷�
(API �Լ�) -> ����ڰ� �����쿡�� �ʿ��� ���� �Լ����·� �޾ƿ´�.

�� ��
-> �ü���� ������ ���� ����� ������ ����ϱ⿡ Ȯ�强 �� ������ / �׸��� ���������� �ſ� �����ϴ�.
�� �������� != ������


�� ��
-> ó���ϴ� ���α׷����� ������ ���� �÷����� ���� ����ȭ�� �߻��� �� �ִ�. (WinAPI)
�� C ���� ���ߵ� �÷����� �Ѱ����� �غ����� ���Ѵٴ� ���α׷����� ���.
-> �̴� ��κ��� Ÿ ���̺귯�� Ȯ������ �ذ��� ������, ���α׷����� ������ ���� �䱸�ϱ� ������
    �̴� ������忡���� �����̶�� �� �� �ִ�.

�� API ����
-> ũ�� 3������ ����ϸ� OK
-> ������ / ���� (�޼���) / Window Procedure


*/
#pragma endregion  

#include <Windows.h>
#include <tchar.h>

// ���� ����
/*
 �ν��Ͻ�
 -> ������ OS�� ���� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��.
 -> ���� ���α׷��̸� �Ϲ������� ���� �ν��Ͻ� ���� ������.
 -> Ŭ������ �޸𸮿� ������ ������ ��ü.
 -> ����ǰ� �ִ� ������ ���α׷���.
*/

HINSTANCE _hInstance;
// �ڵ� : ������ â�� �ǹ��Ѵ�.
HWND _hwnd;
// ������ Ÿ��Ʋ
LPTSTR _lpszClass = TEXT("Windows API");
// TCHAR* pszString = _T("Windows API");

/*
LPSTR -> Long Pointer STR  -> char*
LPCSTR -> Long Pointer Const STR -> const char*
LPCTSTR -> const tchar*

�� TCHAR
 -> �� �ڷ����� ������Ʈ ���ڼ� ������ ���� �ڵ������� ��ȯ�� ���ִ� �߰� ��ũ�� �ڷ���
 -> Type Casting �� �����ϸ�, char �Ǵ� Wchar_t�� ��ȯ�Ѵ�.

 -> ��Ƽ�� ���� ȯ�濡�� ������ ���� �۾� ���� ���α׷��� �����ϱ� ���ؼ��� TCHAR������
  ���ڿ��� ǥ���ϴ� ���� �����Ѵ�.

 -> ������ ���ø����̼��� ����ϴ� ���α׷����ʹ� ���� ���α׷����� ���ڿ� ����� ���� ���ؼ��� �߰� ������ ����
 char* -> wchar_t* �� ��ȯ�� ���ִ� _T ��ũ�ε� ��ȿ�ϴ�.

 // ���� ����:
HINSTANCE hInst;
HWND _hwnd;
LPTSTR _lps2Class = TEXT("Windows API");
TCHAR* ps2String = _T("Windows API");

LPCSTR Scrpit1 = "ABC";
LPCWSTR Scrpit2 = L"ABC";
TCHAR* Scrpit3 = _T("ABC"); // �ڵ����� �ٲ� ������, ������ ���� ������.
*/

// �ݹ� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
hInstance ���α׷� �ν��Ͻ� �ڵ�
hPrevInstance ������ ����� �ν��Ͻ� �ڵ�
IpszCmdParam ��������� �Է��� ���α׷� ����(��)
nCmdShow ���α׷��� ���۵� ���� (�ּ�ȭ / ���� ũ�� ���...)
*/

// wWinMain world wide�� ���������� �ٲٰڴ�.
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpszCmdParam,
                     int       nCmdShow)
{
    _hInstance = hInstance;

    /*
    winMain�� ����
    �� 1. ������ â�� ���� �� ȭ�鿡 ����.
        -> ȭ�鿡 â�� ���� ���ؼ��� 4���� ó���� ����Ǿ�� �Ѵ�.
    �� 2. �޼��� ����
    */

    // 1-1 ������â ����ü ���� �� �ʱ�ȭ
    WNDCLASS wndClass;
    wndClass.cbClsExtra = 0; // Ŭ������ ���� ���� �޸𸮸� �Ҵ� �Ҳ���. // Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; // ������ ``                             // ������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ������ �����Ѵ�.  // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                                     // ���콺
    wndClass.hIcon = LoadIcon(hInstance, IDI_APPLICATION); // ȭ�� ���� ���� �������� �ٸ� ������ �ҽ��� �ҷ��� ���ڴ�. // ������
    wndClass.hInstance = hInstance; // ������ �ν��Ͻ�                                   // ������ �ĺ��� ����.
    wndClass.lpfnWndProc = (WNDPROC)WndProc; // Long Pointer Function Numbering Window Pocedure  // ������ ���ν���
    wndClass.lpszClassName = _lpszClass; // ������ â �̸�.                              // Ŭ���� �̸�.
    wndClass.lpszMenuName = NULL; // ������ �޴� ����. (�ּ�ȭ, �ݱ�) // �޴��̸�.
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                           // ������ ��Ÿ��

    // 1-2 ������ Ŭ���� ���
    RegisterClass(&wndClass);

    // 1-3 ȭ�鿡 ������ ������ â ����.
    _hwnd = CreateWindow
    (
        _lpszClass,                 // ������ Ŭ���� �ĺ���
        _lpszClass,                 // ������ Ÿ��Ʋ �� �̸�
        WS_OVERLAPPEDWINDOW,        // ������ ��Ÿ��
        400,                        // ������ ȭ�� X ��ǥ
        100,                        // ������ ȭ�� Y ��ǥ
        800,                        // ������ ȭ�� ����ũ��.
        800,                        // ������ ȭ�� ����ũ��
        NULL,         // �θ� ������ -> NULL, GetDesktopWindow(), ������ â�� ������(����â, �����۰����â ��) �ʿ��ϸ� ����ϰ� �Ǵ� �뵵�̴�.
        (HMENU)NULL,                // �޴� �ڵ�
        hInstance,                  // �ν��Ͻ� ����
        NULL                        // �������� �ڽ� �����츦 �����ϸ� ���� / �ƴ϶�� NULL
    );

    // 1-4 ȭ�鿡 ������â �����ֱ�
    ShowWindow(_hwnd, nCmdShow);
    // ex) �÷��̾��� ��ġ�� �ٲ���� �� ��� ������Ʈ (���ſ�)
    //UpdateWindow(_hwnd);

    // MSG : �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü.
    MSG message;
    // ZeroMemory(&message, nCmdShow);

    // �ڡڡڡڡ�
    // 2. �⺻ �޽��� ����.
    
    // GetMessage : �޼����� ������ �� ���������� ���.
    // �� �޼��� ť�κ��� �ϳ��� �޼����� �������� ������ �����Ѵ�.
    // �� �ٸ� �޼��� ť�� ������� ��� �޼����� ���ö����� ���.

    // - PeekMessage : �޼����� ������ ��ȯ�� �ȴ�. -> ���ӿ��� ���δ�.

    //while (true)
    //{
    //    if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) // ex) ���� ���Գ�, �ȵ��Գ� Ȯ���ϴ� ���� ���� Ȯ�ξ��Ҷ� ������ Ȯ���Ҽ����⶧����,
    //                                                        // ���� ������ �ð��� Tick�� ����ؼ� ������Ʈ�ϰ� ������ Ȯ���Ҽ��ִ�.
    //    {
    //        if (message.message == WM_QUIT) break;
    //        TranslateMessage(&message);
    //        DispatchMessage(&message);
    //    }
    //}

    while (GetMessage(&message, 0, 0, 0))
    {
        //if (!TranslateAccelerator(message.hwnd, hAccelTable, &message)) // �õ��ڵ�
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    /*
    TranslateMessage : Ű������ �Է� �޼��� ó���� ����Ѵ�. �Էµ� Ű�� ���� Ű���� Ȯ���ϰ�, �빮�� Ȥ�� �ҹ���,
    �ѱ�, ���������� ���� wM_CHAR �޼����� �߻� ��Ų��.

    DispatchMessage : ������ ���ν������� ���޵� �޼����� ���� ������� �����Ѵ�.
    */

    return (int)message.wParam;
}



//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//

// ������ ���ν���
// hwnd : ��� �����쿡�� �߻��� �޼��� ���� ����.
// IMessage : �޼��� ���� ��ȣ
// wParam : unsigned int ���콺 ��ư�� ���� / Ű���� ���� Ű�� ���¸� �����Ѵ�.
// lParam : unsigned long ���콺 Ŭ�� ��ǥ�� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam)
{
    /*
    Window Procedure

    - �޼����� �ü���� ���� -> �ü���� ������ ȣ���� �ȴ�.
       �� WinMain�� �ƴ� �ü���� ���� ȣ���� �Ǵ� �ݹ� �Լ���� �� �� �ִ�.
       �� �����츦 �����Ҷ��� �ݵ�� ������ ���־�� �Ѵ�.

    - ������ ���ν��� ���ο����� �����쿡�� �߻��� ��� �޼����� ó���Ѵ� ���� �ƴ϶� Ư�� �޼������� ó���ϰ�,
    ������ �޼����� DefWindowProc �Լ��� ó���ϵ��� ������ �����ϴ� ���� �Ϲ���.    
    */

    //�ڡڡڡڡ�
    HDC hdc; // -> Handle Device Context ->GDI�� �������� ��ü -> GDI�� Grapic Device Interface�� ȭ��ó���� �׷��ȵ� ��� �����ġ�� �����Ѵ�.
    // GDI�� BMP�� �̷���� �ִµ� �������� ȭ�Ұ� ����. �������� �뷮�� ũ��, A(����, ����)�� ����.
    // PNG�� ������ �̷�����µ�, �� ���� �߰����� ã�� �����Ѵ�.
    // ������ �ȵ��� ȸ���� ��������? -> ���콺�� ���� ȸ���ϸ� �����̴� ��(ex)���ʹ�����)
    // A�� ���� GDI+�� �ִ�.

    PAINTSTRUCT ps;

    const char str[] = "������";
    // �� char[]
    // �� char*

    // RECT -> ����, *LPRECT -> ����, ����
    // �簢���� ��ǥ�� �����ϱ� ���� �ڷ���.
    // �� ������ SX, SY (L, T) / ���� EX, EY (R, B)�� �����Ѵ�.
    RECT rc = { 100, 100, 200, 200 };
    /*
     ���� : ��,   ��,    ��,    ��.
     ->   �ָ�,  ����,  �˾�,  �ָ�
        (���е�)       �ʿ�� (�ʹ�)

     -> �ﰢ���� �ٰ����� ���������� �׸����ִ�.

    */

    switch (IMessage)
    {
    case WM_CREATE: // ������

        break;

    /*
    WM_pAINT
        
    - �����츦 �ٽ� �׷��� �� �� �߻��ϴ� �޼���

    �� �����찡 ó�� ����� ������ �߻��Ѵ�.
    �� ������ ũ�⸦ �����Ҷ�
    �� �����찡 �ٸ� �����쿡 �������ٰ� �ٽ� ���϶�
    �� ���� �Լ��� ȣ��� ��.        
    */
    // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ������� ȭ�鿡 ���̴� ��� ��)
    case WM_PAINT: // �׸��±��
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

        // �� �׸���
        Ellipse(hdc, 300, 100, 200, 200);

        // �簢�� �׸���
        Rectangle(hdc, 100, 100, 200, 200);        
        Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
        
        // TODO: ���⿡ hdc�� ����ϴ�  �׸��� �ڵ带 �߰��մϴ�...
        /*
        ���ڼ�
        (��Ƽ����Ʈ)    (�����ڵ�World Wide)    (��ǻ������ �ñ�°�)
        strlen(x, y) -> wcslen -> _tcslen 
        strcpy(x, y) -> wcscpy -> _tcscpy
        strcmp(x, y) -> ....
        strcat(x, y) -> ....
        +
        strtok(x) ���ڿ� �ڸ��� -> ....

        strchar ���� ã�� -> ....
        strstr ���ڿ� ã�� -> ....

        strlen()
        strnlen()
        strlen_s()
        */

        // ���ڿ� / ���ڿ� ����
        // �� strlen() �Ҵ� ���� �޸𸮿� ���ε� �� ���ڿ����� NULL ���� ������ ���ڿ� ����.
        TextOut(hdc, 300, 300, _T("������ �ʹ� ��մ�^^"), strlen("������ �ʹ� ��մ�^^"));

        SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, 300, 400, _T("�� ���� ������ �ʿ��ϴ�."), strlen("�� ���� ������ �ʿ��ϴ�."));

        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 400);
        /*
        WINGDIAPI BOOL  WINAPI TextOutA( _In_ HDC hdc, _In_ int x, _In_ int y, _In_reads_(c) LPCSTR lpString, _In_ int c);
        // _In_reads_ �� �б⸸�ϰ�, �����ʹ� ���� �ʴ´�.
        // _outpu_reads�� ������ �б⸸. �б�����.
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
        // PostQuitMessage : �� �Լ��� �޼��� ť�� QUIT �޼����� ������ ������ ����.
        // Quit �޼����� �����ϴ� ���� GetMessage�� FALSE�� ��ȯ�ϹǷ� �޼��� ������ ����ȴ�.
        PostQuitMessage(0);
        break;
    }
    
    return (DefWindowProc(hWnd, IMessage, wParam, lParam));
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
����1.

���� ����.
- ��Ʈ�� ������ ����´�. (+����)
 �� CallBack Function�� ���ؼ�, DC, GetDC, ReleaseDC, BeginPaint / EndPaint, WM_PAINT, PAINTSTRUCT

 Ÿ�Ӿ���. ������ â �����
 - �ð��� 10��.
 -> ���н� ���� -> ���� �ο� x 2

*/


// 8 / 28
/*
����1.
 WinApi ���
 -> MovetoEx() + LineTo()�� �̿��Ұ�.
 -> �ڱ� �̸� ��� (�ѱ�) + UnrealEngine (����)
  �� ũ��� 800 x 800 ���� ȭ�鿡 ������ ä��� ũ��� ����Ұ�.

 - ���콺 ������ ������ �ѱ��ھ� ��� �ǰ�, �� Ŭ���� �ϸ� �ѱ��ھ� ��������. (�̸����� ����)

 �� ���� ���� �Լ� ��� ����.

 ����2. ������

 -> ����ó�� �ʼ�
  �� �������� ���� (1�� ���� X / 9�� �̻� X)

-> ���콺 ���� Ŭ���� ���� �� 1�ܾ� ����� �ǰ�, ��Ŭ���� �ϸ� 1�ܾ� ��������.
-> �׸��� 3�ܰ� ���� ������ �Ѵ�.

����ϱ���
����3. ���� �ΰ� ���. ���� �մ� ������.
-> SetPixel()�� �̿��ؼ� �����.
-> �ټ� OK / �ݺ��� OK / �ļ� X

���� ����.
 -> SetTimer
 -> KillTimer
 -> InvaildateRect -> 1, 2�� ������ �ʿ��Ұ�.

*/