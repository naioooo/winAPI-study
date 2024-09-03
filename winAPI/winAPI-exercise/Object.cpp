#include "Object.h"

void Object::init()
{
}

void Object::release()
{
}

void Object::update()
{
    if (m_state == Idle)
    {
        if (m_dir == 0)
        {
            m_center.x += 3;
            m_center.y = Parabola(m_center.x, m_gradient, m_interceptX, m_interceptY);

            if (m_center.x > WINSIZE_X + 100)
            {
                m_state = Die;
            }
        }
        else if (m_dir == 1)
        {
            m_center.x -= 3;
            m_center.y = Parabola(m_center.x, m_gradient, m_interceptX, m_interceptY);

            if (m_center.x < -100)
            {
                m_state = Die;
            }
        }
    }  
    else if (m_state == Die)
    {
        m_center.y += 3;

        if (m_Cnt > 100)
        {
            setState(None);
        }
        else
            m_Cnt++;
    }
}

void Object::render(HDC hdc)
{
   
}

Object::Object()
{
    m_state = Idle;
    m_Cnt = 0;
    m_speed = RND->getFromFloatTo(3.0f, 10.0f);

    m_gradient = RND->getFromFloatTo(0.0005f, 0.001f);
    m_interceptX = 800;
    m_interceptY = RND->getFromIntTo(100, 500);

    m_dir = RND->getInt(2);

    if (m_dir == 0)
    {
        m_center = {0, 0};
    }
    else if (m_dir == 1)
    {
        m_center = {800, 0};
    }
}

Object::~Object()
{
}
