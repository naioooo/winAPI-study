#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "Chikorita.h"
#include "Cyndaquil.h"
#include <sstream> 

class WhackAChikorita : public GameNode
{
private:
	RECT rc;

	shared_ptr<GImage> m_bgImage;
	vector<shared_ptr<Chikorita>> m_chikoritas;
	shared_ptr<Cyndaquil> m_cyndaquil;

	vector<POINT> m_genPoints;
	int m_genTime;
	int m_genCnt;
	int m_score;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	WhackAChikorita();
	~WhackAChikorita();

	void parseCoordinates(const std::string& data, vector<POINT>& points);
	void CreateChikorita();
	void CheckPtCollision(POINT pt);
};

/*

이번과제부터는 OOP를 기반으로 할것

과제

1. 두더지 게임 만들기
 두더지의 수는 최소 8마리부터 시작
 화면에 현재 점수 표시
 예외처리 : 두더지 한번클릭 -> 점수 증가 -> 이후 두더지를 클릴하때마다 점수가 오르면 안된다 -> 두더지가 사라질때까지

2. 클레이 사격
 좌 우 에서 무작위로 출현하는 타켓을 마우스로 제거
 타켓을 제거하면 점수를 획득 -> 제거된 타겟을 그자리에서 떨어져야한다
 등장하는 타겟의 종류는 무작위 도형처리를 할것
 사각형 50점 원 100점 다각형 100점

 시간은 60초 동안 지속 / 시간이 끝나면 다시시작할 수 있게 만들 것

 충돌함수 봉인 해제

3. 1 + 2 번에 이미지 추가
 배경 + 단일 이미지 추가 해오면 된다.
 두더지 없을떄 나올때 때렷을때 망치


한줄조사 IMAGE 클래스에 언급된 함수들 조사

*/