#include "Kirizo.h"

void Kirizo::init()
{
    m_cnt = 0;
    m_idx = 0;
    m_state = STATE_IDLE;
    m_isLeft = true;

    shared_ptr<GImage> state_IDLE = make_shared<GImage>();
    shared_ptr<GImage> state_MOVE_HORIZONTAL = make_shared<GImage>();
    shared_ptr<GImage> state_STAB_HORIZONTAL = make_shared<GImage>();
    shared_ptr<GImage> state_DIAGONAL_STAB = make_shared<GImage>();
    shared_ptr<GImage> state_CONTINUOUS_STAB = make_shared<GImage>();
    shared_ptr<GImage> state_SPIN = make_shared<GImage>();
    shared_ptr<GImage> state_VICTORY_POSE = make_shared<GImage>();
    shared_ptr<GImage> state_SKILL_CLIFFHANGE = make_shared<GImage>();

    state_IDLE             ->init("Resource/Images/Object/tank.bmp", 450, 56);
    state_MOVE_HORIZONTAL  ->init("Resource/Images/Object/tank.bmp", 450, 56);
    state_STAB_HORIZONTAL  ->init("Resource/Images/Object/tank.bmp", 450, 56);
    state_DIAGONAL_STAB    ->init("Resource/Images/Object/tank.bmp", 450, 56);
    state_CONTINUOUS_STAB  ->init("Resource/Images/Object/tank.bmp", 450, 56);
    state_SPIN             ->init("Resource/Images/Object/tank.bmp", 450, 56);
    state_VICTORY_POSE     ->init("Resource/Images/Object/tank.bmp", 450, 56);
    state_SKILL_CLIFFHANGE ->init("Resource/Images/Object/tank.bmp", 450, 56);

    shared_ptr<GImage> m_STATE_IDLE = make_shared<GImage>();
    shared_ptr<GImage> m_STATE_MOVE_HORIZONTAL = make_shared<GImage>();
    shared_ptr<GImage> m_STATE_STAB_HORIZONTAL = make_shared<GImage>();
    shared_ptr<GImage> m_STATE_DIAGONAL_STAB = make_shared<GImage>();
    shared_ptr<GImage> m_STATE_CONTINUOUS_STAB = make_shared<GImage>();
    shared_ptr<GImage> m_STATE_SPIN = make_shared<GImage>();
    shared_ptr<GImage> m_STATE_VICTORY_POSE = make_shared<GImage>();
    shared_ptr<GImage> m_STATE_SKILL_CLIFFHANGER = make_shared<GImage>();

    m_STATE_IDLE               ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    m_STATE_MOVE_HORIZONTAL    ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    m_STATE_STAB_HORIZONTAL    ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    m_STATE_DIAGONAL_STAB      ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    m_STATE_CONTINUOUS_STAB    ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    m_STATE_SPIN               ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    m_STATE_VICTORY_POSE       ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    m_STATE_SKILL_CLIFFHANGER  ->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);

    saveHorizontallyFlippedImage( m_STATE_IDLE             , state_IDLE            );
    saveHorizontallyFlippedImage( m_STATE_MOVE_HORIZONTAL  , state_MOVE_HORIZONTAL );
    saveHorizontallyFlippedImage( m_STATE_STAB_HORIZONTAL  , state_STAB_HORIZONTAL );
    saveHorizontallyFlippedImage( m_STATE_DIAGONAL_STAB    , state_DIAGONAL_STAB   );
    saveHorizontallyFlippedImage( m_STATE_CONTINUOUS_STAB  , state_CONTINUOUS_STAB );
    saveHorizontallyFlippedImage( m_STATE_SPIN             , state_SPIN            );
    saveHorizontallyFlippedImage( m_STATE_VICTORY_POSE     , state_VICTORY_POSE    );
    saveHorizontallyFlippedImage( m_STATE_SKILL_CLIFFHANGER, state_SKILL_CLIFFHANGE);

    m_animations.push_back(m_STATE_IDLE);
    m_animations.push_back(m_STATE_MOVE_HORIZONTAL);
    m_animations.push_back(m_STATE_STAB_HORIZONTAL);
    m_animations.push_back(m_STATE_DIAGONAL_STAB);
    m_animations.push_back(m_STATE_CONTINUOUS_STAB);
    m_animations.push_back(m_STATE_SPIN);
    m_animations.push_back(m_STATE_VICTORY_POSE);
    m_animations.push_back(m_STATE_SKILL_CLIFFHANGER);
}

void Kirizo::release()
{
}

void Kirizo::update()
{
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

shared_ptr<GImage> Kirizo::makeHorizontallyFlippedImage(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor)
{
    /*
    shared_ptr<GImage> state_IDLE = make_shared<GImage>();
    state_IDLE->init(fileName, 450, 56);
    shared_ptr<GImage> m_STATE_IDLE = make_shared<GImage>();
    m_STATE_IDLE->init(m_pos.x, m_pos.y, 450, 56 * 2, 6, 2, true, COLOR_MAGENTA);
    saveHorizontallyFlippedImage(m_STATE_IDLE, state_IDLE);
    return shared_ptr<GImage>();
    */
    return 0;
}

void Kirizo::saveHorizontallyFlippedImage(shared_ptr<GImage> to, shared_ptr<GImage> from)
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
