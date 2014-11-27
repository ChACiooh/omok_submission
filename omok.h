#ifndef OMOK_H_INCLUDED
#define OMOK_H_INCLUDED

#include <algorithm>
#include <vector>

using namespace std;

class Dol
{
public:
    bool IsItBlack() const { return imblack; }
    pair<int, int> GetCoordinate() const { return coordinate; }

protected:
    Dol() {}
    Dol(int x, int y, bool miblack)
    {
        coordinate.first = x;
        coordinate.second = y;
        imblack = miblack;
    }
    bool imblack;

private:
    pair<int, int> coordinate;
};


class Board
{
public:
    Board() : x_max(19), y_max(19), x_min(1), y_min(1) {}
    ~Board() { dols.clear(); }
    pair<bool, bool> IsItOn(int x, int y) const;
    void insert(Dol dol) { dols.push_back(dol); }
    const Dol& GetDol(int idx) { return dols[idx]; }
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

class Defence : public Dol
{
public:
    Defence() {}
    Defence(bool black) : myColor(black), direct(0), count(0) {}
    void Put(int x, int y, bool isblack);
    void DFS(int x, int y, int cnt = 5);

    const bool& GetMyColor() const { return myColor; }

private:
    Board board;
    bool myColor;
    int direct;
    int count;
};

#endif // OMOK_H_INCLUDED
