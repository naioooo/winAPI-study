#pragma once
#include "Stdafx.h"
#include "GImage.h"

class Kirizo
{
public:

	//대기, 이동(좌우), 찌르기(좌우), 대각선 찌르기, 연속 찌르기, 원 돌리기, 승리 포즈(옷던지기), 스킬 클라이막스 연출
	enum AnimationState {
		STATE_IDLE,                // 대기
		STATE_MOVE_HORIZONTAL,     // 이동 (좌우)
		STATE_STAB_HORIZONTAL,     // 찌르기 (좌우)
		STATE_DIAGONAL_STAB,       // 대각선 찌르기
		STATE_CONTINUOUS_STAB,     // 연속 찌르기
		STATE_SPIN,                // 원 돌리기
		STATE_VICTORY_POSE,        // 승리 포즈 (옷던지기)
		STATE_SKILL_CLIFFHANGER    // 스킬 클라이막스 연출
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

