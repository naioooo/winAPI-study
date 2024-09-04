#pragma once

//enum IMAGE_LOAD_KIND : uint16_t
//{
//
//};

class GImage // GDImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,
		LOAD_FILE,
		LOAD_EMPTY,
		LOAD_END
	};

	//BYTE / WORD / DWORD
	// unsigned char / unsigned short / unsigned long
	typedef struct TagImage
	{
		DWORD    resID;    // ���ҽ����̵�
		HDC      hMemDC;   // �޸� DC
		HBITMAP  hBit;     // ��Ʈ��
		HBITMAP  hOBit;    // �õ��Ʈ��
		int      width;	   // �ʺ�
		int      height;   // ����
		BYTE     loadType; // �̹��� �ε�Ÿ��

		TagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO _imageInfo;
	char* _fileName;
	bool         _isTrans;
	COLORREF     _transColor; // RGB 

	BLENDFUNCTION _blendFunction;
	LPIMAGE_INFO _blendImage;

public:
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);


	void setTransColor(bool isTrans, COLORREF transColor);
	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// Ŭ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// ����
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	inline BLENDFUNCTION getBlendFunction(void) { return _blendFunction; }
	inline void setBlendFunction(BYTE alpha) { _blendFunction.SourceConstantAlpha = alpha; }
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	GImage();
	~GImage();
};

