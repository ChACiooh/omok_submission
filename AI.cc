#include "AI.h"

/*** AI ***/
AIResult AI::Run(int array_board[HEIGHT][WIDTH], int BlackCnt, int WhiteCnt, bool COMTurn, int Difficulty)
{
    for(int i=0; i<HEIGHT; i++)
        for(int j=0; j<WIDTH; j++)  board[i][j] = array_board[i][j];

    if( COMTurn == BLACK )
    {
        PlayerTurn = WHITE;
        EnemyTurn = BLACK;
    }
    else
    {
        PlayerTurn = BLACK;
        EnemyTurn = WHITE;
    }

    res.result = 0;

    // 바둑 판에 바둑돌이 하나도 없을때엔, 무조건 정가운데 부터 시작한다.
    if( (COMTurn == BLACK)? BlackCnt+WhiteCnt == 0 : WhiteCnt == 0 )
    {
        if(board[HEIGHT/2][WIDTH/2] == NODRAW)
        {
            res.dol.x = WIDTH/2;
            res.dol.y = HEIGHT/2;
        }
        else
        {
            int dx[] = {0, -1, 0, 1, -1, 1, -1, 0, 1};
            int dy[] = {0, -1, -1, -1, 0, 0, 1, 1, 1};
            int idx = rand()%(8)+1;
            res.dol.x = WIDTH/2 + dx[idx];
            res.dol.y = HEIGHT/2 +dy[idx];
        }

        return res;
    } // if( (COMTurn == BLACK)? BlackCnt+WhiteCnt == 0 : WhiteCnt == 0 ).


    // 여기서 체크 하는 순서를 변경하거나 삭제하는 것에 따라 난이도가 달라진다.
    // 체크시에는 중간의 공백도 포함하여 계산을 한다.

    // begin 기본 세팅. {
    if(CheckMove(UPPER_OMOK_1ST, ATTACK_STATE) == 1) // 바로 공격 하면 이기는 곳이 있는지 체크. (예: 컴퓨터 돌 5개 이상)
    {
        res.result = UPPER_OMOK_1ST;
        return res;
    }
    else if(CheckMove(UPPER_OMOK_2ND, ATTACK_STATE) == 1) // 바로 공격 하면 이기는 곳이 있는지 체크. (예: 컴퓨터 돌 5개 이상)
    {
        res.result = UPPER_OMOK_2ND;
        return res;
    }
    else if(CheckMove(OMOK_1ST, ATTACK_STATE) == 1) // 바로 공격 하면 이기는 곳이 있는지 체크. (예: 컴퓨터 돌 4개)
    {
        res.result = OMOK_1ST;
        return res;
    }
    else if(CheckMove(OMOK_2ND, ATTACK_STATE) == 1) // 바로 공격 하면 이기는 곳이 있는지 체크. (예: 컴퓨터 돌 4개)
    {
        res.result = OMOK_2ND;
        return res;
    }
    else if(CheckMove(UPPER_OMOK_1ST, GUARD_STATE) == 1) // 바로 공격 당하면 지는 곳이 있는지 체크. (예: 플레이어 돌 5개 이상 - 방어가 있는 경우,)
        return res;
    else if(CheckMove(UPPER_OMOK_2ND, GUARD_STATE) == 1) // 바로 공격 당하면 지는 곳이 있는지 체크. (예: 플레이어 돌 5개 이상 - 방어가 있는 경우,)
        return res;
    else if(CheckMove(OMOK_1ST, GUARD_STATE) == 1) // 바로 공격 당하면 지는 곳이 있는지 체크. (예: 플레이어 돌 4개 - 방어가 있는 경우,)
        return res;
    else if(CheckMove(OMOK_2ND, GUARD_STATE) == 1) // 바로 공격 당하면 지는 곳이 있는지 체크. (예: 플레이어 돌 4개 - 방어가 있는 경우,)
        return res;
    // } end 기본 세팅.


    if(Difficulty >= 3)
    {
        if(CheckMove(OMOK_3RD, GUARD_STATE) == 1) // 공격 당하면 질 가능성이 많은곳이 있는지 체크. (공백 포함)
            return res;
        else if(CheckMove(OMOK_4TH, GUARD_STATE) == 1) // 공격 당하면 질 가능성이 많은곳이 있는지 체크. (공백 포함)
            return res;
    }

    if(Difficulty >= 4)
    {
        if(CheckMove(OMOK_3RD, ATTACK_STATE) == 1) // 공격 당하면 이길 가능성이 많은곳이 있는지 체크. (공백 포함)
            return res;
        else if(CheckMove(OMOK_4TH, ATTACK_STATE) == 1) // 공격 하면 이길 가능성이 많은곳이 있는지 체크. (공백 포함)
            return res;
    }

    if(Difficulty >= 2)
    {
        if(CheckMove(DANGER_ATTACK_1ST, ATTACK_STATE) == 1) // 컴퓨터 돌 3개 있는 경우 공격. (방어 없을 시, 공백 포함 - 중간에 공백이 있는 경우, 막아도 다른 공격의 길이 생겨 좋다.)
            return res;
        else if(CheckMove(DANGER_ATTACK_2ND, ATTACK_STATE) == 1) // 컴퓨터 돌 3개 있는 경우 공격. (방어 없을 시,)
            return res;
        if(CheckMove(DANGER_ATTACK_3RD, ATTACK_STATE) == 1) // 컴퓨터 돌 3개 있는 경우 공격. (방어 없을 시, 공백 포함 - 중간에 공백이 있는 경우, 막아도 다른 공격의 길이 생겨 좋다.)
            return res;
        if(CheckMove(DANGER_ATTACK_4TH, ATTACK_STATE) == 1) // 컴퓨터 돌 3개 있는 경우 공격. (방어 있을 시,)
            return res;
        else if(CheckMove(ATTACK_1ST, ATTACK_STATE) == 1) // // 컴퓨터 돌 2개 이상 있는 경우 공격. (방어 없을 시,)
            return res;
        if(CheckMove(ATTACK_2ND, ATTACK_STATE) == 1) // 컴퓨터 돌 2개 이상 있는 경우 공격. (방어 있을 시,)
            return res;
    }

    if(Difficulty >= 1)
    {
        if(CheckMove(DANGER_ATTACK_2ND, GUARD_STATE) == 1) // 컴퓨터 돌 3개 있는 경우 방어. (방어 없을 시,)
            return res;
        if(CheckMove(DANGER_ATTACK_4TH, GUARD_STATE) == 1) // 플레이어 돌 3개 이상 있는 경우 방어. (방어 있을 시,)
            return res;
    }

    // begin 기본 세팅 {
    if(CheckMove(PREATTACK_1ST, ATTACK_STATE) == 1) // 아무데나 둘 곳이 있는지 체크.-_-;
        return res;
    else if(CheckMove(PREATTACK_2ND, ATTACK_STATE) == 1) // 아무데나 둘 곳이 있는지 체크.-_-;
        return res;
    // } end 기본 세팅.

    return res;
} // end AIResult AI::Run().

/*** find to move ***/
bool AI::CheckMove(int AlertLevel, int State)
{
    int i, j, result;

    Dol co[ARRAY_CNT];
    Dol NoRepeatCo[ARRAY_CNT]; // 최종 선별된 좌표.
    int NoRepeatCoCnt[ARRAY_CNT]; // 반복 횟수 카운트.

    int DangerCnt = 0; // 공격 당할 위험이 있는 곳의 갯수 카운트.
    int CoCnt = 0; // 최종 선별된 좌표 카운트.
    int RepeatCoCnt = 0; // 반복되는 좌표 카운트.

    bool bSpaceChk;

    switch(AlertLevel)
    {
        case OMOK_3RD:
        case OMOK_4TH:
        case DANGER_ATTACK_1ST:
        case DANGER_ATTACK_3RD:
            bSpaceChk = true;
        default:
            bSpaceChk = false;
    }

    for(i=0; i<ARRAY_CNT; i++)
    {
        co[i].x = -1;
        co[i].y = -1;

        NoRepeatCo[i].x = -1;
        NoRepeatCo[i].y = -1;

        NoRepeatCoCnt[i] = 0;
    }

    for(i = IH; i<HEIGHT; i++)
    {
        for(j = IW; j<WIDTH; j++)
        {
            if(State == GUARD_STATE)
            {
                if(RowCheck(j, i, PlayerTurn, EnemyTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(RowCheck(j, i, PlayerTurn, EnemyTurn, bSpaceChk) == AlertLevel).

                if(ColCheck(j, i, PlayerTurn, EnemyTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(ColCheck(j, i, PlayerTurn, EnemyTurn, bSpaceChk) == AlertLevel).

                if(UpperDiagCheck(j, i, PlayerTurn, EnemyTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(UpperDiagCheck(j, i, PlayerTurn, EnemyTurn, bSpaceChk) == AlertLevel).

                if(LowerDiagCheck(j, i, PlayerTurn, EnemyTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(LowerDiagCheck(j, i, PlayerTurn, EnemyTurn, bSpaceChk) == AlertLevel).
            } // if(State == GUARD_STATE)
            else if(State == ATTACK_STATE)
            {
                if(RowCheck(j, i, EnemyTurn, PlayerTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(RowCheck(j, i, EnemyTurn, PlayerTurn, bSpaceChk) == AlertLevel).

                if(ColCheck(j, i, EnemyTurn, PlayerTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(ColCheck(j, i, EnemyTurn, PlayerTurn, bSpaceChk) == AlertLevel).

                if(UpperDiagCheck(j, i, EnemyTurn, PlayerTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(UpperDiagCheck(j, i, EnemyTurn, PlayerTurn, bSpaceChk) == AlertLevel).

                if(LowerDiagCheck(j, i, EnemyTurn, PlayerTurn, false, false, bSpaceChk) == AlertLevel)
                {
                    if(board[i][j] == NODRAW)
                    {
                        if(DangerCnt != ARRAY_CNT)
                        {
                            co[DangerCnt].x = j;
                            co[DangerCnt].y = i;

                            DangerCnt++;
                        }
                    }
                } // if(LowerDiagCheck(j, i, EnemyTurn, PlayerTurn, bSpaceChk) == AlertLevel).
            } // if(State == GUARD_STATE)
        } // for(j=0; j<WIDTH; j++).
    } // for(i = 0; i<HEIGHT; i++).


    if(DangerCnt == 0) // 공격 당할 위험이 있는곳이 없다면,
        return false;
    else // 공격 당할 위험이 있는 곳이 있다면,
    {
        for(i = 0; i < DangerCnt; i++)
        {
            result = 0;

            if(CoCnt == 0)
            {
                NoRepeatCo[ CoCnt ].x = co[i].x;
                NoRepeatCo[ CoCnt ].y = co[i].y;

                CoCnt++;
            }
            else
            {
                result = 0;

                for(j = 0; j <= CoCnt; j++)
                {
                    // 중복되는 좌표라면,
                    if(NoRepeatCo[ j ].x == co[i].x && NoRepeatCo[ j ].y == co[i].y)
                    {
                        NoRepeatCoCnt[ j ]++;
                        RepeatCoCnt++;
                        result = 1;
                        break;
                    }

                    if(result == 0)
                        result = -1;
                }

                if(result == -1)
                {
                    NoRepeatCo[ CoCnt ].x = co[i].x;
                    NoRepeatCo[ CoCnt ].y = co[i].y;

                    CoCnt++;
                }
            }
        }
    } // else // 공격 당할 위험이 있는 곳이 있다면.

    // 반복 되는 좌표가 없다면, 렌덤으로 좌표를 결정하여 아무데나 방어한다.
    if(RepeatCoCnt == 0)
    {
        int RandIndex;
        RandIndex = rand() % CoCnt;

        if( board[ NoRepeatCo[ RandIndex ].y ][ NoRepeatCo[ RandIndex ].x ] == NODRAW)
        {
            res.dol.x = NoRepeatCo[ RandIndex ].x;
            res.dol.y = NoRepeatCo[ RandIndex ].y;
            res.result = State;

            return true;
        }
    } // if(RepeatCoCnt == 0).
    else // 반복되는 좌표가 있다면, 가장 많이 반복되는 곳(가장 위험한 곳)을 방어한다.
    {
        int BestRepeat = -1;

        for(i=0; i<CoCnt; i++)
        {
            if(BestRepeat == -1)
                BestRepeat = NoRepeatCoCnt[i];
            else
            {
                if(BestRepeat < NoRepeatCoCnt[i])
                    BestRepeat = NoRepeatCoCnt[i];
                else if(BestRepeat == NoRepeatCoCnt[i])
                {
                    if(board[ NoRepeatCo[ NoRepeatCoCnt[i] ].y ][ NoRepeatCo[ NoRepeatCoCnt[i] ].x ] == NODRAW)
                        if( rand() % 2)
                            BestRepeat = NoRepeatCoCnt[i];
                }
            }
        }

        if(board[ NoRepeatCo[ BestRepeat ].y ][ NoRepeatCo[ BestRepeat ].x ] == NODRAW)
        {
            res.dol.x = NoRepeatCo[ BestRepeat ].x;
            res.dol.y = NoRepeatCo[ BestRepeat ].y;
            res.result = State;

            return true;
        }
    }

    return false;
} // end int AI::CheckMove(int AlertLevel, int State).


/*** check row ***/
int AI::RowCheck(int x, int y, bool player1, bool player2, bool iErr, bool jErr, bool bSpaceChk)
{
    int i = 1, j = 1;   // i는 왼쪽, j는 오른쪽.
    int Cnt  = 1;       // 바둑돌 갯수.
    int GuardCnt = 0;   // 상대편돌 갯수.
    int SpaceCnt = 0;   // 공백 카운트.

    // 오목 체크.
    while(true)
    {
        if(x-i >= IW || iErr == true)
        {
            if(!iErr)
            {
                if(board[y][x-i] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(x-i != IW) /******/
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y][x-i] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }

                    iErr = true;
                }
                else // 공백이라면,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(x-i != IW) /******/
                                i++;
                            else
                                iErr = true;
                        }
                    }
                }
            }
        }
        else if(x == IW)
        {
            iErr = true;
            continue;
        }

        if(x+j < WIDTH || jErr == true)
        {
            if(!jErr)
            {
                if(board[y][x+j] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(x+j != WIDTH - 1)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y][x+j] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }

                    jErr = true;
                }
                else // 공백이라면,
                {
                    if(jErr == false)
                        jErr = true; // j(오른쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            jErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(x+j != WIDTH - 1)
                                j++;
                            else
                                jErr = true;
                        }
                    }
                }
            }
        }
        else if(x == WIDTH-1)
        {
            jErr = true;
            continue;
        }

        if(iErr && jErr) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // 돌이 6개 이상이라면, (방어가 없을때)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // 돌이 6개 이상이라면, (방어가 있을때)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // 돌이 5개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_3RD;
                else // 공백이 없다면,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // 돌이 5개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // 돌이 4개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                {
                    //Sleep(3000);
                    return DANGER_ATTACK_1ST;
                }
                else // 공백이 없다면,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // 돌이 4개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return DANGER_ATTACK_3RD;
                else // 공백이 없다면,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // 돌이 3개 라면, (방어가 없을때)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // 돌이 3개 라면, (방어가 있을때)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // 돌이 2개 라면, (방어가 없을때)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // 돌이 2개 라면, (방어가 있을때)
                return PREATTACK_2ND;
            }

            break; // 루프를 벗어남.
        }
    }

    return 0;
} // end int AI::RowCheck().

/*** check column ***/
int AI::ColCheck(int x, int y, bool player1, bool player2, bool iErr, bool jErr, bool bSpaceChk)
{
    int i = 1, j = 1;
    int Cnt  = 1, GuardCnt = 0;
    int SpaceCnt = 0; // 공백 카운트.

    // 오목 체크.
    while(true)
    {
        if(y-i >= IH || iErr == true)
        {
            if(!iErr)
            {
                if(board[y-i][x] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(y-i != IH)
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y-i][x] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }
                }
                else // 공백이라면,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(y-i != IH)
                                i++;
                            else
                                iErr = true;
                        }
                    }
                }
            }
        }
        else if(y == IH)
        {
            iErr = true;
            continue;
        }

        if(y+j < HEIGHT || jErr == true)
        {
            if(!jErr)
            {
                if(board[y+j][x] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(y+j != HEIGHT - 1)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y+j][x] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }

                    jErr = true;
                }
                else // 공백이라면,
                {
                    if(bSpaceChk == false)
                        jErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            jErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(y+j != HEIGHT - 1)
                                j++;
                            else
                                jErr = true;
                        }
                    }
                }
            }
        }
        else if(y == HEIGHT-1)
        {
            jErr = true;
            continue;
        }

        if(iErr && jErr) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // 돌이 6개 이상이라면, (방어가 없을때)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // 돌이 6개 이상이라면, (방어가 있을때)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // 돌이 5개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_3RD;
                else // 공백이 없다면,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // 돌이 5개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // 돌이 4개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return DANGER_ATTACK_1ST;
                else // 공백이 없다면,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // 돌이 4개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return DANGER_ATTACK_3RD;
                else // 공백이 없다면,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // 돌이 3개 라면, (방어가 없을때)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // 돌이 3개 라면, (방어가 있을때)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // 돌이 2개 라면, (방어가 없을때)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // 돌이 2개 라면, (방어가 있을때)
                return PREATTACK_2ND;
            }

            break; // 루프를 벗어남.
        }
    } // while(true).

    return 0;
} // end int AI::SeroCheck().

/*** / ***/
int AI::UpperDiagCheck(int x, int y, bool player1, bool player2, bool iErr, bool jErr, bool bSpaceChk) // 대각선 줄(/)의 오목 체크.
{
    int i = 1, j = 1;
    int Cnt  = 1, GuardCnt = 0;
    int SpaceCnt = 0; // 공백 카운트.

    // 오목 체크.
    while(true)
    {
        if(x-i >= IW && y+i < HEIGHT || iErr == true)
        {
            if(!iErr)
            {
                if(board[y+i][x-i] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(x-i != IW && y+i != HEIGHT - 1)
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y+i][x-i] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }

                    iErr = true;
                }
                else // 공백이라면,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(x-i != IW && y+i != HEIGHT - 1)
                                i++;
                            else
                                iErr = true;
                        }
                    }
                }
            }
        }
        else if(x == IW || y == HEIGHT-1)
        {
            iErr = true;
            continue;
        }

        if(x+j < WIDTH && y-j >= IH || jErr == true)
        {
            if(!jErr)
            {
                if(board[y-j][x+j] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(x+j != WIDTH - 1 && y-j != IH)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y-j][x+j] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }

                    jErr = true;
                }
                else // 공백이라면,
                {
                    if(!bSpaceChk)
                        jErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            jErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(x+j != WIDTH - 1 && y-j != IH)
                                j++;
                            else
                                jErr = true;
                        }
                    }
                }
            }
        }
        else if(x == WIDTH-1 || y == IH)
        {
            jErr = true;
            continue;
        }

        if(iErr && jErr) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // 돌이 6개 이상이라면, (방어가 없을때)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // 돌이 6개 이상이라면, (방어가 있을때)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // 돌이 5개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_3RD;
                else // 공백이 없다면,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // 돌이 5개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // 돌이 4개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return DANGER_ATTACK_1ST;
                else // 공백이 없다면,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // 돌이 4개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return DANGER_ATTACK_3RD;
                else // 공백이 없다면,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // 돌이 3개 라면, (방어가 없을때)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // 돌이 3개 라면, (방어가 있을때)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // 돌이 2개 라면, (방어가 없을때)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // 돌이 2개 라면, (방어가 있을때)
                return PREATTACK_2ND;
            }
            break; // 루프를 벗어남.
        }
    } // while(true).

    return 0;
} // end int AI::UpperDiagCheck().

/*** \ ***/
int AI::LowerDiagCheck(int x, int y, bool player1, bool player2, bool iErr, bool jErr, bool bSpaceChk) // 대각선 줄(\)의 오목 체크.
{
    int i = 1, j = 1;
    int Cnt  = 1, GuardCnt = 0;
    int SpaceCnt = 0; // 공백 카운트.

    // 오목 체크.
    while(true)
    {
        if(x-i >= IW && y-i >= IH || iErr == true)
        {
            if(!iErr)
            {
                if(board[y-i][x-i] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(x-i != IW && y-i != IH)
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y-i][x-i] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }

                    iErr = true;
                }
                else // 공백이라면,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            iErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(x-i != IW && y-i != IH)
                                i++;
                            else
                                iErr = true;
                        }
                    }
                }
            }
        }
        else if(x == IW || y == IH)
        {
            iErr = true;
            continue;
        }

        if(x+j < WIDTH && y+j < HEIGHT || jErr == true)
        {
            if(!jErr)
            {
                if(board[y+j][x+j] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // 공백 갯수 초기화.

                    if(x+j != WIDTH - 1 && y+j != HEIGHT - 1)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y+j][x+j] == player2)
                {
                    // 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
                    if(++GuardCnt >= 2)
                    {
                        if(Cnt < 5)
                            return 0;
                        else if( Cnt == 5)
                            return OMOK_2ND;
                        else if( Cnt > 5)
                            return UPPER_OMOK_2ND;
                    }

                    jErr = true;
                }
                else // 공백이라면,
                {
                    if(!bSpaceChk)
                        jErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                    else // 공백을 체크하라고 지시했다면,
                    {
                        if(++SpaceCnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
                            jErr = true; // i(왼쪽) 검사는 끝 났음을 알림.
                        else
                        {
                            // 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
                            if(x+j != WIDTH - 1 && y+j != HEIGHT - 1)
                                j++;
                            else
                                jErr = true;
                        }
                    }
                }
            }
        }
        else if(x == WIDTH-1 || y == HEIGHT-1)
        {
            jErr = true;
            continue;
        }

        if(iErr && jErr) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // 돌이 6개 이상이라면, (방어가 없을때)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // 돌이 6개 이상이라면, (방어가 있을때)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // 돌이 5개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_3RD;
                else // 공백이 없다면,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // 돌이 5개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // 돌이 4개 라면, (방어가 없을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return DANGER_ATTACK_1ST;
                else // 공백이 없다면,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // 돌이 4개 라면, (방어가 있을때)
                if(bSpaceChk && SpaceCnt > 0) // 중간에 공백이 있다면,
                    return DANGER_ATTACK_3RD;
                else // 공백이 없다면,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // 돌이 3개 라면, (방어가 없을때)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // 돌이 3개 라면, (방어가 있을때)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // 돌이 2개 라면, (방어가 없을때)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // 돌이 2개 라면, (방어가 있을때)
                return PREATTACK_2ND;
            }
            break; // 루프를 벗어남.
        }
    } // while(true).

    return 0;
} // end int AI::LowerDiagCheck().
