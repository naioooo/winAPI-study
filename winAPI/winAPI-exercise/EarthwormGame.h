#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "WormBody.h"

class EarthwormGame : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;

	vector<WormBody> m_wormBodies;

	int m_speedCnt;
	int m_speedTime;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	EarthwormGame();
	~EarthwormGame();

	void checkCollisionMap();
};

/*
도전과제
 지렁이 만들기
  지렁이는 구슬에 꼬리를 물고 이어지는 형태를 띄고 있다
   각 구슬마다 번호를 표기
  지렁이는 화면밖의 무작위 위치에서 등장
  또한 특별한 키 입력이 없어도 지렁이는 화면 안에서 움직인다
  벽에 부딪히면 팅겨야 하고 왼쪽오른쪽 방향키로 조종이 가능해야한다

  따라오는 구슬은 머리가 방향을 튼다고 같이 틀면 안되고 머리가 있던 위치까지 이동한 후에 방향전환
  게임이 시작되고 10초후에 임의의 숫자가 표시된 아이템이 게임이 추가되고 지렁이가 아이템을 먹으면
  해당하는 번호의 지렁이 구슬이 커진다

  얼마나 자연스러운지
*/