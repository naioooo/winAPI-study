#include "SliceGame.h"

HRESULT SliceGame::init(void)
{
	GameNode::init();

	m_puzzleImage = make_shared<GImage>();
	m_puzzleImage->init("Resource/Images/Background/background.bmp", WINSIZE_X / 2, WINSIZE_Y / 2);

	generateSlice(m_puzzleImage);
	shuffleSlice();
	choiceSlice = 0;

	return S_OK;
}

void SliceGame::release(void)
{
	GameNode::release();
}

void SliceGame::update(void)
{
	input();
	GameNode::update();
}

void SliceGame::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	m_puzzleImage->render(memDC, WINSIZE_X / 2, WINSIZE_Y / 4 );

	for (auto& slice : slices)
	{
		if (checkFinish() && slice.m_num == 4)
		{
			m_puzzleImage->alphaRender(memDC, slice.m_startX, slice.m_startY + WINSIZE_Y / 4, slice.m_sourStartX, slice.m_sourStartY, slice.m_width, slice.m_height, 100);

		}
		else
			m_puzzleImage->render(memDC, slice.m_startX, slice.m_startY + WINSIZE_Y / 4, slice.m_sourStartX, slice.m_sourStartY, slice.m_width, slice.m_height);
	}

	this->getBackBuffer()->render(hdc, 0, 0);
}

void SliceGame::input()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		cheat1();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		cheat2();
	}
}

void SliceGame::mouseInput(UINT message, LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		checkPtCollision(_ptMouse);
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

SliceGame::SliceGame()
{
}

SliceGame::~SliceGame()
{
}

void SliceGame::gameReset()
{
}

void SliceGame::generateSlice(shared_ptr<GImage> puzzleImage)
{
    int width  = puzzleImage->getWidth();
    int height = puzzleImage->getHeight();

	for (int i = 0; i < 9; i++)
	{
		Slice slice;
		slice.m_num    = i;
		slice.m_width  = width / 3;
		slice.m_height = height / 3;
		slice.m_sourStartX = (i % 3) * slice.m_width;
		slice.m_sourStartY = (i / 3) * slice.m_height;

		slice.m_startX = (i % 3) * slice.m_width;
		slice.m_startY = (i / 3) * slice.m_height;

		slices.push_back(slice);
	}


	Slice slice;

	slice.m_num = 9;
	slice.m_width = width / 3;
	slice.m_height = height / 3;
	slice.m_sourStartX = (11 % 3) * slice.m_width;
	slice.m_sourStartY = (11 / 3) * slice.m_height;

	slice.m_startX = (11 % 3) * slice.m_width;
	slice.m_startY = (11 / 3) * slice.m_height;

	slices.push_back(slice);
}

void SliceGame::shuffleSlice()
{
	int cnt = 0;

	while (cnt < 50)
	{
		int rnd1 = RND->getFromIntTo(0, 8);
		int rnd2 = RND->getFromIntTo(0, 8);

		swapSlice(rnd1, rnd2);

		cnt++;
	}
}

void SliceGame::checkPtCollision(POINT pt)
{
	for (auto& slice : slices)
	{
		if (
			(slice.m_width >= abs(slices.back().m_startX - slice.m_startX) && slice.m_startY == slices.back().m_startY) ||
			(slice.m_height >= abs(slices.back().m_startY - slice.m_startY) && slice.m_startX == slices.back().m_startX)
			)
		{
			RECT rect = RectMake(slice.m_startX, slice.m_startY + WINSIZE_Y / 4, slice.m_width, slice.m_height);

			if (PtInRect(&rect, pt))
			{
				swapSlice(slice.m_num, 9);
				break;
			}
		}
	}
}

bool SliceGame::checkFinish()
{
	for (auto& slice : slices)
	{
		if(slice.m_num == 9)
			return true;
		if (
			slice.m_startX != (slice.m_num % 3) * slice.m_width ||
			slice.m_startY != (slice.m_num / 3) * slice.m_height
			)
		{
			return false;
		}
	}

	return true;
}

void SliceGame::swapSlice(int a, int b)
{
	Slice temp = slices[a];
	slices[a].m_startX = slices[b].m_startX;
	slices[a].m_startY = slices[b].m_startY;
	slices[b].m_startX = temp.m_startX;
	slices[b].m_startY = temp.m_startY;
}

void SliceGame::cheat1()
{
	for (int i = 0; i < 9; i++)
	{
		slices[i].m_startX = (i % 3) * slices[i].m_width;
		slices[i].m_startY = (i / 3) * slices[i].m_height;
	}
	slices[9].m_startX = (11 % 3) * slices[9].m_width;
	slices[9].m_startY = (11 / 3) * slices[9].m_height;

	
	swapSlice(RND->getInt(8), 9);
}

void SliceGame::cheat2()
{
	for (int i = 0; i < 9; i++)
	{
		slices[i].m_startX = (i % 3) * slices[i].m_width;
		slices[i].m_startY = (i / 3) * slices[i].m_height;
	}
	slices[9].m_startX = (11 % 3) * slices[9].m_width;
	slices[9].m_startY = (11 / 3) * slices[9].m_height;

	swapSlice(8, 9);
}
