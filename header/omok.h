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


  // 번갈아 (x,y)에 돌을 놓음 (x,y = 0~18). 첫 수는 항상 흑돌로 가정.

  // 판 바깥쪽에 놓거나 이미 놓인 자리에 놓을 경우 false를 리턴.

  // 정상적인 경우 돌을 놓고 blacks_turn_을 턴에 맞게 세팅.

  bool Put(int x, int y);


  // 현재 오목이 나왔는지 판단하여 오목인 경우 true를 리턴하고,

  // is_winner_black은 흑돌이 이긴 경우 true로, 백돌이 이긴 경우 false로

 // 세팅.

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
  bool blacks_turn_;  // 흑돌 차례면 true.
  // 멤버 변수를 추가.

};

ostream& operator<<(ostream& os, const Omok& omok);

#endif // OMOK_H_INCLUDED
