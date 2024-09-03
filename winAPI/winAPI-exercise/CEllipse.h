#pragma once
#include "Object.h"
class CEllipse :
    public Object
{
private:
    int m_radious;

public:
    void init();
    void release();
    void update();
    void render(HDC hdc);

    CEllipse();
    ~CEllipse();

    int getRadious() { return m_radious; };
};

