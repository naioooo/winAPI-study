#include "stdafx.h"
#include "GImage.h"

GImage::GImage() : _imageInfo(nullptr), _fileName(nullptr), _isTrans(false), _transColor(RGB(0, 0, 0))
{
}

GImage::~GImage()
{
}

HRESULT GImage::init(int width, int height)
{
    if (_imageInfo != nullptr)
    {
        this->release();
    }

    HDC hdc = GetDC(_hWnd);
    _imageInfo = new IMAGE_INFO();

    _imageInfo->loadType = LOAD_EMPTY;
    _imageInfo-> resID = 0;
    _imageInfo-> hMemDC = CreateCompatibleDC(hdc);
    _imageInfo-> hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    _imageInfo-> hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo-> width = width;
    _imageInfo-> height = height;

    _fileName = nullptr;

    _isTrans = false;
    _transColor = RGB(0, 0, 0);

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

HRESULT GImage::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
    if (_imageInfo != nullptr)
    {
        this->release();
    }

    HDC hdc = GetDC(_hWnd);

    _imageInfo = new IMAGE_INFO();

    _imageInfo->loadType = LOAD_FILE;
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

    int len = strlen(fileName);
    _fileName = new char[len + 1];

    //버퍼오버플로우 방지
    strcpy_s(_fileName, len + 1, fileName);

    _isTrans = isTrans;
    _transColor = transColor;

    if (_imageInfo->hBit == 0)
    {
        release();
        return E_FAIL;
    }

    ReleaseDC(_hWnd, hdc);

    return S_OK;
}

void GImage::setTransColor(bool isTrans, COLORREF transColor)
{
    _isTrans = isTrans;
    _transColor = transColor;
}

void GImage::release(void)
{
    if (_imageInfo)
    {
        SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
        DeleteObject(_imageInfo->hBit);
        DeleteDC(_imageInfo->hMemDC);

        SAFE_DELETE(_imageInfo);
        SAFE_DELETE_ARRAY(_fileName);

        _isTrans = false;
        _transColor = RGB(0, 0, 0);
    }
}

void GImage::render(HDC hdc)
{
    if (_isTrans)
    {
        // GdiTransparentBlt : 비트맵을 불러올때 특정 색상을 제외하고 복사를 수행하는 함수
        GdiTransparentBlt
        (
            hdc,
            0, 0,                         // 시작점
            _imageInfo->width, _imageInfo->height, // 그릴 사이즈
            _imageInfo->hMemDC,                         // 복사될 대상 메모리 DC
            0, 0,                          // 복사 시작지점
            _imageInfo->width, _imageInfo->height,  // 복사 사이즈
            _transColor                           // 제외할 색상
        );
    }
    else
    {
        // BitBlt : DC 간의 영역끼리 고속 복사를 수행하는 함수
        // SRCCOPY 소스 영역을 대상 영역에 복사한다
        BitBlt
        (
            hdc,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,                    
            0, 0, 
            SRCCOPY
        );
    }
}

void GImage::render(HDC hdc, int destX, int destY)
{
    if (_isTrans)
    {
        // GdiTransparentBlt : 비트맵을 불러올때 특정 색상을 제외하고 복사를 수행하는 함수
        GdiTransparentBlt
        (
            hdc,
            destX, destY,                 // 시작점
            _imageInfo->width, _imageInfo->height, // 그릴 사이즈
            _imageInfo->hMemDC,                         // 복사될 대상 메모리 DC
            0, 0,                           // 복사 시작지점
            _imageInfo->width, _imageInfo->height,   // 복사 사이즈
            _transColor                            // 제외할 색상
        );
    }
    else
    {
        // BitBlt : DC 간의 영역끼리 고속 복사를 수행하는 함수
        // SRCCOPY 소스 영역을 대상 영역에 복사한다
        BitBlt
        (
            hdc,
            destX, destY,
            _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            SRCCOPY
        );
    }
}


