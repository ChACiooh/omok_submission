#include <iostream>
#include "AI.h"

using namespace std;

int main()
{
    srand(time(NULL));
    bool mifirst = false;
    int board[HEIGHT][WIDTH];
    int w_cnt, b_cnt;
    w_cnt = b_cnt = 0;
    AI ai;

    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
            board[i][j] = -1; // NODRAW
    }

    while(true)
    {
        int x, y;
        cin >> x >> y;

        if(x == 0 && y == 0)    mifirst = true;
        else    board[y][x] = !mifirst; // 상대편 돌을 놓는다.

        AIResult res = ai.Run(board, b_cnt, w_cnt, !mifirst, 5);
        x = res.dol.x;
        y = res.dol.y;
        cout << x << " " << y << endl;
        board[y][x] = mifirst;
    }
    return 0;
}
