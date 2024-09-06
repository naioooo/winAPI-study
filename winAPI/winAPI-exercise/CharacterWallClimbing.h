#pragma once
#include "GameNode.h"
#include "stdafx.h"
#include "Simba.h"

class CharacterWallClimbing : public GameNode
{
private:
	shared_ptr<GImage> m_bgImage;
	shared_ptr<GImage> m_brickImage;
	shared_ptr<Simba> m_simba;
	shared_ptr<GImage> m_miniMapBuffer;
	shared_ptr<GImage> m_camera;

	vector<RECT> m_rects;


public:
	HRESULT init(void)override;
	void release(void)override;
	void update(void)override;
	void render(HDC hdc)override;
	void input()override;
	void mouseInput(UINT message, LPARAM lParam)override;

	CharacterWallClimbing();
	~CharacterWallClimbing();
};

