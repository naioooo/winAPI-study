#include "GameNode.h"
#include "stdafx.h"

class MakeMiniMap : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;
	vector<shared_ptr<GImage>> m_Images;
	shared_ptr<GImage> m_miniMapBuffer;

public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	MakeMiniMap();
	~MakeMiniMap();
};

/*
2. 미니맵 만들기
 두가지 버전으로 만들기
  1. 화면위에 표시되는 GUI 형태의 작은 미니맵
  2. 화면위에 그려지는 투명도를 가진 전체화면 미니맵

 플레이어의 움직임을 미니맵에서도 확인 할 수 잇도록
*/

