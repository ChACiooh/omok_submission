#ifndef ARTIFITIAL_INTELIGENCE_H_INCLUDED
#define ARTIFITIAL_INTELIGENCE_H_INCLUDED

#include <ctime>
#include <cstdlib>

#define ERR             -1  // 에러 처리용 코드 -1.

#define WIDTH   19
#define HEIGHT  19
#define IW 0
#define IH 0

enum Dol{
	BLANK = -1, BLACK = 0, WHITE = 1
};

enum State{
	GUARD_STATE, ATTACK_STATE
};

enum Priority{
	PREATTACK_2ND       ,   // 바둑 돌이 2개 놓여 있을때. (상대편의 방어가 없는 경우)
	PREATTACK_1ST       ,   // 바둑 돌이 2개 놓여 있을때. (상대편의 방어가 없는 경우)
	ATTACK_2ND          ,   // 바둑 돌이 3개 놓여있을때. (상대편의 방어가 없는 경우)
	ATTACK_1ST          ,   // 바둑 돌이 3개 놓여있을때. (상대편의 방어가 없는 경우)
	DANGER_ATTACK_4TH   ,   // 바둑 돌이 4개 놓여있을때. (상대편의 방어가 있는경우)
	DANGER_ATTACK_3RD   ,   // 바둑 돌이 4개 놓여져 있을때. (상대편의 방어가 있으며, 중간에 공백이 포함된 경우)
	DANGER_ATTACK_2ND   ,   // 바둑 돌이 4개 놓여져 있을때. (상대편의 방어가 없는 경우)
	DANGER_ATTACK_1ST   ,   // 바둑 돌이 4개 놓여져 있을때. (상대편의 방어가 없으나, 중간에 공백이 포함된 경우)
	OMOK_4TH            ,   // 오목. (상대편의 방어가 있으며, 중간에 공백이 포함된 경우)
	OMOK_3RD            ,   // 오목. (상대편의 방어가 없으나, 중간에 공백이 포함된 경우)
	OMOK_2ND            ,   // 오목. (상대편의 방어가 있는 경우)
	OMOK_1ST            ,   // 오목. (상대편의 방어가 없는 경우)
	UPPER_OMOK_2ND      ,   // 6개 이상. (상대편의 방어가 있는 경우)
	UPPER_OMOK_1ST      ,    // 6개 이상. (상대편의 방어가 없는 경우)
	ERROR
};

struct Point
{
	int x;
	int y;
};
class AI
{
public:
	AI();
	Point Run(Dol my_dol, int difficulty = 3);

	inline void Put(int x, int y, Dol d){ board[y][x] = d; };
	inline Dol Get(int x, int y){ return board[y][x]; };
	Point GetRandomPos();
private:

	bool CheckMove(Priority priority, State state, Point &pos, Dol my_dol);
	int CheckMoveContent(int x, int y, int &i, int &cnt, int &space_cnt, bool &err, Dol my_dol, int &guard_cnt, bool is_space_chk, int compare_dest, int compare_src);
	int CheckMoveContent(int x, int y, int &i, int &cnt, int &space_cnt, bool &err, Dol my_dol, int &guard_cnt, bool is_space_chk, int compare_dest1, int compare_src1, int compare_dest2, int compare_src2);

	int RowCheck(int x, int y, Dol my_dol, bool is_space_chk = false);
	int ColCheck(int x, int y, Dol my_dol, bool is_space_chk = false);
	int UpperDiagCheck(int x, int y, Dol my_dol, bool is_space_chk = false);
	int LowerDiagCheck(int x, int y, Dol my_dol, bool is_space_chk = false);

	Priority GetPriority(int cnt, int guard_cnt, bool is_space_chk, int space_cnt);

	Dol board[HEIGHT][WIDTH];
};

#endif // ARTIFITIAL_INTELIGENCE_H_INCLUDED
