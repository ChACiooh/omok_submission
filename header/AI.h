#ifndef ARTIFITIAL_INTELIGENCE_H_INCLUDED
#define ARTIFITIAL_INTELIGENCE_H_INCLUDED

#include <ctime>
#include <cstdlib>

#define ERR             -1  // 에러 처리용 코드 -1.

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


/*** 내가 (x,y)에 놓았다고 가정하고,
    나의 돌 상태가 다음 중 하나일 때
    각각의 경우에 따라 실행하도록 한다. ***/
#define UPPER_OMOK_1ST      13  // 6개 이상. (상대편의 방어가 없는 경우)
#define UPPER_OMOK_2ND      12  // 6개 이상. (상대편의 방어가 있는 경우)
#define OMOK_1ST            11  // 오목. (상대편의 방어가 없는 경우)
#define OMOK_2ND            10  // 오목. (상대편의 방어가 있는 경우)
#define OMOK_3RD            9   // 오목. (상대편의 방어가 없으나, 중간에 공백이 포함된 경우)
#define OMOK_4TH            8   // 오목. (상대편의 방어가 있으며, 중간에 공백이 포함된 경우)
#define DANGER_ATTACK_1ST   7   // 바둑 돌이 4개 놓여져 있을때. (상대편의 방어가 없으나, 중간에 공백이 포함된 경우)
#define DANGER_ATTACK_2ND   6   // 바둑 돌이 4개 놓여져 있을때. (상대편의 방어가 없는 경우)
#define DANGER_ATTACK_3RD   5   // 바둑 돌이 4개 놓여져 있을때. (상대편의 방어가 있으며, 중간에 공백이 포함된 경우)
#define DANGER_ATTACK_4TH   4   // 바둑 돌이 4개 놓여있을때. (상대편의 방어가 있는경우)
#define ATTACK_1ST          3   // 바둑 돌이 3개 놓여있을때. (상대편의 방어가 없는 경우)
#define ATTACK_2ND          2   // 바둑 돌이 3개 놓여있을때. (상대편의 방어가 있는 경우)
#define PREATTACK_1ST       1   // 바둑 돌이 2개 놓여 있을때. (상대편의 방어가 없는 경우)
#define PREATTACK_2ND       0   // 바둑 돌이 2개 놓여 있을때. (상대편의 방어가 있는 경우)

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

        // (x,y)에 먼저 두었다고 가정하고 그 상태가 무엇인지를 판단한다.
        // 그렇게 판단하여 나온 결과에 대해 만약 (x,y)가 이미 놓여 있는 자리면 넘어간다.
        // 원래는 반대로 해야 하지 않나 싶지만..
        // bSpaceChk의 경우 공백을 따져야 하는 경우에 true
        // iErr는 가로 오차의 한계까지 도달했을 때 true - 예: x-i < 0 || x+i >= WIDTH
        // jErr는 세로 오차의 한계까지 도달했을 때 true - 예: y-j < 0 || y+j >= HEIGHT
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
