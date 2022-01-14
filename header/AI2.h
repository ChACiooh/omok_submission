#ifndef ARTIFITIAL_INTELIGENCE_H_INCLUDED
#define ARTIFITIAL_INTELIGENCE_H_INCLUDED

#include <ctime>
#include <cstdlib>

#define ERR             -1  // ���� ó���� �ڵ� -1.

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
	PREATTACK_2ND       ,   // �ٵ� ���� 2�� ���� ������. (������� �� ���� ���)
	PREATTACK_1ST       ,   // �ٵ� ���� 2�� ���� ������. (������� �� ���� ���)
	ATTACK_2ND          ,   // �ٵ� ���� 3�� ����������. (������� �� ���� ���)
	ATTACK_1ST          ,   // �ٵ� ���� 3�� ����������. (������� �� ���� ���)
	DANGER_ATTACK_4TH   ,   // �ٵ� ���� 4�� ����������. (������� �� �ִ°��)
	DANGER_ATTACK_3RD   ,   // �ٵ� ���� 4�� ������ ������. (������� �� ������, �߰��� ������ ���Ե� ���)
	DANGER_ATTACK_2ND   ,   // �ٵ� ���� 4�� ������ ������. (������� �� ���� ���)
	DANGER_ATTACK_1ST   ,   // �ٵ� ���� 4�� ������ ������. (������� �� ������, �߰��� ������ ���Ե� ���)
	OMOK_4TH            ,   // ����. (������� �� ������, �߰��� ������ ���Ե� ���)
	OMOK_3RD            ,   // ����. (������� �� ������, �߰��� ������ ���Ե� ���)
	OMOK_2ND            ,   // ����. (������� �� �ִ� ���)
	OMOK_1ST            ,   // ����. (������� �� ���� ���)
	UPPER_OMOK_2ND      ,   // 6�� �̻�. (������� �� �ִ� ���)
	UPPER_OMOK_1ST      ,    // 6�� �̻�. (������� �� ���� ���)
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
