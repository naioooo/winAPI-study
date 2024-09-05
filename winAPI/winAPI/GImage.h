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
		DWORD    resID;    // 리소스아이디
		HDC      hMemDC;   // 메모리 DC
		HBITMAP  hBit;     // 비트맵
		HBITMAP  hOBit;    // 올드비트맵

		float x;
		float y;

		int      width;	   // 너비
		int      height;   // 높이

		int currentFrameX;
		int currentFrameY;
		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;

		BYTE     loadType; // 이미지 로드타입

		TagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL; 
			x = 0;
			y = 0;
			width = 0;	   // 너비
			height = 0;   // 높이
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, * LPIMAGE_INFO;

private:
	LPIMAGE_INFO _imageInfo;
	char*        _fileName;
	bool         _isTrans;
	COLORREF     _transColor; // RGB 

	BLENDFUNCTION _blendFunction;
	LPIMAGE_INFO _blendImage;

public:
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName,int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);


	void setTransColor(bool isTrans, COLORREF transColor);
	void release(void);

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	// 클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 알파
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//프레임
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//

	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }
	inline BLENDFUNCTION getBlendFunction(void) { return _blendFunction; }

	inline void setBlendFunction(BYTE alpha) { _blendFunction.SourceConstantAlpha = alpha; }

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	inline float getX(void) { return _imageInfo->x; }
	inline float getY(void) { return _imageInfo->y; }

	inline void setX(float x) { _imageInfo->x = x; }
	inline void setY(float y) { _imageInfo->y = y; }
	inline void setCenter(float x, float y)
	{ 
		_imageInfo->x = x - (_imageInfo->width /2); 
		_imageInfo->y = y - (_imageInfo->height /2); 
	}

	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height
		};

		return rc;
	}

	inline RECT boundingBoxFrame(void)
	{
		RECT rc =
		{
			(int)_imageInfo->x,
			(int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight
		};

		return rc;
	}

	inline float getFrameX(void) { return _imageInfo->currentFrameX; }
	inline float getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage();
	~GImage();
};

