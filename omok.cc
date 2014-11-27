#include "omok.h"

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

void Defence::Put(int x, int y, bool isblack)
{
    Dol dol(x, y, isblack);
    board.insert(dol);
}

void Defence::DFS(int x, int y, int cnt)
{
    if(x < board.GetXMin() || x > board.GetWidth() ||
       y < board.GetYMin() || y > board.GetHeight())    return;
    if(cnt < 0)    return;
    pair<bool, bool> test = board.IsItOn(x, y);
    if(test.first)
    {
        if(test.second != myColor)  count++;
    }

        /** dx[] = 0, -1, 0, 1, -1, 1, -1, 0, 1
         * dy[] = 0, -1, -1, -1, 0, 0, 1, 1, 1
         */
    switch(direct)
    {
    case 0:
        break;
    case 1:
        DFS(x-1, y-1, cnt-1);
        break;
    case 2:
        DFS(x, y-1, cnt-1);
        break;
    case 3:
        DFS(x+1, y-1, cnt-1);
        break;
    case 4:
        DFS(x-1, y, cnt-1);
        break;
    case 5:
        DFS(x+1, y, cnt-1);
        break;
    case 6:
        DFS(x-1, y+1, cnt-1);
        break;
    case 7:
        DFS(x, y+1, cnt-1);
        break;
    case 8:
        DFS(x+1, y+1, cnt-1);
        break;
    }
}
