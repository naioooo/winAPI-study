#include "KirizoAnimation.h"

HRESULT KirizoAnimation::init(void)
{
    GameNode::init();
    m_bgImage = make_shared<GImage>();
    m_bgImage->init("Resource/Images/Background/background.bmp", WINSIZE_X, WINSIZE_Y);
    
    int x = 10;
    int y = 10;
    int width = 150;
    int height = 90;
    //포함할 이미지 : 배경, 대기, 이동(좌우), 찌르기(좌우), 대각선 찌르기, 연속 찌르기, 원 돌리기, 승리 포즈(옷던지기), 스킬 클라이막스 연출
    m_boxButton.push_back(BoxButton(x, y + height * 0, width, height, "대기", Kirizo::STATE_IDLE));
    m_boxButton.push_back(BoxButton(x, y + height * 1, width, height, "이동", Kirizo::STATE_MOVE_HORIZONTAL));
    m_boxButton.push_back(BoxButton(x, y + height * 2, width, height, "찌르기", Kirizo::STATE_STAB_HORIZONTAL));
    m_boxButton.push_back(BoxButton(x, y + height * 3, width, height, "대각선 찌르기", Kirizo::STATE_DIAGONAL_STAB));
    m_boxButton.push_back(BoxButton(x, y + height * 4, width, height, "연속 찌르기", Kirizo::STATE_CONTINUOUS_STAB));
    m_boxButton.push_back(BoxButton(x, y + height * 5, width, height, "원 돌리기", Kirizo::STATE_SPIN));
    m_boxButton.push_back(BoxButton(x, y + height * 6, width, height, "승리 포즈(옷던지기)", Kirizo::STATE_VICTORY_POSE));
    m_boxButton.push_back(BoxButton(x, y + height * 7, width, height, "스킬 클라이막스", Kirizo::STATE_SKILL_CLIFFHANGER));
      
   
    m_kirizoState = BoxButton(600, 10, width, height, "NONE", Kirizo::STATE_IDLE);
    m_changeHorizontal = BoxButton(200, 10, width, height, "좌우반전", Kirizo::STATE_IDLE);

    POINT pos = { 400, 400 };
    m_kirizo = make_shared<Kirizo>(pos);
    m_kirizo->init();

    return S_OK;
}

void KirizoAnimation::release(void)
{
    GameNode::release();
}

void KirizoAnimation::update(void)
{
    input();

    m_kirizo->update();
    GameNode::update();
}

void KirizoAnimation::render(HDC hdc)
{
    // 백버퍼 가져오기
    HDC memDC = this->getBackBuffer()->getMemDC();
    // 검은색 비트맵
    PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
    m_bgImage->render(memDC, 0, 0);

    for (auto& boxButton : m_boxButton)
    {
        boxButton.render(memDC);
    }

    m_kirizo->render(memDC);
    m_kirizoState.render(memDC);
    m_changeHorizontal.render(memDC);


    this->getBackBuffer()->render(hdc, 0, 0);
}

void KirizoAnimation::input()
{
}

void KirizoAnimation::mouseInput(UINT message, LPARAM lParam)
{
    _ptMouse.x = LOWORD(lParam);
    _ptMouse.y = HIWORD(lParam);

    switch (message)
    {
    case WM_LBUTTONDOWN:

        for (auto& boxButton : m_boxButton)
        {
            if (PtInRect(&boxButton.rect, _ptMouse ))
            {
                m_kirizo->setState(boxButton.animationState);
                m_kirizoState.text = boxButton.text;
            }
        }

        if (PtInRect(&m_changeHorizontal.rect, _ptMouse))
        {
            if (m_kirizo->getIsLeft())
            {
                m_kirizo->setIsLeft(false);
            }
            else
            {
                m_kirizo->setIsLeft(true);
            }
        }
        
        break;
    }
}

KirizoAnimation::KirizoAnimation()
{
}

KirizoAnimation::~KirizoAnimation()
{
}
