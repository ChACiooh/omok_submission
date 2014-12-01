// omok.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include <iostream>
#include "AI.h"

using namespace std;

int main()
{
	srand(time(NULL));
	Dol my_dol = WHITE;
	AI ai;
	bool is_first = true;

	while (true)
	{
		try{
			Point pos;
			cin >> pos.x >> pos.y;
			pos.x--;
			pos.y--;

			if (is_first)
			{
				if (pos.x < 0 && pos.y < 0)
				{
					my_dol = BLACK;
					pos.x = pos.y = 9;
				}
				else
				{
					my_dol = WHITE;
					ai.Put(pos.x, pos.y, my_dol == WHITE ? BLACK : WHITE);
					do{
						pos.x = 8 + rand() % 3;
						pos.y = 8 + rand() % 3;
					} while (ai.Get(pos.x, pos.y) != BLANK);
				}
				is_first = false;
			}
			else
			{
				ai.Put(pos.x, pos.y, my_dol == WHITE ? BLACK : WHITE);
				pos = ai.Run(my_dol, 5);
			}


			cout << pos.x + 1 << " " << pos.y + 1 << endl;
			ai.Put(pos.x, pos.y, my_dol);
		}
		catch (exception e) { break; }
	}
	return 0;
}
