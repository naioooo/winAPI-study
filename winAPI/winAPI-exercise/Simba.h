#pragma once
#include "Stdafx.h"
#include "GImage.h"

const float GRAVITY = 0.1f; // 중력 가속도
const float JUMP_VELOCITY = 5.0f; // 초기 점프 속도

class Simba
{
public:

	//이미지 필수(배경, 벽, 캐릭터 : 대기, 이동(좌우), 점프(좌우), 벽잡는 모션)
	enum AnimationState {
		STATE_IDLE,     // 기본
		STATE_PLAYING,  // 대기
		STATE_ROAR,     // 대기
		STATE_WALK,     // 걷기
		STATE_JUMP,     // 점프
		STATE_HANGING,  // 매달리기
		STATE_GETUP,    // 올라서기
	};

	AnimationState m_state;
	vector<shared_ptr<GImage>> m_animations;


private:

	float m_x;
	float m_preX;
	float m_y;
	float m_width;
	float m_height;

	int   m_cnt;
	int   m_idx;
	bool  m_isLeft;
	int  m_speed;

	bool m_isJumping;
	bool m_isCliming;
	bool m_isWalking;
	bool m_isBottomJumping;

	float  m_velocity;

public:
	void init();
	void release();
	void update(vector<RECT> rects);
	void render(HDC hdc);
	void input();

	AnimationState getAnimationState() const { return m_state; }
	void setState(AnimationState state);

	bool getIsLeft() { return m_isLeft; }
	void setIsLeft(bool isLeft) { m_isLeft = isLeft; }

	float getX() { return m_x; }
	float getY() { return m_y; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	void setWidth(float width) { m_width = width; }
	void setHeight(float height) { m_height = height; }

	shared_ptr<GImage> makeSpriteImage(shared_ptr<GImage> image, int startX, int startY, int width, int height, int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor);
	shared_ptr<GImage> saveHorizontallyFlippedImage(shared_ptr<GImage> from,  int maxFrameX, int maxFrameY, bool isTrans, COLORREF transColor);
	
	void StartJump() 
	{
		if (!m_isJumping)
		{
			setState(STATE_JUMP);
			m_velocity = JUMP_VELOCITY;
			m_isJumping = true;
			m_isCliming = false;
		}
	}

	Simba();
	Simba(float x, float y);
	~Simba();
};

