#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "Kirizo.h"

struct BoxButton
{
	RECT rect;
	string text;
	Kirizo::AnimationState animationState;

	BoxButton() {};
	BoxButton(int x, int y, int width, int height, string str, Kirizo::AnimationState _animationState)
	{
		rect = RectMake(x, y, width, height);
		text = str;
		animationState = _animationState;
	}
	~BoxButton() {};

	void render(HDC hdc)
	{
		int x = rect.left + ((rect.right - rect.left) / 2) - (text.length() / 2);
		int y = rect.top + ((rect.bottom - rect.top) / 2);
		DrawRect(hdc, rect);
		TextOut(hdc, x - 50, y, text.c_str(), text.length());
	}
};

class KirizoAnimation : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;
	shared_ptr<Kirizo> m_kirizo;

	vector<BoxButton> m_boxButton;
	BoxButton m_kirizoState;
	BoxButton m_changeHorizontal;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	KirizoAnimation();
	~KirizoAnimation();

};

/*b. 캐릭터 (키리조)
 시작 씬 + 게임 씬
 게임 씬 -> 아래의 이미지를 GUI화 시켜(혹은 버튼화) 재생시킨다 
 포함할 이미지 : 배경, 대기, 이동 (좌우), 찌르기 (좌우), 대각선 찌르기, 연속 찌르기, 원 돌리기, 승리 포즈(옷던지기), 스킬 클라이막스 연출

*/

