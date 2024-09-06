#include "CharacterWallClimbing.h"

HRESULT CharacterWallClimbing::init(void)
{
    GameNode::init();
    m_bgImage = make_shared<GImage>();
    m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);

    m_brickImage = make_shared<GImage>();
    m_brickImage->init("Resource/Images/Object/brick.bmp", 30, 30);

    m_miniMapBuffer = make_shared<GImage>();
    m_miniMapBuffer->init(WINSIZE_X, WINSIZE_Y);

    m_camera = make_shared<GImage>();
    m_camera->init(200, 200);


    m_simba = make_shared<Simba>(WINSIZE_X / 2, WINSIZE_Y / 2);
    m_simba->init();

    m_rects.push_back(RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y - 50, WINSIZE_X, 100));
    m_rects.push_back(RectMakeCenter(WINSIZE_X / 2 + 200, WINSIZE_Y / 2 + 200, 100, 400));
    m_rects.push_back(RectMakeCenter(WINSIZE_X / 2 + 300, WINSIZE_Y - 100, 100, 50));
    m_rects.push_back(RectMakeCenter(WINSIZE_X / 2 - 300, WINSIZE_Y - 200, 100, 10));
    m_rects.push_back(RectMakeCenter(WINSIZE_X / 2 - 200, WINSIZE_Y - 300, 100, 10));
    m_rects.push_back(RectMakeCenter(WINSIZE_X / 2 - 100, WINSIZE_Y - 400, 100, 10));
    m_rects.push_back(RectMakeCenter(WINSIZE_X / 2 , WINSIZE_Y - 500, 100, 10));


    return S_OK;
}

void CharacterWallClimbing::release(void)
{
    GameNode::release();
}

void CharacterWallClimbing::update(void)
{
    input();

    m_simba->update(m_rects);
    GameNode::update();
}

void CharacterWallClimbing::render(HDC hdc)
{ // 백버퍼 가져오기
    HDC memDC = this->getBackBuffer()->getMemDC();
    // 검은색 비트맵
    PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
    m_bgImage->render(memDC, 0, 0);


    for (auto& rect : m_rects)
    {
        DrawRect(memDC, rect);

        int width = (rect.right - rect.left) / 10;
        int height = (rect.bottom - rect.top) / 10;

        for (int i = 0; i <= width; i++)
        {
            for (int j = 0; j <= height; j++)
            {
                StretchBlt
                (
                    memDC,
                    rect.left + i * 10, rect.top + j * 10,
                    10, 10,
                    m_brickImage->getMemDC(),
                    0, 0,
                    10, 10,
                    SRCCOPY
                );
            }
        }
        
    }

    //RECT rc = RectMake(m_simba->m_x, m_simba->m_y, m_simba->m_width, m_simba->m_height);
   // DrawRect(memDC, rc);
    m_simba->render(memDC);

    //카메라 구현
    m_camera->init(200, 200);

    StretchBlt
    (
        m_camera->getMemDC(),
        0, 0,
        m_camera->getWidth(), m_camera->getHeight(), // 그릴 사이즈
        memDC,
        m_simba->getX() + (m_simba->getWidth() / 2) - (m_camera->getWidth() / 2),
        m_simba->getY() + (m_simba->getHeight() / 2) - (m_camera->getHeight() / 2),
        m_camera->getWidth(), m_camera->getHeight(),
        SRCCOPY
    );

    // 미니맵 구현
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


    StretchBlt
    (
        memDC,
        0, 0,
        WINSIZE_X, WINSIZE_Y,
        m_camera->getMemDC(),
        0, 0,
        m_camera->getWidth(), m_camera->getHeight(),
        SRCCOPY
    );

    AlphaBlend
    (
        memDC,
        600, 0,
        200, 200, // 그릴 사이즈
        memDC2,
        0, 0,
        WINSIZE_X, WINSIZE_Y, // 그릴 사이즈
        getBackBuffer()->getBlendFunction()
    );

   

    this->getBackBuffer()->render(hdc, 0, 0);
}

void CharacterWallClimbing::input()
{

}

void CharacterWallClimbing::mouseInput(UINT message, LPARAM lParam)
{
}

CharacterWallClimbing::CharacterWallClimbing()
{
}

CharacterWallClimbing::~CharacterWallClimbing()
{
}
