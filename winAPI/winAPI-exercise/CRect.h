#pragma once
#include "Object.h"
class CRect :
    public Object
{
private:
    int m_width;
    int m_height;

public:
    void init();
    void release();
    void update();
    void render(HDC hdc);

    CRect();
    ~CRect();
};

