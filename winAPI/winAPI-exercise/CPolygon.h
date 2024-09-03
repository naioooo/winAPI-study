#pragma once
#include "Object.h"
class CPolygon :
    public Object
{

private:
    vector<POINT> m_points;

public:
    void init();
    void release();
    void update();
    void render(HDC hdc);

    void GenerateRandomPoints(int width, int height);

    CPolygon();
    ~CPolygon();

    static double CalculateAngle(const POINT& pt)
    {
        return atan2(pt.y, pt.x);
    }

    bool CompareByAngle(const POINT& a, const POINT& b)
    {
        return CalculateAngle(a) < CalculateAngle(b);
    }
};

