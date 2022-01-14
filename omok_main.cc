#include "header/omok.h"
#include <cstdio>
#include <string>
//#include "windows.h"

bool Input(Omok &omok);

int main()
{
    Omok omok;
    int turns = 0;
    while(true)
    {
        bool is_winner_black = omok.IsBlacksTurn();
        if(!Input(omok))    break;
        turns++;
        if(turns > 8)
        {
            if(omok.IsOmok(&is_winner_black))
            {
                cout << omok;
                if(is_winner_black) printf("Winner: Black player\n");
                else    printf("Winner: White player\n");
                break;
            }
        }
        //system("cls");
        //cout << omok;
        omok.TurnChange();
    }
    //system("pause");
    return 0;
}

bool Input(Omok &omok)
{
    if(omok.IsBlacksTurn()) cout << "Black: ";
    else    cout << "White: ";
    string sx, sy;
    cin >> sx >> sy;
    for(int i=0;i<sx.length();i++)
        if(!isdigit(sx[i])) return false;
    for(int i=0;i<sy.length();i++)
        if(!isdigit(sy[i])) return false;

    int x, y;
    sscanf(sx.c_str(), "%d", &x);
    sscanf(sy.c_str(), "%d", &y);

    if(!omok.Put(x, y))
    {
        printf("Can not be placed there.\n");
        return Input(omok);
    }
    return true;
}
