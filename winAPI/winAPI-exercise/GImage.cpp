#include "stdafx.h"
#include "GImage.h"

#pragma comment (lib, "msimg32.lib")

GImage::GImage() : _imageInfo(nullptr), _fileName(nullptr), _isTrans(false), _transColor(RGB(0, 0, 0)), _blendImage(NULL)
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
    _imageInfo->resID = 0;
    _imageInfo->hMemDC = CreateCompatibleDC(hdc);
    _imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
    _imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
    _imageInfo->width = width;
    _imageInfo->height = height;

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

    //���ۿ����÷ο� ����
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

HRESULT GImage::initForAlphaBlend(void)
{
    HDC hdc = GetDC(_hWnd);

    _blendFunction.BlendFlags = 0;
    _blendFunction.AlphaFormat = 0;
    _blendFunction.BlendOp = AC_SRC_OVER;
    //_blendFunction.SourceConstantAlpha

    _blendImage = new IMAGE_INFO;

    _blendImage->loadType = LOAD_FILE;
    _blendImage->resID = 0;
    _blendImage->hMemDC = CreateCompatibleDC(hdc);
    _blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
    _blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
    _blendImage->width = WINSIZE_X;
    _blendImage->height = WINSIZE_Y;

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

    if (_blendImage)
    {
        SelectObject(_blendImage->hMemDC, _blendImage->hBit);
        DeleteObject(_blendImage->hBit);
        DeleteDC(_blendImage->hMemDC);

        SAFE_DELETE(_blendImage);
    }
}

void GImage::render(HDC hdc)
{
    if (_isTrans)
    {
        // GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� ���縦 �����ϴ� �Լ�
        GdiTransparentBlt
        (
            hdc,
            0, 0,                         // ������
            _imageInfo->width, _imageInfo->height, // �׸� ������
            _imageInfo->hMemDC,                         // ����� ��� �޸� DC
            0, 0,                          // ���� ��������
            _imageInfo->width, _imageInfo->height,  // ���� ������
            _transColor                           // ������ ����
        );
    }
    else
    {
        // BitBlt : DC ���� �������� ��� ���縦 �����ϴ� �Լ�
        // SRCCOPY �ҽ� ������ ��� ������ �����Ѵ�
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
        // GdiTransparentBlt : ��Ʈ���� �ҷ��ö� Ư�� ������ �����ϰ� ���縦 �����ϴ� �Լ�
        GdiTransparentBlt
        (
            hdc,
            destX, destY,                 // ������
            _imageInfo->width, _imageInfo->height, // �׸� ������
            _imageInfo->hMemDC,                         // ����� ��� �޸� DC
            0, 0,                           // ���� ��������
            _imageInfo->width, _imageInfo->height,   // ���� ������
            _transColor                            // ������ ����
        );
    }
    else
    {
        // BitBlt : DC ���� �������� ��� ���縦 �����ϴ� �Լ�
        // SRCCOPY �ҽ� ������ ��� ������ �����Ѵ�
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

void GImage::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
    if (_isTrans)
    {
        GdiTransparentBlt
        (
            hdc,
            destX, destY,                 // ������
            sourWidth, sourHeight, // �׸� ������
            _imageInfo->hMemDC,                         // ����� ��� �޸� DC
            sourX, sourY,                           // ���� ��������
            sourWidth, sourHeight,   // ���� ������
            _transColor                            // ������ ����
        );
    }
    else
    {
        BitBlt
        (
            hdc,
            destX, destY,
            sourWidth, sourHeight, // �׸� ������
            _imageInfo->hMemDC,
            sourX, sourY,
            SRCCOPY
        );
    }
}

void GImage::alphaRender(HDC hdc, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunction.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // ����� dc�� �׷��� ������ �����ҰŴ�
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            hdc,
            0, 0,
            SRCCOPY
        );

        // ���� �̹����� ����� ������ ���� �̹����� �׸���
        GdiTransparentBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _transColor
        );
        // ���� �̹����� ȭ�鿡 �׸���
        AlphaBlend
        (
            hdc,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _blendFunction
        );
    }
    else
    {
        // ���� �̹����� ȭ�鿡 �׸���
        AlphaBlend
        (
            hdc,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _blendFunction
        );
    }
}

void GImage::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunction.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // ����� dc�� �׷��� ������ �����ҰŴ�
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY
        );

        // ���� �̹����� ����� ������ ���� �̹����� �׸���
        GdiTransparentBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _transColor
        );
        // ���� �̹����� ȭ�鿡 �׸���
        AlphaBlend
        (
            hdc,
            destX, destY,
            _imageInfo->width, _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _blendFunction
        );
    }
    else
    {
        // ���� �̹����� ȭ�鿡 �׸���
        AlphaBlend
        (
            hdc,
            destX, destY,
            _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _blendFunction
        );
    }
}

void GImage::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
    if (!_blendImage) initForAlphaBlend();

    _blendFunction.SourceConstantAlpha = alpha;

    if (_isTrans)
    {
        // ����� dc�� �׷��� ������ �����ҰŴ�
        BitBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            hdc,
            destX, destY,
            SRCCOPY
        );

        // ���� �̹����� ����� ������ ���� �̹����� �׸���
        GdiTransparentBlt
        (
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _imageInfo->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _transColor
        );
        // ���� �̹����� ȭ�鿡 �׸���
        AlphaBlend
        (
            hdc,
            destX, destY,
            _imageInfo->width, _imageInfo->height,
            _blendImage->hMemDC,
            0, 0,
            _imageInfo->width, _imageInfo->height,
            _blendFunction
        );
    }
    else
    {
        // ���� �̹����� ȭ�鿡 �׸���
        AlphaBlend
        (
            hdc,
            destX, destY,
            sourWidth, sourHeight, // �׸� ������
            _imageInfo->hMemDC,
            sourX, sourY,
            sourWidth, sourHeight, // �׸� ������
            _blendFunction
        );

    }
}


