#include <iostream>
#include "omok.h"

/*** first is black ***/
int main()
{
    bool mifirst = false;
    bool defenceSet = false;
    Defence def;
    while(true)
    {
        int x, y;
        cin >> x >> y;
        if(x == 0 && y == 0)    mifirst = true;

        // set my color in def.
        if(!defenceSet)
        {
            if(mifirst)
            {
                def = Defence(true);
            }
            else
            {
                def = Defence(false);
            }
            defenceSet = true;
        }

        def.Put(x, y, !def.GetMyColor());
    }
    return 0;
}
