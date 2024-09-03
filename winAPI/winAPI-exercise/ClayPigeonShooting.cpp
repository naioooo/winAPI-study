#include "ClayPigeonShooting.h"

HRESULT ClayPigeonShooting::init(void)
{
	GameNode::init();

	m_bgImage = make_shared<GImage>();
	m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
	
	m_gameTime = 0;
	m_score = 0;
	m_reGame = false;

	return S_OK;
}

void ClayPigeonShooting::release(void)
{
	GameNode::release();
}

void ClayPigeonShooting::update(void)
{
	input();

	if (m_gameTime > 6000)
	{
		GameReset();
	}
	else
	{
		if (!m_reGame)
		{
			CreateObject();

			for (auto& object : m_objects)
			{
				object->update();
			}
			m_gameTime++;
		}
	}

	GameNode::update();
}

void ClayPigeonShooting::render(HDC hdc)
{
	// 백버퍼 가져오기
	HDC memDC = this->getBackBuffer()->getMemDC();
	// 검은색 비트맵
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	m_bgImage->render(memDC, 0, 0);

	for (auto& object : m_objects)
	{
		object->render(memDC);
	}

	char strPT[120];
	wsprintf(strPT, "SCORE : %d, Time : %d ", m_score, m_gameTime / 100);
	TextOut(memDC, 10, 10, strPT, strlen(strPT));

	this->getBackBuffer()->render(hdc, 0, 0);
}

void ClayPigeonShooting::input()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (m_reGame)
		{
			m_reGame = false;
		}
	}
}

void ClayPigeonShooting::mouseInput(UINT message, LPARAM lParam)
{
	_ptMouse.x = LOWORD(lParam);
	_ptMouse.y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		CheckPtCollision(_ptMouse);
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

ClayPigeonShooting::ClayPigeonShooting()
{
}

ClayPigeonShooting::~ClayPigeonShooting()
{
}

void ClayPigeonShooting::GameReset()
{
	m_objects.clear();
	m_objects.shrink_to_fit();

	m_gameTime = 0;
	m_score = 0;
	m_reGame = true;

}

void ClayPigeonShooting::CreateObject()
{
	if (m_genCnt > m_genTime)
	{
		int rand = RND->getInt(3);
		if (rand == 0)
		{
			m_objects.push_back(make_shared<CPolygon>());
		}
		else if (rand == 1)
		{
			m_objects.push_back(make_shared<CEllipse>());
		}
		if (rand == 2)
		{
			m_objects.push_back(make_shared<CRect>());
		}

		m_genCnt = 0;
		m_genTime = RND->getFromIntTo(100, 120);
	}

	m_genCnt++;
}

void ClayPigeonShooting::CheckPtCollision(POINT pt)
{
	for (auto& object : m_objects)
	{
		if (object->getState() == Object::Idle)
		{
			if (object->getType() == Object::TYPE::ELLIPSE)
			{
				shared_ptr<CEllipse> ellipse = dynamic_pointer_cast<CEllipse>(object);

				double dx = pt.x - ellipse->getCenter().x;
				double dy = pt.y - ellipse->getCenter().y;
				double distance = (dx * dx) + (dy * dy);
				double r = ellipse->getRadious();

				if (r * r >= distance)
				{
					m_score += 50;
					ellipse->setState(Object::Die);
				}
			}
			else if (object->getType() == Object::TYPE::RECT)
			{
				if (PtInRect(&object->getRect(), pt))
				{
					m_score += 100;
					object->setState(Object::Die);
				}
			}
			else if (object->getType() == Object::TYPE::POLYGON)
			{
				RECT rect = object->getRect();

				rect.left += object->getCenter().x;
				rect.right += object->getCenter().x;
				rect.top += object->getCenter().y;
				rect.bottom += object->getCenter().y;

				if (PtInRect(&rect, pt))
				{
					m_score += 100;
					object->setState(Object::Die);
				}
			}
		}
	}
}
