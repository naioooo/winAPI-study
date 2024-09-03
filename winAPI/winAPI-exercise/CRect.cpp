#include "CRect.h"

void CRect::init()
{
}

void CRect::release()
{
}

void CRect::update()
{
	Object::update();
    m_rect = RectMakeCenter(m_center.x, m_center.y, m_width, m_height);
}

void CRect::render(HDC hdc)
{
    if (m_state != None)
    {
        DrawRect(hdc, m_rect);

        switch (m_state)
        {
        case Idle:
            break;

        case Die:
            break;
        }
    }
}

CRect::CRect()
{
    m_type = TYPE::RECT;
    m_state = Idle;
    m_Cnt = 0;
    m_speed = RND->getFromFloatTo(3.0f, 10.0f);

    m_gradient = RND->getFromFloatTo(0.0005f, 0.001f);
    m_interceptX = 800;
    m_interceptY = RND->getFromIntTo(100, 500);

    m_dir = RND->getInt(2);

    if (m_dir == 0)
    {
        m_center = { 0, 0 };
    }
    else if (m_dir == 1)
    {
        m_center = { 800, 0 };
    }

    m_width = RND->getFromIntTo(50, 100);
    m_height = RND->getFromIntTo(50, 100);
}

CRect::~CRect()
{
}
