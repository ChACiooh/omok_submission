#include <iostream>
#include "../header/AI.h"

using namespace std;

int main()
{
    srand(time(NULL));
    bool mifirst = WHITE;
    int board[HEIGHT][WIDTH];
    int w_cnt, b_cnt;
    w_cnt = b_cnt = 0;
    AI ai;
    AIResult res;

    for(int i=0;i<HEIGHT;i++)
    {
        for(int j=0;j<WIDTH;j++)
            board[i][j] = -1; // NODRAW
    }

    while(true)
    {try{
        int x, y;
        cin >> x >> y;

        if(x == 0 && y == 0)    mifirst = BLACK;
        else
        {
            board[y-1][x-1] = !mifirst; // ����� ���� ���´�.
            if(mifirst == BLACK)    w_cnt++;
            else    b_cnt++;
        }

        res = ai.Run(board, b_cnt, w_cnt, !mifirst, 5);
        x = res.dol.x;
        y = res.dol.y;
        if(x < IW || x >= WIDTH || y < IH || y >= HEIGHT)
        {
            for(int i=0;i<HEIGHT;i++)
            {
                bool flag = false;
                for(int j=0;j<WIDTH;j++)
                {
                    if(board[i][j] == NODRAW)
                    {
                        x = j;
                        y = i;
                        flag = true;
                        break;
                    }
                }
                if(flag)    break;
            }
        }
        else if(board[y][x] != NODRAW)
        {
            for(int i=0;i<HEIGHT;i++)
            {
                bool flag = false;
                for(int j=0;j<WIDTH;j++)
                {
                    if(board[i][j] == NODRAW)
                    {
                        x = j;
                        y = i;
                        flag = true;
                        break;
                    }
                }
                if(flag)    break;
            }
        }
        cout << x+1 << " " << y+1 << endl;
        board[y][x] = mifirst;
        if(mifirst == BLACK)    b_cnt++;
        else    w_cnt++;
    }catch(exception e) { break; }
    }
    return 0;
}
