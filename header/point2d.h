#ifndef POINT2D_H_INCLUDED
#define POINT2D_H_INCLUDED
#include <iostream>
using namespace std;
struct Point {
  int x, y;  // 멤버 변수.

  Point();
  Point(const Point& p);
  explicit Point(int c);
  Point(int x, int y);

  Point operator-() const;  // 전위 - 연산자
  Point& operator+=(const Point& p);
  Point& operator-=(const Point& p);
  Point& operator*=(const Point& p);
};

Point operator+(const Point& lhs, const Point& rhs);
Point operator-(const Point& lhs, const Point& rhs);
Point operator*(const Point& lhs, const Point& rhs);
ostream& operator<<(ostream& os, Point p);


#endif // POINT2D_H_INCLUDED
