#include "Chikorita.h"

void Chikorita::init()
{
	m_state = Up;
	m_Hp = 100;
	m_Cnt = 0;
}

void Chikorita::init(int x, int y)
{
	m_state = Up;
	m_Hp = 100;
	m_Cnt = 0;
}

void Chikorita::release()
{
}

void Chikorita::update()
{
	if (m_state == Up)
	{
		if (m_Cnt > 40)
		{
			setState(Idle);
		}
		else
			m_Cnt++;
	}
	else if (m_state == Hurt)
	{
		if (m_Cnt > 15)
		{
			setState(Idle);
		}
		else
			m_Cnt++;
	}
	else if (m_state == Die)
	{
		if (m_Cnt > 50)
		{
			setState(None);
		}
		else
			m_Cnt++;
	}
}

void Chikorita::render(HDC hdc)
{
	switch (m_state)
	{
	case Chikorita::Idle:
		GdiTransparentBlt
		(
			hdc,
			m_rect.left, m_rect.top,                 // 시작점
			40, 40, // 그릴 사이즈
			m_image->getMemDC(),                         // 복사될 대상 메모리 DC
			0 , 0,                           // 복사 시작지점
			40, 40,   // 복사 사이즈
			COLOR_MAGENTA                            // 제외할 색상
		);

		break;
	case Chikorita::Up:
		GdiTransparentBlt
		(
			hdc,
			m_rect.left, m_rect.top + 40 - m_Cnt,                 // 시작점
			40, m_Cnt, // 그릴 사이즈
			m_image->getMemDC(),                         // 복사될 대상 메모리 DC
			40, 0,                           // 복사 시작지점
			40, m_Cnt,   // 복사 사이즈
			COLOR_MAGENTA                            // 제외할 색상
		);
		break;
	case Chikorita::Hurt:
		GdiTransparentBlt
		(
			hdc,
			m_rect.left, m_rect.top,                 // 시작점
			40, 40, // 그릴 사이즈
			m_image->getMemDC(),                         // 복사될 대상 메모리 DC
			80, 0,                           // 복사 시작지점
			40, 40,   // 복사 사이즈
			COLOR_MAGENTA                            // 제외할 색상
		);
		break;
	case Chikorita::Die:
		GdiTransparentBlt
		(
			hdc,
			m_rect.left, m_rect.top + m_Cnt,                 // 시작점
			40, 40 - m_Cnt, // 그릴 사이즈
			m_image->getMemDC(),                         // 복사될 대상 메모리 DC
			120, 0,                           // 복사 시작지점
			40, 40 - m_Cnt,   // 복사 사이즈
			COLOR_MAGENTA                            // 제외할 색상
		);
		break;
	case Chikorita::None:
		break;
	}
}

Chikorita::Chikorita()
{
	m_state = Up;
	m_Hp = 100;
	m_rect = RectMake(0, 0, 40, 40);
	m_Cnt = 0;

	m_image = make_shared<GImage>();
	m_image->init("Resource/Images/Object/Chikorita.bmp", 160, 40);
}

Chikorita::Chikorita(int x, int y)
{
	m_state = Up;
	m_Hp = 200;
	m_rect = RectMake(x, y, 40, 40);
	m_Cnt = 0;

	m_image = make_shared<GImage>();
	m_image->init("Resource/Images/Object/Chikorita.bmp", 160, 40);
}

Chikorita::~Chikorita()
{
}
