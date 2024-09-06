#include "Kirizo.h"

void Kirizo::init()
{
    m_cnt = 0;
    m_idx = 0;
    m_state = STATE_IDLE;
    m_isLeft = true;

    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/IDLE2.bmp", 1920, 244, 9, 2, true, COLOR_MAGENTA));
    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/MOVE2.bmp", 1920, 189, 8, 2, true, COLOR_MAGENTA));
    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/tank.bmp", 450, 56, 6, 2, true, COLOR_MAGENTA));
    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/tank.bmp", 450, 56, 6, 2, true, COLOR_MAGENTA));
    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/tank.bmp", 450, 56, 6, 2, true, COLOR_MAGENTA));
    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/tank.bmp", 450, 56, 6, 2, true, COLOR_MAGENTA));
    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/tank.bmp", 450, 56, 6, 2, true, COLOR_MAGENTA));
    m_animations.push_back(makeHorizontallyFlippedImage("Resource/Images/Object/tank.bmp", 450, 56, 6, 2, true, COLOR_MAGENTA));
}

void Kirizo::release()
{
}

void Kirizo::update()
{    
    if (!m_isLeft)
    {
        m_cnt++;
        m_animations[m_state]->setFrameY(1);
        if (m_cnt % 5 == 0)
        {
            m_idx--;

            if (m_idx < 0)
            {
                m_idx = m_animations[m_state]->getMaxFrameX();
            }

            m_animations[m_state]->setFrameX(m_idx);
        }
    }
    else
    {
        m_cnt++;
        m_animations[m_state]->setFrameY(0);
        if (m_cnt % 5 == 0)
        {
            m_idx++;

            if (m_idx > m_animations[m_state]->getMaxFrameX())
            {
                m_idx = 0;
            }

            m_animations[m_state]->setFrameX(m_idx);
        }
    }

}

void Kirizo::render(HDC hdc)
{
    m_animations[m_state]->frameRender(hdc, m_pos.x, m_pos.y);
}

void Kirizo::setState(AnimationState state)
{
    m_state = state;
    m_cnt = 0;
    if (m_isLeft)
    {
        m_idx = m_animations[m_state]->getMaxFrameX();
    }
    else
    {
        m_idx = 0;
    }
}
shared_ptr<GImage> Kirizo::makeHorizontallyFlippedImage(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{    
    shared_ptr<GImage> fromImage = make_shared<GImage>();
    fromImage->init(fileName, width, height);
    shared_ptr<GImage> toImage = make_shared<GImage>();
    toImage->init(m_pos.x, m_pos.y, width, height * 2, maxFrameX, maxFrameY, isTrans, transColor);
    saveHorizontallyFlippedImage(toImage, fromImage);
    return toImage;
}

void Kirizo::saveHorizontallyFlippedImage(shared_ptr<GImage>& to, shared_ptr<GImage>& from)
{
    StretchBlt
    (
        to->getMemDC(),
        0, 0,
        to->getWidth(), to->getHeight() / 2,
        from->getMemDC(),
        0, 0,
        from->getWidth(), from->getHeight(),
        SRCCOPY
    );
    StretchBlt
    (
        to->getMemDC(),
        0, to->getHeight() / 2,
        to->getWidth(), to->getHeight() / 2,
        from->getMemDC(),
        from->getWidth() - 1, 0,
        -from->getWidth(), from->getHeight(),
        SRCCOPY
    );
}
Kirizo::Kirizo()
{
}

Kirizo::Kirizo(POINT pos)
{
    m_pos = pos;
}

Kirizo::~Kirizo()
{
}
