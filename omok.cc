#include "omok.h"

bool comp(pair<int, pair<Dol, int> > a, pair<int, pair<Dol, int> > b) { return a.first < b.first; }

pair<bool, bool> Board::IsItOn(int x, int y) const
{
    pair<int, int> c = make_pair(x, y);
    size_t i;
    bool find = false, color;
    for(i = 0; i < dols.size(); i++)
        if(dols[i].GetCoordinate() == c)
        {
            find = true;
            break;
        }
    if(i == dols.size())    return make_pair(false, false);
    color = dols[i].IsItBlack();
    return make_pair(find, color);
}

const Dol& Board::GetDol(int x, int y)
{
    // under existion on (x, y).
    pair<int, int> c = make_pair(x, y);
    size_t i;
    for(i = 0; i < dols.size(); i++)
        if(dols[i].GetCoordinate() == c)    break;

    return GetDol(i);
}

void Defence::Put(int x, int y, bool isblack)
{
    putComplete = true;
    Dol dol(x, y, isblack);
    Board::insert(dol);
}

void Defence::DFS(int x, int y, int cnt)
{
    if(cnt!=5 && cnt_is_not_5 == false)
    {
        cnt_is_not_5 = true;
    }
    if(x < Board::GetXMin() || x > Board::GetWidth() ||
       y < Board::GetYMin() || y > Board::GetHeight())    return;

    pair<bool, bool> test = Board::IsItOn(x, y);
    if(test.first) // found
    {
        if(test.second != myColor)  e_count++;
        else    m_count++;
    }
    else if(cnt <= 3)
    {
        if(e_count < 1) return;
    }

    if(cnt < 0 || !direct)    return;

        /** dx[] = 0, -1, 0, 1, -1, 1, -1, 0, 1
         * dy[] = 0, -1, -1, -1, 0, 0, 1, 1, 1
         */
    DFS(x+dx[direct], y+dy[direct], cnt-1);
}

bool Defence::SetDirect(int d)
{
    if(d > 9 || d < 0)  return false;
    direct = d;
    return true;
}
