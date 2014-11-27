#include <iostream>
#include "omok.h"

/*** first is black ***/
inline void Print(vector<pair<int, pair<Dol, int> > > a)
{
    cout << "Print:" << endl;
    for(size_t i=0; i < a.size(); i++)
    {
        cout << a[i].first << " Color:"
            << a[i].second.first.IsItBlack()
            << " " ;
        cout <<a[i].second.second << endl;
    }
    cout << endl;
}

int main()
{
    bool mifirst = false;
    bool defenceSet = false;
    Defence def;
    while(true)
    {
        Dol putDol; // the dol that I'll put.
        int x, y;
        cin >> x >> y;
        if(x == 0 && y == 0)    mifirst = true;
        else    def.Put(x, y, !mifirst);

        // set my color in def.
        if(!defenceSet)
        {
            def = Defence(mifirst);
            if(mifirst)
            {
                putDol = Dol(def.Board::GetWidth()/2, def.Board::GetHeight()/2, mifirst);
            }
            else
            {
                putDol = Dol(x+1, y, mifirst);
            }
            defenceSet = true;
            continue;
        }

        // change direction in for, and check the direction that gained max count.

        // first means number of same dols.
        // second means index of direction and first dol.
        vector<pair<int, pair<Dol, int> > > enemyCnt;
        vector<pair<int, pair<Dol, int> > > myCnt;

        for(size_t i=0;i<def.size();i++)
        {
            Dol dol(def.Board::GetDol(i));
            int dol_x = dol.GetCoordinate().first;
            int dol_y = dol.GetCoordinate().second;
            for(size_t j=1;j<=9;j++)
            {
                if(!def.SetDirect(j))   continue;
                def.DFS(dol_x, dol_y);
                int e_c = def.GetECount();
                int m_c = def.GetMCount();

                enemyCnt.push_back(make_pair(e_c, make_pair(dol, j)));
                myCnt.push_back(make_pair(m_c, make_pair(dol,j)));

                def.InitCount();
            }
        }
        def.SetDirect(0); // initialize direct.

        sort(enemyCnt.begin(), enemyCnt.end(), comp);
        sort(myCnt.begin(), myCnt.end(), comp);

        if(enemyCnt[0].first >= myCnt[0].first)
        {
            // defence mode
            def.SetDirect(enemyCnt[0].second.second);
            def.DFS(enemyCnt[0].second.first.GetCoordinate().first, enemyCnt[0].second.first.GetCoordinate().second, 7);
        }
        else
        {
            // attack mode
            def.SetDirect(myCnt[0].second.second);
        }

        /*** print for test ***/
        Print(enemyCnt);
        Print(myCnt);
        cout << endl;
    }
    return 0;
}
