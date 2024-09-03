#include "CPolygon.h"

void CPolygon::init()
{
}

void CPolygon::release()
{
}

void CPolygon::update()
{
	Object::update();
}

void CPolygon::render(HDC hdc)
{
    if (m_state != None)
    {
        vector<POINT> transformedPoints;
        transformedPoints.reserve(m_points.size());

        for (const auto& pt : m_points)
        {
            POINT transformedPoint;
            transformedPoint.x = pt.x + m_center.x;
            transformedPoint.y = pt.y + m_center.y;

            transformedPoints.push_back(transformedPoint);
        }

        RECT rect = getRect();

        rect.left += getCenter().x;
        rect.right += getCenter().x;
        rect.top += getCenter().y;
        rect.bottom += getCenter().y;

        DrawRect(hdc, rect);

        Polygon(hdc, transformedPoints.data(), transformedPoints.size());

        switch (m_state)
        {
        case Idle:
            break;

        case Die:
            break;
        }
    }
}

void CPolygon::GenerateRandomPoints(int width, int height)
{
    int numPoints = RND->getFromIntTo(3, 10);

    for (int i = 0; i < numPoints; ++i)
    {
        POINT pt;
        pt.x = RND->getFromIntTo(-(width / 2), width / 2);
        pt.y = RND->getFromIntTo(-(height / 2), height / 2);
        m_points.push_back(pt);
    }

    sort(m_points.begin(), m_points.end(),
        [this](const POINT& a, const POINT& b) { return this->CompareByAngle(a, b); });

}

CPolygon::CPolygon()
{
    m_type = TYPE::POLYGON;
    m_state = Idle;
    m_Cnt = 0;
    m_speed = RND->getFromFloatTo(3.0f, 10.0f);

    m_gradient = RND->getFromFloatTo(0.0005f, 0.001f);
    m_interceptX = 800;
    m_interceptY = RND->getFromIntTo(100, 500);

    m_dir = RND->getInt(2);

    if (m_dir == 0)
    {
        m_center = { 0, 0 };
    }
    else if (m_dir == 1)
    {
        m_center = { 800, 0 };
    }

    GenerateRandomPoints(100, 100);

    m_rect = { INT_MAX , INT_MAX , -INT_MAX , -INT_MAX };

    for (auto& point : m_points)
    {
        if (m_rect.left > point.x) m_rect.left = point.x;
        if (m_rect.top > point.y) m_rect.top = point.y;
        if (m_rect.right < point.x) m_rect.right = point.x;
        if (m_rect.bottom < point.y) m_rect.bottom = point.y;
    }

}

CPolygon::~CPolygon()
{
}
