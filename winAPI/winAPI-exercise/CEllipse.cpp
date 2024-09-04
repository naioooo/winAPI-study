#include "CEllipse.h"

void CEllipse::init()
{
}

void CEllipse::release()
{
}

void CEllipse::update()
{
	Object::update();
}

void CEllipse::render(HDC hdc)
{
    if (m_state != None)
    {
        DrawEllipseCenter(hdc, m_center.x, m_center.y, m_radious * 2, m_radious * 2);

        switch (m_state)
        {
        case Idle:
            GdiTransparentBlt
            (
                hdc,
                m_center.x - m_radious, m_center.y - m_radious,
                m_radious * 2, m_radious * 2,
                m_image->getMemDC(),                      
                0, 0,                        
                40, 40,  
                COLOR_MAGENTA                        
            );
            break;

        case Die:
            GdiTransparentBlt
            (
                hdc,
                m_center.x - m_radious, m_center.y - m_radious,
                m_radious * 2, m_radious * 2,
                m_image->getMemDC(),
                40, 0,
                40, 40,
                COLOR_MAGENTA
            );
            break;
        }
    }
}

CEllipse::CEllipse()
{
    m_image = make_shared<GImage>();
    m_image->init("Resource/Images/Object/zubat.bmp", 80, 40);

    m_type = TYPE::ELLIPSE;
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

    m_radious = RND->getFromIntTo(20, 50);
}

CEllipse::~CEllipse()
{
}
