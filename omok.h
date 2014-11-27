#ifndef OMOK_H_INCLUDED
#define OMOK_H_INCLUDED

#include <algorithm>
#include <vector>

using namespace std;

class Dol
{
public:
    Dol() {}
    Dol(const Dol& dol) : coordinate(dol.GetCoordinate()), imblack(dol.IsItBlack()) {}
    Dol(int x, int y, bool miblack)
    {
        coordinate.first = x;
        coordinate.second = y;
        imblack = miblack;
    }
    bool IsItBlack() const { return imblack; }
    pair<int, int> GetCoordinate() const { return coordinate; }

private:
    pair<int, int> coordinate;
    bool imblack;
};


class Board
{
public:
    Board() : x_max(19), y_max(19), x_min(1), y_min(1) {}
    ~Board() { dols.clear(); }
    pair<bool, bool> IsItOn(int x, int y) const;
    void insert(Dol dol) { dols.push_back(dol); }
    const Dol& GetDol(int idx) { return dols[idx]; }
    const Dol& GetDol(int, int);
    size_t GetSize() const { return dols.size(); }

    const int GetWidth() const { return x_max; }
    const int GetHeight() const { return y_max; }
    const int GetXMin() const { return x_min; }
    const int GetYMin() const { return y_min; }

private:
    int x_max;
    int y_max;
    int x_min;
    int y_min;
    vector<Dol> dols;
};

bool comp(pair<int, pair<Dol, int> > a, pair<int, pair<Dol, int> > b);
const static int dx[] = {0, -1, 0, 1, -1, 1, -1, 0, 1};
const static int dy[] = {0, -1, -1, -1, 0, 0, 1, 1, 1};

class Defence : public Board
{
public:
    Defence() {}
    Defence(bool black) : cnt_is_not_5(false), myColor(black), putComplete(false), direct(0), e_count(0), m_count(0) {}
    void Put(int x, int y, bool isblack);
    void DFS(int x, int y, int cnt = 5);
    void InitCount() { e_count = m_count = 0; }
    void InitDeter() { cnt_is_not_5 = false; }
    bool SetDirect(int d);
    size_t size() const { return Board::GetSize(); }

    const bool& GetMyColor() const { return myColor; }
    const int& GetECount() const { return e_count; }
    const int& GetMCount() const { return m_count; }

private:
    bool cnt_is_not_5;
    bool myColor;
    bool putComplete;
    int direct;
    int e_count;
    int m_count;
};

#endif // OMOK_H_INCLUDED
