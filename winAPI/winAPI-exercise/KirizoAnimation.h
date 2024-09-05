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

/*b. ĳ���� (Ű����)
 ���� �� + ���� ��
 ���� �� -> �Ʒ��� �̹����� GUIȭ ����(Ȥ�� ��ưȭ) �����Ų�� 
 ������ �̹��� : ���, ���, �̵� (�¿�), ��� (�¿�), �밢�� ���, ���� ���, �� ������, �¸� ����(�ʴ�����), ��ų Ŭ���̸��� ����

*/

