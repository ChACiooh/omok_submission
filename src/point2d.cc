#include "../header/point2d.h"

Point::Point() {}
Point::Point(const Point& p)
{
    x = p.x;
    y = p.y;
}

Point::Point(int c)
{
    x = y = c;
}

Point::Point(int x, int y)
{
    this->x = x;
    this->y = y;
}

Point Point::operator-() const
{
    return Point(-x, -y);
}

Point& Point::operator+=(const Point& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

Point& Point::operator-=(const Point& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

Point& Point::operator*=(const Point& p)
{
    x *= p.x;
    y *= p.y;
    return *this;
}

Point operator+(const Point& lhs, const Point& rhs)
{
    return Point(lhs.x+rhs.x, lhs.y+rhs.y);
}

Point operator-(const Point& lhs, const Point& rhs)
{
    return Point(lhs.x-rhs.x, lhs.y-rhs.y);
}

Point operator*(const Point& lhs, const Point& rhs)
{
    return Point(lhs.x*rhs.x, lhs.y*rhs.y);
}

ostream& operator<<(ostream& os, Point p)
{
    os << "(" << p.x << ", " << p.y << ")" << endl;
    return os;
}
