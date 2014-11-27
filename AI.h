#ifndef ARTIFITIAL_INTELIGENCE_H_INCLUDED
#define ARTIFITIAL_INTELIGENCE_H_INCLUDED

#include <ctime>
#include <cstdlib>

#define ERR             -1  // ���� ó���� �ڵ� -1.

#define BLACK    0
#define WHITE    1

#define NODRAW      -1
#define BLACK       0
#define WHITE       1

#define WIDTH   19
#define HEIGHT  19
#define IW 0
#define IH 0

#define PLAYER              0
#define ENEMY               1

#define GUARD_STATE         0
#define ATTACK_STATE        1

#define ARRAY_CNT           361

#define UPPER_OMOK_1ST      13  // 6�� �̻�. (������� �� ���� ���)
#define UPPER_OMOK_2ND      12  // 6�� �̻�. (������� �� �ִ� ���)
#define OMOK_1ST            11  // ����. (������� �� ���� ���)
#define OMOK_2ND            10  // ����. (������� �� �ִ� ���)
#define OMOK_3RD            9   // ����. (������� �� ������, �߰��� ������ ���Ե� ���)
#define OMOK_4TH            8   // ����. (������� �� ������, �߰��� ������ ���Ե� ���)
#define DANGER_ATTACK_1ST   7   // �ٵ� ���� 4�� ������ ������. (������� �� ������, �߰��� ������ ���Ե� ���)
#define DANGER_ATTACK_2ND   6   // �ٵ� ���� 4�� ������ ������. (������� �� ���� ���)
#define DANGER_ATTACK_3RD   5   // �ٵ� ���� 4�� ������ ������. (������� �� ������, �߰��� ������ ���Ե� ���)
#define DANGER_ATTACK_4TH   4   // �ٵ� ���� 4�� ����������. (������� �� �ִ°��)
#define ATTACK_1ST          3   // �ٵ� ���� 3�� ����������. (������� �� ���� ���)
#define ATTACK_2ND          2   // �ٵ� ���� 3�� ����������. (������� �� ���� ���)
#define PREATTACK_1ST       1   // �ٵ� ���� 2�� ���� ������. (������� �� ���� ���)
#define PREATTACK_2ND       0   // �ٵ� ���� 2�� ���� ������. (������� �� ���� ���)

struct Dol
{
    int x;
    int y;
};

struct AIResult
{
    Dol dol;
    int result;
};

class AI
{
    public:
        AIResult Run(int arrayboard[HEIGHT][WIDTH], int BlackCnt, int WhiteCnt, bool COMTurn, int Difficulty=3);

        bool CheckMove(int AlertLevel, int State);

        int RowCheck(int x, int y, bool player1, bool player2,
                     bool iErr = false, bool jErr = false, bool bSpaceChk=false);
        int ColCheck(int x, int y, bool player1, bool player2,
                     bool iErr = false, bool jErr = false, bool bSpaceChk=false);
        int UpperDiagCheck(int x, int y, bool player1, bool player2,
                           bool iErr = false, bool jErr = false, bool bSpaceChk=false);
        int LowerDiagCheck(int x, int y, bool player1, bool player2,
                           bool iErr = false, bool jErr = false, bool bSpaceChk=false);

    private:
        bool PlayerTurn;
        bool EnemyTurn;
        int board[HEIGHT][WIDTH];
        AIResult res;
};

#endif // ARTIFITIAL_INTELIGENCE_H_INCLUDED
