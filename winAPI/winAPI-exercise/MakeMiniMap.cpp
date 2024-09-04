#include "MakeMiniMap.h"

HRESULT MakeMiniMap::init(void)
{
	GameNode::init();

	m_bgImage = make_shared<GImage>();
	m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);

	m_miniMapBuffer = make_shared<GImage>();
	m_miniMapBuffer->init(WINSIZE_X, WINSIZE_Y);

	shared_ptr<GImage> image;

	image = make_shared<GImage>();
	image->init("Resource/Images/Object/Cyndaquil.bmp", 80, 40);
	image->setTransColor(true, COLOR_MAGENTA);
	m_Images.push_back(image);

	image = make_shared<GImage>();
	image->init("Resource/Images/Object/golbat.bmp", 112, 56);
	image->setTransColor(true, COLOR_MAGENTA);
	m_Images.push_back(image);

	image = make_shared<GImage>();
	image->init("Resource/Images/Object/Chikorita.bmp", 160, 40);
	image->setTransColor(true, COLOR_MAGENTA);
	m_Images.push_back(image);

	return S_OK;
}

void MakeMiniMap::release(void)
{
	GameNode::release();
}

void MakeMiniMap::update(void)
{
	input();
	GameNode::update();
}

void MakeMiniMap::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	m_bgImage->render(memDC, 0, 0);
	
	m_Images[0]->render(memDC, 200,200);
	m_Images[0]->render(memDC, 600,400);
	m_Images[1]->render(memDC, 300,200);
	m_Images[1]->render(memDC, 300,300);
	m_Images[2]->render(memDC, 100,500);
	m_Images[2]->render(memDC, 200,300);

	getBackBuffer()->setBlendFunction(200);
	HDC memDC2 = m_miniMapBuffer->getMemDC();

	BitBlt
	(
		memDC2,
		0, 0,
		WINSIZE_X, WINSIZE_Y, // 그릴 사이즈
		memDC,
		0, 0,
		SRCCOPY
	);
	AlphaBlend
	(
		memDC,
		500, 500,
		300, 300, // 그릴 사이즈
		memDC2,
		0, 0,
		WINSIZE_X, WINSIZE_Y, // 그릴 사이즈
		getBackBuffer()->getBlendFunction()
	);

	this->getBackBuffer()->render(hdc, 0, 0);
}


void MakeMiniMap::input()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
	}
}

void MakeMiniMap::mouseInput(UINT message, LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONUP:

		break;
	case WM_MOUSEMOVE:
		break;
	}
}

MakeMiniMap::MakeMiniMap()
{
}

MakeMiniMap::~MakeMiniMap()
{
}
