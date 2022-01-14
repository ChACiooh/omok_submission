#include "../header/omok.h"
#include <algorithm>
#include <queue>

bool compY(Point a, Point b)
{
    return a.y < b.y; // sort by y-axis' values.
}

bool compX(Point a, Point b)
{
    return a.x < b.x; // sort by x-axis' values.
}

bool operator==(const Point &a, const Point &b)
{
    return a.x == b.x && a.y == b.y;
}

Point operator+(const Point &a, const Point &b)
{
    return Point(a.x+b.x, a.y+b.y);
}

bool Omok::Put(int x, int y)
{
    if(x<0 || y<0 || x>=width_ || y>=height_)    return false;
    Point temp(x,y);
    if(FindStone(temp)) return false;
    if(blacks_turn_)
    {
        bl.push_back(temp);
        sort(bl.begin(), bl.end(), compY); // sort by y-axis' value as soon as point is inserted.
    }
    else
    {
        wh.push_back(temp);
        sort(wh.begin(), wh.end(), compY); // sort by y-axis' value as soon as point is inserted.
    }
    return true;
}

bool Omok::CrossCheck(const bool is_col) const
{
    vector<Point> temp;
    int cnt = 0, it = 0;
    if(blacks_turn_) temp = bl;
    else    temp = wh;
    sort(temp.begin(), temp.end(), compX);
    queue<Point> myQ;
    myQ.push(temp[it++]);

    while(cnt!=5 && !myQ.empty() && it<temp.size())
    {
        cnt = 0;
        Point pastp = myQ.front();
        cnt++;
        myQ.pop();
        int i, j, ip, jp;
        if(!is_col)
        {
            i = pastp.x;
            j = pastp.y+1;
            ip = 0;
            jp = 1;
        }
        else
        {
            i = pastp.x+1;
            j = pastp.y;
            ip = 1;
            jp = 0;
        }
        for(; i<width_ && j<height_; i+=ip, j+=jp)
        {
            Point nowp(i, j);
            if(blacks_turn_)
            {
                if(FindBlackStone(nowp))    cnt++;
                else
                {
                    if(cnt == 5)    break;
                    cnt = 0;
                    myQ.push(temp[it++]);
                }
            }
            else
            {
                if(FindWhiteStone(nowp))    cnt++;
                else
                {
                    if(cnt == 5)    break;
                    cnt = 0;
                    myQ.push(temp[it++]);
                }
            }
            if(it == temp.size())   break;
        }
    }
    if(cnt == 5)    return true;
    return false;
}

bool Omok::DiagCheck(const int dir) const
{
    int cnt = 0, it = 0;
    vector<Point> temp;
    queue<Point> myQ;

    if(blacks_turn_)    temp = bl;
    else    temp = wh;
    sort(temp.begin(), temp.end(), compX);
    if(temp.size()>0)   myQ.push(temp[it++]);

    while(!myQ.empty() && cnt!=5 && it<temp.size())
    {
        cnt = 0;
        Point pastp = myQ.front();
        cnt++;
        myQ.pop();
        for(int i=pastp.x+1, j=pastp.y+dir; i<width_ && j>=0 && j<height_; i++, j+=dir)
        {
            Point nowp(i,j);
            if(blacks_turn_)
            {
                if(FindBlackStone(nowp)) cnt++;
                else
                {
                    if(cnt == 5)    break;
                    cnt = 0;
                    myQ.push(temp[it++]);
                }
            }
            else
            {
                if(FindWhiteStone(nowp)) cnt++;
                else
                {
                    if(cnt == 5)    break;
                    cnt = 0;
                    myQ.push(temp[it++]);
                }
            }
            if(it == temp.size())   break;
        }
    }
    if(cnt == 5)    return true;
    return false;
}

bool Omok::FindStone(Point x) const
{
    return FindBlackStone(x) || FindWhiteStone(x);
}

bool Omok::FindBlackStone(Point x) const
{
    for(int i=0;i<bl.size();i++)
        if(x == bl[i])  return true;
    return false;
}

bool Omok::FindWhiteStone(Point x) const
{
    for(int i=0;i<wh.size();i++)
        if(x == wh[i])  return true;
    return false;
}

bool Omok::IsOmok(bool *is_winner_black) const
{
    // optimized memory and function calls.
    if(CrossCheck(true))
    {
        if(blacks_turn_)    *is_winner_black = true;
        else    *is_winner_black = false;
        return true;
    }
    else if(CrossCheck(false))
    {
        if(blacks_turn_)    *is_winner_black = true;
        else    *is_winner_black = false;
        return true;
    }
    else if(DiagCheck(1))
    {
        if(blacks_turn_)    *is_winner_black = true;
        else    *is_winner_black = false;
        return true;
    }
    else if(DiagCheck(-1))
    {
        if(blacks_turn_)    *is_winner_black = true;
        else    *is_winner_black = false;
        return true;
    }
    return false;
}

ostream& operator<<(ostream& os, const Omok& omok)
{
    for(int i=0;i<omok.GetHeight();i++)
    {
        for(int j=0;j<omok.GetWidth();j++)
        {
            Point temp(j, i);
            if(omok.FindBlackStone(temp))
            {
                os << "o ";
            }
            else if(omok.FindWhiteStone(temp))
            {
                os << "x ";
            }
            else os << ". ";
        }
        os << endl;
    }
    return os;
}

