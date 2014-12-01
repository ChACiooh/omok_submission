#include "AI.h"

/*** AI ***/
AI::AI()
{
	for (int i = 0; i < WIDTH * HEIGHT; i++)
		board[i%WIDTH][i/HEIGHT] = BLANK;
}
Point AI::Run(Dol my_dol, int Difficulty)
{
	Point pos;
	pos.x = -1;
	pos.y = -1;

	bool is_checked = false;

    /*** 차례대로 방어되어 있고, 없는 순서대로 ***/
	if (CheckMove(UPPER_OMOK_1ST, ATTACK_STATE, pos, my_dol) == 1) // 6목 이상이 나오는지 체크(방어되어 있음)
	{
		is_checked = true;
	}
	else if (CheckMove(UPPER_OMOK_2ND, ATTACK_STATE, pos, my_dol) == 1) // 6목 이상이 나오는지 체크(방어x)
	{
		is_checked = true;
	}
	else if (CheckMove(OMOK_1ST, ATTACK_STATE, pos, my_dol) == 1) // 오목인지 체크
	{
		is_checked = true;
	}
	else if (CheckMove(OMOK_2ND, ATTACK_STATE, pos, my_dol) == 1) // 오목인지 체크
	{
		is_checked = true;
	}
	else if (CheckMove(UPPER_OMOK_1ST, GUARD_STATE, pos, my_dol) == 1) // 상대가 6목 이상이 있는지 체크
	{
		is_checked = true;
	}
	else if (CheckMove(UPPER_OMOK_2ND, GUARD_STATE, pos, my_dol) == 1) // 상대가 6목 이상이 있는지 체크
	{
		is_checked = true;
	}
	else if (CheckMove(OMOK_1ST, GUARD_STATE, pos, my_dol) == 1) // 여기다 상대가 두면 오목인지 체크
	{
		is_checked = true;
	}
	else if (CheckMove(OMOK_2ND, GUARD_STATE, pos, my_dol) == 1) // 여기다 상대가 두면 오목인지 체크
	{
		is_checked = true;
	}
	else if (Difficulty >= 3)
	{
		if (CheckMove(OMOK_3RD, GUARD_STATE, pos, my_dol) == 1) // 상대가 공백에 두면 오목이 있는지 체크.
		{
			is_checked = true;
		}
		else if (CheckMove(OMOK_4TH, GUARD_STATE, pos, my_dol) == 1) // 상대가 공백에 두면 오목이 있는지 체크.
		{
			is_checked = true;
		}
		else if (Difficulty >= 4)
		{
			if (CheckMove(OMOK_3RD, ATTACK_STATE, pos, my_dol) == 1) // 내가 공백에 두면 오목이 있는지 체크
			{
				is_checked = true;
			}
			else if (CheckMove(OMOK_4TH, ATTACK_STATE, pos, my_dol) == 1) // 내가 공백에 두면 오목이 있는지 체크
			{
				is_checked = true;
			}
		}
	}
	if (Difficulty >= 2 && !is_checked)
	{
		if (CheckMove(DANGER_ATTACK_1ST, ATTACK_STATE, pos, my_dol) == 1) // 돌 3개 있는 경우 공격. (방어 없을 시, 공백 포함 - 중간에 공백이 있는 경우, 막아도 다른 공격의 길이 생겨 좋다.)
		{
			is_checked = true;
		}
		else if (CheckMove(DANGER_ATTACK_2ND, ATTACK_STATE, pos, my_dol) == 1) // 돌 3개 있는 경우 공격. (방어 없을 시,)
		{
			is_checked = true;
		}
		else if (CheckMove(DANGER_ATTACK_3RD, ATTACK_STATE, pos, my_dol) == 1) // 돌 3개 있는 경우 공격. (방어 없을 시, 공백 포함 - 중간에 공백이 있는 경우, 막아도 다른 공격의 길이 생겨 좋다.)
		{
			is_checked = true;
		}
		else if (CheckMove(DANGER_ATTACK_4TH, ATTACK_STATE, pos, my_dol) == 1) // 돌 3개 있는 경우 공격. (방어 있을 시,)
		{
			is_checked = true;
		}
		else if (CheckMove(ATTACK_1ST, ATTACK_STATE, pos, my_dol) == 1) // 돌 2개 이상 있는 경우 공격. (방어 없을 시,)
		{
			is_checked = true;
		}
		else if (CheckMove(ATTACK_2ND, ATTACK_STATE, pos, my_dol) == 1) // 돌 2개 이상 있는 경우 공격. (방어 있을 시,)
		{
			is_checked = true;
		}
	}
	if (Difficulty >= 1 && !is_checked)
	{
		if (CheckMove(DANGER_ATTACK_2ND, GUARD_STATE, pos, my_dol) == 1) // 돌 3개 있는 경우 방어. (방어 없을 시,)
		{
			is_checked = true;
		}
		if (CheckMove(DANGER_ATTACK_4TH, GUARD_STATE, pos, my_dol) == 1) // 돌 3개 이상 있는 경우 방어. (방어 있을 시,)
		{
			is_checked = true;
		}
	}
	if (!is_checked &&CheckMove(PREATTACK_1ST, ATTACK_STATE, pos, my_dol) == 1) // 아무데나 둘 곳이 있는지 체크
	{
		is_checked = true;
	}
	else if (!is_checked && CheckMove(PREATTACK_2ND, ATTACK_STATE, pos, my_dol) == 1) // 재확인
	{

	}
	if(pos.x < 0 || pos.y < 0 || Get(pos.x, pos.y) != BLANK)
		pos = GetRandomPos();
	return pos;
} // end AIResult AI::Run().
/*** find to move ***/
bool AI::CheckMove(Priority priority, State state, Point &pos, Dol my_dol)
{
	int i, j, result;

	Point co[WIDTH * HEIGHT];
	Point no_repeat_co[WIDTH * HEIGHT]; // 최종 선별된 좌표.
	int no_repeat_co_cnt[WIDTH * HEIGHT]; // 반복 횟수 카운트.

	int dange_cnt = 0; // 공격 당할 위험이 있는 곳의 갯수 카운트.
	int co_cnt = 0; // 최종 선별된 좌표 카운트.
	int repeat_co_cnt = 0; // 반복되는 좌표 카운트.

	bool is_space_chk;

	switch (priority)
	{
	case OMOK_3RD:
	case OMOK_4TH:
	case DANGER_ATTACK_1ST:
	case DANGER_ATTACK_3RD:
		is_space_chk = true;
	default:
		is_space_chk = false;
	}

	for (i = 0; i<WIDTH * HEIGHT; i++)
	{
		co[i].x = -1;
		co[i].y = -1;

		no_repeat_co[i].x = -1;
		no_repeat_co[i].y = -1;

		no_repeat_co_cnt[i] = 0;
	}

	for (i = IH; i<HEIGHT; i++)
	{
		for (j = IW; j<WIDTH; j++)
		{
			if (state == GUARD_STATE)
			{
				if (RowCheck(j, i,my_dol, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				} // if(RowCheck(j, i, PlayerTurn, EnemyTurn, is_space_chk) == AlertLevel).

				if (ColCheck(j, i, my_dol, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				} // if(ColCheck(j, i, PlayerTurn, EnemyTurn, is_space_chk) == AlertLevel).

				if (UpperDiagCheck(j, i, my_dol, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				} // if(UpperDiagCheck(j, i, PlayerTurn, EnemyTurn, is_space_chk) == AlertLevel).

				if (LowerDiagCheck(j, i, my_dol, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				} // if(LowerDiagCheck(j, i, PlayerTurn, EnemyTurn, is_space_chk) == AlertLevel).
			} // if(State == GUARD_STATE)
			else if (state == ATTACK_STATE)
			{
				if (RowCheck(j, i, my_dol == WHITE ? BLACK : WHITE, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				} // if(RowCheck(j, i, EnemyTurn, PlayerTurn, is_space_chk) == AlertLevel).

				if (ColCheck(j, i, my_dol == WHITE ? BLACK : WHITE, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				} // if(ColCheck(j, i, EnemyTurn, PlayerTurn, is_space_chk) == AlertLevel).

				if (UpperDiagCheck(j, i, my_dol == WHITE ? BLACK : WHITE, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				} // if(UpperDiagCheck(j, i, EnemyTurn, PlayerTurn, is_space_chk) == AlertLevel).

				if (LowerDiagCheck(j, i, my_dol == WHITE ? BLACK : WHITE, is_space_chk) == priority)
				{
					if (board[i][j] == BLANK)
					{
						if (dange_cnt < WIDTH * HEIGHT)
						{
							co[dange_cnt].x = j;
							co[dange_cnt].y = i;

							dange_cnt++;
						}
					}
				}
			}
		}
	}

	if (dange_cnt == 0) // 공격 당할 위험이 있는곳이 없다면,
		return false;
	else // 공격 당할 위험이 있는 곳이 있다면,
	{
		for (i = 0; i < dange_cnt; i++)
		{
			result = 0;

			if (co_cnt == 0)
			{
				no_repeat_co[co_cnt].x = co[i].x;
				no_repeat_co[co_cnt].y = co[i].y;

				co_cnt++;
			}
			else
			{
				result = 0;

				for (j = 0; j <= co_cnt; j++)
				{
					// 중복되는 좌표라면,
					if (no_repeat_co[j].x == co[i].x && no_repeat_co[j].y == co[i].y)
					{
						no_repeat_co_cnt[j]++;
						repeat_co_cnt++;
						result = 1;
						break;
					}

					if (result == 0)
						result = -1;
				}

				if (result == -1)
				{
					no_repeat_co[co_cnt].x = co[i].x;
					no_repeat_co[co_cnt].y = co[i].y;

					co_cnt++;
				}
			}
		}
	}// 공격 당할 위험이 있는 곳이 있다면.

	// 반복 되는 좌표가 없다면, 렌덤으로 좌표를 결정하여 아무데나 방어한다.
	if (repeat_co_cnt == 0)
	{
		int rand_idx;
		rand_idx = rand() % co_cnt;

		if (board[no_repeat_co[rand_idx].y][no_repeat_co[rand_idx].x] == BLANK)
		{
			pos.x = no_repeat_co[rand_idx].x;
			pos.y = no_repeat_co[rand_idx].y;

			return true;
		}
	}
	else // 반복되는 좌표가 있다면, 가장 많이 반복되는 곳(가장 위험한 곳)을 방어한다.
	{
		int best_repeat = -1;

		for (i = 0; i<co_cnt; i++)
		{
			if (best_repeat == -1)
				best_repeat = no_repeat_co_cnt[i];
			else
			{
				if (best_repeat < no_repeat_co_cnt[i])
					best_repeat = no_repeat_co_cnt[i];
				else if (best_repeat == no_repeat_co_cnt[i])
				{
					if (board[no_repeat_co[no_repeat_co_cnt[i]].y][no_repeat_co[no_repeat_co_cnt[i]].x] == BLANK)
					if (rand() % 2)
						best_repeat = no_repeat_co_cnt[i];
				}
			}
		}

		if (board[no_repeat_co[best_repeat].y][no_repeat_co[best_repeat].x] == BLANK)
		{
			pos.x = no_repeat_co[best_repeat].x;
			pos.y = no_repeat_co[best_repeat].y;

			return true;
		}
	}

	return false;
} // end int AI::CheckMove(int AlertLevel, int State).

Point AI::GetRandomPos()
{
	Point pos;
	pos.x = 8;
	pos.y = 9;
	while (1)
	{
		int delta = 1;
		int limit = 1;

		for (int p = 0; p<limit; p++){
			pos.x += delta;
			if (Get(pos.x, pos.y) == BLANK)
				return pos;
		}
		for (int p = 0; p<limit; p++){
			pos.y += delta;
			if (Get(pos.x, pos.y) == BLANK)
				return pos;
		}

		delta = -delta;
		limit++;

		if (limit>19) break;
	}
	return pos;
}

Priority AI::GetPriority(int cnt, int guard_cnt, bool is_space_chk, int space_cnt)
{
	if (cnt >= 6 && guard_cnt == 0)
	{
		// 돌이 6개 이상이라면, (방어가 없을때)
		return UPPER_OMOK_1ST;
	}
	else if (cnt >= 6 && guard_cnt == 1)
	{
		// 돌이 6개 이상이라면, (방어가 있을때)
		return UPPER_OMOK_2ND;
	}
	else if (cnt == 5 && guard_cnt == 0)
	{
		// 돌이 5개 라면, (방어가 없을때)
		if (is_space_chk && space_cnt > 0) // 중간에 공백이 있다면,
			return OMOK_3RD;
		else // 공백이 없다면,
			return OMOK_1ST;
	}
	else if (cnt == 5 && guard_cnt == 1)
	{
		// 돌이 5개 라면, (방어가 있을때)
		if (is_space_chk && space_cnt > 0) // 중간에 공백이 있다면,
			return OMOK_4TH;
		else
			return OMOK_2ND;
	}
	else if (cnt == 4 && guard_cnt == 0)
	{
		// 돌이 4개 라면, (방어가 없을때)
		if (is_space_chk && space_cnt > 0) // 중간에 공백이 있다면,
			return DANGER_ATTACK_1ST;
		else // 공백이 없다면,
			return DANGER_ATTACK_2ND;
	}
	else if (cnt - guard_cnt == 4 && guard_cnt == 1)
	{
		// 돌이 4개 라면, (방어가 있을때)
		if (is_space_chk && space_cnt > 0) // 중간에 공백이 있다면,
			return DANGER_ATTACK_3RD;
		else // 공백이 없다면,
			return DANGER_ATTACK_4TH;
	}
	else if (cnt == 3 && guard_cnt == 0)
	{
		// 돌이 3개 라면, (방어가 없을때)
		return ATTACK_1ST;
	}
	else if (cnt - guard_cnt == 3 && guard_cnt == 1)
	{
		// 돌이 3개 라면, (방어가 있을때)
		return ATTACK_2ND;
	}
	else if (cnt == 2 && guard_cnt == 0)
	{
		// 돌이 2개 라면, (방어가 없을때)
		return PREATTACK_1ST;
	}
	else if (cnt - guard_cnt == 2 && guard_cnt == 1)
	{
		// 돌이 2개 라면, (방어가 있을때)
		return PREATTACK_2ND;
	}
	return ERROR;
}
/*** check row ***/
int AI::CheckMoveContent(int x, int y, int &i, int &cnt, int &space_cnt, bool &err, Dol my_dol, int &guard_cnt, bool is_space_chk,int compare_dest,int compare_src)
{
	if (!err)
	{
		if (board[y][x] == my_dol)
		{
			cnt++;
			space_cnt = 0; // 공백 갯수 초기화.

			if (compare_dest != compare_src) /******/
				i++;
			else
				err = true;
		}
		else if (board[y][x] == !my_dol)
		{
			// 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
			if (++guard_cnt >= 2)
			{
				if (cnt < 5)
					return 0;
				else if (cnt == 5)
					return OMOK_2ND;
				else if (cnt > 5)
					return UPPER_OMOK_2ND;
			}

			err = true;
		}
		else // 공백이라면,
		{
			if (is_space_chk == false)
				err = true; // i(왼쪽) 검사는 끝 났음을 알림.
			else // 공백을 체크하라고 지시했다면,
			{
				if (++space_cnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
					err = true; // i(왼쪽) 검사는 끝 났음을 알림.
				else
				{
					// 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
					if (compare_dest != compare_src) /******/
						i++;
					else
						err = true;
				}
			}
		}
	}
	return -1;
}
int AI::CheckMoveContent(int x, int y, int &i, int &cnt, int &space_cnt, bool &err, Dol my_dol, int &guard_cnt, bool is_space_chk, int compare_dest1, int compare_src1, int compare_dest2, int compare_src2)
{
	if (!err)
	{
		if (board[y][x] == my_dol)
		{
			cnt++;
			space_cnt = 0; // 공백 갯수 초기화.

			if (compare_dest1 != compare_src1 && compare_dest2 != compare_src2) /******/
				i++;
			else
				err = true;
		}
		else if (board[y][x] == !my_dol)
		{
			// 양쪽다 가로 막혔다면, 오목 가능성이 없으므로, 함수를 벗어난다.
			if (++guard_cnt >= 2)
			{
				if (cnt < 5)
					return 0;
				else if (cnt == 5)
					return OMOK_2ND;
				else if (cnt > 5)
					return UPPER_OMOK_2ND;
			}

			err = true;
		}
		else // 공백이라면,
		{
			if (is_space_chk == false)
				err = true; // i(왼쪽) 검사는 끝 났음을 알림.
			else // 공백을 체크하라고 지시했다면,
			{
				if (++space_cnt>1) // 공백의 갯수가 2개 이상 연속으로 있다면, 더 이상 체크 안함.
					err = true; // i(왼쪽) 검사는 끝 났음을 알림.
				else
				{
					// 공백 갯수만 셀뿐, 바둑돌의 갯수는 카운트 하지 않는다.
					if (compare_dest1 != compare_src1 && compare_dest2 != compare_src2) /******/
						i++;
					else
						err = true;
				}
			}
		}
	}
	return -1;
}
int AI::RowCheck(int x, int y, Dol my_dol, bool is_space_chk)
{
	int i = 1, j = 1;   // i는 왼쪽, j는 오른쪽.
	int cnt = 1;       // 바둑돌 갯수.
	int guard_cnt = 0;   // 상대편돌 갯수.
	int space_cnt = 0;   // 공백 카운트.
	bool i_err = false;
	bool j_err = false;

	// 오목 체크.
	while (true)
	{
		if (x - i >= IW || i_err == true)
		{
			int return_value = CheckMoveContent(x - i, y, i, cnt, space_cnt, i_err, my_dol, guard_cnt, is_space_chk,x-i,IW);
			if (return_value > -1)
				return return_value;
		}
		else if (x == IW)
		{
			i_err = true;
			continue;
		}

		if (x + j < WIDTH || j_err == true)
		{
			int return_value = CheckMoveContent(x + j, y, j, cnt, space_cnt, j_err, my_dol, guard_cnt, is_space_chk,x+j,WIDTH-1);
			if (return_value > -1)
				return return_value;
		}
		else if (x == WIDTH - 1)
		{
			j_err = true;
			continue;
		}

		if (i_err && j_err) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
		{
			Priority return_value = GetPriority(cnt, guard_cnt, is_space_chk, space_cnt);
			if (return_value != ERROR)
				return return_value;
			break;
		}
	}

	return 0;
} // end int AI::RowCheck().
/*** check column ***/
int AI::ColCheck(int x, int y, Dol my_dol, bool is_space_chk)
{
	int i = 1, j = 1;
	int cnt = 1, guard_cnt = 0;
	int space_cnt = 0; // 공백 카운트.
	bool i_err = false;
	bool j_err = false;

	// 오목 체크.
	while (true)
	{
		if (y - i >= IH || i_err == true)
		{
			int return_value = CheckMoveContent(x, y-i, i, cnt, space_cnt, i_err, my_dol, guard_cnt, is_space_chk,y-i,IH);
			if (return_value > -1)
				return return_value;
		}
		else if (y == IH)
		{
			i_err = true;
			continue;
		}

		if (y + j < HEIGHT || j_err == true)
		{
			int return_value = CheckMoveContent(x, y + j, j, cnt, space_cnt, j_err, my_dol, guard_cnt, is_space_chk,y+j,HEIGHT-1);
			if (return_value > -1)
				return return_value;
		}
		else if (y == HEIGHT - 1)
		{
			j_err = true;
			continue;
		}

		if (i_err && j_err) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
		{
			Priority return_value = GetPriority(cnt, guard_cnt, is_space_chk, space_cnt);
			if (return_value != ERROR)
				return return_value;

			break; // 루프를 벗어남.
		}
	} // while(true).

	return 0;
} // end int AI::SeroCheck().

/*** / ***/
int AI::UpperDiagCheck(int x, int y, Dol my_dol, bool is_space_chk ) // 대각선 줄(/)의 오목 체크.
{
	int i = 1, j = 1;
	int cnt = 1, guard_cnt = 0;
	int space_cnt = 0; // 공백 카운트.
	bool i_err = false;
	bool j_err = false;

	// 오목 체크.
	while (true)
	{
		if (x - i >= IW && y + i < HEIGHT || i_err == true)
		{
			int return_value = CheckMoveContent(x - i, y + i, i, cnt, space_cnt, i_err, my_dol, guard_cnt, is_space_chk,x-i,IW,y+i,HEIGHT-1);

		}
		else if (x == IW || y == HEIGHT - 1)
		{
			i_err = true;
			continue;
		}

		if (x + j < WIDTH && y - j >= IH || j_err == true)
		{
			int return_value = CheckMoveContent(x + j, y - j, j, cnt, space_cnt, j_err, my_dol, guard_cnt, is_space_chk,x+j,WIDTH-1,y-j,IH);

		}
		else if (x == WIDTH - 1 || y == IH)
		{
			j_err = true;
			continue;
		}

		if (i_err && j_err) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
		{
			Priority return_value = GetPriority(cnt, guard_cnt, is_space_chk, space_cnt);
			if (return_value != ERROR)
				return return_value;

			break; // 루프를 벗어남.
		}
	} // while(true).

	return 0;
} // end int AI::UpperDiagCheck().

/*** \ ***/
int AI::LowerDiagCheck(int x, int y, Dol my_dol, bool is_space_chk) // 대각선 줄(\)의 오목 체크.
{
	int i = 1, j = 1;
	int cnt = 1, guard_cnt = 0;
	int space_cnt = 0; // 공백 카운트.
	bool i_err = false;
	bool j_err = false;

	// 오목 체크.
	while (true)
	{
		if (x - i >= IW && y - i >= IH || i_err == true)
		{
			int return_value = CheckMoveContent(x - i, y - i, i, cnt, space_cnt, i_err, my_dol, guard_cnt, is_space_chk,x-i,IW,y-i,IH);
		}
		else if (x == IW || y == IH)
		{
			i_err = true;
			continue;
		}

		if (x + j < WIDTH && y + j < HEIGHT || j_err == true)
		{
			int return_value = CheckMoveContent(x + j, y + j, j, cnt, space_cnt, j_err, my_dol, guard_cnt, is_space_chk,x+j,WIDTH-1,y+j,HEIGHT-1);
		}
		else if (x == WIDTH - 1 || y == HEIGHT - 1)
		{
			j_err = true;
			continue;
		}

		if (i_err && j_err) // 왼쪽 오른쪽의 검사가 모두 끝났다면,
		{
			Priority return_value = GetPriority(cnt, guard_cnt, is_space_chk, space_cnt);
			if (return_value != ERROR)
				return return_value;

			break; // 루프를 벗어남.
		}
	} // while(true).

	return 0;
} // end int AI::LowerDiagCheck().
