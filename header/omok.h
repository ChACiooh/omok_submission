#ifndef OMOK_H_INCLUDED
#define OMOK_H_INCLUDED

#include <vector>
#include <iostream>

using namespace std;

struct Point
{
    explicit Point(int a, int b) : x(a), y(b) { }
    int x;
    int y;
};

bool operator==(const Point &a, const Point &b);
Point operator+(const Point &a, const Point&b);

class Omok {

 public:

  Omok() : width_(19), height_(19), blacks_turn_(true) {}


  // ������ (x,y)�� ���� ���� (x,y = 0~18). ù ���� �׻� �浹�� ����.

  // �� �ٱ��ʿ� ���ų� �̹� ���� �ڸ��� ���� ��� false�� ����.

  // �������� ��� ���� ���� blacks_turn_�� �Ͽ� �°� ����.

  bool Put(int x, int y);


  // ���� ������ ���Դ��� �Ǵ��Ͽ� ������ ��� true�� �����ϰ�,

  // is_winner_black�� �浹�� �̱� ��� true��, �鵹�� �̱� ��� false��

 // ����.

  bool CrossCheck(const bool is_col) const;
  bool DiagCheck(const int dir) const;
  bool FindStone(Point x) const;
  bool FindBlackStone(Point x) const;
  bool FindWhiteStone(Point x) const;
  bool IsOmok(bool* is_winner_black) const;

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  bool IsBlacksTurn() const { return blacks_turn_; }
  void TurnChange() { blacks_turn_ = !blacks_turn_; }


 private:

  int width_, height_;
  vector<Point> bl; // black stones
  vector<Point> wh; // white stones
  bool blacks_turn_;  // �浹 ���ʸ� true.
  // ��� ������ �߰�.

};

ostream& operator<<(ostream& os, const Omok& omok);

#endif // OMOK_H_INCLUDED
