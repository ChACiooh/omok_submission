#include "../header/AI.h"

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

    // �ٵ� �ǿ� �ٵϵ��� �ϳ��� ��������, ������ ����� ���� �����Ѵ�.
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


    // ���⼭ üũ �ϴ� ������ �����ϰų� �����ϴ� �Ϳ� ���� ���̵��� �޶�����.
    // üũ�ÿ��� �߰��� ���鵵 �����Ͽ� ����� �Ѵ�.

    // begin �⺻ ����. {
    if(CheckMove(UPPER_OMOK_1ST, ATTACK_STATE) == 1) // �ٷ� ���� �ϸ� �̱�� ���� �ִ��� üũ. (��: ��ǻ�� �� 5�� �̻�)
    {
        res.result = UPPER_OMOK_1ST;
        return res;
    }
    else if(CheckMove(UPPER_OMOK_2ND, ATTACK_STATE) == 1) // �ٷ� ���� �ϸ� �̱�� ���� �ִ��� üũ. (��: ��ǻ�� �� 5�� �̻�)
    {
        res.result = UPPER_OMOK_2ND;
        return res;
    }
    else if(CheckMove(OMOK_1ST, ATTACK_STATE) == 1) // �ٷ� ���� �ϸ� �̱�� ���� �ִ��� üũ. (��: ��ǻ�� �� 4��)
    {
        res.result = OMOK_1ST;
        return res;
    }
    else if(CheckMove(OMOK_2ND, ATTACK_STATE) == 1) // �ٷ� ���� �ϸ� �̱�� ���� �ִ��� üũ. (��: ��ǻ�� �� 4��)
    {
        res.result = OMOK_2ND;
        return res;
    }
    else if(CheckMove(UPPER_OMOK_1ST, GUARD_STATE) == 1) // �ٷ� ���� ���ϸ� ���� ���� �ִ��� üũ. (��: �÷��̾� �� 5�� �̻� - �� ���� ���,)
        return res;
    else if(CheckMove(UPPER_OMOK_2ND, GUARD_STATE) == 1) // �ٷ� ���� ���ϸ� ���� ���� �ִ��� üũ. (��: �÷��̾� �� 5�� �̻� - �� �ִ� ���,)
        return res;
    else if(CheckMove(OMOK_1ST, GUARD_STATE) == 1) // �ٷ� ���� ���ϸ� ���� ���� �ִ��� üũ. (��: �÷��̾� �� 4�� - �� ���� ���,)
        return res;
    else if(CheckMove(OMOK_2ND, GUARD_STATE) == 1) // �ٷ� ���� ���ϸ� ���� ���� �ִ��� üũ. (��: �÷��̾� �� 4�� - �� �ִ� ���,)
        return res;
    // } end �⺻ ����.


    if(Difficulty >= 3)
    {
        if(CheckMove(OMOK_3RD, GUARD_STATE) == 1) // ���� ���ϸ� �� ���ɼ��� �������� �ִ��� üũ. (���� ����)
            return res;
        else if(CheckMove(OMOK_4TH, GUARD_STATE) == 1) // ���� ���ϸ� �� ���ɼ��� �������� �ִ��� üũ. (���� ����)
            return res;
    }

    if(Difficulty >= 4)
    {
        if(CheckMove(OMOK_3RD, ATTACK_STATE) == 1) // ���� ���ϸ� �̱� ���ɼ��� �������� �ִ��� üũ. (���� ����)
            return res;
        else if(CheckMove(OMOK_4TH, ATTACK_STATE) == 1) // ���� �ϸ� �̱� ���ɼ��� �������� �ִ��� üũ. (���� ����)
            return res;
    }

    if(Difficulty >= 2)
    {
        if(CheckMove(DANGER_ATTACK_1ST, ATTACK_STATE) == 1) // ��ǻ�� �� 3�� �ִ� ��� ����. (��� ���� ��, ���� ���� - �߰��� ������ �ִ� ���, ���Ƶ� �ٸ� ������ ���� ���� ����.)
            return res;
        else if(CheckMove(DANGER_ATTACK_2ND, ATTACK_STATE) == 1) // ��ǻ�� �� 3�� �ִ� ��� ����. (��� ���� ��,)
            return res;
        if(CheckMove(DANGER_ATTACK_3RD, ATTACK_STATE) == 1) // ��ǻ�� �� 3�� �ִ� ��� ����. (��� ���� ��, ���� ���� - �߰��� ������ �ִ� ���, ���Ƶ� �ٸ� ������ ���� ���� ����.)
            return res;
        if(CheckMove(DANGER_ATTACK_4TH, ATTACK_STATE) == 1) // ��ǻ�� �� 3�� �ִ� ��� ����. (��� ���� ��,)
            return res;
        else if(CheckMove(ATTACK_1ST, ATTACK_STATE) == 1) // // ��ǻ�� �� 2�� �̻� �ִ� ��� ����. (��� ���� ��,)
            return res;
        if(CheckMove(ATTACK_2ND, ATTACK_STATE) == 1) // ��ǻ�� �� 2�� �̻� �ִ� ��� ����. (��� ���� ��,)
            return res;
    }

    if(Difficulty >= 1)
    {
        if(CheckMove(DANGER_ATTACK_2ND, GUARD_STATE) == 1) // ��ǻ�� �� 3�� �ִ� ��� ���. (��� ���� ��,)
            return res;
        if(CheckMove(DANGER_ATTACK_4TH, GUARD_STATE) == 1) // �÷��̾� �� 3�� �̻� �ִ� ��� ���. (��� ���� ��,)
            return res;
    }

    // begin �⺻ ���� {
    if(CheckMove(PREATTACK_1ST, ATTACK_STATE) == 1) // �ƹ����� �� ���� �ִ��� üũ.-_-;
        return res;
    else if(CheckMove(PREATTACK_2ND, ATTACK_STATE) == 1) // �ƹ����� �� ���� �ִ��� üũ.-_-;
        return res;
    // } end �⺻ ����.

    return res;
} // end AIResult AI::Run().

/*** find to move ***/
bool AI::CheckMove(int AlertLevel, int State)
{
    int i, j, result;

    Dol co[ARRAY_CNT];
    Dol NoRepeatCo[ARRAY_CNT]; // ���� ������ ��ǥ.
    int NoRepeatCoCnt[ARRAY_CNT]; // �ݺ� Ƚ�� ī��Ʈ.

    int DangerCnt = 0; // ���� ���� ������ �ִ� ���� ���� ī��Ʈ.
    int CoCnt = 0; // ���� ������ ��ǥ ī��Ʈ.
    int RepeatCoCnt = 0; // �ݺ��Ǵ� ��ǥ ī��Ʈ.

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


    if(DangerCnt == 0) // ���� ���� ������ �ִ°��� ���ٸ�,
        return false;
    else // ���� ���� ������ �ִ� ���� �ִٸ�,
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
                    // �ߺ��Ǵ� ��ǥ���,
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
    } // else // ���� ���� ������ �ִ� ���� �ִٸ�.

    // �ݺ� �Ǵ� ��ǥ�� ���ٸ�, �������� ��ǥ�� �����Ͽ� �ƹ����� ����Ѵ�.
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
    else // �ݺ��Ǵ� ��ǥ�� �ִٸ�, ���� ���� �ݺ��Ǵ� ��(���� ������ ��)�� ����Ѵ�.
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
    int i = 1, j = 1;   // i�� ����, j�� ������.
    int Cnt  = 1;       // �ٵϵ� ����.
    int GuardCnt = 0;   // ������� ����.
    int SpaceCnt = 0;   // ���� ī��Ʈ.

    // ���� üũ.
    while(true)
    {
        if(x-i >= IW || iErr == true)
        {
            if(!iErr)
            {
                if(board[y][x-i] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(x-i != IW) /******/
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y][x-i] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(����) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            iErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(x+j != WIDTH - 1)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y][x+j] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(jErr == false)
                        jErr = true; // j(������) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            jErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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

        if(iErr && jErr) // ���� �������� �˻簡 ��� �����ٸ�,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_3RD;
                else // ������ ���ٸ�,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                {
                    //Sleep(3000);
                    return DANGER_ATTACK_1ST;
                }
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return DANGER_ATTACK_3RD;
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_2ND;
            }

            break; // ������ ���.
        }
    }

    return 0;
} // end int AI::RowCheck().

/*** check column ***/
int AI::ColCheck(int x, int y, bool player1, bool player2, bool iErr, bool jErr, bool bSpaceChk)
{
    int i = 1, j = 1;
    int Cnt  = 1, GuardCnt = 0;
    int SpaceCnt = 0; // ���� ī��Ʈ.

    // ���� üũ.
    while(true)
    {
        if(y-i >= IH || iErr == true)
        {
            if(!iErr)
            {
                if(board[y-i][x] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(y-i != IH)
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y-i][x] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(����) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            iErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(y+j != HEIGHT - 1)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y+j][x] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(bSpaceChk == false)
                        jErr = true; // i(����) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            jErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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

        if(iErr && jErr) // ���� �������� �˻簡 ��� �����ٸ�,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_3RD;
                else // ������ ���ٸ�,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return DANGER_ATTACK_1ST;
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return DANGER_ATTACK_3RD;
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_2ND;
            }

            break; // ������ ���.
        }
    } // while(true).

    return 0;
} // end int AI::SeroCheck().

/*** / ***/
int AI::UpperDiagCheck(int x, int y, bool player1, bool player2, bool iErr, bool jErr, bool bSpaceChk) // �밢�� ��(/)�� ���� üũ.
{
    int i = 1, j = 1;
    int Cnt  = 1, GuardCnt = 0;
    int SpaceCnt = 0; // ���� ī��Ʈ.

    // ���� üũ.
    while(true)
    {
        if(x-i >= IW && y+i < HEIGHT || iErr == true)
        {
            if(!iErr)
            {
                if(board[y+i][x-i] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(x-i != IW && y+i != HEIGHT - 1)
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y+i][x-i] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(����) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            iErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(x+j != WIDTH - 1 && y-j != IH)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y-j][x+j] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(!bSpaceChk)
                        jErr = true; // i(����) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            jErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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

        if(iErr && jErr) // ���� �������� �˻簡 ��� �����ٸ�,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_3RD;
                else // ������ ���ٸ�,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return DANGER_ATTACK_1ST;
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return DANGER_ATTACK_3RD;
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_2ND;
            }
            break; // ������ ���.
        }
    } // while(true).

    return 0;
} // end int AI::UpperDiagCheck().

/*** \ ***/
int AI::LowerDiagCheck(int x, int y, bool player1, bool player2, bool iErr, bool jErr, bool bSpaceChk) // �밢�� ��(\)�� ���� üũ.
{
    int i = 1, j = 1;
    int Cnt  = 1, GuardCnt = 0;
    int SpaceCnt = 0; // ���� ī��Ʈ.

    // ���� üũ.
    while(true)
    {
        if(x-i >= IW && y-i >= IH || iErr == true)
        {
            if(!iErr)
            {
                if(board[y-i][x-i] == player1)
                {
                    Cnt++;
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(x-i != IW && y-i != IH)
                        i++;
                    else
                        iErr = true;
                }
                else if(board[y-i][x-i] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(bSpaceChk == false)
                        iErr = true; // i(����) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            iErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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
                    SpaceCnt = 0; // ���� ���� �ʱ�ȭ.

                    if(x+j != WIDTH - 1 && y+j != HEIGHT - 1)
                        j++;
                    else
                        jErr = true;
                }
                else if(board[y+j][x+j] == player2)
                {
                    // ���ʴ� ���� �����ٸ�, ���� ���ɼ��� �����Ƿ�, �Լ��� �����.
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
                else // �����̶��,
                {
                    if(!bSpaceChk)
                        jErr = true; // i(����) �˻�� �� ������ �˸�.
                    else // ������ üũ�϶�� �����ߴٸ�,
                    {
                        if(++SpaceCnt>1) // ������ ������ 2�� �̻� �������� �ִٸ�, �� �̻� üũ ����.
                            jErr = true; // i(����) �˻�� �� ������ �˸�.
                        else
                        {
                            // ���� ������ ����, �ٵϵ��� ������ ī��Ʈ ���� �ʴ´�.
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

        if(iErr && jErr) // ���� �������� �˻簡 ��� �����ٸ�,
        {
            if(Cnt >= 6 && GuardCnt == 0)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_1ST;
            }
            else if(Cnt >= 6 && GuardCnt == 1)
            {
                // ���� 6�� �̻��̶��, (�� ������)
                return UPPER_OMOK_2ND;
            }
            else if(Cnt == 5 && GuardCnt == 0)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_3RD;
                else // ������ ���ٸ�,
                    return OMOK_1ST;
            }
            else if(Cnt == 5 && GuardCnt == 1)
            {
                // ���� 5�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return OMOK_4TH;
                else
                    return OMOK_2ND;
            }
            else if(Cnt == 4 && GuardCnt == 0)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return DANGER_ATTACK_1ST;
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_2ND;
            }
            else if(Cnt-GuardCnt == 4 && GuardCnt == 1)
            {
                // ���� 4�� ���, (�� ������)
                if(bSpaceChk && SpaceCnt > 0) // �߰��� ������ �ִٸ�,
                    return DANGER_ATTACK_3RD;
                else // ������ ���ٸ�,
                    return DANGER_ATTACK_4TH;
            }
            else if(Cnt == 3 && GuardCnt == 0)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 3 && GuardCnt == 1)
            {
                // ���� 3�� ���, (�� ������)
                return ATTACK_2ND;
            }
            else if(Cnt == 2 && GuardCnt == 0)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_1ST;
            }
            else if(Cnt-GuardCnt == 2 && GuardCnt == 1)
            {
                // ���� 2�� ���, (�� ������)
                return PREATTACK_2ND;
            }
            break; // ������ ���.
        }
    } // while(true).

    return 0;
} // end int AI::LowerDiagCheck().
