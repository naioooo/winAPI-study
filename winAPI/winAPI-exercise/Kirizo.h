#pragma once
#include "Stdafx.h"
#include "GImage.h"

class Kirizo
{
public:

	//���, �̵�(�¿�), ���(�¿�), �밢�� ���, ���� ���, �� ������, �¸� ����(�ʴ�����), ��ų Ŭ���̸��� ����
	enum AnimationState {
		STATE_IDLE,                // ���
		STATE_MOVE_HORIZONTAL,     // �̵� (�¿�)
		STATE_STAB_HORIZONTAL,     // ��� (�¿�)
		STATE_DIAGONAL_STAB,       // �밢�� ���
		STATE_CONTINUOUS_STAB,     // ���� ���
		STATE_SPIN,                // �� ������
		STATE_VICTORY_POSE,        // �¸� ���� (�ʴ�����)
		STATE_SKILL_CLIFFHANGER    // ��ų Ŭ���̸��� ����
	};

private:
	AnimationState m_state;
	vector<shared_ptr<GImage>> m_animations;

	POINT m_pos;

	int   m_cnt;
	int   m_idx;
	bool  m_isLeft;

public:
	void init();
	void release();
	void update();
	void render(HDC hdc);

	AnimationState getAnimationState() const { return m_state; }
	void setState(AnimationState state);

	bool getIsLeft() { return m_isLeft; }
	void setIsLeft(bool isLeft) { m_isLeft = isLeft; }

	shared_ptr<GImage> makeHorizontallyFlippedImage(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor);
	void saveHorizontallyFlippedImage(shared_ptr<GImage> to, shared_ptr<GImage> from);

	Kirizo();
	Kirizo(POINT pos);
	~Kirizo();
};

