#include "Stdafx.h"
#include <sstream> // std::istringstream
#include <string>  // std::string

// 전역 변수:

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

HINSTANCE _hInstance;
HWND      _hWnd;
POINT     _ptMouse;

struct BodyPart
{
    vector<POINT> points;
    COLORREF color;
};

POINT cen;
vector<BodyPart> _bodyParts;
vector<vector<POINT>> _polygons;

string _background = "{x=2 y=788} {x=0 y=433} {x=795 y=441} {x=798 y=792} {x=794 y=800} {x=8 y=800}";
string _face = "{x=207 y=237} {x=196 y=403} {x=202 y=445} {x=210 y=490} {x=225 y=521} {x=237 y=550} {x=251 y=580} {x=261 y=605} {x=273 y=618} {x=292 y=631} {x=301 y=635} {x=321 y=639} {x=339 y=640} {x=361 y=642} {x=384 y=643} {x=399 y=644} {x=435 y=643} {x=460 y=642} {x=477 y=638} {x=506 y=635} {x=516 y=632} {x=526 y=626} {x=541 y=612} {x=555 y=596} {x=567 y=578} {x=574 y=566} {x=579 y=553} {x=581 y=543} {x=587 y=524} {x=589 y=500} {x=590 y=469} {x=593 y=459} {x=597 y=447} {x=596 y=424} {x=595 y=404} {x=597 y=377} {x=599 y=341} {x=600 y=323} {x=600 y=296} {x=595 y=267} {x=591 y=256} {x=580 y=235} {x=577 y=231}";
string _hair = "{ x = 189 y = 191 } {x = 161 y = 232} {x = 153 y = 274} {x = 145 y = 312} {x = 144 y = 348} {x = 150 y = 375} {x = 166 y = 392} {x = 212 y = 407} {x = 242 y = 407} {x = 294 y = 411} {x = 313 y = 412} {x = 335 y = 406} {x = 345 y = 382} {x = 345 y = 347} {x = 351 y = 327} {x = 361 y = 311} {x = 377 y = 294} {x = 397 y = 282} {x = 425 y = 276} {x = 445 y = 280} {x = 463 y = 296} {x = 476 y = 328} {x = 478 y = 340} {x = 478 y = 344} {x = 484 y = 365} {x = 490 y = 375} {x = 508 y = 384} {x = 547 y = 385} {x = 569 y = 382} {x = 596 y = 374} {x = 608 y = 366} {x = 617 y = 354} {x = 626 y = 331} {x = 628 y = 307} {x = 625 y = 284} {x = 615 y = 253} {x = 605 y = 222} {x = 600 y = 204} {x = 581 y = 169} {x = 552 y = 140} {x = 526 y = 124} {x = 494 y = 121} {x = 427 y = 120} {x = 387 y = 116} {x = 352 y = 114} {x = 312 y = 119} {x = 278 y = 132} {x = 246 y = 147} {x = 206 y = 163} {x = 196 y = 173}";; // 머리
string _eye1 = "{x=286 y=431} {x=278 y=447} {x=279 y=450} {x=283 y=455} {x=292 y=456} {x=303 y=456} {x=314 y=456} {x=323 y=456} {x=336 y=456} {x=344 y=456} {x=349 y=451} {x=353 y=443} {x=353 y=434} {x=352 y=428} {x=351 y=426} {x=350 y=426} {x=349 y=425} {x=348 y=422} {x=335 y=422} {x=325 y=422} {x=316 y=422} {x=307 y=423} {x=294 y=427} {x=290 y=430}"; // 눈
string _eye2 = "{x=458 y=418} {x=456 y=427} {x=456 y=440} {x=462 y=443} {x=474 y=445} {x=503 y=450} {x=511 y=448} {x=519 y=443} {x=522 y=437} {x=524 y=431} {x=525 y=422} {x=524 y=417} {x=523 y=413} {x=515 y=412} {x=498 y=412} {x=490 y=412} {x=485 y=412} {x=474 y=414} {x=470 y=416}";
string _pupil1 = "{x=309 y=430} {x=303 y=441} {x=303 y=444} {x=307 y=448} {x=310 y=449} {x=316 y=450} {x=322 y=450} {x=327 y=449} {x=333 y=447} {x=339 y=444} {x=340 y=443} {x=341 y=436} {x=341 y=431} {x=341 y=430} {x=334 y=429} {x=324 y=428} {x=320 y=428} {x=319 y=428}"; // 눈동자
string _pupil2 = "{x=485 y=417} {x=482 y=426} {x=482 y=434} {x=485 y=438} {x=492 y=440} {x=500 y=440} {x=507 y=438} {x=512 y=431} {x=513 y=422} {x=513 y=420} {x=506 y=418} {x=502 y=418} {x=499 y=416}";
string _nose = "{x=396 y=435} {x=383 y=443} {x=379 y=451} {x=379 y=467} {x=378 y=475} {x=377 y=480} {x=372 y=486} {x=367 y=489} {x=363 y=492} {x=359 y=497} {x=359 y=503} {x=358 y=508} {x=360 y=513} {x=371 y=516} {x=380 y=517} {x=392 y=517} {x=408 y=517} {x=413 y=517} {x=428 y=516} {x=435 y=514} {x=443 y=512} {x=449 y=509} {x=452 y=501} {x=450 y=493} {x=448 y=489} {x=447 y=485} {x=445 y=481} {x=439 y=480} {x=430 y=480} {x=426 y=482} {x=421 y=478} {x=418 y=471} {x=419 y=463} {x=420 y=453} {x=420 y=444} {x=420 y=442} {x=420 y=438} {x=418 y=435} {x=414 y=434} {x=400 y=435} {x=398 y=436} {x=395 y=437}"; // 코
string _mouse = "{x=394 y=553} {x=392 y=557} {x=383 y=557} {x=376 y=554} {x=367 y=551} {x=362 y=548} {x=358 y=546} {x=349 y=546} {x=340 y=548} {x=337 y=555} {x=335 y=563} {x=334 y=572} {x=334 y=581} {x=337 y=585} {x=341 y=589} {x=350 y=592} {x=378 y=599} {x=386 y=600} {x=402 y=599} {x=417 y=596} {x=443 y=592} {x=453 y=584} {x=460 y=578} {x=465 y=572} {x=468 y=563} {x=468 y=558} {x=466 y=551} {x=459 y=546} {x=450 y=542} {x=441 y=542} {x=427 y=545} {x=419 y=550} {x=413 y=556} {x=411 y=558}";
string _ear1 = "{x=199 y=408} {x=187 y=400} {x=178 y=399} {x=172 y=400} {x=167 y=404} {x=166 y=410} {x=166 y=419} {x=165 y=430} {x=165 y=438} {x=165 y=447} {x=169 y=458} {x=171 y=468} {x=173 y=476} {x=174 y=479} {x=176 y=485} {x=183 y=495} {x=186 y=499} {x=189 y=502} {x=194 y=506} {x=201 y=509} {x=205 y=510} {x=210 y=511} {x=214 y=511} {x=218 y=512} {x=221 y=512} {x=224 y=511} {x=227 y=510} {x=229 y=510}";
string _ear2 = "{x=598 y=394} {x=600 y=387} {x=608 y=378} {x=616 y=374} {x=622 y=373} {x=629 y=374} {x=639 y=382} {x=642 y=394} {x=642 y=408} {x=640 y=420} {x=636 y=432} {x=631 y=442} {x=629 y=448} {x=626 y=454} {x=617 y=464} {x=614 y=468} {x=611 y=473} {x=606 y=479} {x=597 y=485} {x=593 y=486} {x=591 y=487} {x=589 y=487} {x=588 y=486} {x=584 y=485} {x=583 y=485} {x=583 y=485}";
string _body = "{x=52 y=793} {x=54 y=777} {x=63 y=763} {x=75 y=749} {x=94 y=734} {x=105 y=732} {x=127 y=731} {x=157 y=729} {x=182 y=732} {x=194 y=732} {x=211 y=731} {x=235 y=730} {x=257 y=728} {x=273 y=726} {x=283 y=725} {x=293 y=724} {x=308 y=723} {x=326 y=722} {x=346 y=718} {x=372 y=718} {x=388 y=724} {x=416 y=729} {x=436 y=729} {x=456 y=726} {x=483 y=719} {x=511 y=714} {x=540 y=713} {x=552 y=713} {x=558 y=713} {x=581 y=713} {x=602 y=714} {x=627 y=714} {x=636 y=712} {x=647 y=712} {x=670 y=712} {x=674 y=712} {x=691 y=714} {x=697 y=718} {x=714 y=738} {x=717 y=741} {x=720 y=743} {x=725 y=751} {x=730 y=761} {x=733 y=770} {x=734 y=776} {x=734 y=785} {x=734 y=792} {x=734 y=795} {x=734 y=801} {x=734 y=803} {x=49 y=799}";
string _neck = "{x=316 y=599} {x=288 y=745} {x=333 y=756} {x=333 y=756} {x=352 y=759} {x=361 y=760} {x=390 y=760} {x=401 y=758} {x=411 y=756} {x=435 y=756} {x=446 y=754} {x=452 y=754} {x=475 y=754} {x=480 y=752} {x=488 y=749} {x=499 y=744} {x=504 y=738} {x=482 y=593}";
string _eyebrow1 = "{x=249 y=381} {x=246 y=395} {x=245 y=408} {x=246 y=414} {x=248 y=415} {x=259 y=415} {x=268 y=415} {x=280 y=414} {x=291 y=413} {x=304 y=413} {x=315 y=414} {x=331 y=416} {x=349 y=416} {x=350 y=416} {x=352 y=415} {x=358 y=413} {x=361 y=405} {x=361 y=398} {x=359 y=390} {x=357 y=381} {x=356 y=380} {x=354 y=376} {x=352 y=376} {x=341 y=375} {x=335 y=374} {x=334 y=374}";
string _eyebrow2 = "{x=491 y=361} {x=469 y=365} {x=462 y=365} {x=450 y=367} {x=443 y=374} {x=440 y=381} {x=440 y=386} {x=447 y=396} {x=454 y=397} {x=460 y=397} {x=477 y=398} {x=491 y=399} {x=504 y=399} {x=520 y=397} {x=523 y=396} {x=530 y=395} {x=533 y=394} {x=538 y=392} {x=540 y=391} {x=544 y=387} {x=544 y=381} {x=544 y=373} {x=542 y=367} {x=538 y=362}";

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

// 문자열을 파싱하여 vector에 POINT를 추가하는 함수
BodyPart parseCoordinates(const std::string& data, COLORREF color) {
    std::istringstream iss(data);
    std::string token;
    BodyPart bodyPart;
    bodyPart.color = color;

    // 문자열을 토큰으로 나누고 POINT로 변환하여 벡터에 추가
    while (std::getline(iss, token, '}')) {
        if (token.empty()) continue;

        // 중괄호 제거
        size_t start = token.find('{');
        if (start != std::string::npos) {
            token = token.substr(start + 1);
        }

        // 좌표를 추출
        int x, y;
        char ignore;

        std::istringstream(token) >> ignore >> ignore >> x >> ignore >> ignore >> y;

        bodyPart.points.push_back(POINT{ x, y });
    }

    return bodyPart;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH hBrush; 
    HBRUSH hOldBrush;
    POINT pt;
   
    
    switch (message)
    {
    case WM_CREATE:


        cen.x = WINSIZE_X / 2;
        cen.y = WINSIZE_Y / 2;

        _bodyParts.push_back(parseCoordinates(_background, RGB(60, 60, 255)));
        _bodyParts.push_back(parseCoordinates(_body, COLOR_DARK_BLUE));
        _bodyParts.push_back(parseCoordinates(_neck, COLOR_BODY));
        _bodyParts.push_back(parseCoordinates(_ear1, COLOR_BODY));
        _bodyParts.push_back(parseCoordinates(_ear2, COLOR_BODY));
        _bodyParts.push_back(parseCoordinates(_face, COLOR_BODY));
        _bodyParts.push_back(parseCoordinates(_eyebrow1, COLOR_BLACK));
        _bodyParts.push_back(parseCoordinates(_eyebrow2, COLOR_BLACK));
        _bodyParts.push_back(parseCoordinates(_hair, COLOR_BLACK));
        _bodyParts.push_back(parseCoordinates(_eye1, COLOR_WHITE));
        _bodyParts.push_back(parseCoordinates(_eye2, COLOR_WHITE));
        _bodyParts.push_back(parseCoordinates(_pupil1, COLOR_BLACK));
        _bodyParts.push_back(parseCoordinates(_pupil2, COLOR_BLACK));
        _bodyParts.push_back(parseCoordinates(_nose, RGB(255, 225, 203)));
        _bodyParts.push_back(parseCoordinates(_mouse, COLOR_RED));



        _polygons.push_back(vector<POINT>());
        break;

    case WM_LBUTTONDOWN:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);

        _polygons.back().push_back(pt);
        InvalidateRect(hwnd, NULL, true);
        break;
    case WM_RBUTTONDOWN:

        _polygons.push_back(vector<POINT>());
        InvalidateRect(hwnd, NULL, true);
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        hBrush = CreateSolidBrush(COLOR_BODY);

        // 머리
        // 얼굴
        /*hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        DrawEllipseCenter(hdc, cen.x, cen.y, 400, 450);
        SelectObject(hdc, hOldBrush);*/

        if (!_bodyParts.empty())
        {
            for (auto& bodyPart : _bodyParts)
            {
                hBrush = CreateSolidBrush(bodyPart.color);
                hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                Polygon(hdc, bodyPart.points.data(), bodyPart.points.size());
                SelectObject(hdc, hOldBrush);
            }
        }


        hBrush = CreateSolidBrush(COLOR_BODY);
        hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        if (!_polygons.empty())
        {
            for (auto& polygon : _polygons)
            {
                Polygon(hdc, polygon.data(), polygon.size());
            }
        }


        //// 눈
        //hBrush = CreateSolidBrush(COLOR_WHITE);
        //hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        //DrawEllipseCenter(hdc, cen.x - 80, cen.y - 80, 80, 30);
        //DrawEllipseCenter(hdc, cen.x + 80, cen.y - 80, 80, 30);
        //SelectObject(hdc, hOldBrush);

        //// 눈동자
        //hBrush = CreateSolidBrush(COLOR_BLACK);
        //hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        //DrawEllipseCenter(hdc, cen.x - 80, cen.y - 80, 40, 20);
        //DrawEllipseCenter(hdc, cen.x + 80, cen.y - 80, 40, 20);
        //SelectObject(hdc, hOldBrush);

        //// 코
        //hBrush = CreateSolidBrush(COLOR_BODY);
        //hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        //DrawtriangleCenter(hdc, cen.x, cen.y, 30, 70);
        //SelectObject(hdc, hOldBrush);

        //// 입
        //hBrush = CreateSolidBrush(COLOR_RED);
        //hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
        //DrawtriangleCenter(hdc, cen.x, cen.y, 30, 70);
        //SelectObject(hdc, hOldBrush);

        // 귀

        // 눈썹

        // 머리

        // 

        

        DeleteObject(hBrush);
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
//담주화욜
//3. 내얼굴 그리기
//도형을 통해 과제를 해올것
