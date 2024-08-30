// winAPIproject.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.

#include <windows.h>
#include <tchar.h>

#pragma region WinAPI
/*
API
 �ü���� �������α׷� ������ ���� �����ϴ� �Լ��� ����
 ��ɾ� �������� ���ø����̼� ���α׷����� ���۷����� �ý����� �⺻���� ����� ����� �ʿ䰡 ������� API�� ��ɿ� ȣ���� ����

 �ϵ����            �ü��           �������α׷�
  API�Լ�

����
 �ü���� ������ ���� ����� ������ ����ϱ⿡ Ȯ�强 �� ������ ���������� �ſ� ����
 �����콺 != ������

���� 
 ����ϴ� ���α׷����� ������ ���� �÷����� ���� ����ȭ�� �߻�
 C���� ���ߵ� �÷����� �Ѱ踦 �غ����� ���Ѵ� ���α׷����� ���?
 ���̺귯�� Ȯ������ �ذ��� �� ������ ������ ���� �䱸�Ǳ⿡ �ʽ��ڴ� ���巯����..

API ����
 ������ / ���� / Window Procedure 

*/
#pragma endregion

// ���� ����:
HINSTANCE _hInstance;                              
/*
�ν��Ͻ� 
 ������ os�� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��
 ���� ���α׷��̸� �Ϲ������� ���� �ν��Ͻ� ���� ������
 Ŭ������ �޸𸮰� ������ ������ ��ü
 ����ǰ� �ִ� ������ ���α׷���

*/
HWND _hwnd; // ������ â
LPCTSTR _IpszClass = _TEXT("WINDOW API");
const TCHAR* pszString = _T("WINDOW API");

/*
TCHAR�� ������Ʈ ���ڼ� ������ ���� �ڵ������� ��ȯ ���ִ� �߰� ��ũ�� �ڷ���
Ÿ�� ĳ������ ������ char �Ǵ� wchar�� ��ȯ
��Ƽ�� �����ڵ� ȯ�濡�� ������ ���� �۾� ���� ���α׷��� �����ϱ� ���ؼ��� tchar���ڿ��� ǥ�� ����
������ ���ÿ� ����ϴ� ���α׷����� �������α׷����� ���ڿ� ����� �������ؼ��� 
�߰� ������ ���� char* -> wchar*�κ�ȯ�ϴ� _T��ũ�ΰ� ����
*/

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

/*
 hInstance
  ���α׷� �ν��Ͻ� �ڵ�
 hPrevInstance
  ������ ����� �ν��Ͻ� �ڵ�
 lpszCmdParam
  ��������� �Էµ� ���α׷� ����
 nCmdShow
  ���α׷��� ���۵� ����
*/

int APIENTRY WinMain(_In_     HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_     LPSTR     lpszCmdParam,
                     _In_     int       nCmdShow)
{         
    /*
    �������� ����
     ������ â�� ������ ȭ�鿡 ����
      â�� ���� ���ؼ� 4���� ó���� ����
     �޼��� ������ ����
    */

    _hInstance = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    // ������ â ����ü ����
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0; //Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0; //������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��׶���
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW); // Ŀ��
    wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION); // ���� ��
    wndClass.hInstance = hInstance; // �ĺ���
    wndClass.lpfnWndProc = WndProc; // ������Ʈ ��� ������ ���ν���
    wndClass.lpszClassName = pszString; // Ŭ���� �̸�
    wndClass.lpszMenuName = NULL; // �޴��̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ ��Ÿ��

    RegisterClass(&wndClass);

    // ȭ�鿡 ������â ����
    _hwnd = CreateWindow
    (
        _IpszClass, // Ŭ���� �ĺ���
        _IpszClass, // ������ Ÿ��Ʋ �� �̸�
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
        MessageBox(NULL, TEXT("CreateWindow failed!"), TEXT("Error"), MB_OK); // �����ߴٴ� �޼��� �ڽ� ���
        return false;
    }

    ShowWindow(_hwnd, nCmdShow);
    //UpdateWindow(hWnd);

    // �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
    MSG message;
    //ZeroMemory(&message, sizeof(message)); �޼����� 0���� �ʱ�ȭ

    /*
     ��
      �⺻ �޽��� �����Դϴ� 
      GetMessage �޼����� ������ �� ������ ���� ���
      �޼��� ť�κ��� �ϳ��� �޼����� �������� ������ ����
      �ٸ� �޼��� ť�� ���������� �޼����� �ö����� ���
     
      peekMessage �޼����� ������ ��ȯ�� �ȴ�
    */
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message); 
        DispatchMessage(&message);
    }

    /*
    TranslateMessage 
     Ű������ �Է� �޼��� ó���� ����Ѵ�
     �Էµ� Ű�� ����Ű���� Ȯ���ϰ� ��ҹ��� �Ѹ����� WH_CHAR�޼����� �߻�

    DispatchMessage
     ������ ���ν������� ���޵� �޼����� ��ü ������� ����
              
    */
    return (int)message.wParam;
}

/*
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
// HWND : ��� �����쿡�� �߻��� �޼������� ����
// message : �޼��� ���� ��ȣ
// wParam : unsigned int ���콺 ��ư�� ����/ Ű���� ����Ű�� ���¸� ����
// lParam : unsigned int ���콺 Ŭ����ǥ�� ����
// 
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    /*
    WindowProcedure
     �޼����� �ü���� ���� -> �ü���� ������ ȣ���� �ȴ�
      �������� �ƴ� �ü���� ���� ȣ���� �Ǵ� �ݹ� �Լ��̴�
      ������ ������ ���� �ݵ�� ������ ������Ѵ�
     ������ ���ν��� ���ο��� �����쿡�� �߻��� ��� �޼����� ó���ϴ� ���� �ƴ϶� Ư�� �޼������� ó���ϰ�
     ������ �޼����� DefwindowProc�Լ��� ó���ϴ� �������谡 �Ϲ����̴�
    */

    HDC hdc;
    hdc->unused;

    switch (message)
    {
    case WM_CREATE:
        // Ŭ������ �����ڿ� ���� ��� 
        break;
    case WM_PAINT:
    {
            // ȭ�鿡 ���� �׸���
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0); // �޼��� ť�� QUIT�� ������ ������ ����
                                     //Quit �޼����� �����ϴ� GetMessage�� False�� ��ȯ�ϹǷ� �޼��������� ����
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


/*
����

Ÿ�Ӿ��� ������â �����
 10��?


��������
 ��Ʈ�� ������ ����´�
 CallBack function, DC, GetDC, ReleaseDC, BeginPaint, WM_PAINT, PAINTSTRUCT

*/