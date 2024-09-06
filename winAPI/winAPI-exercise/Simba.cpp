#include "Simba.h"

void Simba::init()
{
    shared_ptr<GImage> spriteImage;

    spriteImage = make_shared<GImage>();
    spriteImage->init("Resource/Images/Object/LionKing.bmp", 419, 1849);


    m_animations.push_back(makeSpriteImage(spriteImage, 14, 24, 150, 30, 5, 1, true, COLOR_SKYBLUE));   //STATE_IDLE,    
    m_animations.push_back(makeSpriteImage(spriteImage, 11, 84, 400, 26, 11, 1, true, COLOR_SKYBLUE));  //STATE_PLAYING, 
    m_animations.push_back(makeSpriteImage(spriteImage, 11, 112, 248, 27, 8, 1, true, COLOR_SKYBLUE));  //STATE_ROAR,    
    m_animations.push_back(makeSpriteImage(spriteImage, 7, 178, 35 * 8, 29, 8, 1, true, COLOR_SKYBLUE));//STATE_WALK       
    m_animations.push_back(makeSpriteImage(spriteImage, 17, 353, 42 * 7, 34, 7, 1, true, COLOR_SKYBLUE));//STATE_JUMP      
    m_animations.push_back(makeSpriteImage(spriteImage, 7, 820, 27 * 2, 48, 2, 1, true, COLOR_SKYBLUE));//STATE_HANGING      
    m_animations.push_back(makeSpriteImage(spriteImage, 7, 894, 26 * 4, 49, 4, 1, true, COLOR_SKYBLUE));//STATE_GETUP     


    m_cnt = 0;
    m_idx = 0;
    m_isLeft = false;
    m_speed = 5.f;

    m_preX = m_x;

    m_height = 30;
    m_width = 30;

    m_isJumping = true;
    m_isCliming = false;
    m_isWalking = false;
    m_velocity = 0.0f;

    m_state = STATE_IDLE;
}

void Simba::release()
{
}

void Simba::update(vector<RECT> rects)
{
    input();

    m_cnt++;
    if (!m_isLeft)
    {
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
   

    RECT rc;
    if (m_isJumping)
    {
        // 업데이트 속도 및 위치
        int preY = m_y;

        m_y -= m_velocity;
        RECT boundingBox = RectMake(m_x, m_y, m_width, m_height);

        m_velocity -= GRAVITY;

        if (m_isBottomJumping)
        {
            m_isBottomJumping = false;
        }
        else if (m_velocity < 0)
        {
            for (auto& rect : rects)
            {        
                if (IntersectRect(&rc, &rect, &boundingBox))
                {
                    if (preY + m_height <= rect.top)
                    {
                        m_y = rect.top - m_height;
                        m_isJumping = false;
                        m_velocity = 0.0f;
                        break;
                    }
                }
            }
        }

        for (auto& rect : rects)
        {
            if (IntersectRect(&rc, &rect, &boundingBox))
            {
                if (m_preX >= rect.right && m_x < rect.right)
                {
                    m_isCliming = true;
                    m_isJumping = false;
                    m_x = rect.right - 1;
                    m_velocity = 0.0f;
                    break;
                }
                else if (m_preX + m_width <= rect.left && m_x + m_width > rect.left)
                {
                    m_isCliming = true;
                    m_isJumping = false;
                    m_x = rect.left - m_width + 1;
                    m_velocity = 0.0f;
                    break;
                }
            }
        }
    }
    else if (m_isCliming)
    {

        m_velocity = 0.5f;
        int preY = m_y;
        m_y += m_velocity;

        bool check = false;
        RECT boundingBox = RectMake(m_x, m_y, m_width, m_height);

        for (auto& rect : rects)
        {
            if (IntersectRect(&rc, &rect, &boundingBox))
            {
                if (preY + m_height <= rect.top)
                {
                    m_y = rect.top - m_height;
                    m_isJumping = false;
                    m_isCliming = false;
                    m_velocity = 0.0f;
                }

                check = true;
                break;
            }
        }
        if (!check)
        {
            m_isJumping = true;
            m_isCliming = false;
        }
    }
    else
    {
        bool check = false;
        RECT boundingBox = RectMake(m_x, m_y, m_width, m_height);

        for (auto& rect : rects)
        {
            if (IntersectRect(&rc, &rect, &boundingBox))
            {
                check = true;
                break;
            }
        }
        if (!check)
        {
            m_isJumping = true;
            m_isCliming = false;
        }
    }

    if (m_isCliming)
    {
        setState(STATE_HANGING);
    }
    else if (m_isWalking)
    {
        setState(STATE_WALK);
    }    
    else if (m_isJumping)
    {
       // setState(STATE_JUMP);
    }    
    else
    {
        setState(STATE_IDLE);
    }
}

void Simba::render(HDC hdc)
{
    m_animations[m_state]->frameRender(hdc, m_x, m_y);
}

void Simba::input()
{

    m_isWalking = false; 

    if (KEYMANAGER->isStayKeyDown(VK_LEFT) ||
        KEYMANAGER->isStayKeyDown(VK_RIGHT) ||
        KEYMANAGER->isStayKeyDown(VK_UP) ||
        KEYMANAGER->isStayKeyDown(VK_DOWN) ||
        KEYMANAGER->isStayKeyDown(VK_SPACE) ||
        KEYMANAGER->isStayKeyDown(VK_LSHIFT)
        )
    {
        if (!m_isCliming)
        {
            if (KEYMANAGER->isStayKeyDown(VK_LEFT))
            {
                m_preX = m_x;
                m_isLeft = false;
                m_x -= m_speed;
                m_isWalking = true;
            }
            if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
            {
                m_preX = m_x;
                m_isLeft = true;
                m_x += m_speed;
                m_isWalking = true;
            }
        }
        if (m_isCliming)
        {
            if (KEYMANAGER->isStayKeyDown(VK_UP))
            {
                m_y -= m_speed;
            }
            if (KEYMANAGER->isStayKeyDown(VK_DOWN))
            {
                m_y += m_speed;
            }
        }
        else
        {
            if(KEYMANAGER->isStayKeyDown(VK_LSHIFT))
            {
                m_isBottomJumping = true;
                m_isJumping = true;
            }
        }
        if (KEYMANAGER->isStayKeyDown(VK_SPACE))
        {
            StartJump();
        }

        m_animations[m_state]->setX(m_x);
    }



}

void Simba::setState(AnimationState state)
{
    if (m_state != state)
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
}
shared_ptr<GImage> Simba::makeSpriteImage(shared_ptr<GImage> spriteImage, int startX, int startY, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    shared_ptr<GImage> image = make_shared<GImage>();
    image->init(width, height);

    StretchBlt
    (
        image->getMemDC(),
        0, 0,
        width, height,
        spriteImage->getMemDC(),
        startX, startY,
        width, height,
        SRCCOPY
    );

    return saveHorizontallyFlippedImage(image, maxFrameX, maxFrameY, isTrans, transColor);
}

shared_ptr<GImage> Simba::saveHorizontallyFlippedImage(shared_ptr<GImage> from, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    shared_ptr<GImage> to = make_shared<GImage>();
    to->init(m_x, m_y, from->getWidth(), from->getHeight() * 2, maxFrameX, maxFrameY * 2, true, COLOR_SKYBLUE);

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

    return to;
}
Simba::Simba()
{
}

Simba::Simba(float x, float y) : m_x(x), m_y(y)
{

}

Simba::~Simba()
{
}
